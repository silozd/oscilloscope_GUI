#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <qcustomplot.h>
#include <QTabWidget>
#include <QScrollBar>
#include <QtQuickWidgets/QQuickWidget>
#include <QGraphicsView>

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
    void on_show_sig_clicked();

    void on_go_page1_clicked();

    void on_go_page2_clicked();

    void on_back_main1_clicked();

    void on_back_main2_clicked();

private:
    Ui::MainWindow *ui;

    QCustomPlot *customPlot;
    QTimer *time_t;
    QOpenGLBuffer *positionBuffer;
    QOpenGLBuffer *colorBuffer;
    QOpenGLVertexArrayObject *arrayObject;
    QCPPlottableLegendItem *plItem;
    QLinearGradient axisRectGradient;


};

#endif // MAINWINDOW_H
