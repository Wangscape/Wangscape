#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>

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
    void clickOptionsDirectoryButton();
    void displayTilesetPreview(const QString& name);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::map<std::string, QImage> previewImages;
    QString optionsFilePath;
};

#endif // MAINWINDOW_H
