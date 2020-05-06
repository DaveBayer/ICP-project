#include "streetmap.h"



StreetMap::StreetMap(std::vector<Street> streets) : color(0,0,0), streets(streets)
{
	pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

void StreetMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

	

	// painter->setBrush(Qt::black);
	painter->setPen(pen);
	for (auto it : streets) {
		auto pts = it.getPoints();
		painter->drawLine(pts[0].getX(),pts[0].getY(),pts[1].getX(),pts[1].getY());
	}
	
	
    // // Body
    // painter->setBrush(color);
    // painter->drawEllipse(-10, -20, 20, 40);

    // // Eyes
    // painter->setBrush(Qt::white);
    // painter->drawEllipse(-10, -17, 8, 8);
    // painter->drawEllipse(2, -17, 8, 8);

    // // Nose
    // painter->setBrush(Qt::black);
    // painter->drawEllipse(QRectF(-2, -22, 4, 4));

  
    // // Ears
    // painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
    // painter->drawEllipse(-17, -12, 16, 16);
    // painter->drawEllipse(1, -12, 16, 16);

    // // Tail
    // QPainterPath path(QPointF(0, 20));
    // path.cubicTo(-5, 22, -5, 22, 0, 25);
    // path.cubicTo(5, 27, 5, 32, 0, 30);
    // path.cubicTo(-5, 32, -5, 42, 0, 35);
    // painter->setBrush(Qt::NoBrush);
    // painter->drawPath(path);
}

QRectF StreetMap::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-300 - adjust, -300 - adjust,
                  600 + adjust, 600 + adjust);
}