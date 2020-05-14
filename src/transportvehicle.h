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



    TransportVehicle(Graph *,uint32_t,uint32_t,bool);
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
    std::vector<std::vector<Point>> getRoute();

    Graph * graph;

    uint32_t line;
    uint8_t state;
    float speed;
    float length;
    float acc;
    float duration;
    float station_delay;

    enum VEHICLESTATE
    {
        RUNNING,
        PAUSED,
        STOPPED
    };
private slots:
	void finished();

signals:
    void showConnectionInfo(TransportVehicle *);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool direction;
    QGraphicsItemAnimation * animation;
};

#endif // __TRANSPORTVEHICLE_H__