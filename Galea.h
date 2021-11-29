#ifndef GALEA 
#define GALEA 1
#include "Atomo.h"

class Galea : public Atomo {
    private:

    public: 
        Galea(int pId){
            this->setIdAtomo(pId);
            this->setId(pId);
            this->setNombre("Galea");
            this->setMolecula(false);
            this->setOrganismo(false);
            this->setParticipa(false);
        }

};

#endif