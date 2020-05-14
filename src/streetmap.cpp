#include "streetmap.h"



StreetMap::StreetMap(std::vector<Street> streets) : color(0,0,0), streets(streets)
{
	pen = QPen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
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

StreetMap::StreetMap(Graph * g,std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>> map, std::vector<Station> stations_v) : graph(g),color(0,0,0), map(map)
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
    for (auto it : lines) {
        if (it->contains(mapToScene(event->pos()))){
            it->setPen(QPen(Qt::red, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            auto line = it->line();
            Point p1(line.p1().x(),line.p1().y());
            Point p2(line.p2().x(),line.p2().y());
            // std::cout<< p1.x()<< "," << p1.y() << "--"<< p2.x() << "," <<p2.y()<<std::endl;
            auto idx1 = graph->getNodeID(p1);
            auto idx2 = graph->getNodeID(p2);
            // std::cout<<*graph<<"\nblablabla\n";
            // graph->setTC(-0.5);
            // graph->incEdgeTC(idx1, idx2);
            // std::cout<<*graph;
            // emit updateRoute(1.f);
            emit actStreet(idx1,idx2);

        } else{
            it->setPen(pen);
        }
    }
}

void StreetMap::closeStreet()
{
    if (act_street_line != nullptr){
        act_street_line->setPen(QPen(Qt::black, 4, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    }

}


void StreetMap::changeRoute(Point p1, Point p2, uint32_t line)
{
    std::cout<<p1.getX()<<std::endl;

    start_point = p1;
    end_point   = p2;
    act_point   = start_point;


    QPointF s1(start_point.getX(),start_point.getY());
    QPointF s2(end_point.getX(),end_point.getY());
    s1_item = new QGraphicsEllipseItem(s1.x()-6,s1.y()-6,12,12);
    s2_item = new QGraphicsEllipseItem(s2.x()-6,s2.y()-6,12,12);
    s1_item->setPen(QPen(Qt::red,   3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    s2_item->setPen(QPen(Qt::blue,  3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    s1_item->setParentItem(this);
    s2_item->setParentItem(this);


}

void StreetMap::setEditMode()
{
    for(auto s : stations){
        s->setVisible(false);
    }
    for(auto node : nodes){
        node->setVisible(true);
    }
    edit_mode = true;
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
    std::cout<<"here\n";

    // show stations
    for(auto s : stations){
        s->setVisible(true);
    }

    // hide crossroad nodes
    for(auto node : nodes){
        node->setVisible(false);
    }

    
}