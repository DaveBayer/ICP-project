#ifndef STREETMAP_H
#define STREETMAP_H

#include <QGraphicsItem>
#include <QPainter>
#include "street.h"
#include "point.h"
class StreetMap : public QGraphicsItem
{
public:
    StreetMap(std::vector<Street>);
    QPen pen;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


private:
    QColor color;
    std::vector<Street> streets;
};

#endif