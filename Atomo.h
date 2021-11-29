#ifndef ATOMO 
#define ATOMO 1

#include <string>
#include "INodo.h"

using namespace std;

class Atomo : public INodo{
    protected:
        int idAtomo;
        string nombre;
        bool molecula;
        bool organismo;
        bool participa;

    public:
        Atomo(int pId, string pNombre){
            this->setId(pId);
            this->idAtomo = pId;
            this->nombre = pNombre;
            this->molecula = false;
            this->organismo = false;
            this->participa = false;
        }

        Atomo(int pId){ 
            this->setId(pId);
            this->idAtomo = pId;
            this->molecula = false;
            this->organismo = false;
            this->participa = false;
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

        bool getMolecula() {
            return this->molecula;
        }
        void setMolecula(bool molecula) {
            this->molecula = molecula;
        }

        bool getOrganismo() {
            return this->organismo;
        }
        void setOrganismo(bool organismo) {
            this->organismo = organismo;
        }

        bool getParticipa() {
            return this->participa;
        }
        void setParticipa(bool participa) {
            this->participa = participa;
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