#include "lineroute.h"



LineRoute::LineRoute(uint32_t id, std::vector<Point> route) : id(id),route(std::move(route))
{
	pen = QPen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    this->setVisible(false);
}

void LineRoute::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

	

	// painter->setBrush(Qt::black);
	painter->setPen(pen);

    QPainterPath path;

    if (route.size() != 0) {
        path.moveTo(route[0].getX(),route[0].getY());
        for (auto i = 1; i < route.size(); i++){
            path.lineTo(route[i].getX(),route[i].getY());
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
    qreal adjust = 0.5;
    return QRectF(-300 - adjust, -300 - adjust,
                  600 + adjust, 600 + adjust);
}

void LineRoute::showRoute()
{
    if (isVisible())
        setVisible(false);
    else
        setVisible(true);
    if(auto s = scene()){
        s->update();
    }
}