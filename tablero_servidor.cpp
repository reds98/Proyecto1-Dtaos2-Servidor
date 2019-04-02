#include "ficha.h"
#include "tablero_servidor.h"
#include <iostream>
#include <string>
#include <fstream>
#include <QDebug>
#include <qfile.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;
using namespace std;

Tablero_Servidor::Tablero_Servidor()
{
    ListaPalabras=new LinkedList();
    for (int i=0;i<15;i++){
        for (int j=0;j<15;j++){
            if (i==j || i+j==14){
                this->PosEspeciales[i][j]=1;
            }
            this->FichasColocadas[i][j]='.';
        }
    }

    this->PosEspeciales[2][6]=2;
    this->PosEspeciales[2][7]=2;
    this->PosEspeciales[2][8]=2;

    this->PosEspeciales[12][6]=2;
    this->PosEspeciales[12][7]=2;
    this->PosEspeciales[12][8]=2;

    this->PosEspeciales[6][2]=2;
    this->PosEspeciales[7][2]=2;
    this->PosEspeciales[8][2]=2;

    this->PosEspeciales[6][12]=2;
    this->PosEspeciales[7][12]=2;
    this->PosEspeciales[8][12]=2;
}

/**
 * @brief Tablero_Servidor::ColocarFichas Se encarga de colocar una lista de fichas desempequetadas en otros atributos
 * además asigna la menor ficha y la referencia
 */
void Tablero_Servidor::ColocarFichas()
{
    menor=15;
    mayor=0;
    int det=0;
    for(int i=0;i<tam;i++){
        int f=FilasJugadas[i];
        int c=ColumnasJugadas[i];
        this->FichasColocadas[f][c]=LetrasJugadas[i];
        if (VaHorizontal){
            ref=f;
            det+=c;
            if(menor>c) menor=c;
            if(c>mayor) mayor=c;
        }
        else{
            ref=c;
            det+=f;
            if(menor>f) menor=f;
            if(f>mayor) mayor=f;
        }
    }

    cout<<"Menor: "<<menor<<endl;
    cout<<"Mayor: "<<mayor<<endl;
    cout<<"Ref: "<<ref<<endl;
}
/**
 * @brief Tablero_Servidor::LeerPalabras Coloca y lee todas las palabras nuevas formadas
 * @return una lista con las strings de las palabras formadas
 */
string Tablero_Servidor::LeerPalabras()
{
    LinkedList* L;
    bool val;
    TraductorServidor T=TraductorServidor::getInstance();
    if(tam==1){
        L=CasoUnaFicha();
    }
    else{
        L= new LinkedList();
        string* stmp;
        ColocarFichas();
        int dif=menor;
        if (VaHorizontal){
             menor= MenorDesdeTablero(VaHorizontal,ref,menor);
             stmp=Leer(VaHorizontal,ref,menor);
        }
        else{
            menor= MenorDesdeTablero(VaHorizontal,menor,ref);
            stmp=Leer(VaHorizontal,menor,ref);
        }

        dif=dif-menor;
        if ((*stmp).length()<mayor-menor+1){
            cout<<"Fragmentación, las fichas colocadas no se conectan"<<endl;
        }

        if ((*stmp).length()==tam){
            cout<<"La palabra no conecta con otras "<<*stmp<<endl;
        }

        cout<<"Palabra principal: "<<*stmp<<endl;
        L->Add(stmp);
        AgregarPerpendiculares(L);
    }

    string s;
    if (L->getT()>0){
        val=ValidarPalabras(L);
        s=Bolsa::getInstance().fichas_turno(tam);
    }
    else {
        val=false;
        s="";
    }
    bool hayfichas;
    if (s.length()==tam){
        hayfichas=true;
    }
    else{
        hayfichas=false;
    }
    return T.SerializarRespuestaTurnoPropio(val,hayfichas,PuntajeFichas(),s);
}
/**
 * @brief Tablero_Servidor::AgregarPerpendiculares Agrega a una lista palabras perpendiculares a la principal
 * @param L lista dentro de la cual agregar
 */
void Tablero_Servidor::AgregarPerpendiculares(LinkedList *L)
{
    int tmp;
    int fila;
    int columna;
    string* stmp;
    for (int i=0;i<tam;i++){
        fila=FilasJugadas[i];
        columna=ColumnasJugadas[i];
        if(VaHorizontal){
            tmp=MenorDesdeTablero(false,fila,columna);
            stmp=Leer(false,tmp,columna);
        }
        else{
            tmp=MenorDesdeTablero(true,fila,columna);
            stmp=Leer(true,fila,tmp);
        }
        if (stmp->length()<2) continue;
        cout<<"Palabra perpendicular: "<<*stmp<<endl;
        L->Add(stmp);
    }
}
/**
 * @brief Tablero_Servidor::ColocarFichaManual Coloca fichas sin restricciones para pruebas
 * @param letra char
 * @param fila eje Y
 * @param columna eje X
 */
void Tablero_Servidor::ColocarFichaManual(char letra, int fila, int columna)
{
    this->FichasColocadas[fila][columna]=letra;
}
/**
 * @brief Tablero_Servidor::MenorDesdeTablero Con la menor posición de las fichas jugadas
 * busca si hay una menor conectada a en la palabra
 */
int Tablero_Servidor::MenorDesdeTablero(bool VaHorizontal,int fila, int columna)
{
    char tmp;
    if(VaHorizontal){
        if (columna==0) return 0;
        tmp=this->FichasColocadas[fila][columna-1];
        while (tmp!='.' && columna!=0){
            columna--;
            tmp=this->FichasColocadas[fila][columna-1];
        }
        return columna;
    }
    else{
        if (fila==0) return 0;
        tmp=this->FichasColocadas[fila-1][columna];
        while (tmp!='.' && fila!=0){
            fila--;
            tmp=this->FichasColocadas[fila-1][columna];
        }
        return fila;
    }
}
/**
 * @brief Tablero_Servidor::Leer Se encarga de leer a partir de una posicón en sentido horizontal o vertical
 * @return Palabra principal formada
 */
string* Tablero_Servidor::Leer(bool VaHorizontal,int fila,int columna)
{
    char tmp;
    string* palabra=new string("");
    int i=0;
    if(VaHorizontal){
        tmp=this->FichasColocadas[fila][columna];
        while (tmp!='.' && menor!=14){
            *palabra+=tmp;
            columna++;
            i++;
            tmp=this->FichasColocadas[fila][columna];
        }
    }
    else{
        tmp=this->FichasColocadas[fila][columna];
        while (tmp!='.' && menor!=14){
            *palabra+=tmp;
            fila++;
            i++;
            tmp=this->FichasColocadas[fila][columna];
        }
    }
    return palabra;
}


/**
 * @brief Tablero_Servidor::print print de los char colocadas en el tablero
 */
void Tablero_Servidor::print()
{
    for (int i=0;i<15;i++){
        for (int j=0;j<15;j++){
            cout<<this->FichasColocadas[i][j]<<" ";
        }
        cout<<endl;
    }
}

/**
 * @brief Tablero_Servidor::Desempaquetar
 * @param L
 */
void Tablero_Servidor::Desempaquetar(string s)
{
    TraductorServidor T=TraductorServidor::getInstance();
    T.DeserializarFichasJugadas(s,&tam,&VaHorizontal,LetrasJugadas,FilasJugadas,ColumnasJugadas);
}
/**
 * @brief Tablero_Servidor::SumaParcial suma elementos desde a hasta a+t
 * @param a primer elemento
 * @param t largo
 * @return suma
 */
int Tablero_Servidor::SumaParcial(int a, int t)
{
    int b=0;
    int c=a+t;
    for (;a<c;a++) {
        b+=a;
    }
    return b;
}
/**
 * @brief Tablero_Servidor::ValidarPalabras método que valida una lista de string
 * @param L lista de palabras
 * @return true si todas pasan la validación
 */
bool Tablero_Servidor::ValidarPalabras(LinkedList *L)
{
    Node* tmp=L->getFirst();
    string* s;
    cout<<"VALIDANDO: ";
    while (tmp!=nullptr){
        s=(string*)tmp->getData();
        cout<<*s<<", ";
        if (!Validar(s)) {
            cout<<"-VALIDADCIÓN FALLA EN: "<<*s<<endl;
            Limpiar();
            return false;
        }
        tmp=tmp->getNext();
    }
    cout<<"-VALIDADCIÓN EXITOSA"<<endl;
    return true;
}
/**
 * @brief Tablero_Servidor::Validar valida una palabra según el diccionario inglés
 * @param s palabra
 * @return true si esta en el diccionario
 */
bool Tablero_Servidor::Validar(string *s)
{
    QFile file(":/txt/txt/words_alpha.txt");
    if(!file.exists()){
        qDebug() <<"No abre el diccionario xd";
        return false;
    }
    else{
        file.open(QFile::ReadOnly);
        QString line;
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            if(*s==line.toUtf8().constData()){
                return true;
            }
        }
        file.flush();
        file.close();
        return false;
    }
}
/**
 * @brief Tablero_Servidor::Limpiar En caso de que la validación falle se limpian las fichas jugadas
 */
void Tablero_Servidor::Limpiar()
{
    int fila;
    int columna;
    for (int i=0;i<tam;i++){
        fila=FilasJugadas[i];
        columna=ColumnasJugadas[i];
        this->FichasColocadas[fila][columna]='.';
    }
}
/**
 * @brief Tablero_Servidor::CasoUnaFicha Método que abarca el caso de tener una sola ficha
 * @return Lista con maxímo dos palabras resultantes
 */
LinkedList *Tablero_Servidor::CasoUnaFicha()
{
    string * stmp;
    LinkedList* L=new LinkedList();

    int fila=FilasJugadas[0];
    int columna=ColumnasJugadas[0];
    int tmp;
    this->FichasColocadas[fila][columna]=LetrasJugadas[0];

    tmp=MenorDesdeTablero(true,fila,columna);
    stmp= Leer(true,fila,tmp);
    if(stmp->length()>1){
        cout<<"Palabra 1: "<<*stmp<<endl;
        L->Add(stmp);
    }

    tmp=MenorDesdeTablero(false,fila,columna);
    stmp=Leer(false,tmp,columna);
    if(stmp->length()>1){
        cout<<"Palabra 2: "<<*stmp<<endl;
        L->Add(stmp);
    }
    return L;
}
/**
 * @brief Tablero_Servidor::PuntajeFichas Obtiene el puntaje por cada ficha jugada basado en su letra y su posció el tablero
 * @return puntos totales por el turno
 */
int Tablero_Servidor::PuntajeFichas()
{
    int p=0;
    bool doble=false;
    char letra;
    int fila;
    int columna;
    int puntos;
    for (int i=0;i<tam;i++){
        letra=LetrasJugadas[i];
        fila=FilasJugadas[i];
        columna=ColumnasJugadas[i];
        puntos=Ficha::Puntos(letra);
        if (this->PosEspeciales[fila][columna]==2) doble=true;
        else if (this->PosEspeciales[fila][columna]==1) puntos*=2;
        p+=puntos;
        printf("Puntos (%c)=%d\n",letra,puntos);
    }

    if (doble) p*=2;
    cout<<"Puntaje final: "<<p<<endl;
    return p;
}



