#ifndef STREETMAP_H
#define STREETMAP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <map>
#include <QString>
#include <QGraphicsTextItem>
#include "street.h"
#include "point.h"
#include "station.h"
class StreetMap : public QGraphicsItem
{
public:
    StreetMap(std::vector<Street>);
    StreetMap(std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>>, std::vector<Station>);
    QPen pen;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor color;
	std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>> map;
    std::vector<Street> streets;
    std::vector<QGraphicsLineItem *> lines;
    std::vector<QGraphicsItem *> stations;
};

#endif