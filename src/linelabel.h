#ifndef __LINELABEL_H__
#define __LINELABEL_H__


#include <QLabel>
#include <QWidget>
#include "line.h"
class LineLabel : public QLabel
{
	Q_OBJECT
public:
	LineLabel(std::string,QWidget *parent = nullptr);
	~LineLabel(){};

protected:
	void mouseReleaseEvent(QMouseEvent *ev);

signals:
	// void clicked(uint32_t);
	void clicked();

private:
	std::string name;
};

#endif // __LINELABEL_H__