#ifndef _GALEA_ 
#define _GALEA_ 1
#include "Atomo.h"

class Galea : public Atomo {
    private:
        int id;
        string nombre;

    public: 
        Galea(int pId, string pNombre){
            this->setIdAtomo(pId);
            this->setId(pId);
            this->setNombre(pNombre);
        }

};

#endif