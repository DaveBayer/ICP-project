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
    void closeStreet();
    void addTraffic();
    void clearTraffic();
    void changeLineRoute();
    void showConnectionInfo();

signals:
    void timeChanged(float);
    void stopAnimation();
    void resumeAnimation();
    void editNextRoute_s();

    void closeEditMode();
    void startEditMode();

private:

    std::vector<uint32_t> colliding_lines;
    bool clock_state = true;
    QGraphicsView * view;
    QGraphicsView * connectionView;
    QGraphicsScene * scene;
    QGraphicsScene * connectionScene;
    QLabel *label;

    QTimer * sys_clock;
    QTime * time;
    QTimeEdit * changeTime_e;
    QLabel * time_l;

    QLabel * info_l;
    QLabel * editInfo_l;
    QLabel * street_l;
    QLabel * streetInfo_l;


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


    std::vector<LineObject *> lines;

    StreetMap *sm;
    Graph * graph;
    Map * map;

    std::vector<Point> act_street;

    // layout
    QGridLayout * mainLayout_l;
    QGridLayout * mainGrid_l;
    QGridLayout * editGrid_l;
    QStackedLayout * main_l;
    QVBoxLayout * lineLabels_l;
    QHBoxLayout * viewControl_l;
    QHBoxLayout * timeControl_l;
    QGridLayout * streetControl_l;
    QStackedLayout * controlView_l;

    QWidget * streetControl_w;
    QWidget * timeControl_w;
    QWidget * viewControl_w;
    QWidget * mainGrid_w;
    QWidget * editGrid_w;

};

#endif // __MAINWINDOW_H__