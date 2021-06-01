#ifndef MACIERZ_HH
#define MACIERZ_HH

/**
 *  @file
 *  @brief Definiuje szablon wektor
 * 
 *  Zostaje zdefiniowany szablon macierz o możliwym rozmiarze 
 *  typu unsigned int, metody pozwalajace na operacje na tej macierzy
 *  oraz przeciazenia strumieni wyjscia i wejscia do wypisywania macierzy.
 */

#include <iostream>
#include <cmath>
#include "Wektor3D.hh"


/**
 *  @brief Modeluje macierz kwadratową
 * 
 *  Klasa modeluje szablon macierzy kwadratowej o mozliwym rozmiarze Rozmiar.
 *  Jej atrybutami są elementy umieszczone w tablicy 'Rozmiar'x'Rozmiar'.
 * 
 *  @tparam Rozmiar zadanej macierzy kwadratowej.
 */
template <unsigned int Rozmiar>
class Macierz {

     /**
      * Tablica dwuwymiarowa przechowyjaca elementy macierzy.
      */
    double Elem[Rozmiar][Rozmiar];
    
  public:
    /**
     * @brief Konstruktor domyslny
     * Inicjuje macierz jednostkowa.
     */
    Macierz();

    /**
     * @brief Przeciazenie operatora indeksujacego dla macierzy
     */
    double operator () (unsigned int wiersz, unsigned int kolumna) const;
    
    /**
     * @brief Metoda umozliwiajaca przypisanie wartosci elementowi macierzy
     */
    void UstawWar(unsigned int wiersz, unsigned int kolumna, double wartosc);

    /**
     * @brief Przeciazenie operatora mnozenia macierzy przez wektor
     */
    Wektor<Rozmiar> operator * (const Wektor<Rozmiar> &Wek) const;

    /**
     * @brief Przeciazenie operatora mnozenia macierzy przez macierz
     */
    Macierz<Rozmiar> operator * (const Macierz<Rozmiar> &Mac) const; 
    

};

/**
 * Tworzy macierz jedostkową, tzn mającą na diagonalii same '1'
 * a na reszczie swoich pól '0'.
 * 
 * @post Zainicjalizowana macierz jako jednostkowa.
 */
template <unsigned int Rozmiar>
Macierz<Rozmiar>::Macierz() {

   for (unsigned int i = 0; i < Rozmiar; ++i) {
      for (unsigned int j = 0; j < Rozmiar; ++j) {
         if(i == j) Elem[i][j] = 1;
         else Elem[i][j] = 0;
      }
   }
}

/**
  *  Przeciazenie operatora indeksujacego dla macierzy, zwraca wskazane pole macierzy.
  *  Jezeli indeks bedzie nieprawidlowy, metoda zakonczy dzialanie programu.
  *
  *  @param wiersz - wiersz zwracanego elementu macierzy
  *  @param kolumna - kolumna zwracanego elementu macierzy
  * 
  *  @pre
  *   Wiersz i kolumna zawierac sie musza w przedziale <0,Rozmiar)
  *
  * @retval element - zwrócony zostaje element macierzy, zgodnie z podanymi parametrami.
*/
template <unsigned int Rozmiar>
double Macierz<Rozmiar>::operator () (unsigned int wiersz, unsigned int kolumna) const {
   
   if (wiersz > Rozmiar || kolumna > Rozmiar) {
      std::cerr << "Nieprawidlowy indeks macierzy." << std::endl;
      exit(0);
   }
   return Elem[wiersz][kolumna];
}

/**
 * Metoda umozliwiajaca przypisanie wartosci elementowi macierzy 
 * dzieki podanym danym jako parametry.
 * 
 * @param wiersz - Wiersz, w ktorym lezy element
 * @param kolumna - Kolumna, w ktorej lezy element
 * @param wartosc - Wartosc, ktora przypisujemy elementowi scharakteryzownemu przez dwa poprzednie parametry.
 * 
 * @pre Prawidlowo podane numery wiersza i kolumny - nie moga przekraczac rozmiaru macierzy.
 * @post Zadany element macierzy majacy wartosc podana jako parametr.
 */
template <unsigned int Rozmiar>
void Macierz<Rozmiar>::UstawWar(unsigned int wiersz, unsigned int kolumna, double wartosc) {
   if (wiersz > Rozmiar || kolumna > Rozmiar) {
      std::cerr << "Nieprawidlowy indeks macierzy." << std::endl;
      exit(0);
   }
   Elem[wiersz][kolumna] = wartosc;
}

/**
  *  Przeciazenie operatora mnozenia macierzy przez wektor, jako wynik zwraca wektor.
  *  Jest to mnozenie, gdzie macierz jest z prawej strony a wektor z lewej.
  *
  *  @param Wek - wektor, przez ktory mnozymy macierz
  *
  *  @pre Poprawnie zdefiniowana macierz i wektor.
  *
  *  @retval wektor bedacy wynikiem mnozenia macierzy oraz podanego wektora.
*/
template <unsigned int Rozmiar>
Wektor<Rozmiar> Macierz<Rozmiar>::operator * (const Wektor<Rozmiar> &Wek) const {

   Wektor<Rozmiar> Wynik;
   for (unsigned int i = 0; i < Rozmiar; ++i) {
      double Suma = 0;
      for (unsigned int j = 0; j < Rozmiar; ++j)
      Suma += Elem[i][j] * Wek[j];
      Wynik[i] = Suma;
   }
   return Wynik;
}

/**
  *  Przeciazenie operatora mnozenia macierzy przez macierz, jako wynik zwraca macierz.
  *  Jest to mnozenie, gdzie macierz obiektu jest z prawej strony a druga podana z lewej.
  *
  *  @param Mac - macierz, przez ktory mnozymy macierz
  *
  *  @pre Poprawnie zdefiniowane kwadratowe macierze o takim samym rozmiarze.
  *
  *  @retval macierz bedacy wynikiem mnozenia macierzy kwadratowych tego samego rozmiaru.
*/
template <unsigned int Rozmiar>
Macierz<Rozmiar> Macierz<Rozmiar>::operator * (const Macierz<Rozmiar> &Mac) const {

   Macierz<Rozmiar> Wynik;
   for (unsigned int i = 0; i < Rozmiar; ++i) {
      for (unsigned int j = 0; j < Rozmiar; ++j) {
         double Suma = 0;
         for (unsigned int k = 0; k < Rozmiar; ++k)
            Suma += this->Elem[i][k] * Mac.Elem[k][j];
      Wynik.Elem[i][j] = Suma;
      }
   }
   return Wynik;
}

/**
  *  Funkcja wypisuje macierz w postaci graficznej na zadane wyjscie.
  *
  *  @param Strm - strumien na ktory wypisujemy macierz
  *  @param Mac - obiekt z ktorego wczytujemy macierz
  *
  *  @pre Prawidlowy strumien i macierz Mac.
  *  @post Macierz wypisana w postaci graficznej na zadane wyjscie.
*/
template <unsigned int Rozmiar>
std::ostream& operator << (std::ostream &Strm, const Macierz<Rozmiar> &Mac) {

   for (unsigned int i = 0; i < Rozmiar; ++i) {
      for (unsigned int j = 0; j < Rozmiar; ++j)
         Strm << std::setw(8) << std::fixed << std::setprecision(5) << Mac(i,j) << "\t";
      Strm << std::endl;
   }
   return Strm;
}


#endif
