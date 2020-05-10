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

signals:
    void timeChanged(float);
    void stopAnimation();
    void resumeAnimation();

private:
    bool clock_state = true;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QLabel *label;

    QGridLayout *mainLayout;
    QVBoxLayout * line_labels;

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

    StreetMap *sm;
    Graph * graph;
    Map * map;

};

#endif // __MAINWINDOW_H__