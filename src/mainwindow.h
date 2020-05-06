#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();

private slots:
    // void lineClicked(uint32_t id);

private:
    QGraphicsScene *scene;
    QLabel *label1;
};