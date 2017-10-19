#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class CustomGraphicsView : public QGraphicsView
{
public:
    CustomGraphicsView(QWidget* parent = 0);
    CustomGraphicsView(QGraphicsScene* scene, QWidget* parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent* event);
};

#endif // CUSTOMGRAPHICSVIEW_H
