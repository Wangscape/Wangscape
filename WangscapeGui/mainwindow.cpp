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
    ui->setupUi(this);
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

    tg.generate([](const sf::Texture& output, std::string filename)
    {
        if (!output.copyToImage().saveToFile(filename))
            throw std::runtime_error("Couldn't write image");
    });
    tg.metaOutput.writeAll(optionsManager.getOptions());
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
