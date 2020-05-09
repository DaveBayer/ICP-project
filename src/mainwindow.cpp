#include "mainwindow.h"



MainWindow::MainWindow(Map * m) : map(m)
{
    line_labels = new QVBoxLayout;
    graph = &(m->g);

    zoomin = new QPushButton("&Zoom In");
    zoomout = new QPushButton("&Zoom Out");
    zoomdefault = new QPushButton("&Default Zoom");
    changetime = new QPushButton("&Change Time");
    settime = new QPushButton("&Set Time");
    pauseresumetime = new QPushButton("&Pause/Resume time");
    settime->hide();

}

void MainWindow::createScene()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,600);
    scene->setBackgroundBrush(QBrush(Qt::white));
}


void MainWindow::createStreetMap()
{
    StreetMap *sm = new StreetMap(graph->cs, map->stations);
    scene->addItem(sm);
}

void MainWindow::createSystemClock()
{
    sys_clock = new QTimer(this);
    time = new QTime(0,0,0);
    time_edit = new QTimeEdit();
    time_edit->hide();
    time_edit->setTime(*time);
    clock_label = new QLabel(time->toString("hh:mm:ss"));
    QObject::connect(sys_clock, SIGNAL(timeout()), this, SLOT(updateClock()));
}


void MainWindow::createLines()
{
    for (auto line : graph->line_pts) {
        std::cout<<line.first<<std::endl;
        LineObject * lineObject = new LineObject(graph,line.first, line.second, time);
        struct timetable_s connection1 = {.start = (0 + 0 + 2)};
        struct timetable_s connection2 = {.start = (1*60*60 + 0*60 + 2)};
        struct timetable_s connection3 = {.start = (1*60*60 + 10*60 + 50)};
        
        std::vector<timetable_s> t = {connection1,connection2,connection3};        
        lineObject->createVehicles(t);

        line_labels->addWidget(lineObject->label);
        
        scene->addItem(lineObject->route);
        for (auto v : lineObject->vehicles){
            scene->addItem(v);
        }

        QObject::connect(lineObject->label, SIGNAL(clicked()),lineObject->route,SLOT(showRoute()));
        QObject::connect(sys_clock,SIGNAL(timeout()),lineObject, SLOT(startVehicle()));
        QObject::connect(this, SIGNAL(timeChanged()), lineObject, SLOT(timeChanged()));
        QObject::connect(this, SIGNAL(stopAnimation()), lineObject, SLOT(stopAnimation()));
        QObject::connect(this, SIGNAL(resumeAnimation()), lineObject, SLOT(resumeAnimation()));
    }
}


void MainWindow::finish() 
{

    sys_clock->start(1000);
    

    view = new QGraphicsView(scene);
    view->show();

    QObject::connect(zoomin, SIGNAL(clicked()), this, SLOT(zoomIn()));
    QObject::connect(zoomout, SIGNAL(clicked()), this, SLOT(zoomOut()));
    QObject::connect(zoomdefault, SIGNAL(clicked()), this, SLOT(defaultZoom()));
    QObject::connect(changetime, SIGNAL(clicked()), time_edit, SLOT(show()));
    QObject::connect(changetime, SIGNAL(clicked()), settime, SLOT(show()));
    QObject::connect(settime, SIGNAL(clicked()), time_edit, SLOT(hide()));
    QObject::connect(settime, SIGNAL(clicked()), this, SLOT(setTime()));
    QObject::connect(settime, SIGNAL(clicked()), settime, SLOT(hide()));
    QObject::connect(pauseresumetime, SIGNAL(clicked()), this, SLOT(toggleClock()));

    mainLayout = new QGridLayout;

    mainLayout->addWidget(view,0,0,1,5);
    mainLayout->addLayout(this->line_labels, 0, 5);
    mainLayout->addWidget(clock_label, 1,0);
    mainLayout->addWidget(pauseresumetime,1,1);
    mainLayout->addWidget(changetime,1,2);
    mainLayout->addWidget(time_edit,2,0);
    mainLayout->addWidget(settime,2,1);  
    mainLayout->addWidget(zoomout,1,3);
    mainLayout->addWidget(zoomdefault,1,4);
    mainLayout->addWidget(zoomin,1,5);
    
    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);


    setWindowTitle(tr("ICP -Traffic simulator"));
    setUnifiedTitleAndToolBarOnMac(true);
}


void MainWindow::updateClock()
{
    *time = time->addSecs(1);
    clock_label->setText(time->toString("hh:mm:ss"));
}

void MainWindow::zoomIn()
{
    view->scale(1.1,1.1);
}
void MainWindow::zoomOut()
{
    view->scale(0.9,0.9);
}

void MainWindow::setTime()
{
    *time = time_edit->time();
    clock_label->setText(time->toString("hh:mm:ss"));
    emit timeChanged();
}

void MainWindow::defaultZoom()
{
    view->resetMatrix();
}

void MainWindow::toggleClock()
{
    if (sys_clock->isActive()){
        sys_clock->stop();
        emit stopAnimation();
    }else { 
        sys_clock->start();
        emit resumeAnimation();
    }
}