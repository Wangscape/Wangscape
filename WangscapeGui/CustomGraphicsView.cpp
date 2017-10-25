#include "CustomGraphicsView.h"

CustomGraphicsView::CustomGraphicsView(QWidget* parent) :
    QGraphicsView(parent) {}

CustomGraphicsView::CustomGraphicsView (QGraphicsScene* scene, QWidget* parent) :
    QGraphicsView(scene, parent) {}

void CustomGraphicsView::wheelEvent(QWheelEvent* event)
{
    static const double zoomInFactor = 1.5;
    static const double zoomOutFactor = 1.0 / zoomInFactor;

    if(event->modifiers() & Qt::ControlModifier)
    {
        QGraphicsView::wheelEvent(event);
    }
    else
    {
        if(event->delta() > 0)
       {
           scale(zoomInFactor, zoomInFactor);
       }
       else
       {
           scale(zoomOutFactor, zoomOutFactor);
       }
   }
}
