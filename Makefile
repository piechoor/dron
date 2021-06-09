TASKNO=5
APP=sterowanie-dronem
TASKDIR=${HOME}/edu/po/zad/z${TASKNO}

__start__: obj dat ./${APP}
	rm -f core.* core; ./${APP}

# Tworzy katalog "obj" gdy go nie ma
# 
obj:
	mkdir obj

dat:
	mkdir dat


./${APP}: obj/main.o obj/lacze_do_gnuplota.o obj/Macierz3x3.o obj/Prostopadloscian.o obj/Wektor3D.o obj/Dron.o obj/BrylaGeometryczna.o obj/Graniastoslup6.o obj/Scena.o obj/Menu.o obj/Przeszkoda_gora.o obj/Przeszkoda_gran.o obj/Przeszkoda_plaskowyz.o obj/ObiektSceny.o
	g++ -o ./${APP} obj/main.o obj/lacze_do_gnuplota.o obj/Macierz3x3.o obj/Prostopadloscian.o obj/Wektor3D.o obj/Dron.o obj/BrylaGeometryczna.o obj/Graniastoslup6.o obj/Scena.o obj/Menu.o obj/Przeszkoda_gora.o obj/Przeszkoda_gran.o obj/Przeszkoda_plaskowyz.o obj/ObiektSceny.o


ext: ./${APP}_rozszerzony
	rm -f core.* core; echo "2i 1+3.1i 2 ? / + ?" | ./${APP}_rozszerzony


obj/main.o: src/main.cpp inc/lacze_do_gnuplota.hh 
	g++ -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/Macierz3x3.o: src/Macierz3x3.cpp inc/Macierz3x3.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Macierz3x3.o src/Macierz3x3.cpp

obj/Menu.o: src/Menu.cpp inc/Menu.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Menu.o src/Menu.cpp

obj/Prostopadloscian.o: src/Prostopadloscian.cpp inc/Prostopadloscian.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Prostopadloscian.o src/Prostopadloscian.cpp

obj/Wektor3D.o: src/Wektor3D.cpp inc/Wektor3D.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Wektor3D.o src/Wektor3D.cpp

obj/Dron.o: src/Dron.cpp inc/Dron.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Dron.o src/Dron.cpp

obj/BrylaGeometryczna.o: src/BrylaGeometryczna.cpp inc/BrylaGeometryczna.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/BrylaGeometryczna.o src/BrylaGeometryczna.cpp

obj/Graniastoslup6.o: src/Graniastoslup6.cpp inc/Graniastoslup6.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Graniastoslup6.o src/Graniastoslup6.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Scena.o src/Scena.cpp

obj/Przeszkoda_gora.o: src/Przeszkoda_gora.cpp inc/Przeszkoda_gora.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Przeszkoda_gora.o src/Przeszkoda_gora.cpp

obj/Przeszkoda_gran.o: src/Przeszkoda_gran.cpp inc/Przeszkoda_gran.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Przeszkoda_gran.o src/Przeszkoda_gran.cpp

obj/Przeszkoda_plaskowyz.o: src/Przeszkoda_plaskowyz.cpp inc/Przeszkoda_plaskowyz.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/Przeszkoda_plaskowyz.o src/Przeszkoda_plaskowyz.cpp

obj/ObiektSceny.o: src/ObiektSceny.cpp inc/ObiektSceny.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/ObiektSceny.o src/ObiektSceny.cpp

	
clean:
	rm -f obj/* ./${APP} core.* core

${TASKDIR}:
	mkdir -p ${TASKDIR}/bin.diablo ${TASKDIR}/bin.panamint

__TARGET__:
	if [ ! "${HOST}" = "diablo" ] && [ ! "${HOST}" = "panamint" ]; then exit 1; fi

export: __TARGET__ ./${APP}  ./${APP}_rozszerzony ${TASKDIR}
	mv ${APP} ${APP}_rozszerzony ${HOME}/edu/po/zad/z${TASKNO}/bin.${HOST}/

help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make ext    - tworzenie i uruchomienie aplikacji w wersji rozszerzonej"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make help   - wyswietla niniejsza informacje"
	@echo
