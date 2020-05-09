#include "transportvehicle.h"

TransportVehicle::TransportVehicle(uint32_t timeStart)
{
	pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	

	timer = new QTimeLine();
	timer->setFrameRange(0, 100);
	timer->setCurveShape(QTimeLine::LinearCurve);

	time_start = new QTime(0,0,0);
	*time_start = time_start->addSecs(timeStart);

	animation = new QGraphicsItemAnimation;


}


void TransportVehicle::setRouteDuration(float length)
{
	int duration = (int)((length / 20) * 1000);
	timer->setDuration(duration);
}

void TransportVehicle::setRoutePath(std::vector<std::vector<Point>> route, float length)
{
	QObject::connect(timer, SIGNAL(finished()), this, SLOT(finished()));
	if (route.size() != 0) {
		animation->setItem(this);
		animation->setTimeLine(timer);

		// float street_length = 0;


		// QPointF p(route[0].getX(), route[0].getY());
		
		// setPos(p-QPointF(5,5));
		// animation->setPosAt((0/length), p - QPointF(5,5));
		
		// for (uint32_t i = 1; i < route.size();i++){
		// 	street_length += route[i-1].dist(route[i]); // TODO: getEdgeLength()!!!
		// 	QPointF p(route[i].getX(), route[i].getY());
		// 	animation->setPosAt((street_length/length), p - QPointF(5,5));
		// }



		auto numOfStations = route.size() - 1;
		float station_delay = 60; // 20pixel/s -> 2 s in station

		float route_time = 0.f;
		total_time = length + numOfStations*station_delay;

		QPointF start(route[0][0].getX(),route[0][0].getY());
		QPointF vehicleSize(5,5);

		setPos(start - vehicleSize);
		animation->setPosAt((0/total_time), start - vehicleSize);

		for (uint32_t i = 1; i < route.size(); i++) {
			route_time += station_delay;
			QPointF s(route[i][0].getX(),route[i][0].getY());
			animation->setPosAt((route_time/total_time), s - vehicleSize);
			for (uint32_t j = 1; j < route[i].size(); j++){
				route_time +=  route[i][j-1].dist(route[i][j]);
				std::cout<<route_time<<std::endl;
				QPointF p(route[i][j].getX(), route[i][j].getY());
				animation->setPosAt((route_time/total_time), p - vehicleSize);
			}
		}
	}
}

void TransportVehicle::setVehiclePosition(int postime)
{
	timer->setCurrentTime(postime);
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
	this->setVisible(false);
}

TransportVehicle::~TransportVehicle(){}