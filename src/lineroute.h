#ifndef __LINEROUTE_H__
#define __LINEROUTE_H__

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QGraphicsScene>
#include "graph.h"
#include "street.h"
#include "point.h"
class LineRoute :  public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
    LineRoute(Graph *, uint32_t);
    QPen pen;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    uint32_t getId();

public slots:
	void showRoute();
    void hideRoute();
    void toggleRoute();
private:
    Graph * graph;
    QColor color;
    uint32_t line;
    std::vector<std::vector<Point>> route;
};

#endif // __LINEROUTE_H__