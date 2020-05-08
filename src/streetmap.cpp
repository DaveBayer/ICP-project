#include "streetmap.h"



StreetMap::StreetMap(std::vector<Street> streets) : color(0,0,0), streets(streets)
{
	pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

StreetMap::StreetMap(std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>> map) : color(0,0,0), map(map)
{
    pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    if (!map.empty()){
        for (auto street = map.begin(); street != map.end(); street++){
            for (size_t part = 0; part < street->second.size() - 1; part++) {
                auto pts1 = street->second[part].first;
                auto pts2 = street->second[part+1].first;
                // painter->drawLine(pts1.getX(),pts1.getY(),pts2.getX(),pts2.getY());
                auto item = new QGraphicsLineItem(pts1.getX(),pts1.getY(),pts2.getX(),pts2.getY());
                item->setPen(pen);
                lines.push_back(item);
            }
        }
    }
}

void StreetMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

	
    for (auto it : lines){
        it->setParentItem(this);
    }
	// painter->setBrush(Qt::black);
	// painter->setPen(pen);
 //    if (!streets.empty()){
	//    for (auto it : streets) {
	// 	  auto pts = it.getPoints();
	// 	  painter->drawLine(pts[0].getX(),pts[0].getY(),pts[1].getX(),pts[1].getY());
	//    }
 //    } else if (!map.empty()){
 //        for (auto street = map.begin(); street != map.end(); street++){
 //            for (size_t part = 0; part < street->second.size() - 1; part++) {
 //                auto pts1 = street->second[part].first;
 //                auto pts2 = street->second[part+1].first;
 //                // painter->drawLine(pts1.getX(),pts1.getY(),pts2.getX(),pts2.getY());
 //                auto item = new QGraphicsLineItem(pts1.getX(),pts1.getY(),pts2.getX(),pts2.getY(),this);
 //                // item->setPen(pen);
 //                lines.push_back(item);
 //            }
 //        }
 //    }
}

QRectF StreetMap::boundingRect() const
{
    return QRectF(0, 0, 600, 600);
}

void StreetMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // qDebug() << "There are" << items(event->pos()).size()
    //          << "items at position" << mapToScene(event->pos());
    std::cout << mapToScene(event->pos()).x() << std::endl;
    for (auto it : lines) {
        if (it->contains(mapToScene(event->pos()))){
            std::cout << "hell yeah" << std::endl;
            it->setPen(QPen(Qt::blue, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        } else{
            it->setPen(pen);
        }
    }
}