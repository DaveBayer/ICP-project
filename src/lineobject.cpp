#include "lineobject.h"
LineObject::LineObject(Graph * g, Line *line, QTime * time) : graph(g), line(line), id(line->getNumber()), currTime(time)
{
    std::string name = "line" + std::to_string(id);
	label = new LineLabel(name);
        
    route = new LineRoute(g, id);
    running = true;
}

// float LineObject::getLineLength()
// {
//     auto route_lenght = 0.f;
//     for (auto i = 1; i < route_vector.size() -1; i++) {
//         for (auto j = 1; j < route_vector[i].size(); j++) {
//             route_lenght += graph->getEdgeW(route_vector[i][j-1], route_vector[i][j]) / graph->getEdgeTC(route_vector[i][j-1], route_vector[i][j]);
//         }
//     }
//     return route_lenght;
// }


void LineObject::createVehicles()
{
    // for (auto line : lines) {
    //     if (line.getNumber() == id){
    //         for (auto connection : line.forward) {
    //             TransportVehicle *v = new TransportVehicle(graph, connection, id, true);
    //             QObject::connect(v, SIGNAL(showConnectionInfo()), this, SLOT(showConnectionInfo()));
    //             v->initVehicle();
    //             v->setRouteDuration(1); // timer->setDuration()
    //             v->setRoutePath();
    //             vehicles.push_back(v);
    //             v->setVisible(false);
    //         }
            
    //         for (auto connection : line.backward) {
                          
    //             TransportVehicle *v = new TransportVehicle(graph, connection,id, false);
    //             QObject::connect(v, SIGNAL(showConnectionInfo()), this, SLOT(showConnectionInfo()));
    //             v->initVehicle();
    //             v->setRouteDuration(1); // timer->setDuration()
    //             v->setRoutePath();
    //             vehicles.push_back(v);
    //             v->setVisible(false);
    //         }
    //     }
    // }
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


void LineObject::showConnectionInfo()
{
    emit showConnectionInfo_s();
}

LineObject::~LineObject(){}