#include "streetmap.h"



StreetMap::StreetMap(std::vector<Street> streets) : color(0,0,0), streets(streets)
{
	pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

StreetMap::StreetMap(std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>> map, std::vector<Station> stations_v) : color(0,0,0), map(map)
{
    pen = QPen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    if (!map.empty()){
        for (auto street = map.begin(); street != map.end(); street++){
            for (size_t part = 0; part < street->second.size() - 1; part++) {
                auto pts1 = street->second[part].first;
                auto pts2 = street->second[part+1].first;
                auto item = new QGraphicsLineItem(pts1.getX(),pts1.getY(),pts2.getX(),pts2.getY());
                item->setPen(pen);
                lines.push_back(item);
            }
        }
    }

    for (auto s : stations_v) {
        QPointF pos(s.getPoint().getX()-5,s.getPoint().getY()-5);
        auto sta = new QGraphicsRectItem(s.getPoint().getX()-5,s.getPoint().getY()-5,10,10);
        sta->setPen(pen);
        sta->setBrush(QBrush(Qt::black));
        auto name = new QGraphicsTextItem(QString::fromStdString(s.getName()));
        name->setPos(pos + QPointF(0,10));
        name->setDefaultTextColor(Qt::black);
        stations.push_back(name);
        stations.push_back(sta);
    }
}

void StreetMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    for (auto it : lines){
        it->setParentItem(this);
    }

    for (auto it : stations) {
        it->setParentItem(this);
    }
}

QRectF StreetMap::boundingRect() const
{
    return QRectF(0, 0, 600+3, 600+3);
}

void StreetMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << mapToScene(event->pos()).x() << std::endl;
    for (auto it : lines) {
        if (it->contains(mapToScene(event->pos()))){
            it->setPen(QPen(Qt::red, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            auto line = it->line();
            auto p1 = line.p1();
            auto p2 = line.p2();
            std::cout<< p1.x()<< "," << p1.y() << "--"<< p2.x() << "," <<p2.y()<<std::endl;
        } else{
            it->setPen(pen);
        }
    }
}