#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>

#include "streetmap.h"
#include "line.h"
#include "linelabel.h"
#include "lineroute.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();
   void createStreetMap(std::vector<Street>);
   void createLines(std::vector<Line>);
   void finish();

private slots:
    void lineClicked(uint32_t id);

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QLabel *label;

    QGridLayout *mainLayout;
    QVBoxLayout * line_labels;

};