#ifndef KATMEO 
#define KATMEO 1
#include "Atomo.h"

class Katmeo : public Atomo {
    private:

    public:
        Katmeo(int pId){
            this->setIdAtomo(pId);
            this->setId(pId);
            this->setNombre("Katmeo");
            this->setMolecula(false);
            this->setOrganismo(false);
            this->setParticipa(false);
        }

};

#endif