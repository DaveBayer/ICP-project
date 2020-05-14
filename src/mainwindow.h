#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QStackedLayout>
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
   void createButtons();
   void createMainLayout();
   void connectButtons();
   void createView();
   void finish();
   void startEditMode();


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
    void actStreet(uint32_t);
    // void closeStreet();
    void addTraffic();
    void clearTraffic();
    void changeLineRoute();
    void showConnectionInfo();
    void getCollidingLines();
    void updateLineRoute(uint32_t, std::vector<Point>);


signals:
    void timeChanged(float);
    void stopAnimation();
    void resumeAnimation();
    void editNextRoute_s();

    void closeEditMode();
    // void startEditMode();

private:
    bool clock_state = true;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QLabel *label;

    QTimer * sys_clock;
    QTime * time;
    QTimeEdit * changeTime_e;
    QLabel * time_l;


    // buttons
    QPushButton * zoomIn_b;
    QPushButton * zoomOut_b;
    QPushButton * zoomDefault_b;
    QPushButton * changeTime_b;
    QPushButton * setTime_b;
    QPushButton * pauseResumeTime_b;
    QPushButton * faster_b;
    QPushButton * slower_b;

    QPushButton * addTraffic_b;
    QPushButton * clearTraffic_b;
    QPushButton * closeStreet_b;
    QPushButton * closeStreetControl_b;


    StreetMap *sm;
    Graph * graph;
    Map * map;

    std::vector<uint32_t> act_street;

    // layout
    QGridLayout * mainLayout_l;
    QVBoxLayout * lineLabels_l;
    QHBoxLayout * viewControl_l;
    QHBoxLayout * timeControl_l;
    QHBoxLayout * streetControl_l;
    QStackedLayout * controlView_l;

    QWidget * streetControl_w;
    QWidget * timeControl_w;
    QWidget * viewControl_w;

};

#endif // __MAINWINDOW_H__