#ifndef _CIUDAD_
#define _CIUDAD_ 1  

#include <iostream>
#include "INodo.h"

using namespace std;

class Ciudad : public INodo {
    public:
        Ciudad(string pNombre, int pPoblacion, int id){
            this->nombre = pNombre;
            this->poblacion = pPoblacion;
            this->identificador = id;
            this->setId(id);
        }

        Ciudad() {    
        }

        string getNombre() {
            return this->nombre;
        }

        int getPoblacion(){
            return this->poblacion;
        }

        void setNombre(string pNombre) {
            this->nombre = pNombre;
        }

        void setPoblacion(int pPoblacion){
            this->poblacion = pPoblacion;
        }
 
        int getIdentificador() {
	         return this->identificador;
        }

        bool igual(Ciudad pCiudad) { // decide entre la igualdad de nombres
            return this->nombre == pCiudad.nombre;
        }

        // void setIdentificador(int identificador) {
        //     this->identificador = identificador;
        // }

    private:
        string nombre;
        int poblacion;
        int identificador;

};

#endif