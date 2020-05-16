/**
 * @file street.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Street
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#include "linelabel.h"

LineLabel::LineLabel(std::string name, QWidget *parent)
	: QLabel(parent)
{
	setText(name.c_str());
}

void LineLabel::mouseReleaseEvent(QMouseEvent* event) 
{
	emit clicked();
}