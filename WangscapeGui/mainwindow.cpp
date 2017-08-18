#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <fstream>
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
    mUi(new Ui::MainWindow)
{
    mScene = new QGraphicsScene(this);

    mUi->setupUi(this);
    mUi->progressBar->setRange(0, 100);
    mUi->progressBar->setValue(0);

    connect(mUi->generateButton, SIGNAL(pressed()), this, SLOT(clickGenerateButton()));
    connect(mUi->saveButton, SIGNAL(pressed()), this, SLOT(clickSaveButton()));
    connect(mUi->optionsDirectoryButton, SIGNAL(pressed()), this, SLOT(clickOptionsDirectoryButton()));
    connect(mUi->comboBox, SIGNAL(activated(const QString&)), this, SLOT(displayTilesetPreview(const QString&)));
}

MainWindow::~MainWindow()
{
    delete mUi;
}

void MainWindow::clickGenerateButton()
{
    if (mTilesetGenerator == nullptr)
    {
        QMessageBox error_message;
        error_message.critical(this, "Error during tileset generation", QString("You have to select options file before clicking 'Generate...' button"));
        return;
    }

    mTilesetGenerator->generate([this](const sf::Texture& output, std::string filename)
    {
        const sf::Image source_image = output.copyToImage();

        const auto basename = filename.substr(filename.rfind('/') + 1);
        const auto qimage = convertSfImageToQImage(source_image);
        mPreviewImages.emplace(std::make_pair(basename,
                                             std::make_pair(filename, std::move(qimage))));
    });

    initializePreviewArea();
    displayTilesetPreview();
}

void MainWindow::clickSaveButton()
{
    if (mPreviewImages.empty())
    {
        QMessageBox warning_message;
        warning_message.warning(this, "Warning", QString("You have to generate tileset before saving it"));
        return;
    }

    for (const auto& preview_image : mPreviewImages)
    {
        const std::string image_dir = boost::filesystem::path(preview_image.second.first).remove_filename().string();
        boost::filesystem::create_directories(image_dir);
        if (!preview_image.second.second.save(QString(preview_image.second.first.c_str())))
        {
            QMessageBox critical_error_message;
            critical_error_message.critical(this, "Error during saving tilesets", QString("Couldn't save tileset image"));
            return;
        }
    }

    mTilesetGenerator->metaOutput.writeAll(mOptionsManager->getOptions());

    QMessageBox success_message;
    success_message.information(this, "Saved!", QString("Output has been saved successfully"));
}

void MainWindow::clickOptionsDirectoryButton()
{
    QString chosen_path = QFileDialog::getOpenFileName(this,
                                                     tr("QFileDialog::getExistingDirectory()"),
                                                     QString("hello"));
    if (chosen_path.isEmpty())
        return;

    mUi->currentOptionsPath->setText(QString(chosen_path));

    // TODO(hryniuk): make OptionsManager throw custom exception, catch it here
    // and show QMessageBox with a proper error message
    mOptionsManager = std::make_unique<OptionsManager>(chosen_path.toLocal8Bit().constData());
    mOptions = mOptionsManager->getOptions();
    resetTilesetGenerator();

    mUi->comboBox->clear();
    mPreviewImages.clear();
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

    for (int y = 0; y < output_image_size.y; ++y)
    {
        for (int x = 0; x < output_image_size.x; ++x)
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
        std::make_unique<tilegen::partition::TilePartitionerNoise>(mOptions);

    mTilesetGenerator = std::make_unique<tilegen::TilesetGenerator>(mOptions, std::move(tileset_partitioner));
}
