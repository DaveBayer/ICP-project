#include "connection.h"

Connection::Connection(Graph * g, uint32_t line) : graph(g), line(line), vehicle(nullptr)
{
	pen = QPen(Qt::white, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}
void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(pen);
	painter->setBrush(QBrush(Qt::red));

	if (vehicle != nullptr) {
		std::cout<<"Zde\n";
		vehicle->setPos(xpos,35);
	} 
}

QRectF Connection::boundingRect() const
{
    return QRectF(0,0,700,80);
}

void Connection::show(TransportVehicle * v, std::vector<std::pair<std::string,float>> schedule)
{
	auto route = v->getRoute();

	QGraphicsLineItem * station_line = new QGraphicsLineItem(50,40,650,40);
	station_line->setParentItem(this);
	station_line->setPen(pen);
	auto numOfStations = route.size()-1;
	auto offset = 600/(numOfStations-1);

	for (auto i = 1; i < route.size(); i++) {
		QGraphicsEllipseItem * station = new QGraphicsEllipseItem(45 + offset*(i-1),35,10,10);
		auto name = new QGraphicsTextItem(QString::fromStdString(schedule[i-1].first));
		name->setParentItem(this);
		name->setPos(40 +offset*(i-1),40);
		auto bla = new QGraphicsTextItem(QString::fromStdString(std::to_string(schedule[i-1].second)));
		bla->setParentItem(this);
		bla->setPos(40 +offset*(i-1),50);
		station->setParentItem(this);
		station->setBrush(Qt::white);
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