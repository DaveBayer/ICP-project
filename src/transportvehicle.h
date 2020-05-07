#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QPainter>


class TransportVehicle : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
    TransportVehicle(QGraphicsScene *scene);
    ~TransportVehicle();
    QPen pen;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void addToScene();
    void createAnimation();

private slots:
	void finished();

private:
	QGraphicsScene *scene;
    QColor color;
    QTimeLine *timer;
};