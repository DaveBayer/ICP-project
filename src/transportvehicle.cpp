#include "transportvehicle.h"

TransportVehicle::TransportVehicle(QGraphicsScene *scene) : scene(scene)
{
	pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	timer = nullptr;
}

void TransportVehicle::createAnimation(std::vector<Point> route)
{
	if (route.size() != 0){
		timer = new QTimeLine((800/10)*1000);
		timer->setFrameRange(0, 100);
		timer->setCurveShape(QTimeLine::LinearCurve);
		timer->setCurrentTime(4000);
		QObject::connect(timer, SIGNAL(finished()), this, SLOT(finished()));

		QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
		animation->setItem(this);
		animation->setTimeLine(timer);

		QPointF p(route[0].getX(), route[0].getY());
		float length = 0;
		setPos(p-QPointF(5,5));
		animation->setPosAt((0/(float)800), p - QPointF(5,5));
		for (uint32_t i = 1; i < route.size();i++){
			length += route[i-1].dist(route[i]);
			QPointF p(route[i].getX(), route[i].getY());
			animation->setPosAt((length/(float)800), p - QPointF(5,5));
		}

	} else {
		setVisible(false);
	}
}

void TransportVehicle::addToScene()
{
	scene->addItem(this);
	if(timer)
		timer->resume();
}


void TransportVehicle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(pen);

    painter->drawEllipse(0,0,10,10);	
}

QRectF TransportVehicle::boundingRect() const
{
    return QRectF(0, 0, 10, 10);
}


void TransportVehicle::finished()
{
	scene->removeItem(this);
}

TransportVehicle::~TransportVehicle(){}