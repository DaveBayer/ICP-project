#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QTimer>
#include <QTime>
#include <map>
#include <QPushButton>
#include <QTimeEdit>

#include "streetmap.h"
#include "line.h"
#include "linelabel.h"
#include "lineroute.h"
#include "transportvehicle.h"
#include "lineobject.h"
#include "graph.h"
#include "map.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

   MainWindow(Map *);
   void createStreetMap();
   void createScene();
   void createLines();
   void createSystemClock();
   void finish();


private slots:
    // void clock_tick_slot();
    void updateClock();
    void zoomIn();
    void zoomOut();
    void defaultZoom();
    void setTime();
    void toggleClock();
    void fasterClock();
    void slowerClock();
    void actStreet(uint32_t,uint32_t);
    void closeStreet();
    void addTraffic();
    void clearTraffic();

signals:
    void timeChanged(float);
    void stopAnimation();
    void resumeAnimation();

private:
    bool clock_state = true;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QLabel *label;

    QGridLayout * mainLayout;
    QVBoxLayout * line_labels;
    QWidget * street_layout_w;
    QHBoxLayout * street_options_l;

    QTimer * sys_clock;
    QTime * time;
    QTimeEdit * time_edit;
    QLabel * clock_label;


    QPushButton * zoomin;
    QPushButton * zoomout;
    QPushButton * zoomdefault;
    QPushButton * changetime;
    QPushButton * settime;
    QPushButton * pauseresumetime;
    QPushButton * faster;
    QPushButton * slower;

    QPushButton * addtraffic;
    QPushButton * cleartraffic;
    QPushButton * closestreet;


    StreetMap *sm;
    Graph * graph;
    Map * map;

    std::vector<uint32_t> act_street;

};

#endif // __MAINWINDOW_H__