#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <fstream>
#include <memory>


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
    connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(clickPushButton()));
}

void MainWindow::clickPushButton()
{
    logging::addAppender(std::make_unique<logging::ConsoleAppender>("console", logging::Level::Debug));

    std::string filename = "/home/hryniuk/projekty/Wangscape/doc/examples/example2/example_options.json";

    OptionsManager optionsManager(filename);
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

MainWindow::~MainWindow()
{
    delete ui;
}
