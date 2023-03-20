#include <iostream>
#include <malloc.h>

using namespace std;

struct Atleta {
    char* nombre;
    int numero;
    float promedio;
    Atleta* siguiente;
};

struct Tiempo {
    int ronda;
    float tiempo;
};

struct NodoTiempo {
    Tiempo tiempo;
    NodoTiempo* siguiente;
};

NodoTiempo* tiempos = NULL;
Atleta* promedios = NULL;

bool comparar_promedios(const Atleta& a, const Atleta& b) {
    return a.promedio < b.promedio;
}

void solicitar_datos(Atleta*& a) {
    a = (Atleta*)malloc(sizeof(Atleta));
    a->nombre = (char*)malloc(sizeof(char)*100);
    cout << "Ingrese el nombre del atleta: ";
    cin.getline(a->nombre, 100);
    cout << "Ingrese el numero asignado del atleta: ";
    cin >> a->numero;
    cin.ignore();
    a->siguiente = NULL;
}

void registrar_tiempos() {
    for (int ronda = 1; ronda <= 2; ronda++) {
        float tiempo;
        cout << "Ingrese el tiempo registrado por el atleta en la ronda " << ronda << ": ";
        cin >> tiempo;
        NodoTiempo* nodo = (NodoTiempo*)malloc(sizeof(NodoTiempo));
        nodo->tiempo.ronda = ronda;
        nodo->tiempo.tiempo = tiempo;
        nodo->siguiente = tiempos;
        tiempos = nodo;
    }
}

void calcular_promedio(Atleta*& a) {
    if (tiempos != NULL && tiempos->siguiente != NULL) {
        float suma = 0;
        int contador = 0;
        NodoTiempo* temp = tiempos;
        for (int i = 0; i < 2 && temp != NULL; i++) {
            suma += temp->tiempo.tiempo;
            temp = temp->siguiente;
            contador++;
        }
        a->promedio = suma / contador;
        a->siguiente = promedios;
        promedios = a;
        for (Atleta* i = promedios; i->siguiente != NULL && comparar_promedios(*(i->siguiente), *i); i = i->siguiente) {
            swap(*(i->siguiente), *i);
        }
    }
}

void listar_promedios() {
    cout << "Lista de promedios:" << endl;
    for (Atleta* i = promedios; i != NULL; i = i->siguiente) {
        cout << i->numero << " - " << i->nombre << ": " << i->promedio << endl;
    }
}

void liberar_memoria() {
    NodoTiempo* temp = tiempos;
    while (temp != NULL) {
        NodoTiempo* siguiente = temp->siguiente;
        free(temp);
        temp = siguiente;
    }
    Atleta* temp2 = promedios;
    while (temp2 != NULL) {
        Atleta* siguiente = temp2->siguiente;
        free(temp2->nombre);
        free(temp2);
        temp2 = siguiente;
    }
}

int main() {
    int opcion = 0;
    while (opcion != 3) {
        cout << "Menu:" << endl;
        cout << "1. Registrar tiempos" << endl;
        cout << "2. Listar promedios" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion) {
            case 1: {
                Atleta* a = NULL;
                solicitar_datos(a);
                registrar_tiempos();
                calcular_promedio(a);
                break;
            }
            case 2: {
                listar_promedios();
                break;
            }
            case 3: {
                liberar_memoria();
                break;
            }
            default: {
                cout << "Opcion invalida." << endl;
                break;
            }
        }
        cout << endl;
    }
    return 0;
}