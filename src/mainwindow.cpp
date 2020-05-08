#include "mainwindow.h"

MainWindow::MainWindow()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,600);
    scene->setBackgroundBrush(QBrush(Qt::white));

    line_labels = new QVBoxLayout;

    zoomin = new QPushButton("&Zoom In");
    zoomout = new QPushButton("&Zoom Out");
    zoomdefault = new QPushButton("&Default Zoom");



}

void MainWindow::createStreetMap(std::vector<Street> s)
{
    StreetMap *sm = new StreetMap(s);
    scene->addItem(sm);
}
void MainWindow::createStreetMap(std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>> m)
{
    StreetMap *sm = new StreetMap(m);
    scene->addItem(sm);
}

void MainWindow::createSystemClock()
{
    sys_clock = new QTimer(this);
    time = new QTime(0,0,0);
    clock_label = new QLabel(time->toString("hh:mm:ss"));
    QObject::connect(sys_clock, SIGNAL(timeout()), this, SLOT(updateClock()));
}


void MainWindow::createLines(std::vector<Line> l)
{
    for (auto line : l) {
        LineObject * lineObject = new LineObject(line, line_labels, scene);
        QObject::connect(sys_clock,SIGNAL(timeout()),lineObject, SLOT(createVehicle()));
        // QObject::connect(this, SIGNAL(clock_tick_signal()),lineObject,SLOT(createVehicle()));
    }
}


void MainWindow::finish() 
{

    // connect(sys_clock, SIGNAL(timeout()), this,SLOT(clock_tick_slot()));
    sys_clock->start(1000);
    

    view = new QGraphicsView(scene);
    view->show();

    QObject::connect(zoomin, SIGNAL(clicked()), this, SLOT(zoomIn()));
    QObject::connect(zoomout, SIGNAL(clicked()), this, SLOT(zoomOut()));
    QObject::connect(zoomdefault, SIGNAL(clicked()), this, SLOT(defaultZoom()));


    mainLayout = new QGridLayout;

    mainLayout->setColumnStretch(0, 2);
    mainLayout->addWidget(view,0,0,1,4);
    mainLayout->addLayout(this->line_labels, 0, 4);
    mainLayout->addWidget(clock_label, 1,0);
    mainLayout->addWidget(zoomout,1,1);
    mainLayout->addWidget(zoomdefault,1,2);
    mainLayout->addWidget(zoomin,1,3);
    
    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);


    setWindowTitle(tr("ICP -Traffic simulator"));
    setUnifiedTitleAndToolBarOnMac(true);
}

// void MainWindow::clock_tick_slot()
// {
//     static uint32_t time = 0;
//     std::cout<<"Clock ticked()\n";
//     time++;
//     if(time == 5){
//         emit clock_tick_signal();
//     }
// }

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

void MainWindow::defaultZoom()
{
    view->resetMatrix();
}