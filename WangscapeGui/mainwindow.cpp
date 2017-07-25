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
#include "tilegen/TilesetGenerator.h"
#include "tilegen/TileGenerator.h"
#include "tilegen/partition/TilePartitionerNoise.h"

#include "OptionsManager.h"


std::string usage(std::string program_path)
{
    return "Usage: " + program_path + " rel/path/to/options.json\n";
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scene = new QGraphicsScene(this);
    ui->setupUi(this);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
    connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(clickGenerateButton()));
    connect(ui->optionsDirectoryButton, SIGNAL(pressed()), this, SLOT(clickOptionsDirectoryButton()));
}

void MainWindow::clickGenerateButton()
{
    logging::addAppender(std::make_unique<logging::ConsoleAppender>("console", logging::Level::Debug));

    if (optionsFilePath.isEmpty())
    {
        QMessageBox errorMessage;
        errorMessage.critical(this, "Error", QString("You have to select options file before clicking 'Generate...' button"));
        return;
    }

    OptionsManager optionsManager(optionsFilePath.toLocal8Bit().constData());
    const Options& options = optionsManager.getOptions();

    std::unique_ptr<tilegen::partition::TilePartitionerBase> tp =
        std::make_unique<tilegen::partition::TilePartitionerNoise>(options);

    tilegen::TilesetGenerator tg(options, std::move(tp));

    std::cout << "generating tiles..." << std::endl;

    tg.generate([this](const sf::Texture& output, std::string /*filename*/)
    {
        const sf::Image outputImage = output.copyToImage();
        const sf::Vector2u outputImageSize = outputImage.getSize();

        const QSize previewImageSize = previewImage.size();
        if (outputImageSize.x != previewImageSize.width() || outputImageSize.y != previewImageSize.height())
        {
            previewImage = QImage(outputImageSize.x, outputImageSize.y, QImage::Format_RGB32);
        }
        for (int y = 0; y < outputImageSize.y; ++y)
        {
            for (int x = 0; x < outputImageSize.x; ++x)
            {
                const sf::Color sfmlColor = outputImage.getPixel(x, y);
                const QColor color{sfmlColor.r, sfmlColor.g, sfmlColor.b, sfmlColor.a};
                previewImage.setPixelColor(x, y, color);
            }
            const int progressValue = 100 * (static_cast<double>(y) / static_cast<double>(outputImageSize.y));
            std::cout << y << " " << outputImageSize.y <<  " " << progressValue << std::endl;
            ui->progressBar->setValue(progressValue);
        }
        ui->progressBar->setValue(100);
    });


    const QPixmap pixmap = QPixmap::fromImage(previewImage);
    scene->clear();
    scene->addPixmap(pixmap);
    scene->setSceneRect(pixmap.rect());

    ui->tilesetPreview->setScene(scene);

    // tg.metaOutput.writeAll(optionsManager.getOptions());
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
        std::cout << "Chosen path: " << chosenPath.toLocal8Bit().constData() << std::endl;
        optionsFilePath = chosenPath;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
