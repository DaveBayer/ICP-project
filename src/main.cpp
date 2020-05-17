/**
 * @file main.cpp
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */

/** @mainpage ICP projekt
 * @section DES Popis
 * Nejprve jsme se rozhodli identifikovat základní objekty,
 * se kterými se v implementaci pracovat. Ze zadání jsme usoudili,
 * že vytvoříme třídu pro mapu Map. Měla by obsahovat rozměry mapy a
 * seznam objektů, které na ní leží. Těmito objekty mohou být
 * ulice Street, stanice Station a linka Line. Ulice bude ohraničena dvěma body, bude
 * obsahovat své jméno a své unikátní id. Stanice bude jedním bodem
 * na mapě a bude mít rovněž jméno. Linka bude mít číslo a seznam
 * stanic, kterými projíždí. Dále bylo třeba vytvořit třídu pro
 * snadnou manipulaci s body Point. @n
 * 
 * Po vytvoření mapy by se pak měl vytvořit také její graf. V něm
 * se vytvoří ulice, spočítají jejich průsečíky a přidají stanice.
 * Pak se mohou do grafu zanést linky. Cesty mezi zastávkami se
 * spočítají pomocí algoritmu UCS, aby byly co nejkratší. @n @n
 * 
 * Při návrhu grafického rozhraní bylo třeba brát v potaz logickou
 * funkcionalitu jednotlivých částí simulátoru. Mezi tyto části patří: 
 * - zobrazení mapového podkladu, 
 * - zobrazení animace jednotlivých spojů v různém režimu (bežný, s omezeními),
 * - zobrazení jízdného řádu spoje,
 * - možnost interakce s ulicemi (stupně provozu, uzavření)
 * - a práce se systémovým časem.
 * 
 * Nakonec jsme po zhodnocení situace dospěli k následujícímu návrhu.
 * Hlavní třídou grafického rohraní je třída MainWindow, která dědí
 * ze třídy QMainWindow z frameworku QT. Tato třída je základní
 * komponentou QApplication, která se stará o zobrazení grafické
 * aplikace uživateli. V naší implementaci třídy MainWindow se
 * následně vytváří instance dalších komponent programu. Pro zobrazení
 * textových polí a interaktivních tlačítek jsme ve většině případů
 * použili odpovídající třídy z QT (QLabel,QPushButton,...). Pro rozložení
 * komponent další QT třídy (QGridLayout, QHBoxLayout, QStackedLayout, ...).
 * Veškeré části, které vyžadují komplexnější vykreslování (mapový podklad,
 * animace,...), se pak vykreslují a zobrazují využitím grafických objektů
 * tříd QGraphicsView, QGraphicsScene a QGraphicsItem (opět z frameworku QT). @n
 * 
 * Mapový podklad reprezentuje třída StreetMap. Tato třída pracuje z daty
 * o ulicích a stanicích, které poskytuje třída Map. Tato třída dědí metody
 * ze QT třídy QObject a QGraphicsItem, jež umožují snadno implementovat
 * reakce na stisknutí myši (při vybrání ulice,..) pomocí signálů a slotů
 * jež je typické pro framework QT. Jednotlivé linky jsou v grafickém rozhraní
 * reprezentovány třídou LineObject. Tato třída se stará o vykreslení trasy
 * linky v hlavní grafické scéně a o vypsání názvů jednotlivých linek na pravé
 * straně aplikace. Pro tyto účely jsme vytvořili novou třídu LineLabel
 * rozšiřující třídu QLabel, tak, aby byla schopna zobrazit trasu linky
 * po kliknutí. Pro vykreslení trasy pak slouží funkce LineRoute, která
 * z logických důvodů rozšiřuje třídu QGraphicsItem. @n
 * 
 * V každé instanci třídy
 * LineObject také vznikaní instance třídy TransportVehicle. Tato třída
 * reprezentuje jeden spoj linky. Jedná se opět o třídu rozšiřující
 * QGraphicsItem. V této třídě je pak implementována animace spoje.
 * Pro zobrazení informací o spoji slouží třída Connection. Ta se stará
 * o vytvoření jízdního řádu jednotlivých spojů a vykreslení časové osy
 * s názvy stanic a s časy odjezdů. Instance této třídy je vyvořena ve třídě MainWindow.
 * 
 * @section GUI Grafické rozhraní
 * Práce se simulátorem je ve většině případů velice intuitivní. V základním
 * režimu se uživateli zobrazí přibližně ve středu aplikace mapový podklad
 * zobrazující ulice a stanice. V pravé části aplikace je pak seznam
 * definovaných linek. Pod mapovým podkladem se nachází informační text, který
 * stručně popisuje základní použití aplikace. V levém spodním rohu se nachází
 * systémový čas a ovládací tlačítka času. V pravé spodní části jsou pak
 * tlačítka na ovládání pohledu na grafickou scénu. Pohled je možné oddalovat a
 * přibližovat, popřípadě nastavit na základní hodnotu. Systémový čas je pak
 * možné pomocí tlačítka "Změnit čas" nastavit na libovolný čas. Je také možné
 * jej urychlit nebo zpomalit a tím tak ovllivnit rychlost animace vozidel.
 * Mapový podklad je interaktivní, klinutím na ulici se daná čast zvýrazní a pod
 * mapovým podkladem se objeví tlačítka pro nastavení vlastností ulice. Na ulici
 * je možné nastavit stupeň provozu nebo naopak provoz na ulici úplně vyčistit.
 * Celou ulici je možné uzavřít, což může vést k případné změně režimu aplikace,
 * a sice do režimu editačního. @n
 *
 * Pro všechny linky, které jsou ovlivněny uzavírkou je třeba nastavit objížďnou
 * trasu. To se dá ulělat následujícím způsobem. V první řadě je třeba vybrat
 * počáteční stanici, poté postupným klikáním na křižovatky nebo stanice lze
 * vytvořit novou trasu. Ta musí být opět ukončena stanicí, jinak ji nebude
 * možné tlačítkem "Uložit trasu" uložit. Při volbě nové trasy je také třeba
 * brát ohled na posloupnost nových bodů trasy. Každý nově vybraný bod musí
 * tvořit hranu s posledním vybraným bodem a zároveń nemůže ceta vést přes
 * uzavřenou ulici. Po upravení všech zasažených linek se aplikace vrátí do
 * normálního režimu. @n
 *
 * Další možnou iterakcí s aplikací je zobrazení jízdního řádu spoje po kliknutí
 * na vozidlo. Jízdní řád se zobrazí ve formě osy pod mapovým podkladem společně
 * s názvy jednotlivých stanic a s časy odjezdů z nich. Tyto časy jsou
 * automaticky dopočítané z aktuální trasy daného spoje.
 */

#include <fstream>

#include "error.h"
#include "graph.h"
#include "line.h"
#include "map.h"
#include "point.h"
#include "station.h"
#include "street.h"
#include <QApplication>
#include "mainwindow.h"

std::ifstream fileOpen(const char *name)
{
    std::ifstream f;
    f.open(name, std::ios::in);
    if (!(f.is_open()))
        errExit(1, "File cannot be opened");
    return f;
}

std::vector<Street> getStreets(const char *name)
{
    std::vector<Street> streets;
    std::ifstream f = fileOpen(name);
    while (!f.eof()) {
        Street s;
        f >> s;
        streets.push_back(s);
    }
        
    f.close();
    return streets;
}

std::vector<Station> getStations(const char *name)
{
    std::vector<Station> stations;
    std::ifstream f = fileOpen(name);
    Station s;
    while (f >> s){
        stations.push_back(s);
    }
    f.close();

    return stations;
}

std::vector<Line> getLines(const char *name)
{
    std::vector<Line> lines;
    std::ifstream f = fileOpen(name);
    while (!f.eof()) {
        Line l;
        f >> l;
        lines.push_back(l);
    }
    f.close();
    return lines;
}

int main(int argc, char  *argv[])
{
    
    std::vector<Street> streets = getStreets(argv[1]);
    std::vector<Station> stations = getStations(argv[2]);
    std::vector<Line> lines = getLines(argv[3]);

    Map m(600.f, 600.f, streets, stations);


    m.addLines(lines);
    m.setLinesInGraph();



    QApplication app(argc, argv);
    MainWindow mainWindow(&m);
    mainWindow.setGeometry(200, 200, 1000, 950);

    mainWindow.init();
    mainWindow.show();

    return app.exec();
}
