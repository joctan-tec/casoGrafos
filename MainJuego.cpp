#include <iostream>
#include "grafo.h"
#include "Atomo.h"
#include "leeInitUniverseGrafo.h"

using namespace std;
 
int main(){
    //Tomamos el modelo inicial del archivo .json
    InitUniverseGraph archivo;
    archivo.setPath("initUniverso.json");

    Grafo grafoGlobal(true);
    grafoGlobal = archivo.leerArchivo();    //seteamos el grafo con el modelo inicial

    vector<NodoGrafo*> nodos = grafoGlobal.getListaNodos();

    int cantidadGeneraciones;
    int contador = 0;

    //aqui se encuentra el desarrollo del juego
    cout << "*************************************" << endl;
    cout << "**  BIENVENIDOS A ATOMS FOR PEACE  **" << endl;
    cout << "*************************************" << endl;

    cout << "\nIngrese la cantidad de generaciones a ejecutarse" << endl;
    cin >> cantidadGeneraciones;
    cout << endl;

    vector<INodo*> recorrido;
    while (contador < cantidadGeneraciones) {
        cout << contador+1 << " GENERACION" << endl;

        //ALEATORIAMENTE EL NODO
        random_device rd;
        default_random_engine eng(rd());
        uniform_int_distribution<int> distr(0, grafoGlobal.getSize());
        int numeroNodo = distr(eng);
        //cout << numeroNodo << endl;

        //el recorrido se hara desde un atomo aleatorio
        recorrido = grafoGlobal.deepPath(numeroNodo);

        for (int recorrer = 0; recorrer < recorrido.size(); recorrer++) {
            Atomo atomoActual = *((Atomo*)(void*)recorrido.at(recorrer));
            grafoGlobal.reproduccionAtomos(recorrido.at(recorrer));
            if (!atomoActual.getParticipa()){
                //union
            }
            //molecula 
            //organismo
        }
        
        cout << "Cantidad de atomos: " << grafoGlobal.getSize() << endl;
        contador++;
        grafoGlobal.resetNodesParticipated();

    }

    int porcentajeNoUnidos = ((grafoGlobal.getSize() - grafoGlobal.sonMolecula())/grafoGlobal.getSize())*100;

    //Al final de las generaciones se imprimen algunos datos 
    cout << "*************************************" << endl;
    cout << "***      ESTADISTICAS FINALES     ***" << endl;
    cout << "*************************************" << endl;
    cout << "Cantidad de atomos totales:\t" << grafoGlobal.getSize() << endl;
    cout << "Porcentaje de atomos que no se unieron a moleculas u organismos: "<< porcentajeNoUnidos << "%" << endl;
    cout << "Cantidad de moleculas:\t" << grafoGlobal.getMoleculas() << endl;
    cout << "Cantidad de organismos:\t" << grafoGlobal.getOrganismos() << endl;

}