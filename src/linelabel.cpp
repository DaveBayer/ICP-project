#include "linelabel.h"
#include "line.h"

LineLabel::LineLabel(std::string name, QWidget *parent)
	: QLabel(parent),name(name)
{
	setText(name.c_str());
}

void LineLabel::mouseReleaseEvent(QMouseEvent* event) 
{
	emit clicked();
}