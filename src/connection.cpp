#include "connection.h"

Connection::Connection() : vehicle(nullptr)
{
	pen = QPen(Qt::white, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QGraphicsLineItem * station_line = new QGraphicsLineItem(50,40,650,40);
	station_line->setParentItem(this);
	station_line->setPen(pen);
}
void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(pen);
	painter->setBrush(QBrush(Qt::red));

	if (vehicle != nullptr) {
		vehicle->setPos(xpos,35);
	} 
}

QRectF Connection::boundingRect() const
{
    return QRectF(0,0,700,80);
}

void Connection::show(TransportVehicle * v, std::vector<std::pair<std::string,float>> schedule)
{


	for (auto s : stations){
		delete s;
	}
	stations.clear();
	for (auto i : stations_info) {
		delete i;
	}
	stations_info.clear();

	auto route = v->getRoute();

	QTime time = *(v->time_start);
	
	auto numOfStations = route.size()-1;
	auto offset = 600/(numOfStations-1);

	for (auto i = 1; i < route.size(); i++) {
		QGraphicsEllipseItem * station = new QGraphicsEllipseItem(45 + offset*(i-1),35,10,10);
		stations.push_back(station);
		
		auto name = new QGraphicsTextItem(QString::fromStdString(schedule[i-1].first));
		name->setParentItem(this);
		name->setPos(40 +offset*(i-1),40);

		time = time.addSecs(((schedule[i-1].second)/VEHICLE_SPEED));
		auto station_time = new QGraphicsTextItem(time.toString("hh:mm:ss"));
		station_time->setParentItem(this);
		station_time->setPos(40 +offset*(i-1),55);
		station->setParentItem(this);
		station->setBrush(Qt::white);

		stations_info.push_back(name);
		stations_info.push_back(station_time);

		time = time.addSecs(STATION_DELAY);
	}
	vehicle = new QGraphicsEllipseItem(0,0,10,10);
	vehicle->setParentItem(this);
	vehicle->setBrush(Qt::red);
	xpos= 50;

}
void Connection::setVehicle(TransportVehicle * v)
{
	this->v = v;
}

Connection::~Connection(){}