Název:	ICP projekt
Autoři:	David Bayer (xbayer09)
		Michal Szymik (xszymi00)

Adresářová struktura:
	./doc/* - obsahuje vygenerovanou dokumentaci příkazem make doxygen
	./examples/* - obsahuje příklady
	./src/*.cpp, ./src/*.hpp - zdrojové soubory
	./src/icp.pro - projektový soubor pro qmake
	./doxyfile - soubor s konfigurací pro vygenerování dokumentace
	./Makefile - soubor Makefile
./README.txt

Příkazem make icp se vytvoří program icp. Ten pro správný chod očekává 3 soubory.

První obsahuje ulice ve formátu:

x1 y1	x2 y2	jmeno_ulice

x{1, 2} a y{1, 2} jsou souřadnice počátečního
a koncového bodu ulice a jmeno_ulice její jméno.
Očekává se jedna ulice na řádek.


Druhý obsahuje stanice ve formátu:

x y 	jmeno_stanice

x a y jsou souřadnice stanice a jmeno_stanice její jméno.
Očekává se jedna stanice na řádek.


Třetí obsahuje linky ve formátu:

jmeno_stanice (jmeno_stanice)+
(časy_odjezdu_z_výchozí_stanice)+
(časy_odjezdu_z_konečné_stanice)+


Jména stanic musí být alespoň 2, časy odjezdu jsou očekávány
v sekundách od času 0. Jedna linka takto zabere 3 řádky.



Program je možno vyzkoušet příkazem make run, kdy se program
spustí se vstupy ze složky examples.
