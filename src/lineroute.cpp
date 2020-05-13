#include "lineroute.h"

LineRoute::LineRoute(std::vector<std::vector<Point>> route) :route(std::move(route))
{
	pen = QPen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    this->setVisible(false);
}

void LineRoute::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

	

	// painter->setBrush(Qt::black);
	painter->setPen(pen);

    QPainterPath path;

    path.moveTo(route[0][0].getX(),route[0][0].getY());
    for (uint32_t i = 1; i < route.size()-1; i++){
        for (auto j = 1; j < route[i].size(); j++){
            path.lineTo(route[i][j].getX(),route[i][j].getY());
        }
    }

    painter->drawPath(path);	

}

uint32_t LineRoute::getId()
{
    return id;
}

QRectF LineRoute::boundingRect() const
{
    return QRectF(0,0,600, 600);
}

void LineRoute::toggleRoute()
{
    if (isVisible())
        setVisible(false);
    else
        setVisible(true);
    if(auto s = scene()){
        s->update();
    }
}

void LineRoute::hideRoute()
{
    setVisible(false);
    if(auto s = scene()){
        s->update();
    }
}

void LineRoute::showRoute()
{
    setVisible(true);
    if(auto s = scene()){
        s->update();
    }
}