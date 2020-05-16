#include "mainwindow.h"



MainWindow::MainWindow(Map * m) : map(m)
{
    
    // street_layout_w->hide();
    graph = &(m->g);

    mainLayout_l = new QGridLayout;

    lineLabels_l = new QVBoxLayout;

    main_l = new QStackedLayout;

    mainGrid_w = new QWidget();
    mainGrid_l = new QGridLayout(mainGrid_w);

    editGrid_w = new QWidget();
    editGrid_l = new QGridLayout(editGrid_w);

    streetControl_w = new QWidget();
    streetControl_l = new QGridLayout(streetControl_w);

    timeControl_w = new QWidget();
    timeControl_l = new QHBoxLayout(timeControl_w);

    viewControl_w = new QWidget();
    viewControl_l = new QHBoxLayout(viewControl_w);

    controlView_l = new QStackedLayout();

    info_l = new QLabel("&Traffic simulator");
    editInfo_l = new QLabel("Edit information label");
    street_l = new QLabel("");
    streetInfo_l = new QLabel("Traffic index: 0");
    status_l = new QLabel();

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


    // street control button  
    addTraffic_b = new QPushButton("&Add Traffic");
    clearTraffic_b = new QPushButton("&Clear Traffic");
    closeStreet_b = new QPushButton("&Close Street");
    // closeStreetControl_b = new QPushButton("&X");
    // closeStreetControl_b->setFixedSize(30,30);
    openStreets_b = new QPushButton("&Open Streets");
    saveNewRoute_b = new QPushButton("&Save Route");

}

void MainWindow::createMainLayout()
{
   


    // main layout
    mainLayout_l->addWidget(view,0,0,1,7);
    mainLayout_l->addLayout(lineLabels_l,0,7);
    
    mainLayout_l->addLayout(main_l,1,0,1,8);
    mainLayout_l->addWidget(status_l,2,0);


    // 
    mainGrid_l->addLayout(controlView_l,1,0,1,6);
    
    mainGrid_l->addWidget(time_l, 2,0);
    mainGrid_l->addWidget(changeTime_b,2,1);
    mainGrid_l->addWidget(openStreets_b,2,2);
    mainGrid_l->addWidget(viewControl_w,2,5,1,2);

    mainGrid_l->addWidget(timeControl_w,3,0);
    mainGrid_l->addWidget(changeTime_e,3,1);
    mainGrid_l->addWidget(setTime_b,3,2);

    // street control
    streetControl_l->addWidget(street_l,0,0);
    streetControl_l->addWidget(streetInfo_l,0,1);
    // streetControl_l->addWidget(closeStreetControl_b,0,2,Qt::AlignRight);
    streetControl_l->addWidget(closeStreet_b,1,0);
    streetControl_l->addWidget(clearTraffic_b,1,1);
    streetControl_l->addWidget(addTraffic_b,1,2);

    // time control
    timeControl_l->addWidget(slower_b);
    timeControl_l->addWidget(pauseResumeTime_b);
    timeControl_l->addWidget(faster_b);

    // view control
    viewControl_l->addWidget(zoomOut_b);
    viewControl_l->addWidget(zoomDefault_b);
    viewControl_l->addWidget(zoomIn_b);

    // control view
    controlView_l->addWidget(info_l);
    controlView_l->addWidget(streetControl_w);
    controlView_l->addWidget(connectionView);

    // main
    main_l->addWidget(mainGrid_w);
    main_l->addWidget(editGrid_w);

    // edit grid
    editGrid_l->addWidget(editInfo_l,0,0);
    editGrid_l->addWidget(saveNewRoute_b,1,0);
}

void MainWindow::createScene()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(-50,-50,700,700);
    scene->setBackgroundBrush(QBrush(Qt::white));

    connectionScene = new QGraphicsScene();
    connectionScene->setSceneRect(0,0,700,80);
}

void MainWindow::createView()
{
    view = new QGraphicsView(scene);
    view->show();
    connectionView = new QGraphicsView(connectionScene);
    connectionView->show();
}


void MainWindow::createStreetMap()
{
    sm = new StreetMap(map);
    scene->addItem(sm);

    // QObject::connect(this,  SIGNAL(startEditMode()),        sm,     SLOT(startEditMode()));
    QObject::connect(this,  SIGNAL(closeEditMode()),        sm,     SLOT(closeEditMode()));
    QObject::connect(sm,    SIGNAL(editNextRoute()),        this,   SLOT(changeLineRoute()));
    QObject::connect(this,  SIGNAL(editNextRoute_s()),      this,   SLOT(changeLineRoute()));
    QObject::connect(sm,    SIGNAL(actStreet(uint32_t)),    this,   SLOT(actStreet(uint32_t)));
    QObject::connect(sm,    SIGNAL(updateLineRoute(uint32_t, std::vector<Point>)), this, SLOT(updateLineRoute(uint32_t, std::vector<Point>)));
    QObject::connect(sm,    SIGNAL(setStatusLabel(std::string)),  this, SLOT(setStatusLabel(std::string)));
}

void MainWindow::createSystemClock()
{
    sys_clock = new QTimer(this);
    time = new QTime(0,0,0);
    
    changeTime_e = new QTimeEdit();
    changeTime_e->hide();
    changeTime_e->setTime(*time);
    
    time_l = new QLabel(time->toString("hh:mm:ss"));
    time_l->setAlignment(Qt::AlignCenter);
    
    QObject::connect(sys_clock, SIGNAL(timeout()), this, SLOT(updateClock()));
}


void MainWindow::createLines()
{
    for (auto line : map->lines) {
        LineObject * lineObject = new LineObject(graph, &line, time);
        lines.push_back(lineObject);
        
        lineObject->createVehicles();

        lineLabels_l->addWidget(lineObject->label);
        
        scene->addItem(lineObject->route);
        for (auto v : lineObject->vehicles){
            scene->addItem(v);
        }

        QObject::connect(lineObject->label, SIGNAL(clicked()),                      lineObject->route,  SLOT(toggleRoute()));
        QObject::connect(sys_clock,         SIGNAL(timeout()),                      lineObject,         SLOT(startVehicle()));
        QObject::connect(this,              SIGNAL(timeChanged(float)),             lineObject,         SLOT(timeChanged(float)));
        QObject::connect(this,              SIGNAL(stopAnimation()),                lineObject,         SLOT(stopAnimation()));
        QObject::connect(this,              SIGNAL(resumeAnimation()),              lineObject,         SLOT(resumeAnimation()));
        QObject::connect(lineObject,        SIGNAL(getConnectionInfo_s(uint32_t,TransportVehicle *)),this,            SLOT(getConnectionInfo(uint32_t,TransportVehicle *)));
        QObject::connect(this,              SIGNAL(showConnectionInfo_s(std::vector<std::pair<std::string,float>>)), lineObject, SLOT(showConnectionInfo(std::vector<std::pair<std::string,float>>)));
    }
    connection_info = new Connection();
    connectionScene->addItem(connection_info);
}

void MainWindow::connectButtons()
{

    // view control 
    QObject::connect(zoomIn_b,          SIGNAL(clicked()), this,            SLOT(zoomIn()));
    QObject::connect(zoomOut_b,         SIGNAL(clicked()), this,            SLOT(zoomOut()));
    QObject::connect(zoomDefault_b,     SIGNAL(clicked()), this,            SLOT(defaultZoom()));
    
    // time control
    QObject::connect(changeTime_b,      SIGNAL(clicked()), changeTime_e,    SLOT(show()));
    QObject::connect(changeTime_b,      SIGNAL(clicked()), setTime_b,       SLOT(show()));
    
    QObject::connect(setTime_b,         SIGNAL(clicked()), changeTime_e,    SLOT(hide()));
    QObject::connect(setTime_b,         SIGNAL(clicked()), this,            SLOT(setTime()));
    QObject::connect(setTime_b,         SIGNAL(clicked()), setTime_b,       SLOT(hide()));
     
    QObject::connect(pauseResumeTime_b, SIGNAL(clicked()), this,            SLOT(toggleClock()));
    QObject::connect(faster_b,          SIGNAL(clicked()), this,            SLOT(fasterClock()));
    QObject::connect(slower_b,          SIGNAL(clicked()), this,            SLOT(slowerClock()));
    
    // street control
    QObject::connect(addTraffic_b,      SIGNAL(clicked()), this,            SLOT(addTraffic()));
    QObject::connect(clearTraffic_b,    SIGNAL(clicked()), this,            SLOT(clearTraffic()));


    QObject::connect(closeStreet_b,     SIGNAL(clicked()), this,            SLOT(getCollidingLines()));
    QObject::connect(closeStreet_b,     SIGNAL(clicked()), sm,              SLOT(closeStreet()));

    QObject::connect(saveNewRoute_b,    SIGNAL(clicked()), sm,              SLOT(saveRoute()));

    QObject::connect(openStreets_b,     SIGNAL(clicked()), this,            SLOT(openStreets()));
}  

void MainWindow::finish() 
{

    sys_clock->start(1000);
    

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout_l);

    setCentralWidget(widget);


    setWindowTitle(tr("ICP -Traffic simulator"));
    setUnifiedTitleAndToolBarOnMac(true);

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
    
    graph->setTC(-0.1);
    auto currentTC = graph->getStreetTC(act_street[0],act_street[1]);
    if (currentTC > 0.1){
        graph->incStreetTC(act_street[0],act_street[1]);
        std::string street_traffic = "Traffic index: " + std::to_string(currentTC-0.1);
        streetInfo_l->setText(QString::fromStdString(street_traffic));
        emit timeChanged(1.f);
    } else {
        setStatusLabel("Traffic index reached its minimum.");
    }
}

void MainWindow::clearTraffic()
{
    graph->resetEdgeTC(graph->getNodeID(act_street[0]),graph->getNodeID(act_street[1]));
    auto currentTC = graph->getStreetTC(act_street[0],act_street[1]);
    std::string street_traffic = "Traffic index: " + std::to_string(currentTC);
    streetInfo_l->setText(QString::fromStdString(street_traffic));
    emit timeChanged(1.f);
}


void MainWindow::actStreet(uint32_t s_id)
{
    for (auto s : map->streets){
        if (s_id == s.getID()) {
            controlView_l->setCurrentIndex(1);
            auto pts = s.getPoints();
            act_street.clear();
            act_street.push_back(pts[0]);
            act_street.push_back(pts[1]);
            street_l->setText(QString::fromStdString(s.getName()));
            auto currentTC = graph->getStreetTC(act_street[0],act_street[1]);
            std::string street_traffic = "Traffic index: " + std::to_string(currentTC);
            streetInfo_l->setText(QString::fromStdString(street_traffic));
            streetControl_w->show();
            break;
        }
    } 
}

void MainWindow::updateLineRoute(uint32_t line, std::vector<Point> route)
{
    map->setDetour(line, route);
}

void MainWindow::changeLineRoute()
{

    if (colliding_lines.size() != 0){
        startEditMode();
        auto line = colliding_lines.back();
        for (auto l : lines) {
            if (l->id == line) {
                l->route->showRoute();
            } else {
                l->route->hideRoute();
            }
        }
        sm->changeRoute(graph->line_pts[line][0][0],graph->line_pts[line].back()[0],line);
        colliding_lines.pop_back();
    } else {

        emit closeEditMode();
        main_l->setCurrentIndex(0);
    }
}

void MainWindow::getConnectionInfo(uint32_t line_id, TransportVehicle * vehicle)
{
    controlView_l->setCurrentIndex(2);
    auto schedule = map->getLineSchedule(line_id,!(vehicle->direction));
    connection_info->show(vehicle, schedule);
    // emit showConnectionInfo_s(schedule);
}

void MainWindow::startEditMode()
{

    // set new control view
    main_l->setCurrentIndex(1);
    
    if (sys_clock->isActive()){
        sys_clock->stop();
        clock_state = false;
        emit stopAnimation();
    } else {
    }
    sm->startEditMode();
}

void MainWindow::getCollidingLines()
{
    if (act_street.size() == 2) {
        map->closeStreet(act_street[0],act_street[1],colliding_lines);
        changeLineRoute();
    }
}

void MainWindow::openStreets()
{
    sm->openStreets();
    map->openStreets();
}

void MainWindow::setStatusLabel(std::string msg)
{
    status_l->setText(QString::fromStdString(msg));
}