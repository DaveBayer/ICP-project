#ifndef __TRANSPORTVEHICLE_H__
#define __TRANSPORTVEHICLE_H__

#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QTime>

#include "point.h"
#include "graph.h"

class TransportVehicle : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:

    QTimeLine *timer;
    QTime * time_start;
    float total_time;



    TransportVehicle(Graph *,uint32_t);
    ~TransportVehicle();
    QPen pen;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // void createAnimation(std::vector<Point>);
    void setRouteDuration(float length);
    void setRoutePath(std::vector<std::vector<Point>>, float);
    void setVehiclePosition(int);
    Graph * graph;

private slots:
	void finished();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor color;
    QGraphicsItemAnimation * animation;
};

#endif // __TRANSPORTVEHICLE_H__