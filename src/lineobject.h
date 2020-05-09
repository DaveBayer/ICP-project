
#ifndef __LINEOBJECT_H__
#define __LINEOBJECT_H__


#include <QLayout>
#include <QGraphicsScene>
#include <QObject>
#include <QTime>

#include "line.h"
#include "linelabel.h"
#include "graph.h"
#include "lineroute.h"
#include "transportvehicle.h"
class LineObject : public QObject
{
	Q_OBJECT
public:
    LineObject(Graph *,std::vector<Line>,uint32_t, std::vector<std::vector<Point>> route_vector,QTime *);
    ~LineObject();

    void createVehicles();
    float getLineLength();

	uint32_t id;
    LineRoute *route;
    LineLabel *label;
    Graph * graph;
    std::vector<Line> lines;
	std::vector<TransportVehicle *> vehicles;

private slots:
    void startVehicle();
    void timeChanged();
    void stopAnimation();
    void resumeAnimation();

private:
    Line *line;
    QTime * currTime;
    QGraphicsScene * scene;
    std::vector<std::vector<Point>> route_vector;
};


#endif // __LINEOBJECT_H__