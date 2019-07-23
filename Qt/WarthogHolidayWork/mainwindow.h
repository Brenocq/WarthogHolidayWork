#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void paintEvent(QPaintEvent *e);

public slots:
    void drawRobot();

private:
    Ui::MainWindow *ui;
    QColor penColor;
    QTimer *timer;
};

#endif // MAINWINDOW_H
