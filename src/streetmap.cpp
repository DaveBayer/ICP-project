/**
 * @file streetmap.cpp
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy StreetMap
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#include "streetmap.h"

StreetMap::StreetMap(Map *m) : map(m),graph(&(m->g))
{
	pen = QPen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    new_route_pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    closed_street_pen = QPen(Qt::black, 4, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    
    edit_mode = false;

    if (!map->streets.empty()) {
        for(auto street : map->streets) {
            auto pts = street.getPoints();
            auto item = new QGraphicsLineItem(pts[0].getX(),pts[0].getY(),pts[1].getX(),pts[1].getY());
            item->setPen(pen);

            auto name = new QGraphicsTextItem(QString::fromStdString(street.getName()));
            name->setPos(QPointF() + QPointF(0,10));
            name->setDefaultTextColor(Qt::black);

            this->streets.push_back(item);
        }
    }
    for (auto s : map->stations) {
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
    for (auto n : graph->nodes) {
        if (map->isStation(n.first)){
            auto node = new QGraphicsRectItem(0,0,10,10);
            node->setPos(n.first.getX()-5,n.first.getY()-5);
            node->setPen(pen);
            node->setBrush(QBrush(Qt::gray));
            node->setVisible(false);
            this->nodes.push_back(node);
        } else{
            auto node = new QGraphicsEllipseItem(0,0,10,10);
            node->setPos(n.first.getX()-5,n.first.getY()-5);
            node->setPen(pen);
            node->setBrush(QBrush(Qt::gray));
            node->setVisible(false);
            this->nodes.push_back(node);
        }
        
    }
}


void StreetMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    for (auto it : streets){
        it->setParentItem(this);
    }
    for (auto it : closed_streets){
        it->setPen(closed_street_pen);
    }

    for (auto it : stations) {
        it->setParentItem(this);
    }
    for(auto node : nodes){
        node->setParentItem(this);
    }
}

QRectF StreetMap::boundingRect() const
{
    return QRectF(0, 0, 600+3, 600+3);
}

void StreetMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(edit_mode){
        for (auto n : nodes) {
            if (n->contains(mapToItem(n,event->pos()))) {
                Point p(n->pos().x()+5,n->pos().y()+5);
                auto idx = graph->getNodeID(p);
                if(!start_point_set) {
                    if (!map->isStation(p)) {
                        emit setStatusLabel("First line point must be a station.");
                    } else {
                        emit setStatusLabel("First line point selected.");
                        start_point_set = true;
                        act_point = p;
                        new_route_v.push_back(act_point);
                    }
                    break;
                }
                if(!graph->isEdge(act_point, p)){
                    emit setStatusLabel("Selected point is not connected with last point.");
                }else {
                    emit setStatusLabel("Line point selected.");
                    auto path = new QGraphicsLineItem(act_point.getX(),act_point.getY(),p.getX(),p.getY());
                    path->setPen(new_route_pen);
                    path->setParentItem(this);
                    path->setZValue(1);
                    new_route.push_back(path);
                    act_point = p;
                    new_route_v.push_back(act_point);
                }
            }
        }
    } else{
        for (auto it : streets) {
            if (it->contains(mapToScene(event->pos()))){
                act_street_line = it;
                it->setPen(QPen(Qt::cyan, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                auto line = it->line();
                Point p1(line.p1().x(),line.p1().y());
                Point p2(line.p2().x(),line.p2().y());
                auto street_id = graph->getStreetFromPoints(p1,p2);
                emit actStreet(street_id);

            } else{
                it->setPen(pen);
            }
        }
    }
}

void StreetMap::closeStreet()
{
    if (act_street_line != nullptr){
        closed_streets.push_back(act_street_line);
        act_street_line->setPen(closed_street_pen);
    }

}


void StreetMap::changeRoute(uint32_t line)
{

    start_point_set = false;
    new_route_v.clear();
    act_line = line;


}

void StreetMap::startEditMode()
{
    if (!edit_mode){
        for(auto s : stations){
            s->setVisible(false);
        }
        for(auto node : nodes){
            node->setVisible(true);
            node->setZValue(1);
        }
        edit_mode = true;
    } 
}

void StreetMap::closeEditMode()
{
    edit_mode = false;

    

    // show stations
    for(auto s : stations){
        s->setVisible(true);
    }

    // hide crossroad nodes
    for(auto node : nodes){
        node->setVisible(false);
    }

    
}

void StreetMap::openStreets()
{
    for (auto s : closed_streets) {
        s->setPen(pen);
    }
    closed_streets.clear();
}

void StreetMap::saveRoute()
{
    if(map->isStation(act_point)){
        emit updateLineRoute(act_line, new_route_v);
        for(auto p : new_route){
            delete p;
        }
        new_route.clear();
        emit setStatusLabel("");
        emit editNextRoute();
    } else {
        emit setStatusLabel("Last line point must be a station.");
    }
}

StreetMap::~StreetMap() {}