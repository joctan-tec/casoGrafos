#ifndef INTI 
#define INTI 1
#include "Atomo.h"

class Inti : public Atomo {
    private:

    public:
        Inti(int pId){
            this->setIdAtomo(pId);
            this->setId(pId);
            this->setNombre("Inti");
            this->setMolecula(false);
            this->setOrganismo(false);
            this->setParticipa(false);
        }

};

#endif