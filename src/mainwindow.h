/**
 * @file mainwindow.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy MainWindow
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QStackedLayout>
#include <QTimer>
#include <QTime>
#include <map>
#include <QPushButton>
#include <QTimeEdit>

#include "streetmap.h"
#include "line.h"
#include "linelabel.h"
#include "lineroute.h"
#include "transportvehicle.h"
#include "lineobject.h"
#include "graph.h"
#include "map.h"
#include "connection.h"


/**
 * @class      MainWindow
 *
 * Třída reprezentující grafické rozhraní aplikace.
 *
 * Grafické rozhraní je implementováno pomocí frameworku QT. Třída MainWindow
 * dědí vlastnosti QT třídy QMainWindow, která je hlavní komponentou
 * QApplication, jež obstarává základní grafické úkony. Třída se stará o
 * vytvoření veškerých základních grafických komponent aplikace jako jsou:
 *      - označení linek
 *      - funkční tlačítka
 *      - rozložení komponent
 *      - ...
 *
 * Dále obstarává další funkce, které jsou taktéž specifické pro grafické
 * rozhraní:
 *      - systémový čas
 *      - tvorba jednotlivých spojů
 *      - animace vozidel
 *      - ...
 *
 * Instatce této třídy je vytvořena hlavním modulem @c main.cpp, který je
 * následně zodpovědný za správnou inicializaci tohoto objektu. Část instance je
 * nainicializována již v konstruktoru, pro úplné vytvoření tohoto objektu je
 * však třeba ještě volat jeho funkci init(), která se stará vytvoření částí
 * grafických komponent, které nešli vytvořit již v kontruktoru.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

   /**
    * Vytvoří novou instanci třídy MainWindow
    *
    * Dochází zde k volání privátních funcí třídy:
    *  - @c createLayouts()
    *  - @c createButtons()
    *  - @c createLabels()
    *  - @c createScenes()
    *  - @c createViews()
    *
    * @param      m     Ukazatel na instanci třídy Map
    */
   MainWindow(Map *m);
   /**
    * @brief      Destruktor třídy MainWindow
    */
   ~MainWindow();
   /**
    * Funkce pro inicializaci instance třídy MainWindow.
    *
    * Dochází zde k volání privátních funkcí pro vytvoření komponent grafického
    * rozhraní aplikace. Volají se funkce:
    *   - @c createSystemClock()
    *   - @c createStreetMap()
    *   - @c createLines()
    *   - @c createMainLayout()
    *   - @c connectButtons()
    */
   void init();

private slots:
    /**
     * @brief      Slot pro aktualizaci zobrazení aktuaálního systémového času.
     */
    void updateClock();
    /**
     * @brief      Slot pro přiblížení hlavní grafické scény.
     */
    void zoomIn();
    /**
     * @brief      Slot pro oddálení hlavní grafické scény.
     */
    void zoomOut();
    /**
     * @brief      Slot pro nastavené základního pohledu hlavní grafické scény.
     */
    void defaultZoom();
    /**
     * @brief      Slot pro nastavení systémového času.
     */
    void setTime();
    /**
     * @brief      Slot pro zastavené, respektive spuštění, systémového času
     */
    void toggleClock();
    /**
     * @brief      Slot pro zrychlení systémového času.
     */
    void fasterClock();
    /**
     * @brief      Slot pro zpomalení systémového času.
     */
    void slowerClock();
    /**
     * @brief      Slot pro nastavení aktuálně vybrané ulice.
     *
     * @param[in]  s_id  Identifikátor ulice @c Street
     */
    void actStreet(uint32_t s_id);
    /**
     * @brief      Slot pro zvýšení provozu na aktuální ulici @c act_street
     */
    void addTraffic();
    /**
     * @brief      Slot pro vyčištění provozu na ulici.
     */
    void clearTraffic();
    /**
     * @brief      Slot pro nastavení změny trasy linky.
     */
    void changeLineRoute();
    /**
     * @brief      Slot pro získání linek, kterých se týká uzavření ulice.
     */
    void getCollidingLines();
    /**
     * @brief      Slot pro aktualizování trasy linky.
     *
     * @param[in]  line   Identifikátor linky
     * @param[in]  route  Vektor bodů nové trasy
     */
    void updateLineRoute(uint32_t line, std::vector<Point> route);
    /**
     * @brief      Slot pro otevření uzavřených ulic.
     */
    void openStreets();
    /**
     * @brief      Slot pro získání jízdního řádu daného spoje.
     *
     * @param[in]  line_id  Identifikátor linky
     * @param      vehicle  Ukazatel na daný spoj
     */
    void getConnectionInfo(uint32_t line_id,TransportVehicle * vehicle);
    /**
     * @brief      Slot pro nastavení statusové informace.
     *
     * @param[in]  msg   Zpráva, která se má zobrazit
     */
    void setStatusLabel(std::string msg);
    /**
     * @brief      Slot pro zahájení editačního módu.
     */
    void startEditMode();
    /**
     * @brief      Slot pro zavření nastavení ulice.
     */
    void closeStreetControl();



signals:
    /**
     * @brief      Signál reprezentující jeden tik systémových hodin
     *
     * @param[in]  speed  Koeficient rychlosti hodin
     */
    void timeChanged(float);
    /**
     * @brief      Signál pro zastavení animace vozidel.
     */
    void stopAnimation();
    /**
     * @brief      Signál pro spuštění animace vozidel.
     */
    void resumeAnimation();

    /**
     * @brief      Signál pro ukončení editačního módu.
     */
    void closeEditMode();

private:
    /**
     * @brief      Funkce pro vytvoření rozložení grafických komponent.
     */
    void createLayouts();
    /**
     * @brief      Funkce pro vytvoření tlačítek aplikace.
     */
    void createButtons();
    /**
     * @brief      Funkce pro vytvoření textových označení aplikace.
     */
    void createLabels();
    /**
     * @brief      Funkce pro vytvoření grafických scén.
     */
    void createScenes();
    /**
     * @brief      Funkce pro vytvoření grafických pohledů.
     */
    void createViews();
    /**
     * @brief      Funkce pro vytvoření mapového podkladu.
     */
    void createStreetMap();
    /**
     * @brief      Funkce pro vytvoření objektů linek.
     */
    void createLines();
    /**
     * @brief      Funkce pro vytvoření systémového času.
     */
    void createSystemClock();
    /**
     * @brief      Funkce pro dotvoření rozložení grafických komponent v aplikaci.
     */
    void createMainLayout();
    /**
     * @brief      Funkce pro propojení události stisktnutí tlačítka s příslušným slotem.
     */
    void connectButtons();


    // Graphics
    /// Základná grafincký pohled
    QGraphicsView * view;
    /// Grafincký pohled na jízdní řád spoje
    QGraphicsView * connectionView;

    /// Základní grafická scéna
    QGraphicsScene * scene;
    /// Grafická scéna pro jízdní řád spoje  
    QGraphicsScene * connectionScene;
    
    /// Časovač určující tik systémových hodin
    QTimer * sys_clock;
    /// Systémový čas
    QTime * time;
    /// Editační pole pro změnu času
    QTimeEdit * changeTime_e;
    /// Proměnná určující stav systémových hodin. True pokud čas běží, jinak false.
    bool clock_state = true;

    // Labels
    /// Zobrazení systémového času
    QLabel * time_l;
    /// Zobrazení základních informací o aplikaci
    QLabel * info_l;
    /// Zobrazení informací o editačním módu
    QLabel * editInfo_l;
    /// Zobrazení názvu ulice
    QLabel * street_l;
    /// Zobrazení informací o ulici
    QLabel * streetInfo_l;
    /// Zobrazení statutové hlášky aplikace
    QLabel * status_l;


    // Buttons
    /// Tlačítko pro přiblížení grafického pohledu
    QPushButton * zoomIn_b;
    /// Tlačítko pro oddálení grafického pohledu
    QPushButton * zoomOut_b;
    /// Tlačítko pro nastavení základního pohledu grafického pohledu
    QPushButton * zoomDefault_b;
    /// Tlačítko pro změnu času
    QPushButton * changeTime_b;
    /// Tlačítko pro nastavení nového času
    QPushButton * setTime_b;
    /// Tlačítko pro zastavení, respektive spuštění, času
    QPushButton * pauseResumeTime_b;
    /// Tlačítko pro zrychlení času
    QPushButton * faster_b;
    /// Tlačítko pro zpomalení času
    QPushButton * slower_b;

    /// Tlačítko pro přidání provozu na ulici
    QPushButton * addTraffic_b;
    /// Tlačítko pro vyčištění provozu na ulici
    QPushButton * clearTraffic_b;
    /// Tlačítko pro uzavření ulice
    QPushButton * closeStreet_b;
    /// Tlačítko pro zavření informací o ulici
    QPushButton * closeStreetControl_b;
    /// Tlačítko pro otevření všech uzavřených ulic
    QPushButton * openStreets_b;
    /// Tlačítko pro uložení nové trasy
    QPushButton * saveNewRoute_b;
    /// Tlačítko pro zrušení uzavření ulice
    QPushButton * cancelstreetclose_b;

    /// Vektor uchovávající ukazatele na objekty linek 
    std::vector<LineObject *> lines;
    /// Vektor uchovávající identifikátory linek, kolidujících s uzavřenou ulicí
    std::vector<uint32_t> colliding_lines;

    /// Ukazatel na instanci třídy Connection
    Connection * connection_info;
    /// Ukazatel na mapový podklad
    StreetMap *sm;
    /// Ukazatel na graf
    Graph * graph;
    /// Ukazatel na mapu
    Map * map;

    /// Vektor uchovávající body aktuálně vybrané ulice
    std::vector<Point> act_street;

    // Layout
    /// Ukazatel na hlavní rozložení aplikace
    QGridLayout * mainLayout_l;
    /// Ukazatel na základní rozložení kontrolních prvků aplikace
    QGridLayout * mainGrid_l;
    /// Ukazatel na editační rozložení prvků aplikace
    QGridLayout * editGrid_l;
    /// Ukazatel na zásobníkové rozložení 
    QStackedLayout * main_l;
    /// Ukazatel na rozložení uchovávající názvy linek
    QVBoxLayout * lineLabels_l;
    /// Ukazatel na rozložení prvků měnící grafický pohled
    QHBoxLayout * viewControl_l;
    /// Ukazatel na rozložení obsahující ovladače systémového času
    QHBoxLayout * timeControl_l;
    /// Ukazatel na rozložení obsahující nastavení ulice
    QGridLayout * streetControl_l;
    /// Ukazatel na zásobníkové rozložení uchovávající kontrolní rozložení
    QStackedLayout * controlView_l;
    /// Ukazatel na rozložení informacích spoje
    QHBoxLayout * connection_l;

    /// Ukazatel na objekt uchovávající rozložení nastavení ulice
    QWidget * streetControl_w;
    /// Ukazatel na objekt uchovávající rozložení nastavení času
    QWidget * timeControl_w;
    /// Ukazatel na objekt uchovávající rozložení nastavení nastavení pohledu
    QWidget * viewControl_w;
    /// Ukazatel na objekt uchovávající hlavní rozložení
    QWidget * mainGrid_w;
    /// Ukazatel na objekt uchovávající editační rozložení
    QWidget * editGrid_w;
    /// Ukazatel na objekt uchovávající rozložení s informacemi o spoji
    QWidget * connection_w;


    const std::string app_information_str = "Simulace pohybu hromadné dopravy.\n"
                                            "\n"
                                            "Kliknutím na ulici v mapě se otevře nabídka s nastavením ulice.\n"
                                            "Kliknutím na spoj (vozidlo) se objeví jízdní  řád daného spoje.\n"
                                            "Klinutím na název linky v pravé části aplikace se zvýrazní trasa dané linky.\n"
                                            "V levé spodní části se nachází systémový čas. Ten je možné změnit klinutím na tlačítko Změnit čas, popřípadě pozastavit, či změnit rychlost.\n"
                                            "V pravé spodní části se nachází tlačítka pro přiblížení, oddálení a nastavení základního pohledu na mapu.\n";
    const std::string edit_route_str = "Pro navolení objíždné trasy linky je třeba manuálně naklikat novou trasu celé linky.\n"
                                       "Nová trasa musí začínat a končit stanicí.\n"
                                       "Stanice jsou na mapě znázorněny čtverci, křižovatky kružnicemi.\n"
                                       "Každý nový bod trasy musí tvořit hranu s bodem předchozím.\n"
                                       "Kliknutím na název linky se skryje, resp. zobrazí, její zvýrazněná trasa.\n";
    const std::string traffic_c_str = "Stupeň provozu: ";
};

#endif // __MAINWINDOW_H__