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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();
   void createStreetMap(std::vector<Street>);
   void createStreetMap(std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>>);
   void createLines(std::vector<Line>);
   void createSystemClock();
   void finish();


private slots:
    // void clock_tick_slot();
    void updateClock();
    void zoomIn();
    void zoomOut();
    void defaultZoom();
    void setTime();

signals:
    void timeChanged();

private:
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



};

#endif // __MAINWINDOW_H__