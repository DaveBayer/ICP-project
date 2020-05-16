/**
 * @file street.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Street
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __LINEOBJECT_H__
#define __LINEOBJECT_H__


#include <QLayout>
#include <QObject>
#include <QTime>

#include "line.h"
#include "linelabel.h"
#include "graph.h"
#include "lineroute.h"
#include "transportvehicle.h"


/**
 * @class      LineObject
 *
 * @brief      Třída reprezentující linku pro grafické rozhraní aplikace.
 *             Obsahuje v sobě třídy @p LineLabel a @p LineRoute, jejichž
 *             instance graficky znázorňují danou linku. V této třídě dochází k
 *             vytvoření jednotlivých spojů linky.
 */
class LineObject : public QObject
{
	Q_OBJECT
public:
    /**
     * @brief      Vytvoří novou instanci třídy LineObject.
     *
     * @param      g          Ukazatel na graf.
     * @param      line       Ukazatel na linku
     * @param      time       Ukazatel na systémový čas
     */
    LineObject(Graph *,Line * line,QTime *);
    /**
     * @brief      Destruktor třídy LineObject
     */
    ~LineObject();

    /**
     * @brief      Funkce pro vytvoření vozidel linky (@p TransportVehicle).
     *             Postupně prochází vektory @c line->forward a @c
     *             line->backward linky @Line, které obsahují časy odjezdů
     *             jednotlivých spojů. Vytváří instance třídy @p
     *             TransportVehicle a ukladá ukazatele na ně do vektoru @c
     *             vehicles. Nad každým nově vytvořeným vozidlem poté zavolá
     *             funkce pro jejich inicializaci a spojí jejich signál @c
     *             getConnectionInfo(TransportVehicle *) se slotem @p
     *             getConnectionInfo(TransportVehicle *).
     */
    void createVehicles();

    /// Identifikační číslo linky.
	uint32_t id;
    /// Ukazatel instanci třídy @p LineRoute
    LineRoute *route;
    /// Ukazatel instanci třídy @p LineLabel
    LineLabel *label;
    /// Vektor uchovávající ukazatele na vozidla 
    std::vector<TransportVehicle *> vehicles;


private slots:
    /**
     * @brief      Zahájí animaci vozidla na základě systémového času. Spustí
     *             časovač animace vozidla a nastaví viditelnost pokud čas
     *             startu vozidla je roven systémovému času.
     */
    void startVehicle();
    /**
     * @brief      Aktualizuje polohu vozidla na základě systémového času.
     *             Prochází vektorem vozidel a nastavuje pozici vozidla na mapě
     *             v daný časový okamžik.
     *
     * @param[in]  speed  Rychlost systémového času.
     */
    void timeChanged(float);
    /**
     * @brief      Zastaví animaci vozidel.
     */
    void stopAnimation();
    /**
     * @brief      Znovu spustí zastavenou animaci vozidel.
     */
    void resumeAnimation();
    /**
     * @brief      Vyšle signál s idetifikačním číslem linky a ukazatelem na
     *             dané vozidlo, pro nějž chce získat jízdní řád. 
     *
     * @param      v     Ukazatel na dané vozidlo
     */
    void getConnectionInfo(TransportVehicle *v);
signals:
	/**
      * @brief      Signál pro vyslání požadavku pro získání jízdního řádu
      *             daného vozidla.
      *
      * @param[in]  id    Identifikační číslo linky
      * @param      v     Ukazatel na vozidlo
      */
    void getConnectionInfo_s(uint32_t id,TransportVehicle *v);

private:
    
    /// Ukazatel na instanci třídy @p Line.
    Line *line;
    /// Ukazatel na instanci třídy @p Graph.
    Graph * graph;
    /// Ukazatel na systémový čas aplikace. 
    QTime * currTime;
    /// Proměnná reprezentující stav animace vozidel.
    bool running;
};


#endif // __LINEOBJECT_H__