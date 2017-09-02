#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QGraphicsScene>
#include <QMainWindow>

#include <OptionsManager.h>
#include <tilegen/TilesetGenerator.h>
#include <Options.h>

#include "OptionsEditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void generate();
    void saveOutput();
    void loadOptionsFromFile();
    void displayTilesetPreview(const QString& name=QString());
    void openOptionsEditor();
    void resetOptions();

private:
    void initializePreviewArea();
    QImage convertSfImageToQImage(const sf::Image &source_image);
    void resetTilesetGenerator();

    Ui::MainWindow *mUi;
    QGraphicsScene *mScene;
    // TODO(hryniuk): create a struct for this map's elements
    std::map<std::string, std::pair<std::string, QImage>> mPreviewImages;
    QString mOptionsFilePath;
    boost::optional<Options> mOriginalOptions;
    std::shared_ptr<Options> mOptions;
    OptionsEditor* mOptionsEditor;
    std::unique_ptr<tilegen::TilesetGenerator> mTilesetGenerator;
};

#endif // MAINWINDOW_H
