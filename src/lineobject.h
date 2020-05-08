
#ifndef __LINEOBJECT_H__
#define __LINEOBJECT_H__


#include <QLayout>
#include <QGraphicsScene>
#include <QObject>

#include "line.h"
#include "linelabel.h"
#include "lineroute.h"
#include "transportvehicle.h"
class LineObject : public QObject
{
	Q_OBJECT
public:
    LineObject(Line,QVBoxLayout*,QGraphicsScene *);
    ~LineObject();


private slots:
    void createVehicle();

private:
    Line line;
    LineRoute *route;
    LineLabel *label;

    QGraphicsScene * scene;

    uint32_t time;
};


#endif // __LINEOBJECT_H__