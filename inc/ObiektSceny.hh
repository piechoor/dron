#ifndef OBIEKTSCENY_HH
#define OBIEKTSCENY_HH

#include <memory>
#include "BrylaGeometryczna.hh"
#include "Dron.hh"

class ObiektSceny : public Bryla {

    public:
        virtual bool SprKolizje(std::shared_ptr<Dron> DronKol);
        
};

#endif