#include "BrylaGeometryczna.hh"

#define ILOSC_WIERZ_LINII_TWORZACEJ 4

using namespace std;

/**
  *  Metoda skalujaca podany jako parametr wierzcholek zgodnie ze skala
  *  zawarta w polach klasy obiekt.
  *
  *  @param[in] Wierzch - wierzcholek, ktory poddajemy skalowaniu
  * 
  *  @pre Zainicjowana skala w polu klasy
  *  
  *  @retval - zwraca przeskalowany wektor
*/
const Wektor3D Bryla::Skaluj(const Wektor3D &Wierzch) const {
    Wektor3D Tymcz;
    for (int i = 0; i < 3; ++i) Tymcz[i] = this->Skala[i] * Wierzch[i];
    return Tymcz;
}