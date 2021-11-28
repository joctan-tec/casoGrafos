#ifndef _ATOMO_ 
#define _ATOMO_ 1

#include <string>
#include "INodo.h"

using namespace std;

class Atomo : public INodo{
    protected:
        int idAtomo;
        string nombre;

    public:
        Atomo(int pId, string pNombre){
            this->setId(pId);
            this->idAtomo = pId;
            this->nombre = pNombre;
        }

        Atomo(int pId){ 
            this->setId(pId);
            this->idAtomo = pId;
        }

        Atomo(){            
        }


        int getIdAtomo() {
            return this->idAtomo;
        }

        void setIdAtomo(int pId) {
            this->idAtomo = pId;
        }

        string getNombre(){
            return this->nombre;
        }

        void setNombre(string pNombre){
            this->nombre = pNombre;
        }

        bool igual(Atomo* pAtomo){
            return getIdAtomo() == pAtomo->getIdAtomo();
        }

        bool igualNombre(string pNombre){
            return getNombre() == pNombre;
        }

        bool igualId(int pId){
            return getIdAtomo() == pId;
        }

};

#endif