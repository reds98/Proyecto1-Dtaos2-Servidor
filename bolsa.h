/**
* @file bolsa.h
* @Author Sahid Rojas Chacon , Juan Pablo Alvarado y Wajib Zagnul
* @date 8/4/2019
* @brief Implementacion de una bolsa total de fichas
*/
#ifndef BOLSA_H
#define BOLSA_H
#include <string>
#include <cstdlib>
#include "iostream"
using namespace std;
/**
 * @class bolsa
 * @brief es  la bolsa total de fichas por partida
 */
class Bolsa
{
private:
    /**
* ESta es una variable para ver cuantas fichas totales hay en el juego
*/
int cantidad_total=100;
/**
* ESta es un array de char para el total de las fichas
*/
 char* letras="abcdefghijklmnopqrstuvwxyz ";
//                  a b c d  e f g h i j k l m n o p q r s t u v w x y z _
 /**
 * ESta es un array de la cantidad total de cada letra
 */
 int cantidad[27] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1,2};
 //                  a b c d  e f g h i j k l m n o p q r s t u v w x y z _
  /**
  * ESte metodo nos brinda una cantidad especifica de  letras de la bolsa
  */
char agarrar_ficha_aux(int valor);
/**
* ESte es para agarra una ficha nada mas
*/
char agarrar_ficha();
char prueba(int r);
/**
* Este metodo lo que hace es que revisa si todavia hay fichas en la bolsa
*/
bool revisar_cantidad();
void poner_cero();
int contar_cantidad();
public:
/**
* Este metodo  es el constructor de la clase bolsa
*/
Bolsa();
 string fichas_turno(int numero_de_fichas);
};

#endif // BOLSA_H
