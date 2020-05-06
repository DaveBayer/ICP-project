#include "mainwindow.h"

MainWindow::MainWindow()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,600);
    

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
        // new LineGraphicsItem
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