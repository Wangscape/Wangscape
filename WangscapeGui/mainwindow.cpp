#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <fstream>
#include <memory>

#include <QMessageBox>
#include <QFileDialog>

#include "logging/Logger.h"
#include "logging/Logging.h"
#include "logging/ConsoleAppender.h"
#include "logging/FileAppender.h"
#include "tilegen/TileGenerator.h"
#include "tilegen/partition/TilePartitionerNoise.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scene = new QGraphicsScene(this);
    ui->setupUi(this);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
    connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(clickGenerateButton()));
    connect(ui->saveButton, SIGNAL(pressed()), this, SLOT(clickSaveButton()));
    connect(ui->optionsDirectoryButton, SIGNAL(pressed()), this, SLOT(clickOptionsDirectoryButton()));
    connect(ui->comboBox, SIGNAL(activated(const QString&)), this, SLOT(displayTilesetPreview(const QString&)));
}

void MainWindow::clickGenerateButton()
{
    ui->comboBox->clear();
    previewImages.clear();
    logging::addAppender(std::make_unique<logging::ConsoleAppender>("console", logging::Level::Debug));

    if (optionsFilePath.isEmpty())
    {
        QMessageBox errorMessage;
        errorMessage.critical(this, "Error", QString("You have to select options file before clicking 'Generate...' button"));
        return;
    }

    optionsManager = std::make_unique<OptionsManager>(optionsFilePath.toLocal8Bit().constData());
    const Options& options = optionsManager->getOptions();

    std::unique_ptr<tilegen::partition::TilePartitionerBase> tp =
        std::make_unique<tilegen::partition::TilePartitionerNoise>(options);

    tilesetGenerator = std::make_unique<tilegen::TilesetGenerator>(options, std::move(tp));

    tilesetGenerator->generate([this](const sf::Texture& output, std::string filename)
    {
        const sf::Image outputImage = output.copyToImage();
        const sf::Vector2u outputImageSize = outputImage.getSize();

        const auto basename = filename.substr(filename.rfind('/') + 1);
        previewImages.emplace(std::make_pair(basename,
                                             std::make_pair(filename, QImage(outputImageSize.x, outputImageSize.y, QImage::Format_RGB32))));

        for (int y = 0; y < outputImageSize.y; ++y)
        {
            for (int x = 0; x < outputImageSize.x; ++x)
            {
                const sf::Color sfmlColor = outputImage.getPixel(x, y);
                const QColor color{sfmlColor.r, sfmlColor.g, sfmlColor.b, sfmlColor.a};
                previewImages.at(basename).second.setPixel(x, y, color.rgba());
            }
            const int progressValue = 100 * (static_cast<double>(y) / static_cast<double>(outputImageSize.y));
            ui->progressBar->setValue(progressValue);
        }
        ui->progressBar->setValue(100);
    });

    ui->comboBox->addItems([this]()
    {
        QStringList list;
        for (const auto name : previewImages)
        {
            list << QString(name.first.c_str());
        }
        return list;
    }());

    const QPixmap pixmap = QPixmap::fromImage((*previewImages.begin()).second.second);

    scene->clear();
    scene->addPixmap(pixmap);
    scene->setSceneRect(pixmap.rect());
    ui->tilesetPreview->setScene(scene);
}

void MainWindow::clickSaveButton()
{
    if (previewImages.empty())
    {
        QMessageBox warningMessage;
        warningMessage.warning(this, "Error", QString("You have to generate tileset before saving it"));
        return;
    }

    for (const auto& previewImage : previewImages)
    {
        const std::string image_dir = boost::filesystem::path(previewImage.second.first).remove_filename().string();
        boost::filesystem::create_directories(image_dir);
        if (!previewImage.second.second.save(QString(previewImage.second.first.c_str())))
            throw std::runtime_error("Couldn't write image");
    }

    tilesetGenerator->metaOutput.writeAll(optionsManager->getOptions());

    QMessageBox successMessage;
    successMessage.information(this, "Saved!", QString("Output has been saved successfully"));
}

void MainWindow::displayTilesetPreview(const QString& name)
{
    const QPixmap pixmap = QPixmap::fromImage(previewImages[name.toLocal8Bit().constData()].second);

    scene->clear();
    scene->addPixmap(pixmap);
    scene->setSceneRect(pixmap.rect());
    ui->tilesetPreview->setScene(scene);

}

void MainWindow::clickOptionsDirectoryButton()
{
    QFileDialog::Options options;
    options |= QFileDialog::DontResolveSymlinks;
    QString chosenPath = QFileDialog::getOpenFileName(this,
                                                     tr("QFileDialog::getExistingDirectory()"),
                                                     QString("hello"));
    if (!chosenPath.isEmpty())
    {
        optionsFilePath = chosenPath;
        ui->currentOptionsPath->setText(QString(chosenPath));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
