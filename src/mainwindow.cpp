#include "mainwindow.h"

MainWindow::MainWindow()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,600);
    scene->setBackgroundBrush(QBrush(Qt::white));

    line_labels = new QVBoxLayout;

}

void MainWindow::createStreetMap(std::vector<Street> s)
{
    StreetMap *sm = new StreetMap(s);
    scene->addItem(sm);
}


void MainWindow::createLines(std::vector<Line> l)
{
    for (auto line : l) {
        LineLabel * lineLabel = new LineLabel(line);
        line_labels->addWidget(lineLabel);
        LineRoute * lineRoute = new LineRoute(line.getId(),line.getRoute());
        QObject::connect(lineLabel, SIGNAL(clicked()),lineRoute,SLOT(showRoute()));

        scene->addItem(lineRoute);
    }
}


void MainWindow::finish() 
{

    QTimer *sys_clock = new QTimer(this);
    connect(sys_clock, SIGNAL(timeout()), this,SLOT(clock_tick()));
    sys_clock->start(1000);
    

    view = new QGraphicsView(scene);
    view->show();

    mainLayout = new QGridLayout;

    mainLayout->addWidget(view,0,0);
    mainLayout->addLayout(this->line_labels, 0, 1);
    
    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);


    setWindowTitle(tr("ICP -Traffic simulator"));
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::clock_tick()
{
    static uint32_t time = 0;
    std::cout<<"Clock ticked()\n";
    time++;
    if(time == 5){
        TransportVehicle *v = new TransportVehicle(scene);
        v->createAnimation();
        v->addToScene();
    }
}