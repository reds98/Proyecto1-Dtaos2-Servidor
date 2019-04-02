#include "traductorservidor.h"
#include "qdebug.h"

TraductorServidor::TraductorServidor()
{

}

void TraductorServidor::DeserializarFichasJugadas(string json, int *tam, bool *EsHorizontal, char *letras, int *filas, int *columnas)
{
    Document d;
    d.Parse(json.c_str());
    *tam =d["tam"].GetInt();
    *EsHorizontal=d["horizontal"].GetBool();
    string stmp;
    for (int i=0;i<*tam;i++){
        stmp=d["letras"].GetString();
        letras[i]=stmp[i];
        filas[i]=d["filas"].GetArray()[i].GetInt();
        columnas[i]= d["columnas"].GetArray()[i].GetInt();
    }
}

string TraductorServidor::SerializarRespuestaTurnoPropio(bool val, bool hayfichas, int puntos, string repo)
{
    const char* json = "{\"val\":true,"
                       "\"hayfichas\":true,"
                       "\"puntos\":0,"
                       "\"repo\":\"abcd\"}";
    Document d;
    d.Parse(json);
    d["val"].SetBool(val);
    d["hayfichas"].SetBool(hayfichas);
    d["puntos"].SetInt(puntos);
    d["repo"].SetString(repo.c_str(),sizeof (char)*repo.length());
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
}

string TraductorServidor::SerializarRespuestaTurnoAjeno(string json)
{
    Document d;
    d.Parse(json.c_str());
    StringBuffer buffer;
    d.RemoveMember("id");
    d.RemoveMember("horizontal");

    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    qDebug()<<buffer.GetString();
    return buffer.GetString();

}

int TraductorServidor::getID(string json)
{
    Document d;
    d.Parse(json.c_str());
    return d["id"].GetInt();
}

string TraductorServidor::getPalabra(string json)
{
    Document d;
    d.Parse(json.c_str());
    return d["palabra"].GetString();
}

void TraductorServidor::DeserializarCrearSala(string json, string *ip)
{
    Document d;
    d.Parse(json.c_str());
    *ip =d["ip"].GetString();

}

string TraductorServidor::SerializarRespuestaCrearSala(bool val, int codigo, int turno)
{
    const char* json = "{\"val\":true,"
                       "\"codigo\":123456,"
                       "\"turno\":1}";
    Document d;
    d.Parse(json);
    d["val"].SetBool(val);
    d["codigo"].SetInt(codigo);
    d["turno"].SetInt(turno);
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
}

