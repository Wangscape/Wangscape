#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QGraphicsScene>
#include <QMainWindow>

#include <OptionsManager.h>
#include <tilegen/TilesetGenerator.h>


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
    void clickGenerateButton();
    void clickSaveButton();
    void clickOptionsDirectoryButton();
    void displayTilesetPreview(const QString& name);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    // TODO(hryniuk): create a struct for this map's elements
    std::map<std::string, std::pair<std::string, QImage>> previewImages;
    QString optionsFilePath;
    std::unique_ptr<OptionsManager> optionsManager;
    std::unique_ptr<tilegen::TilesetGenerator> tilesetGenerator;
};

#endif // MAINWINDOW_H
