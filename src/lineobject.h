
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
#include "connection.h"
class LineObject : public QObject
{
	Q_OBJECT
public:
    LineObject(Graph *,Line * line,QTime *);
    ~LineObject();

    void createVehicles();
    // float getLineLength();

	uint32_t id;
    LineRoute *route;
    LineLabel *label;
    Graph * graph;
    std::vector<Line> lines;
	std::vector<TransportVehicle *> vehicles;
	float route_length;
	Connection * connection_info;

private slots:
    void startVehicle();
    void timeChanged(float);
    void stopAnimation();
    void resumeAnimation();
    void showConnectionInfo(std::vector<std::pair<std::string,float>>);
    void getConnectionInfo(TransportVehicle *v);
signals:
	void showConnectionInfo_s();
	void getConnectionInfo_s(uint32_t,TransportVehicle *);

private:
    Line *line;
    QTime * currTime;
    bool running;
    QGraphicsScene * scene;
    TransportVehicle * act_v;
};


#endif // __LINEOBJECT_H__