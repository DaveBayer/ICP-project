/**
 * @file streetmap.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy StreetMap
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef STREETMAP_H
#define STREETMAP_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <map>
#include <QString>
#include <QGraphicsTextItem>
#include "street.h"
#include "point.h"
#include "graph.h"
#include "map.h"
#include "station.h"


/**
 * @class      StreetMap
 *
 * @brief      Třída reprezentující mapový podklad aplikace a interakce nad jeho komponenty.
 */
class StreetMap : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    /**
     * @brief      Vytvoří novou instanci třídy StreetMap
     *
     * @param      m     Ukazatel na mapu
     */
    StreetMap(Map *m);
    /**
     * @brief      Destruktor třídy StreetMap
     */
    ~StreetMap();
    
    /**
     * @brief      Funkce pro změnu trasy linky ovlivněné uzavřením ulice.
     *
     * @param[in]  line  Identifikátor linky
     */
    void changeRoute(uint32_t line);

    /**
    * @brief      Funkce zděděná z QT třídy QGraphicsItem.
    *
    */
    QRectF boundingRect() const override;
    /**
     * @brief      Funkce zděděná z QT třídy QGraphicsItem. Vykreslí všechny ulice a stanice.
     *
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

signals:
    /**
     * @brief      Signál pro nastavení aktuální ulice.
     *
     * @param[in]  line  Identifikátor ulice
     */
    void actStreet(uint32_t line);
    /**
     * @brief      Signál pro vyvolání editace trasy linky.
     */
    void editNextRoute();
    /**
     * @brief      Signál pro vyvolání aktualizace nové trasy linky
     *
     * @param[in]  line   Identifikátor linky
     * @param[in]  route  Nová trasa
     */
    void updateLineRoute(uint32_t line, std::vector<Point> route);
    /**
     * @brief      Signál pro vypsání statutové hlášky
     *
     * @param[in]  msg   Nová hláška
     */
    void setStatusLabel(std::string msg);

public slots:
    /**
     * @brief      Slot pro zahájení editačního módu. Mapový podlad reauguje na
     *             stisknutí stanice nebo křižovatky.
     */
    void startEditMode();
    /**
     * @brief      Slot pro ukončení editačního módu. Nově vyznačená trasa je
     *             smazána. Znovu se vykreslí základní podlad mapy.
     */
    void closeEditMode();
    /**
     * @brief      Slot pro uzavření ulice. Ulice je přidána do vektoru
     *             uzavřených ulic @c closed_streets a je vykreslena
     *             přerušovaně.
     */
    void closeStreet();
    /**
     * @brief      Slot pro otevření uzavřených ulic. Z vektoru @c
     *             closed_streets zresetuje původní styl vykreslení.
     */
    void openStreets();
    /**
     * @brief      Slot pro uložení nové trasy linky. Vyvolá signál @c
     *             updateLineRoute(), který je spojen se slotem ve třídě
     *             MainWindow, jež povede uložení nové trasy. Nová trasa je
     *             uložena pouze pokud začíná a končí stanicí.
     */
    void saveRoute();

protected:
	/**
      * @brief      Funkce ze QT třídy QObject. Definuje interakce s mapovým
      *             podkladem. Má dva módy: běžný a editační, které jsou určeny
      *             na základě proměnné @c edit_mode. V běžném režimu reaguje na
      *             stisknutí ulic, v editačním reřimu reaguje na stisknutí
      *             stanic a křižovatek.
      *
      */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    /// Základní pero pro vykreslení grafických komponent
    QPen pen;
    /// Pero pro vykreslení nové trasy
    QPen new_route_pen;
    /// Pero pro vykreslení uzavřených ulic
    QPen closed_street_pen;

    /// Vektor uchovávající grafické komponenty ulic
    std::vector<QGraphicsLineItem *> streets;
    /// Vektor uchovávající grafické komponenty uzavřených ulic
    std::vector<QGraphicsLineItem *> closed_streets;
    /// Vektor uchovávající grafické komponenty stanic
    std::vector<QGraphicsItem *> stations;
    /// Vektor uchovávající uzlů grafu (stanice a křižovatky)
    std::vector<QGraphicsItem *>nodes;
    /// Vektor uchovávající novou trasu
    std::vector<QGraphicsLineItem* > new_route;

    /// Ukazatel na instanci grafu
    Graph * graph;
    /// Ukazatel na instanci mapy
    Map * map;
    /// Promměná reprezentující současný režim. Pokud je true, pak je nastavený
    /// editační režim, jinak je běžný režim.
    bool edit_mode;

    /// Ukazatel na aktuální vybranou ulici
    QGraphicsLineItem * act_street_line;

    /// Proměnná reprezentující existenci počátečního bodu nové trasy. Dokud
    /// není vybraný validní počáteční bod, tj. stanice, je false, jinak true.
    bool start_point_set;
    
    /// Aktuální hodnota vybraného bodu nové trasy
    Point act_point;

    /// Vektor uchovávající body nové trasy
    std::vector<Point> new_route_v;
    /// Identifikátor aktuálně editované linky
    uint32_t act_line;
};

#endif