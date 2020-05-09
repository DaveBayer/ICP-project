
#ifndef __LINEOBJECT_H__
#define __LINEOBJECT_H__


#include <QLayout>
#include <QGraphicsScene>
#include <QObject>
#include <QTime>

#include "line.h"
#include "linelabel.h"
#include "lineroute.h"
#include "transportvehicle.h"
class LineObject : public QObject
{
	Q_OBJECT
public:
    LineObject(Line *,QVBoxLayout*,QGraphicsScene *,QTime *);
    ~LineObject();


private slots:
    void startVehicle();
    void timeChanged();

private:
	std::vector<TransportVehicle *> vehicles;
    Line *line;
    LineRoute *route;
    LineLabel *label;
    QTime * currTime;
    QGraphicsScene * scene;

    uint32_t time;
};


#endif // __LINEOBJECT_H__