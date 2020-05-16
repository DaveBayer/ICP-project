/**
 * @file mainwindow.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy MainWindow
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
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
#include "connection.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

   MainWindow(Map *);
   void init();
   void startEditMode();



private slots:
    void updateClock();
    void zoomIn();
    void zoomOut();
    void defaultZoom();
    void setTime();
    void toggleClock();
    void fasterClock();
    void slowerClock();
    void actStreet(uint32_t);
    void addTraffic();
    void clearTraffic();
    void changeLineRoute();
    void getCollidingLines();
    void updateLineRoute(uint32_t, std::vector<Point>);
    void openStreets();
    void getConnectionInfo(uint32_t,TransportVehicle *);
    void setStatusLabel(std::string);


signals:
    void timeChanged(float);
    void stopAnimation();
    void resumeAnimation();
    void editNextRoute_s();
    void showConnectionInfo_s(std::vector<std::pair<std::string,float>>);
    void closeEditMode();

private:
    void createLayouts();
    void createButtons();
    void createLabels();
    void createScenes();
    void createViews();
    void createStreetMap();
    void createLines();
    void createSystemClock();
    void createMainLayout();
    void connectButtons();


    // Graphics
    QGraphicsView * view;
    QGraphicsView * connectionView;

    QGraphicsScene * scene;
    QGraphicsScene * connectionScene;
    

    QTimer * sys_clock;
    QTime * time;
    QTimeEdit * changeTime_e;
    bool clock_state = true;

    // Labels
    QLabel * time_l;
    QLabel * info_l;
    QLabel * editInfo_l;
    QLabel * street_l;
    QLabel * streetInfo_l;
    QLabel * status_l;


    // Buttons
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
    QPushButton * openStreets_b;
    QPushButton * saveNewRoute_b;


    std::vector<LineObject *> lines;
    std::vector<uint32_t> colliding_lines;

    Connection * connection_info;
    StreetMap *sm;
    Graph * graph;
    Map * map;

    std::vector<Point> act_street;

    // Layout
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