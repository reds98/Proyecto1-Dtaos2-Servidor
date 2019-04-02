#ifndef BOLSA_H
#define BOLSA_H
#include <string>
using namespace std;
class Bolsa
{
private:
int cantidad_total=100;
 char* letras="abcdefghijklmnopqrstuvwxyz ";
//                  a b c d  e f g h i j k l m n o p q r s t u v w x y z _
 int cantidad[27] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1,2};
public:
  Bolsa();
char agarrar_ficha_aux(int valor);
char agarrar_ficha();
char prueba(int r);
bool revisar_cantidad();
void poner_cero();
int contar_cantidad();

static Bolsa &getInstance(){
    static Bolsa instance;
    return instance;
}

 int getCantidad_total() const;
 void setCantidad_total(int value);
 string fichas_turno(int numero_de_fichas);
};

#endif // BOLSA_H
