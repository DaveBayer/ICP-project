#include "lineroute.h"

LineRoute::LineRoute(Graph * g, uint32_t line) : graph(g), line(line)
{
	pen = QPen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    this->setVisible(false);   
}

void LineRoute::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setPen(pen);

    QPainterPath path;

    route = graph->line_pts[line];
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
    return line;
}

QRectF LineRoute::boundingRect() const
{
    return QRectF(0,0,600, 600);
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