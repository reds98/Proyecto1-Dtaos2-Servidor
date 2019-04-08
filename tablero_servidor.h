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
    int PosEspeciales[15][15];

    char LetrasJugadas[7];
    int FilasJugadas[7];
    int ColumnasJugadas[7];
    bool VaHorizontal;
    int tam;
    int menor;
    int mayor;
    int ref;
    string resumen_palabras="";
    /**
     * @brief ColocarFichas coloca todas las fichas de la lista
     */
    void ColocarFichas();
    /**
     * @brief AgregarPerpendiculares busca palabras adyacentes ala principal
     * @param L
     */
    void AgregarPerpendiculares(LinkedList* L);
    /**
     * @brief ColocarFichaManual coloca una ficha para prubeas
     * @param letra
     * @param fila
     * @param columna
     */
    void ColocarFichaManual(char letra,int fila, int columna);
    /**
     * @brief MenorDesdeTablero
     * @param VaHorizontal
     * @param fila
     * @param columna
     * @return
     */
    int MenorDesdeTablero(bool VaHorizontal,int fila, int columna);
    /**
     * @brief Leer
     * @param VaHorizontal
     * @param fila
     * @param columna
     * @return
     */
    string* Leer(bool VaHorizontal,int fila,int columna);
    void print();
    /**
     * @brief SumaParcial
     * @param a
     * @param t
     * @return
     */
    int SumaParcial(int a,int t);
    /**
     * @brief ValidarPalabras
     * @param L
     * @return
     */
    bool ValidarPalabras(LinkedList* L);
    /**
     * @brief Validar
     * @param s
     * @return
     */

    /**
     * @brief Limpiar
     */
    void Limpiar();

    /**
     * @brief CasoUnaFicha
     * @return
     */
    LinkedList* CasoUnaFicha();
    int PuntajeFichas();
public:
    Tablero_Servidor();
    /**
     * @brief Desempaquetar toma un json y obtiene valores escenciales para validación y ćalculos
     * @param s
     */
    void Desempaquetar(string s);
    /**
     * @brief LeerPalabras devuelve un json con los datos de validación y palabras encontradas
     * @param Total_Fichas
     * @return
     */
    string LeerPalabras(Bolsa* Total_Fichas);
    bool Validar(string* s);
};

#endif // TABLERO_SERVIDOR_H
