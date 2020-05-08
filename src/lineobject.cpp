#include "lineobject.h"
LineObject::LineObject(Line line, QVBoxLayout *layout, QGraphicsScene * scene) : line(line), scene(scene)
{
	time = 0;

	label = new LineLabel(line.getName());
    
    layout->addWidget(label);
    
    route = new LineRoute(line.getId(),line.getRoute());
    QObject::connect(label, SIGNAL(clicked()),route,SLOT(showRoute()));

    scene->addItem(route);
}



void LineObject::createVehicle()
{
	if (time++ == 2){
		TransportVehicle *v = new TransportVehicle(scene);
    	v->createAnimation(line.getRoute());
    	v->addToScene();
	}
}




LineObject::~LineObject(){}