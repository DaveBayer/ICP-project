#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QTimer>

#include "streetmap.h"
#include "line.h"
#include "linelabel.h"
#include "lineroute.h"
#include "transportvehicle.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();
   void createStreetMap(std::vector<Street>);
   void createLines(std::vector<Line>);
   void finish();

private slots:
    void clock_tick();

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QLabel *label;

    QGridLayout *mainLayout;
    QVBoxLayout * line_labels;

};