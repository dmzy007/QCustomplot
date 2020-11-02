#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <math.h>
#include <QTime>

Widget::Widget(QWidget *parent) : QWidget(parent), x(5), y(5), m_point(-1), ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_myName = "我的折线图";
    for (int i = 0; i < 5; i++)
    {
        x[i] = i;
        y[i] = 1;
    }
    qDebug() << x.size() << "  " << y.size();

    ui->plot->addGraph();
    ui->plot->graph()->setData(x, y);
    ui->plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    //    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    connect(ui->plot, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(myMousePressEvent(QMouseEvent *)));
    connect(ui->plot, SIGNAL(mouseRelease(QMouseEvent *)), this, SLOT(myMouseReleaseEvent(QMouseEvent *)));
    connect(ui->plot, SIGNAL(mouseMove(QMouseEvent *)), this, SLOT(myMouseMoveEvent(QMouseEvent *)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::myMousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent";

    int x_pos = event->pos().x();
    int y_pos = event->pos().y();

    float x_val = ui->plot->xAxis->pixelToCoord(x_pos);
    float y_val = ui->plot->yAxis->pixelToCoord(y_pos);

    m_point = -1;
    for (int i = 0; i < 5; i++)
    {
        if (fabs(x_val - x.at(i)) < 0.3 && fabs(y_val - y.at(i)) < 0.3)
        {
            qDebug() << "现在选择的是第" << i << "个点";
            m_point = i;
            break;
        }
    }
}

void Widget::myMouseReleaseEvent(QMouseEvent *event)
{
    //    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    m_point = -1;
}

void Widget::myMouseMoveEvent(QMouseEvent *event)
{
    if (m_point == -1) return;

    //    ui->plot->setInteractions(QCP::iRangeZoom);

    int x_pos = event->pos().x();
    int y_pos = event->pos().y();

    float x_val = ui->plot->xAxis->pixelToCoord(x_pos);
    float y_val = ui->plot->yAxis->pixelToCoord(y_pos);

    x[m_point] = x_val;
    y[m_point] = y_val;

    ui->plot->graph()->setData(x, y);
    ui->plot->replot();
}
