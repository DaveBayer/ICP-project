/**
 * @file lineroute.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy LineRoute
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __LINEROUTE_H__
#define __LINEROUTE_H__

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QGraphicsScene>
#include "graph.h"
#include "street.h"
#include "point.h"


/**
 * @class      LineRoute
 * @brief      Třída reprezentující grafickou reprezentaci trasy linky.
 */
class LineRoute :  public QObject, public QGraphicsItem
{
	Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    /**
     * @brief      Vytvoří novou instanci třídy LineRoute. Nastaví pero pro
     *             vykreslení trasy.
     *
     * @param      g     Ukazatel na graf
     * @param[in]  line  Identifikační číslo linky
     */
    LineRoute(Graph *, uint32_t);
    /**
     * @brief      Destruktor třídy LineRoute.
     */
    ~LineRoute();

    /**
     * @brief      Funkce zděděná z QT třídy QGraphicsItem.
     *
     */
    QRectF boundingRect() const override;
    /**
     * @brief      Funkce zděděná z QT třídy QGraphicsItem. Vykresluje trasu
     *             linky použitím grafického objektu QPainterPath.
     *
     * @param      painter  The painter
     * @param[in]  option   The option
     * @param      widget   The widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


public slots:
	/**
     * @brief      Slot pro zobrazení trasy linky.
     */
    void showRoute();
    /**
     * @brief      Slot pro skrytí trasy linky.
     */
    void hideRoute();
    /**
     * @brief      Slot pro zobrazení, respektive skrytí linky.
     */
    void toggleRoute();
private:
    /// Pero pro vykreslení trasy linky
    QPen pen;
    /// Ukazatel na instanci třídy @p Graph
    Graph * graph;
    /// Identifikační číslo linky
    uint32_t line;
    /// Vektor uchovávající trasu linky.
    std::vector<std::vector<Point>> route;
};

#endif // __LINEROUTE_H__