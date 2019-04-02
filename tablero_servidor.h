#ifndef TABLERO_SERVIDOR_H
#define TABLERO_SERVIDOR_H

#include "linkedlist.h"
#include <string>
using namespace std;

#include "traductorservidor.h"
#include "bolsa.h"



class Tablero_Servidor
{
private:

    char FichasColocadas[15][15];
    char LetrasJugadas[7];
    int FilasJugadas[7];
    int ColumnasJugadas[7];
    bool VaHorizontal;
    int tam;
    int menor;
    int mayor;
    int ref;
    LinkedList* ListaPalabras;
    int PosEspeciales[15][15];
public:
    Tablero_Servidor();
    static Tablero_Servidor& getInstance(){
        static Tablero_Servidor instance;
        return instance;
    }
    void ColocarFichas();
    string LeerPalabras();
    void AgregarPerpendiculares(LinkedList* L);
    void ColocarFichaManual(char letra,int fila, int columna);
    int MenorDesdeTablero(bool VaHorizontal,int fila, int columna);
    string* Leer(bool VaHorizontal,int fila,int columna);
    void print();
    void Desempaquetar(string s);
    int SumaParcial(int a,int t);
    bool ValidarPalabras(LinkedList* L);
    bool Validar(string* s);
    void Limpiar();
    LinkedList* CasoUnaFicha();
    int PuntajeFichas();
};

#endif // TABLERO_SERVIDOR_H
