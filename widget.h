#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "qcustomplot.h"

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void myMousePressEvent(QMouseEvent *event);
    void myMouseReleaseEvent(QMouseEvent *event);
    void myMouseMoveEvent(QMouseEvent *event);

private:
    Ui::Widget *    ui;
    QString         m_myName;
    QVector<double> x, y;
    int             m_point;
};

#endif  // WIDGET_H
