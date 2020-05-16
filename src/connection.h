/**
 * @file connection.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Connection
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */

#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QTime>

#include "point.h"
#include "transportvehicle.h"



/**
 * @class      Connection
 *
 * @brief      Třída reprezentující jednotlivé spoje linek. Slouží pro
 *             vykreslení informací o daném spoji. Dědí od QT tříd QObject a
 *             QGraphicsItem.
 */
class Connection : public QObject, public QGraphicsItem
{
	Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:

    /**
     * @brief      Vytvoří novou instanci třídy @p Connection. Nastaví pero
     *             (QPen), podle kterého se má vykreslit časová osa spoje s jeho
     *             jízdním řádem. Poté vykresí mustr časové osy.
     */
    Connection();
    /**
     * @brief      Destruktor pro instanci třídy \p Connection.
     */
    ~Connection();

    /**
     * @brief      Funkce poděděná ze QT třídy QGraphicsItem
     *
     */
    QRectF boundingRect() const override;
    /**
     * @brief      Funkce poděděná ze QT třídy QGraphicsItem
     *
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief      Funkce na vykreslení stanic spoje s jeho dopočítaným jízdním
     *             řádem.
     *
     * @param      v         Ukazatel na vozidlo spoje.
     * @param[in]  schedule  Jízdní řád daného spoje
     */
    void show(TransportVehicle *, std::vector<std::pair<std::string,float>>);

private:
    /// Vektor, do kterého se ukládají vykreslené stanice spoje.
    std::vector<QGraphicsEllipseItem *> stations; 
    /// Vektor, do kterého se ukládají vykreslené informace o spoji.
    std::vector<QGraphicsTextItem *> stations_info;  
    /// Pero, dle kterého se vykresluje daná scéna.
    QPen pen;
    /// Štětec, dle kterého se vykresluje daná scéna.
    QBrush brush;

};

#endif // __CONNECTION_H__