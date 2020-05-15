#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QTime>

#include "point.h"
#include "graph.h"
#include "transportvehicle.h"



class Connection : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:

    Connection(Graph *,uint32_t);
    ~Connection();
    QPen pen;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void show(TransportVehicle *, std::vector<std::pair<std::string,float>>);
    void setVehicle(TransportVehicle *);

    Graph * graph;

    uint32_t line;

private slots:


signals:

protected:
    // void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsItemAnimation * animation;
    QGraphicsEllipseItem * vehicle;
    TransportVehicle * v;
    float xpos;
};

#endif // __CONNECTION_H__