#ifndef _INTI_ 
#define _INTI_ 1
#include "Atomo.h"

class Inti : public Atomo {
    private:
        int id;
        string nombre;

    public:
        Inti(int pId, string pNombre){
            this->setIdAtomo(pId);
            this->setId(pId);
            this->setNombre(pNombre);
        }

};

#endif