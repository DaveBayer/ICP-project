#include "linelabel.h"
#include "line.h"

LineLabel::LineLabel(Line line, QWidget *parent)
	: QLabel(parent),line(line)
{
	setText(line.getName().c_str());
}

void LineLabel::mouseReleaseEvent(QMouseEvent* event) 
{
	emit clicked(line.getId());
}