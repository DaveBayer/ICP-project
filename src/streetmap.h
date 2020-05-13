#ifndef STREETMAP_H
#define STREETMAP_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <map>
#include <QString>
#include <QGraphicsTextItem>
#include "street.h"
#include "point.h"
#include "graph.h"
#include "station.h"
class StreetMap : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    StreetMap(Graph *,std::vector<Street>,std::vector<Station>,std::vector<std::pair<Point,uint32_t>>);
    // StreetMap(Graph *,std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>>, std::vector<Station>);
    void changeRoute(Point, Point,uint32_t);
    QPen pen;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
signals:
    void actStreet(uint32_t);
    void editNextRoute();

public slots:
    void setEditMode();
    void closeEditMode();
    void closeStreet();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor color;
	std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>> map;
    std::vector<QGraphicsLineItem *> streets;
    std::vector<QGraphicsLineItem *> lines;
    std::vector<QGraphicsItem *> stations;
    std::vector<QGraphicsEllipseItem *>nodes;

    std::vector<QGraphicsLineItem* > new_route;
    Graph * graph;
    bool edit_mode;

    QGraphicsLineItem * act_street_line;

    QGraphicsEllipseItem * s1_item;
    QGraphicsEllipseItem * s2_item;

    Point start_point;
    Point end_point;
    Point act_point;
};

#endif