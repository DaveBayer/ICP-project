#include "transportvehicle.h"

TransportVehicle::TransportVehicle(QGraphicsScene *scene) : scene(scene)
{
	pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

void TransportVehicle::createAnimation()
{
	timer = new QTimeLine(7000);
	timer->setFrameRange(0, 100);
	QObject::connect(timer, SIGNAL(finished()), this, SLOT(finished()));

	QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
	animation->setItem(this);
	animation->setTimeLine(timer);

	animation->setPosAt(0.f / 1000.f, QPointF(100, 100)-QPointF(5,5));
	animation->setPosAt(100.f / 1000.f, QPointF(200, 100)-QPointF(5,5));
	animation->setPosAt(200.f / 1000.f, QPointF(200, 200)-QPointF(5,5));
	animation->setPosAt(300.f / 1000.f, QPointF(300, 200)-QPointF(5,5));
	animation->setPosAt(400.f / 1000.f, QPointF(400, 200)-QPointF(5,5));
	animation->setPosAt(500.f / 1000.f, QPointF(400, 300)-QPointF(5,5));
	animation->setPosAt(600.f / 1000.f, QPointF(400, 400)-QPointF(5,5));
	animation->setPosAt(700.f / 1000.f, QPointF(400, 500)-QPointF(5,5));
	animation->setPosAt(800.f / 1000.f, QPointF(300, 500)-QPointF(5,5));
	animation->setPosAt(900.f / 1000.f, QPointF(200, 500)-QPointF(5,5));
	animation->setPosAt(1000.f / 1000.f, QPointF(200, 400)-QPointF(5,5));
}

void TransportVehicle::addToScene()
{
	// 
	scene->addItem(this);
	timer->start();
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