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
    QTime * time_end;
    float total_time;



    TransportVehicle(Graph *,std::vector<std::vector<Point>> &,uint32_t);
    ~TransportVehicle();
    QPen pen;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // void createAnimation(std::vector<Point>);
    void setRouteDuration(float);
    void setRoutePath();
    float getRouteLength();
    void setVehiclePosition(float);
    void initVehicle();
    Graph * graph;

    uint8_t state;
    float speed;
    float length;
    float acc;
    float duration;
    float station_delay;
    std::vector<std::vector<Point>> route;

    enum VEHICLESTATE
    {
        RUNNING,
        PAUSED,
        STOPPED
    };
private slots:
	void finished();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor color;
    QGraphicsItemAnimation * animation;
};

#endif // __TRANSPORTVEHICLE_H__