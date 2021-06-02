#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include <iomanip>
#include <cmath>
#include <initializer_list>

/**
 *  @file Wektor.hh
 * 
 *  Plik zawiera definicje szablonu wektora,
 *  ktroy posiada modyfikowalny rozmiar.
 */

/**
 * @brief Modeluje wektor
 * 
 * Klasa modeluje szablon wektora o możliwym rozmiarze 'Rozmiar'
 * 
 * @tparam Rozmiar zadanego wektora.
 */
template <unsigned int Rozmiar>
class Wektor {

  private:
    /**
     * Tablica jednowymiarowa przechowująca współrzędne wektora.
     */
    double Wsp[Rozmiar];
  
  public:

    /**
     * @brief Konstruktor domyslny zerujacy pola wektora
     */
    Wektor() { for (unsigned int i = 0; i < Rozmiar; ++i) Wsp[i] = 0;}

    Wektor(const Wektor<Rozmiar> &Wek) {(*this) = Wek;}

    ~Wektor() {}

    /**
     * @brief Zwraca wartość modułu między punktami wyrażonymi jako wektory
     */
    double Modul(const Wektor<Rozmiar> &Wek) const;

    /**
     * @brief Przeciążenie operatora indeksującego dla wektora
     */
    const double& operator [] (unsigned int indeks) const;
    double& operator [] (unsigned int indeks);

    /**
     * @brief Przeciążenie operatora dodawania dla wektora
     */
    Wektor<Rozmiar> operator + (const Wektor<Rozmiar> &Skladnik) const;

    /**
     * @brief Przeciążenie operatora odejmowania dla wektora
     */
    Wektor<Rozmiar> operator - (const Wektor<Rozmiar> &Odjemnik) const;

    Wektor<Rozmiar>& operator = (const Wektor<Rozmiar> &Wek) {for (unsigned int i = 0; i < Rozmiar; ++i) Wsp[i] = Wek[i]; return *this;}

};



/**
  *  Metoda zwracajaca odleglosc miedzy dwoma punktami reprezentowanymi jako wektory.
  *
  *  @param[in] Wek - zawiera drugi wektor - punkt wzgledem ktorego liczymy modul.
  * 
  *  @pre
  *   Obiekt i Wek musza byc prawidlowo zdefiniowanymi wektorami.
  *  
  *  @retval odleglosc miedzy punktami wyrazonymi jako wektory zaczepionymi
  *   w srodku ukladu wspolrzednych.
*/
template <unsigned int Rozmiar>
double Wektor<Rozmiar>::Modul(const Wektor<Rozmiar> &Wek) const {
    Wektor<Rozmiar> Tymcz = *this - Wek;;
    double Suma_kwadr = 0;
    for (unsigned int i = 0; i < Rozmiar; ++i)
     Suma_kwadr += pow(Tymcz[i], 2); 
    return sqrt(Suma_kwadr);
    return 0;
}

/**
  *  Przeciazenia operatora indeksujacego dla wektora, zwraca wskazane pole wektora.
  *  Jezeli indeks bedzie nieprawidlowy, metoda zakonczy dzialanie programu.
  *
  *  @param[in] indeks zwracanej wspolrzednej wektora. 
  * 
  *  @pre
  *   indeks musi byc rowny 0 lub 1, gdyz rozwazamy wektor o dwoch wspolrzednych
  * 
  *  @retval element wektora, zgodnie z podanym indeksem.
*/
template <unsigned int Rozmiar>
const double& Wektor<Rozmiar>::operator [] (unsigned int indeks) const {
    if (indeks > Rozmiar)  {
        std::cerr << "Nieprawidlowy indeks odwolania do elementu wektora" << std::endl;
        exit(0);
    }
    return Wsp[indeks];
}
template <unsigned int Rozmiar>
double& Wektor<Rozmiar>::operator [] (unsigned int indeks) {
    if (indeks > Rozmiar)  {
        std::cerr << "Nieprawidlowy indeks odwolania do elementu wektora" << std::endl;
        exit(0);
    }
    return Wsp[indeks];
}

/**
  *  Przeciazenie operatora dodawania dla dwoch wektorow, danego obiektu
  *  oraz wektora podanego jako parametr.
  *
  *  @param[in] Skladnik - wektor, drugi obok obiektu skladnik dodwania
  *
  *  @pre
  *   Obiekt i Skladnik musza byc prawidlowo zdefiniowanymi wektorami.
  *
  *  @retval wektor bedacy suma obiektu i parametru.
*/
template <unsigned int Rozmiar>
Wektor<Rozmiar> Wektor<Rozmiar>::operator + (const Wektor<Rozmiar> &Skladnik) const {
   Wektor<Rozmiar> Wynik;
   for (unsigned int i = 0; i < Rozmiar; ++i)
      Wynik[i] = Wsp[i] + Skladnik.Wsp[i];
   return Wynik;
}

/**
  *  Przeciazenie operatora odejmowania dla dwoch wektorow, danego obiektu
  *  oraz wektora podanego jako parametr.
  *
  *  @param[in] Skladnik - wektor, drugi obok obiektu skladnik odejmowania
  *
  *  @pre
  *   Obiekt i Skladnik musza byc prawidlowo zdefiniowanymi wektorami.
  *
  *  @retval wektor bedacy roznica obiektu i parametru.
*/
template <unsigned int Rozmiar>
Wektor<Rozmiar> Wektor<Rozmiar>::operator - (const Wektor<Rozmiar> &Skladnik) const {
   Wektor<Rozmiar> Wynik;
   for (unsigned int i = 0; i < Rozmiar; ++i)
      Wynik[i] = this->Wsp[i] - Skladnik[i];
   return Wynik;
}

/**
  *  Funkcja wczytuje wektor postaci (x_1 x_2 x_3 .. x_n) ze strumienia Strm
  *  (liczba elementów uzalezniona jest od wielkosci wektora) i wpisuje go 
  *  do obiektu typu Wektor Wek. 
  *  Jezeli wprowadzono wektor nieprawidlowo, ustawi flage failbit.
  *
  *   @param[in] Strm - strumien z ktorego wczytujemy wektor
  *   @param[in] Wek - obiekt do ktorego wczytujemy wektor
  *
  *  @pre
  *   Prawidlowo zapisany wektor - musi byc postaci (x_1 x_2 x_3 .. x_n), gdzie x_1-x_n sa liczbami
  *   rzeczywistymi, a liczba elementów uzalezniona jest od wielkosci wektora.
  *   Jezeli nie bedzie to spelnione zostanie ustawiona flaga bledu.
  *  @post 
  *   Wektor wczytany w obiekt Wek.
*/
template <unsigned int Rozmiar>
std::istream& operator >> (std::istream &Strm, Wektor<Rozmiar> &Wek)
{
    for (unsigned int i = 0; i < Rozmiar; ++i)
      Strm >> Wek[i];

    return Strm;
}

/**
  *  Funkcja wypisuje wspolrzedne wektora Wek 2D na strumien Strm w postaci (x,y)
  *
  *   @param[in] Strm - strumien na ktory wypisujemy wektor
  *   @param[in] Wek - obiekt z ktorego wczytujemy wektor
  *
  *  @pre
  *   Prawidlowy strumien i wektor Wek.
  *  @post
  *   Wypisany zostaje wektor w postaci (x_1 x_2 x_3 .. x_n), liczba elementow zalezy
  *   od rozmiaru wektora.
  * 
*/
template <unsigned int Rozmiar>
std::ostream& operator << (std::ostream &Strm, const Wektor<Rozmiar> &Wek)
{
  for (unsigned int i = 0; i < Rozmiar; ++i)
    Strm << Wek[i] << " ";

  return Strm;
} 


#endif
