#include "Prostopadloscian.hh"

using namespace std;


/**
 * Tworzy i ustawia jako nazwe robocza bryly nazwe wedlug podanych parametrow.
 * 
 * @param[in] NrDrona - numer drona wystepujacy w stworzonej nazwie
 */
void Prostopadloscian::UstawNazwe_Roboczy(unsigned int NrDrona) {
    ostringstream StrWyj;
    StrWyj << "dat/PlikRoboczy_Dron" << NrDrona << "_Korpus.dat";
    Nazwa_BrylaRobocza = StrWyj.str();
}