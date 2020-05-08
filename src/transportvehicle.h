#ifndef __TRANSPORTVEHICLE_H__
#define __TRANSPORTVEHICLE_H__

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QPainter>

#include "point.h"

class TransportVehicle : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
    TransportVehicle(QGraphicsScene *scene);
    ~TransportVehicle();
    QPen pen;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void addToScene();
    void createAnimation(std::vector<Point>);

private slots:
	void finished();

private:
	QGraphicsScene *scene;
    QColor color;
    QTimeLine *timer;
};

#endif // __TRANSPORTVEHICLE_H__