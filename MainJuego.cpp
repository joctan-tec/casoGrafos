#include <iostream>
#include "grafo.h"
#include "Atomo.h"
#include "leeInitUniverseGrafo.h"
//#include "leeInitUniverse.h"

using namespace std;
 
int main(){
    int cantidadGeneraciones;
    //aqui se encuentra el desarrollo del juego
    cout << "*************************************" << endl;
    cout << "**  BIENVENIDOS A ATOMS FOR PEACE  **" << endl;
    cout << "*************************************" << endl;

    cout << "\nIngrese la cantidad de generaciones a ejecutarse" << endl;
    cin >> cantidadGeneraciones;
    cout << endl;

    //ALEATORIAMENTE EL NODO
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(rangoInicialPeso, rangoFinalPeso);
    int numeroNodo = distr(eng);


}