#ifndef _INODO_
#define _INODO_ 1

class INodo {
    public:
        int getId() {
            return id;
        }

        void setId(int pId) {
            this->id = pId;
        }

        void resetDistancia(){
            this->distancia=0;
        }
        void setDistancia(int pNumero){
            this->distancia=pNumero;
        }
        
        int getDistancia(){
            return this->distancia;
        }
        
    protected:
        int id;
        int distancia=0;
};

#endif