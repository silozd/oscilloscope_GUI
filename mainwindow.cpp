#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "math.h"
#include <QGraphicsView>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    customPlot = new QCustomPlot(ui->gl_widget);
    customPlot->addGraph();
    customPlot->setGeometry(0,0,ui->gl_widget->width(),ui->gl_widget->height());
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setLabel("x");
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::addRandomGraph()
{
  int n = 50;
  double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
  double yOffset = (rand()/(double)RAND_MAX - 0.5)*10;
  double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; i++)
  {
    x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
    y[i] = (qSin(x[i]*r1*5)*qSin(qCos(x[i]*r2)*r4*3)+r3*qCos(qSin(x[i])*r4*2))*yScale + yOffset;
  }
  customPlot->addGraph();
  customPlot->graph()->setName(QString("New graph %1").arg(customPlot->graphCount()-1));
  customPlot->graph()->setData(x, y);
  customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
  if (rand()%100 > 50)
    customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
  QPen graphPen;
  graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
  graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
  customPlot->graph()->setPen(graphPen);
  customPlot->replot();
  //selam cınım nasılsın
 }
void MainWindow::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);
  menu->addAction("Add random graph", this, SLOT(addRandomGraph()));
  if (customPlot->selectedGraphs().size() > 0)
  menu->popup(customPlot->mapToGlobal(pos));
}
