#include "lineobject.h"
LineObject::LineObject(Graph * g, Line *line, QTime * time) : graph(g), line(line), id(line->getNumber()), currTime(time)
{
    std::string name = "line " + std::to_string(id);
	label = new LineLabel(name);
        
    route = new LineRoute(g, id);
    running = true;

    connection_info = new Connection(graph, id);
}

void LineObject::createVehicles()
{

    for (auto connection : line->forward) {
        TransportVehicle *v = new TransportVehicle(graph, connection, id, true);
        vehicles.push_back(v);
    }
    for (auto connection : line->backward) {
        TransportVehicle *v = new TransportVehicle(graph, connection, id, false);
        vehicles.push_back(v);
    }
    for (auto v : vehicles) {
        v->initVehicle();
        v->setRouteDuration(1); // timer->setDuration()
        v->setRoutePath();
        v->setVisible(false);
        QObject::connect(v, SIGNAL(showConnectionInfo(TransportVehicle *)), this, SLOT(showConnectionInfo(TransportVehicle *)));
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


void LineObject::timeChanged(float speed) 
{
    for (auto vehicle : vehicles) {
        vehicle->timer->stop();
        vehicle->timer->setCurrentTime(0);
        vehicle->setRoutePath();
        vehicle->setVisible(false);
        vehicle->setRouteDuration(speed);
        if (*currTime >= *(vehicle->time_start) && *currTime <= (vehicle->time_start->addSecs(vehicle->duration/1000))) {
            auto pos_time = vehicle->time_start->secsTo(*currTime);
            // vehicle
            vehicle->setVehiclePosition(pos_time*1000/vehicle->duration);
            vehicle->setVisible(true);
            vehicle->timer->resume();
            vehicle->timer->setPaused(true);
            if (running)
                vehicle->timer->resume();
        }
    }
}

void LineObject::stopAnimation()
{
    running = !running;
    for (auto vehicle : vehicles) {
        if (vehicle->timer->state() == QTimeLine::Running){
            vehicle->timer->setPaused(true);
            vehicle->setZValue(-1);
        }
    }
}

void LineObject::resumeAnimation()
{
    running = !running;
    for (auto vehicle : vehicles) {
        if (vehicle->timer->state() == QTimeLine::Paused){
            vehicle->timer->resume();
            vehicle->setZValue(1);
        }
    }
}


void LineObject::showConnectionInfo(TransportVehicle * v)
{
    std::cout<<"object\n";

    connection_info->show(v);
    emit showConnectionInfo_s();
}



LineObject::~LineObject(){}