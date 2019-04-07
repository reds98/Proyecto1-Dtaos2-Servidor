#ifndef TRADUCTORSERVIDOR_H
#define TRADUCTORSERVIDOR_H
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
using namespace std;
using namespace rapidjson;


class TraductorServidor
{
public:
    TraductorServidor();
    static TraductorServidor& getInstance(){
        static TraductorServidor instance;
        return instance;
    }
    void DeserializarFichasJugadas(string json, int* tam,bool* EsHorizontal, char* letras,int* filas,int* columnas);
    string SerializarRespuestaTurnoPropio(bool val, bool hayfichas,int puntos, string repo,string resumen);
    string SerializarRespuestaTurnoAjeno(string json,string ganador);

    int getID(string json);
    bool getval(string json);
    string getPalabra(string json);
    int getPuntos(string json);
    string setHayfichas(string json,bool hayfichas);

    void DeserializarCrearSala(string json,string* ip,string* nombre,int *tsala);
    string SerializarRespuestaCrearSala( int codigo);
    string SerializarRespuestaUnirseSala(string inciales, int turno,int puerto,int tsala);
    void DeserializarUnirseSala(string json,string* ip,string* nombre,int * codigo);
};

#endif // TRADUCTORSERVIDOR_H
