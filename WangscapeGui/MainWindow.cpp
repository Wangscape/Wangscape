#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <memory>

#include<boost/filesystem.hpp>

#include <QMessageBox>
#include <QFileDialog>

#include "logging/Logger.h"
#include "logging/Logging.h"
#include "logging/ConsoleAppender.h"
#include "logging/FileAppender.h"
#include "tilegen/TileGenerator.h"
#include "tilegen/partition/TilePartitionerNoise.h"


MainWindow::MainWindow(QWidget *parent_) :
    QMainWindow(parent_),
    mUi(new Ui::MainWindow),
    mOptionsEditor(new OptionsEditor(this))
{
    mScene = new QGraphicsScene(this);

    mUi->setupUi(this);
    mUi->progressBar->setRange(0, 100);
    mUi->progressBar->setValue(0);

    openOptionsEditor();

    connect(mUi->generateButton, SIGNAL(pressed()), this, SLOT(generate()));
    connect(mUi->comboBox, SIGNAL(activated(const QString&)), this, SLOT(displayTilesetPreview(const QString&)));
    connect(mUi->actionLoadOptions, SIGNAL(triggered()), this, SLOT(loadOptionsFromFile()));
    connect(mUi->actionSaveOutput, SIGNAL(triggered()), this, SLOT(saveOutput()));
    connect(mUi->actionOpenOptionsEditor, SIGNAL(triggered()), this, SLOT(openOptionsEditor()));
}

MainWindow::~MainWindow()
{
    delete mUi;
}

void MainWindow::generate()
{
    if (mTilesetGenerator == nullptr)
    {
        QMessageBox error_message;
        error_message.critical(this, "Error during tileset generation", QString("You must select an options file before clicking the 'Generate...' button"));
        return;
    }

    resetTilesetGenerator();

    mUi->comboBox->clear();
    mPreviewImages.clear();

    mTilesetGenerator->generate([this](const sf::Texture& output, std::string filepath)
    {
        const sf::Image source_image = output.copyToImage();

        const auto filename = boost::filesystem::path(filepath).filename().string();
        const auto qimage = convertSfImageToQImage(source_image);
        mPreviewImages.emplace(std::make_pair(filename,
                                             std::make_pair(filepath, std::move(qimage))));
    });

    initializePreviewArea();
    displayTilesetPreview();
}

void MainWindow::saveOutput()
{
    if (mOptionsEditor->useDefaultOuputDir())
    {
        mOptions->relativeOutputDirectory = (*mOriginalOptions).relativeOutputDirectory;
    }
    else
    {
        QString chosen_path = QFileDialog::getExistingDirectory(this, tr("Select output directory"));
        if (chosen_path.isEmpty())
        {
            return;
        }
        mOptions->relativeOutputDirectory = chosen_path.toLocal8Bit().constData();
    }

    if (mPreviewImages.empty())
    {
        QMessageBox warning_message;
        warning_message.warning(this, "Warning", QString("You must generate a tileset before saving it"));
        return;
    }

    // set to mOptions.relativeOutputDirectory not part of preview_image filepath,
    // cause it is is used to generate that filepath and it makes
    // modifying output dir for the whole output a lot easier
    const std::string image_dir = mOptions->relativeOutputDirectory;
    boost::filesystem::create_directories(image_dir);
    boost::filesystem::path p(image_dir);
    for (const auto& preview_image : mPreviewImages)
    {
        p.append(preview_image.first);
        if (!preview_image.second.second.save(QString(p.string().c_str())))
        {
            QMessageBox critical_error_message;
            critical_error_message.critical(this, "Error during saving tilesets", QString("Couldn't save tileset image"));
            return;
        }
        p.remove_filename();
    }

    mTilesetGenerator->metaOutput.writeAll(*mOptions);

    QMessageBox success_message;
    success_message.information(this, "Saved!", QString("Output has been saved successfully"));
}

void MainWindow::resetOptions()
{
    if (mOriginalOptions)
    {
        mOptions = std::make_shared<Options>(*mOriginalOptions);
        mOptionsEditor->setOptions(mOptions);
    }
}

void MainWindow::loadOptionsFromFile()
{
    QString chosen_path = QFileDialog::getOpenFileName(this,
                                                     tr("Select options file"));
    if (chosen_path.isEmpty())
        return;

    mUi->currentOptionsPath->setText(QString(chosen_path));

    // TODO(hryniuk): make OptionsManager throw custom exception, catch it here
    // and show QMessageBox with a proper error message
    auto& options_manager = getOptionsManager();
    options_manager.loadOptions(chosen_path.toLocal8Bit().constData());
    mOriginalOptions = boost::make_optional(options_manager.getOptions());

    resetOptions();

    resetTilesetGenerator();

    mUi->comboBox->clear();
    mPreviewImages.clear();
    mScene->clear();
}

void MainWindow::displayTilesetPreview(const QString& name)
{
    const QImage preview_image = name.isEmpty() ? (mPreviewImages.begin())->second.second : mPreviewImages.at(name.toLocal8Bit().constData()).second;
    const QPixmap pixmap = QPixmap::fromImage(preview_image);

    mScene->clear();
    mScene->addPixmap(pixmap);
    mScene->setSceneRect(pixmap.rect());
    mUi->tilesetPreview->setScene(mScene);
}

void MainWindow::openOptionsEditor()
{
    mOptionsEditor->show();
    addDockWidget(Qt::RightDockWidgetArea, mOptionsEditor);
}

void MainWindow::initializePreviewArea()
{
    mUi->comboBox->addItems([this]()
    {
        QStringList list;
        for (const auto name : mPreviewImages)
        {
            list << QString(name.first.c_str());
        }
        return list;
    }());
}

QImage MainWindow::convertSfImageToQImage(const sf::Image& source_image)
{

    const sf::Vector2u output_image_size = source_image.getSize();
    QImage output_image(output_image_size.x, output_image_size.y, QImage::Format_RGB32);

    for (unsigned int y = 0u; y < output_image_size.y; ++y)
    {
        for (unsigned int x = 0u; x < output_image_size.x; ++x)
        {
            const sf::Color sfml_color = source_image.getPixel(x, y);
            const QColor color{sfml_color.r, sfml_color.g, sfml_color.b, sfml_color.a};
            output_image.setPixel(x, y, color.rgba());
        }
        const int progress_value = 100 * (static_cast<double>(y) / static_cast<double>(output_image_size.y));
        mUi->progressBar->setValue(progress_value);
    }
    mUi->progressBar->setValue(100);

    return output_image;
}

void MainWindow::resetTilesetGenerator()
{
    std::unique_ptr<tilegen::partition::TilePartitionerBase> tileset_partitioner =
        std::make_unique<tilegen::partition::TilePartitionerNoise>(*mOptions);

    mTilesetGenerator = std::make_unique<tilegen::TilesetGenerator>(*mOptions, std::move(tileset_partitioner));
}
