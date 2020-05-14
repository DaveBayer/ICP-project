#include "mainwindow.h"


MainWindow::MainWindow(Map * m) : map(m)
{
    
    // street_layout_w->hide();
    graph = &(m->g);

    mainLayout_l = new QGridLayout;

    lineLabels_l = new QVBoxLayout;

    streetControl_w = new QWidget();
    streetControl_l = new QHBoxLayout(streetControl_w);

    timeControl_w = new QWidget();
    timeControl_l = new QHBoxLayout(timeControl_w);

    viewControl_w = new QWidget();
    viewControl_l = new QHBoxLayout(viewControl_w);

    controlView_l = new QStackedLayout();

}

void MainWindow::createButtons()
{
    zoomIn_b = new QPushButton("&+");
    zoomOut_b = new QPushButton("&-");
    zoomDefault_b = new QPushButton("&Default");
    changeTime_b = new QPushButton("&Change Time");
    setTime_b = new QPushButton("&Set Time");
    pauseResumeTime_b = new QPushButton("&>||");
    setTime_b->hide();
    faster_b = new QPushButton("&>>");
    slower_b = new QPushButton("&<<");


    pauseResumeTime_b->setFixedSize(30,25);
    faster_b->setFixedSize(30,25);
    slower_b->setFixedSize(30,25);
    zoomOut_b->setFixedSize(30,25);
    zoomIn_b->setFixedSize(30,25);
    zoomDefault_b->setFixedSize(60,25);


    addTraffic_b = new QPushButton("&Add Traffic");
    clearTraffic_b = new QPushButton("&Clear Traffic");
    closeStreet_b = new QPushButton("&Close Street");
}

void MainWindow::createMainLayout()
{
    std::cout<<"h\n";
   


    // main layout
    mainLayout_l->addWidget(view,0,0,1,7);
    mainLayout_l->addLayout(lineLabels_l,0,7);
    
    mainLayout_l->addLayout(controlView_l,1,0,1,6);
    
    mainLayout_l->addWidget(time_l, 2,0);
    mainLayout_l->addWidget(changeTime_b,2,1);
    mainLayout_l->addWidget(viewControl_w,2,5,1,2);

    mainLayout_l->addWidget(timeControl_w,3,0);
    mainLayout_l->addWidget(changeTime_e,3,1);
    mainLayout_l->addWidget(setTime_b,3,2);

    // street control
    streetControl_l->addWidget(closeStreet_b);
    streetControl_l->addWidget(clearTraffic_b);
    streetControl_l->addWidget(addTraffic_b);

    // time control
    timeControl_l->addWidget(slower_b);
    timeControl_l->addWidget(pauseResumeTime_b);
    timeControl_l->addWidget(faster_b);

    // view control
    viewControl_l->addWidget(zoomOut_b);
    viewControl_l->addWidget(zoomDefault_b);
    viewControl_l->addWidget(zoomIn_b);
}

void MainWindow::createScene()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(-50,-50,700,700);
    scene->setBackgroundBrush(QBrush(Qt::white));
}

void MainWindow::createView()
{
    view = new QGraphicsView(scene);
    view->show();
}


void MainWindow::createStreetMap()
{
    sm = new StreetMap(graph, graph->cs, map->stations);
    scene->addItem(sm);
}

void MainWindow::createSystemClock()
{
    sys_clock = new QTimer(this);
    time = new QTime(0,0,0);
    changeTime_e = new QTimeEdit();
    changeTime_e->hide();
    changeTime_e->setTime(*time);
    time_l = new QLabel(time->toString("hh:mm:ss"));
    QObject::connect(sys_clock, SIGNAL(timeout()), this, SLOT(updateClock()));
}


void MainWindow::createLines()
{

    for (auto line : graph->line_pts) {
        LineObject * lineObject = new LineObject(graph, map->lines,line.first, line.second, time);
        
        lineObject->createVehicles();

        lineLabels_l->addWidget(lineObject->label);
        
        scene->addItem(lineObject->route);
        for (auto v : lineObject->vehicles){
            scene->addItem(v);
        }

        QObject::connect(lineObject->label, SIGNAL(clicked()),                      lineObject->route,  SLOT(showRoute()));
        QObject::connect(sys_clock,         SIGNAL(timeout()),                      lineObject,         SLOT(startVehicle()));
        QObject::connect(this,              SIGNAL(timeChanged(float)),             lineObject,         SLOT(timeChanged(float)));
        QObject::connect(this,              SIGNAL(stopAnimation()),                lineObject,         SLOT(stopAnimation()));
        QObject::connect(this,              SIGNAL(resumeAnimation()),              lineObject,         SLOT(resumeAnimation()));
        QObject::connect(sm,                SIGNAL(actStreet(uint32_t,uint32_t)),   this,               SLOT(actStreet(uint32_t,uint32_t)));
    std::cout<<"hh\n";
    }
}

void MainWindow::connectButtons()
{
    QObject::connect(zoomIn_b,          SIGNAL(clicked()), this,            SLOT(zoomIn()));
    QObject::connect(zoomOut_b,         SIGNAL(clicked()), this,            SLOT(zoomOut()));
    QObject::connect(zoomDefault_b,     SIGNAL(clicked()), this,            SLOT(defaultZoom()));
    QObject::connect(changeTime_b,      SIGNAL(clicked()), changeTime_e,    SLOT(show()));
    QObject::connect(changeTime_b,      SIGNAL(clicked()), setTime_b,         SLOT(show()));
    QObject::connect(setTime_b,         SIGNAL(clicked()), changeTime_e,    SLOT(hide()));
    QObject::connect(setTime_b,         SIGNAL(clicked()), this,            SLOT(setTime()));
    QObject::connect(setTime_b,         SIGNAL(clicked()), setTime_b,         SLOT(hide()));
    QObject::connect(pauseResumeTime_b, SIGNAL(clicked()), this,            SLOT(toggleClock()));
    QObject::connect(faster_b,          SIGNAL(clicked()), this,            SLOT(fasterClock()));
    QObject::connect(slower_b,          SIGNAL(clicked()), this,            SLOT(slowerClock()));
    QObject::connect(addTraffic_b,      SIGNAL(clicked()), this,            SLOT(addTraffic()));
}

void MainWindow::finish() 
{

    sys_clock->start(1000);
    
    // mainLayout->addWidget(view,0,0,1,7);
    // mainLayout->addLayout(this->lineLabels_l, 0, 7);
    // mainLayout->addWidget(street_layout_w,1,0);
    // mainLayout->addWidget(clock_label, 2,0);
    // mainLayout->addWidget(slower,2,1);
    // mainLayout->addWidget(faster,2,2);
    // mainLayout->addWidget(pauseresumetime,2,3);
    // mainLayout->addWidget(changetime,2,4);
    // mainLayout->addWidget(time_edit,3,0);
    // mainLayout->addWidget(settime,3,1);  
    // mainLayout->addWidget(zoomout,2,5);
    // mainLayout->addWidget(zoomdefault,2,6);
    // mainLayout->addWidget(zoomin,2,7);
    
    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout_l);

    setCentralWidget(widget);


    setWindowTitle(tr("ICP -Traffic simulator"));
    setUnifiedTitleAndToolBarOnMac(true);
        std::cout<<"he\n";

}


void MainWindow::updateClock()
{
    *time = time->addSecs(1);
    time_l->setText(time->toString("hh:mm:ss"));
    emit timeChanged(1.f);
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
    *time = changeTime_e->time();
    time_l->setText(time->toString("hh:mm:ss"));

    emit timeChanged(1.f);
}

void MainWindow::defaultZoom()
{
    view->resetMatrix();
}

void MainWindow::toggleClock()
{
    if (sys_clock->isActive()){
        sys_clock->stop();
        clock_state = false;
        emit stopAnimation();
    }else { 
        sys_clock->start();
        clock_state = true;
        emit resumeAnimation();
    }
}

void MainWindow::fasterClock()
{
    if (sys_clock->interval()>10){
        sys_clock->setInterval(sys_clock->interval()*0.5);
        emit timeChanged(0.5);
    }
}

void MainWindow::slowerClock()
{
    if(sys_clock->interval()<10000){       
        sys_clock->setInterval(sys_clock->interval()*2);
        emit timeChanged(2);
    }
}

void MainWindow::addTraffic()
{
    graph->setTC(-0.5);
    graph->incEdgeTC(act_street[0],act_street[1]);
    std::cout<<*graph;
    emit timeChanged(1.f);
}

void MainWindow::clearTraffic()
{
    graph->setTC(0.5);
    graph->incEdgeTC(act_street[0],act_street[1]);
    emit timeChanged(1.f);
}

void MainWindow::closeStreet()
{

}

void MainWindow::actStreet(uint32_t idx1,uint32_t idx2)
{
    act_street.push_back(idx1);
    act_street.push_back(idx2);
    streetControl_w->show();
}