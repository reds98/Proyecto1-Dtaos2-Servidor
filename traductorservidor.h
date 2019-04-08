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
    /**
     * @brief DeserializarFichasJugadas desmpequeta las fichas de un turno
     * @param json
     * @param tam
     * @param EsHorizontal
     * @param letras
     * @param filas
     * @param columnas
     */
    void DeserializarFichasJugadas(string json, int* tam,bool* EsHorizontal, char* letras,int* filas,int* columnas);
    /**
     * @brief SerializarRespuestaTurnoPropio envia la respuesta a un turno directo
     * @param val
     * @param hayfichas
     * @param puntos
     * @param repo
     * @param resumen
     * @return
     */
    string SerializarRespuestaTurnoPropio(bool val, bool hayfichas,int puntos, string repo,string resumen);
    /**
     * @brief SerializarRespuestaTurnoAjeno envia la respuesta a un turno indirecto
     * @param json
     * @param ganador
     * @return
     */
    string SerializarRespuestaTurnoAjeno(string json,string ganador);


    int getID(string json);
    bool getval(string json);
    string getPalabra(string json);
    int getPuntos(string json);
    string setHayfichas(string json,bool hayfichas);

    /**
     * @brief DeserializarCrearSala desmpequeta datos para crear sala
     * @param json
     * @param ip
     * @param nombre
     * @param tsala
     */
    void DeserializarCrearSala(string json,string* ip,string* nombre,int *tsala);
    /**
     * @brief SerializarRespuestaCrearSala serializa datos para responder la creación
     * @param codigo
     * @return
     */
    string SerializarRespuestaCrearSala( int codigo);
    /**
     * @brief SerializarRespuestaUnirseSala serializa datos para responder la unión
     * @param inciales
     * @param turno
     * @param puerto
     * @param tsala
     * @return
     */
    string SerializarRespuestaUnirseSala(string inciales, int turno,int puerto,int tsala);
    /**
     * @brief DeserializarUnirseSala
     * @param json
     * @param ip
     * @param nombre
     * @param codigo
     */
    void DeserializarUnirseSala(string json,string* ip,string* nombre,int * codigo);
};

#endif // TRADUCTORSERVIDOR_H
