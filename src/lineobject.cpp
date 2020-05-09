#include "lineobject.h"
LineObject::LineObject(Graph * g,uint32_t id, std::vector<std::vector<Point>> route_vector, QTime * time) : graph(g), id(id), currTime(time), route_vector(route_vector)
{
    std::string name = "line" + std::to_string(id);
	label = new LineLabel(name);
        
    route = new LineRoute(route_vector);
    
}

float LineObject::getLineLength()
{
    auto route_lenght = 0.f;
    for (auto i = 1; i < route_vector.size() -1; i++) {
        for (auto j = 1; j < route_vector[i].size(); j++) {
            route_lenght += graph->getEdgeW(route_vector[i][j-1], route_vector[i][j]) / graph->getEdgeTC(route_vector[i][j-1], route_vector[i][j]);
        }
    }
    return route_lenght;
}


void LineObject::createVehicles(std::vector<timetable_s> timetable)
{
    std::cout<<getLineLength()<<std::endl;
    for (auto connection : timetable) {
        TransportVehicle *v = new TransportVehicle(graph, connection.start);
        v->setRouteDuration(getLineLength()); // timer->setDuration()
        v->setRoutePath(route_vector,getLineLength());
        vehicles.push_back(v);
        v->setVisible(false);
    }
}




void LineObject::startVehicle()
{    
    for (auto vehicle : vehicles) {
        if (*currTime == *(vehicle->time_start)){
            vehicle->setVisible(true);
            vehicle->timer->start();
        }
    } 
}


void LineObject::timeChanged() 
{
    for (auto vehicle : vehicles) {
        vehicle->timer->stop();
        vehicle->timer->setCurrentTime(0);
        vehicle->setVisible(false);
        if (*currTime >= *(vehicle->time_start) && *currTime <= (vehicle->time_start->addSecs(vehicle->total_time))) {
            std::cout<<vehicle->time_start->secsTo(*currTime)*1000<<std::endl;
            vehicle->setVehiclePosition(vehicle->time_start->secsTo(*currTime)*1000);
            vehicle->setVisible(true);
            vehicle->timer->resume();
        }
    }
}

void LineObject::stopAnimation()
{
    for (auto vehicle : vehicles) {
        if (vehicle->timer->state() == QTimeLine::Running)
            vehicle->timer->setPaused(true);
    }
}

void LineObject::resumeAnimation()
{
    for (auto vehicle : vehicles) {
        if (vehicle->timer->state() == QTimeLine::Paused)
            vehicle->timer->resume();
    }
}

LineObject::~LineObject(){}