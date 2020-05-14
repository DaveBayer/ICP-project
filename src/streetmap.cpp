#include "streetmap.h"



StreetMap::StreetMap(Graph * g,std::vector<Street> streets, std::vector<Station> stations_v,std::vector<std::pair<Point,uint32_t>> nodes) : graph(g), color(0,0,0)
{
	pen = QPen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    new_route_pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    closed_street_pen = QPen(Qt::black, 4, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    edit_mode = false;
    s1_item = nullptr;
    s2_item = nullptr;

    if (!streets.empty()) {
        for(auto street : streets) {
            auto pts = street.getPoints();
            auto item = new QGraphicsLineItem(pts[0].getX(),pts[0].getY(),pts[1].getX(),pts[1].getY());
            item->setPen(pen);

            auto name = new QGraphicsTextItem(QString::fromStdString(street.getName()));
            name->setPos(QPointF() + QPointF(0,10));
            name->setDefaultTextColor(Qt::black);

            this->streets.push_back(item);
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
    for (auto n : nodes) {
        auto node = new QGraphicsEllipseItem(0,0,10,10);
        node->setPos(n.first.getX()-5,n.first.getY()-5);
        node->setPen(pen);
        node->setBrush(QBrush(Qt::gray));
        node->setVisible(false);
        this->nodes.push_back(node);
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
                std::cout<<idx<<std::endl;
                if(!graph->isEdge(act_point, p)){
                    std::cout<<"not egde"<<std::endl;
                }else {
                    std::cout<<"yupyup"<<std::endl;
                    auto path = new QGraphicsLineItem(act_point.getX(),act_point.getY(),p.getX(),p.getY());
                    path->setPen(new_route_pen);
                    path->setParentItem(this);
                    path->setZValue(1);
                    new_route.push_back(path);
                    act_point = p;
                    new_route_v.push_back(act_point);
                    if (act_point == end_point){
                        std::cout<<"end point"<<std::endl;
                        emit updateLineRoute(act_line, new_route_v);
                        for(auto p : new_route){
                            delete p;
                        }
                        new_route.clear();
                        emit editNextRoute();
                    } 
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


void StreetMap::changeRoute(Point p1, Point p2, uint32_t line)
{
    std::cout<<p1.getX()<<std::endl;

    start_point = p1;
    end_point   = p2;
    act_point   = start_point;
    new_route_v.clear();
    new_route_v.push_back(p1);
    act_line = line;

    QPointF s1(start_point.getX(),start_point.getY());
    QPointF s2(end_point.getX(),end_point.getY());
    s1_item = new QGraphicsEllipseItem(s1.x()-6,s1.y()-6,12,12);
    s2_item = new QGraphicsEllipseItem(s2.x()-6,s2.y()-6,12,12);
    s1_item->setPen(QPen(Qt::red,   3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    s2_item->setPen(QPen(Qt::blue,  3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    s1_item->setParentItem(this);
    s2_item->setParentItem(this);


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
    } else {
        // std::cout<<"edit mode is already set"<<std::endl;
    }
}

void StreetMap::closeEditMode()
{
    edit_mode = false;

    if (s1_item && s2_item){
        s1_item->setVisible(false);
        s2_item->setVisible(false);
        delete s1_item;
        delete s2_item;
        s1_item = nullptr;
        s2_item = nullptr;
    }
    // std::cout<<"here\n";

    // show stations
    for(auto s : stations){
        s->setVisible(true);
    }

    // hide crossroad nodes
    for(auto node : nodes){
        node->setVisible(false);
    }

    
}