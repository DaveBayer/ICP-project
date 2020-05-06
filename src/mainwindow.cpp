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
        QObject::connect(lineLabel, SIGNAL(clicked(uint32_t)),this,SLOT(lineClicked(uint32_t)));

        scene->addItem(lineRoute);
    }
}


void MainWindow::finish() 
{
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

void MainWindow::lineClicked(uint32_t id)
{
    std::cout<<"Line with id " << id << " clicked.\n";
    auto item_list = scene->items();
    for (auto it : item_list){
        LineRoute *route = qgraphicsitem_cast<LineRoute *>(it);
        if (!route) continue;
        if(route->getId() == id) {
            std::cout << route->getId() <<std::endl;
            if (route->isVisible())
                route->setVisible(false);
            else
                route->setVisible(true);
            scene->update();
        }
    }
    // it->setVisible(true);
}