
#include <QLabel>
#include <QWidget>
#include "line.h"
class LineLabel : public QLabel
{
	Q_OBJECT
public:
	LineLabel(Line line,QWidget *parent = nullptr);
	~LineLabel(){};

protected:
	void mouseReleaseEvent(QMouseEvent *ev);

signals:
	// void clicked(uint32_t);
	void clicked();

private:
	Line line;
};