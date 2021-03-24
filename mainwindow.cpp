#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <math.h>
#include <QTimer>
#include <QString>
#include <QApplication>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QPen>
#include <QMenu>
#include <QLinearGradient>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainPage->show();

    time_t = new QTimer(this);
    time_t->setInterval(100);

 //   connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
 //   connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    connect(time_t, SIGNAL(timeout()),this,SLOT(CreateGraph()));
    connect(ui->show_sig, SIGNAL(clicked(bool)),this,SLOT(on_show_sig_clicked()));
//    connect(ui->back_main1, SIGNAL(clicked(bool)),this,SLOT(on_show_sig_clicked()));
//    connect(ui->back_main2, SIGNAL(clicked(bool)),this,SLOT(on_show_sig_clicked()));

///////////////////  // *****  ADDING  TWO  GRAPHICS  **** // //////////////////////////////

    customPlot = new QCustomPlot(ui->gl_widget);
    customPlot->addGraph();
    customPlot->setGeometry(0,0,ui->gl_widget->width(),ui->gl_widget->height());
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setLabel("x");
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    customPlot->addGraph();
    customPlot->setGeometry(0,0,ui->gl_widget->width(),ui->gl_widget->height());
    customPlot->graph(1)->setPen(QPen(Qt::red));
    customPlot->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
    customPlot->rescaleAxes();
    customPlot->axisRect()->setupFullAxesBox();

///////////////////  //  **** CUSTOMIZE  GRAPHICS  ***** // //////////////////////////////

    customPlot->setBackground(QColor(255,250,250));
    customPlot->xAxis->setBasePen(QPen(Qt::black, 1));
    customPlot->yAxis->setBasePen(QPen(Qt::black, 1));
    customPlot->xAxis->setTickPen(QPen(Qt::black, 1));
    customPlot->yAxis->setTickPen(QPen(Qt::black, 1));
    customPlot->xAxis->setSubTickPen(QPen(Qt::black, 1));
    customPlot->yAxis->setSubTickPen(QPen(Qt::black, 1));
    customPlot->xAxis->setTickLabelColor(Qt::black);
    customPlot->yAxis->setTickLabelColor(Qt::black);
    customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customPlot->xAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);;

    bak=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


///////////////////  // *****  ADDING FUNCTIONAL SLOTS  *****   // //////////////////////////////

void MainWindow::on_show_sig_clicked()
{
  time_t->start();
}
void MainWindow::CreateGraph()
{

    int deg1 = ui->spinSin1->value();
    int deg2 = ui->spinSin2->value();
    int deg3 = ui->spinCos1->value();
    int deg4 = ui->spinCos2->value();

    val_x = val_x + 10;
    val_y= sin(((double)val_x*M_PI)/deg1) + sin(((double)val_x*M_PI)/deg2);
    val_t= cos(((double)val_x*M_PI)/deg3) + cos(((double)val_x*M_PI)/deg4);

    qDebug() << QString("val_x: ") << QString::number(val_x, 'f', 3);
    bak=1;
    customPlot->xAxis->setRange(0 , val_x + 1);
    customPlot->yAxis->setRange(val_y - 2 , val_y + 2);
    customPlot->graph(0)->addData(val_x , val_y);

    customPlot->xAxis2->setRange(0 , val_x + 1);
    customPlot->yAxis2->setRange(val_t - 3 , val_t + 3);
    customPlot->graph(1)->addData(val_x , val_t);

    customPlot->rescaleAxes();
    customPlot->replot();


 }

void MainWindow::on_go_page1_clicked()
{
    ui->mainPage->close();
    ui->page1->show();
}

void MainWindow::on_back_main1_clicked()
{
    ui->page1->close();
    ui->mainPage->show();

}

void MainWindow::on_go_page2_clicked()
{
    ui->mainPage->close();
    ui->page2->show();

}

void MainWindow::on_back_main2_clicked()
{
    ui->page2->close();
    ui->mainPage->show();
}



//void MainWindow::mousePress()
//{
//  if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
//    customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
//  else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
//    customPlot->axisRect()->setRangeDrag(customPlot->yAxis->orientation());
//  else
//    customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
//}

//void MainWindow::mouseWheel()
//{
//  if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
//    customPlot->axisRect()->setRangeZoom(customPlot->xAxis->orientation());
//  else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
//    customPlot->axisRect()->setRangeZoom(customPlot->yAxis->orientation());
//  else
//    customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
//}
