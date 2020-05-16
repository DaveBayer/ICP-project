/**
 * @file transportvehicle.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy TransportVehicle
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __TRANSPORTVEHICLE_H__
#define __TRANSPORTVEHICLE_H__

#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QTime>

#include "point.h"
#include "graph.h"

/// Makro pro rychlost vozidla v pixelech za jednu milisekundu. K dopočtení jízdního řádu.
#define VEHICLE_SPEED 0.0014
/// Makro pro čas strávený na stanici v sekundách. K dopočtení jízdního řádu.
#define STATION_DELAY 10

/**
 * @class      TransportVehicle
 *
 * Třída reprezentující grafickou podobu spoje linky.
 *
 * Objekty jsou vytvářeny třídou LineObject, která na základě seznamů
 * odjezdových časů vygeneruje správný počet instancí této třídy. Tento grafický prvek pracuje s
 */
class TransportVehicle : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:



    /**
     * @brief      Vytvoří novou instanci třídy TransportVehicle
     *
     * @param      g          Ukazatel na graf
     * @param[in]  timeStart  Čas výjezdu vozidla
     * @param[in]  line       Ukazatel na linku
     * @param[in]  direction  Směr vozidla
     */
    TransportVehicle(Graph *g,uint32_t timeStart,uint32_t line,bool direction);
    /**
     * @brief      Destruktor třídy
     */
    ~TransportVehicle();

    /**
     * @brief      Funkce zděděná z QT třídy QGraphicsItem.
     *
     */
    QRectF boundingRect() const override;
    /**
     * @brief      Funkce zděděná z QT třídy QGraphicsItem.
     *
     *             Vykreslí vozidlo ve formě elipsy.
     *
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief      Funkce pro nastavení délky trvání animace. Čas je vypočtem z
     *             proměnné @c duration, který obsahuje délku trvání jízdy
     *             vozidla. Tento čas je pak pronásobený koeficientem rychlosti.
     *
     * @param[in]  c     Koeficient rychlosti systémového času
     */
    void setRouteDuration(float c);
    /**
     * @brief      Funkce nastaví trasu linky a animaci na dané trase. Tato
     *             funkce je volána každý tik systémových hodin. Dojde k výpočtu
     *             trasy animace a délky trvání jednotlivých přesunů mezi body
     *             trasy.
     */
    void setRoutePath();
    /**
     * @brief      Funkce vrací délky trasy podle hodnot hran v grafu. Délka
     *             trasy reflektuje provozní situaci.
     *
     * @return     Délka trasy
     */
    float getRouteLength();
    /**
     * @brief      Nastaví pozici vozidla na jeho trase podle systémového času.
     *             Tato funkce je volána každý tik systémových hodin. Pozice je
     *             vypočítána na základě celkového doby trvání jízdy vozidla.
     *
     * @param[in]  speed  Pozice vozidla v daném čase
     */
    void setVehiclePosition(float postime);
    /**
     * @brief      Funkce pro inicializaci základních vlastností vozidla. Zde se
     *             nastaví rychlost vozidla, doba času stráveného ve stanici,
     *             délka trasy, objekt animace, ... .
     *             
     */
    void initVehicle();
    /**
     * @brief      Funkce pro získání trasy daného vozidla.
     *
     * @return     Trasa vozidla ve formě vektorů bodů mezi jednotlivými
     *             stanicemi
     */
    std::vector<std::vector<Point>> getRoute();

    /// Identifikátor linky vozidla 
    uint32_t line;
    /// rychlost vozidla v pixelech za jednu milisekundu
    float speed;
    /// délka trasy vozidla v pixelech
    float length;
    /// koleficient zrychlení systémových hodin
    float acc;
    /// Doba trvání animace vozidla
    float duration;
    /// Doba čekání vozidla na stanici
    float station_delay;
    /// Proměnná udávající směr vozidla. True když je směr podle nadefinovaných stanic linky, jinak false
    bool direction;

    /// Časovač animace vozidla 
    QTimeLine *timer;
    /// Čas výjezdu vozidla
    QTime * time_start;
    /// Čas dojezdu vozidla
    QTime * time_end;

private slots:
	/**
      * @brief      Slot pro skrytí vozidla ze scény jakmile dokončí svoji
      *             jízdu.
      */
    void finished();

signals:
    /**
     * @brief      Signál pro získání jízního řádu vozidla. Je vyvolaný při
     *             kliknutí na vozidlo.
     *
     * @param      v     Ukazatel na kliknuté vozidlo
     */
    void getConnectionInfo(TransportVehicle *v);

protected:
    /**
     * @brief      Funkce zděděná z QT třídy QObject. Zaznaménává kliknutí na
     *             vozidla, které vyvolává signál @c
     *             getConnectionInfo(TransportVehicle *v)
     *
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    /// Pero pro vykreslení vozidla
    QPen pen;
    /// Ukazatel na instanci animace vozidla
    QGraphicsItemAnimation * animation;
    /// Ukazatel na graf
    Graph * graph;

};

#endif // __TRANSPORTVEHICLE_H__