#include "transportvehicle.h"

TransportVehicle::TransportVehicle(Graph * g, uint32_t timeStart, uint32_t line, bool direction) : graph(g), line(line), direction(direction)
{
	pen = QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	
	time_start = new QTime(0,0,0); // time of vehicle start
	*time_start = time_start->addSecs(timeStart);
	
}

std::vector<std::vector<Point>> TransportVehicle::getRoute()
{
	auto route = graph->line_pts[line]; 
	if (!direction) {
		std::vector<std::vector<Point>> reverse_route;
		std::vector<Point> reverse_part; 
		for (auto it =  route.rbegin(); it != route.rend(); it++) {
		    reverse_part.clear();
		    for (auto jt = (*it).rbegin(); jt != (*it).rend(); jt++) {
		        reverse_part.push_back(*jt);
		    }
		    reverse_route.push_back(reverse_part);
		} 
		route = reverse_route;
	}
	return route;
}

void TransportVehicle::initVehicle()
{
	station_delay = 7;
	speed = 0.0014; 			// 0.0014 pixs/s -> 14m/s -> 50km/h
	length = getRouteLength();			// total pixel route length (pixs)
	std::cout<<length<<"len\n";
	duration = length / speed; 	// duration of route with basic speed (ms)


	timer = new QTimeLine(duration);
	timer->setFrameRange(0, 100);
	timer->setCurveShape(QTimeLine::LinearCurve);

	
	time_end = new QTime(0,0,0);
	*time_end = time_start->addSecs(duration); // time of vehicle end

	animation = new QGraphicsItemAnimation;
	QObject::connect(timer, SIGNAL(finished()), this, SLOT(finished()));
	animation->setItem(this);
	animation->setTimeLine(timer);
	acc = 1.f;
}

float TransportVehicle::getRouteLength()
{
	auto route = getRoute();
	auto numOfStations = route.size() - 1;
	float route_lenght = 0.f;
    for (auto i = 1; i < route.size() -1; i++) {
        for (auto j = 1; j < route[i].size(); j++) {

            route_lenght += graph->getEdgeW(route[i][j-1], route[i][j]) / graph->getEdgeTC(route[i][j-1], route[i][j]);
        }
    }
    route_lenght += numOfStations*station_delay;
    return route_lenght;
}

void TransportVehicle::setRouteDuration(float c)
{
	acc *= c;
	duration = length /speed;
	timer->setDuration((int)(duration*acc));
}

void TransportVehicle::setRoutePath()
{
	auto route = getRoute(); 
	length = getRouteLength();
	if (route.size() != 0) {
		animation->clear();
		float route_time = 0.f;

		QPointF start(route[0][0].getX(),route[0][0].getY());
		QPointF vehicleSize(5,5);

		setPos(start - vehicleSize);
		animation->setPosAt((0/length), start - vehicleSize);

		for (uint32_t i = 1; i < route.size(); i++) {
			route_time += station_delay;
			QPointF s(route[i][0].getX(),route[i][0].getY());
			animation->setPosAt((route_time/length), s - vehicleSize);
			for (uint32_t j = 1; j < route[i].size(); j++){
				route_time +=  graph->getEdgeW(route[i][j-1],route[i][j]) / graph->getEdgeTC(route[i][j-1],route[i][j]);
				QPointF p(route[i][j].getX(), route[i][j].getY());
				animation->setPosAt((route_time/length), p - vehicleSize);
			}
		}
	}
}

void TransportVehicle::setVehiclePosition(float postime)
{
	timer->setCurrentTime(postime*timer->duration());
}




void TransportVehicle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(pen);
	painter->setBrush(QBrush(Qt::red));

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

void TransportVehicle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	std::cout<<"vehicle\n";
	emit showConnectionInfo(this);
}


TransportVehicle::~TransportVehicle(){}