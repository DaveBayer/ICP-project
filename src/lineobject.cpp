#include "lineobject.h"
LineObject::LineObject(Line * line, QVBoxLayout *layout, QGraphicsScene * scene, QTime * time) : line(line), scene(scene), currTime(time)
{
	time = 0;

	label = new LineLabel(line->getName());
    
    layout->addWidget(label);
    
    route = new LineRoute(line->getId(),line->getRoute());
    QObject::connect(label, SIGNAL(clicked()),route,SLOT(showRoute()));

    scene->addItem(route);



    
    for (auto vehicle : line->timetable) {
        TransportVehicle *v = new TransportVehicle(vehicle.start);
        v->setRouteDuration(line->length); // timer->setDuration()
        v->setRoutePath(vehicle.route,line->length);
        scene->addItem(v);
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
    std::cout<<"timeChanged"<<std::endl;
    for (auto vehicle : vehicles) {
        vehicle->timer->stop();
        vehicle->setVisible(false);
        if (*currTime >= *(vehicle->time_start) && *currTime <= (vehicle->time_start->addSecs(vehicle->total_time))) {
            std::cout<<vehicle->time_start->secsTo(*currTime)*1000<<std::endl;
            vehicle->setVehiclePosition(vehicle->time_start->secsTo(*currTime)*1000);
            vehicle->setVisible(true);
            vehicle->timer->resume();
        }
    }
}

LineObject::~LineObject(){}