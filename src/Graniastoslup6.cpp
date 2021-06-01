#include "Graniastoslup6.hh"

using namespace std;

/**
 * Tworzy i ustawia jako nazwe robocza bryly nazwe wedlug podanych parametrow.
 * 
 * @param[in] NrDrona - numer drona wystepujacy w stworzonej nazwie
 * @param[in] NrRotora - numer rotora wystepujacy w stworzonej nazwie
 */
void Graniastoslup6::UstawNazwe_Roboczy(unsigned int NrDrona, unsigned int NrRotora) {
    ostringstream StrWyj;
    StrWyj << "dat/PlikRoboczy_Dron" << NrDrona << "_Rotor" << NrRotora + 1 << ".dat";
    Nazwa_BrylaRobocza = StrWyj.str();
}