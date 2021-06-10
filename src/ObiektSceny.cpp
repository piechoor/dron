#include "ObiektSceny.hh"

using namespace std;

bool ObiektSceny::SprKolizje(const Wektor3D &Polozenie, double Promien) {
    cerr << "Nie udalo sie sprawdzic kolizji dla parametrow: " << endl
    << "Polozenie: " << Polozenie << endl
    << "Promien: " << Promien << endl;
    exit(0);
    return 0;
}