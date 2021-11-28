#ifndef _KATMEO_ 
#define _KATMEO_ 1
#include "Atomo.h"

class Katmeo : public Atomo {
    private:
        int id;
        string nombre;

    public:
        Katmeo(int pId, string pNombre){
            this->setIdAtomo(pId);
            this->setId(pId);
            this->setNombre(pNombre);
        }

};

#endif