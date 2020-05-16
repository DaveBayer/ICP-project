/**
 * @file street.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy LineRoute
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __LINEROUTE_H__
#define __LINEROUTE_H__

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QGraphicsScene>
#include "graph.h"
#include "street.h"
#include "point.h"


/**
 * @class      LineRoute
 * @brief      Třída reprezentující grafickou reprezentaci trasy linky.
 */
class LineRoute :  public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
    LineRoute(Graph *, uint32_t);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    uint32_t getId();

public slots:
	void showRoute();
    void hideRoute();
    void toggleRoute();
private:
    QPen pen;

    Graph * graph;
    uint32_t line;
    std::vector<std::vector<Point>> route;
};

#endif // __LINEROUTE_H__