/**
 * @file linelabel.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy LineLabel
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __LINELABEL_H__
#define __LINELABEL_H__


#include <QLabel>
#include <QWidget>
#include "line.h"

/**
 * @class      LineLabel
 *
 * @brief      Třída reprezentující označení jména linky v grafickém rozhraní
 *             aplikace. Třída dědí z QT třídy QLabel.
 */
class LineLabel : public QLabel
{
	Q_OBJECT
public:
	/**
	 * @brief      Vytvoří novou instanci třídy @p LineLabel.
	 *
	 * @param[in]  name  	  Jméno linky.
	 * @param      parent     Rodič grafického objektu.
	 */
	LineLabel(std::string,QWidget *parent = nullptr);
	/**
	 * @brief      Destruktor instance třídy LineLabel.
	 */
	~LineLabel(){};

protected:
	/**
	 * @brief      Funkce poděděná ze QT třídy QObject.
	 *
	 */
	void mouseReleaseEvent(QMouseEvent *ev);

signals:
	/**
	 * @brief      Signál, který vysílán po kliknutí na danou linku.
	 */
	void clicked();

};

#endif // __LINELABEL_H__