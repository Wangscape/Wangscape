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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QImage previewImage;
    QString optionsFilePath;
};

#endif // MAINWINDOW_H
