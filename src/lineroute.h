#ifndef __LINEROUTE_H__
#define __LINEROUTE_H__

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QGraphicsScene>
#include "street.h"
#include "point.h"
class LineRoute :  public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
    LineRoute(uint32_t, std::vector<Point>);
    QPen pen;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    uint32_t getId();

public slots:
	void showRoute();
private:
    QColor color;
    uint32_t id;
    std::vector<Point> route;
};

#endif // __LINEROUTE_H__