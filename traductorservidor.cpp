#include "traductorservidor.h"
#include "qdebug.h"
#include"iostream"

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

string TraductorServidor::SerializarRespuestaTurnoPropio(bool val, bool hayfichas, int puntos, string repo,string resumen)
{
    const char* json = "{\"val\":true,"
                       "\"hayfichas\":true,"
                       "\"puntos\":0,"
                       "\"resumen\":\"abcd\","
                       "\"repo\":\"abcd\"}";
    Document d;
    d.Parse(json);
    d["val"].SetBool(val);
    d["hayfichas"].SetBool(hayfichas);
    d["puntos"].SetInt(puntos);
    d["resumen"].SetString(resumen.c_str(),sizeof (char)*resumen.length());
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

bool TraductorServidor::getval(string json)
{
    Document d;
    d.Parse(json.c_str());
    return d["val"].GetBool();
}

string TraductorServidor::getPalabra(string json)
{
    Document d;
    d.Parse(json.c_str());
    return d["palabra"].GetString();
}

void TraductorServidor::DeserializarCrearSala(string json, string *ip,string* nombre,int *tsala)
{
    Document d;
    d.Parse(json.c_str());
    *ip =d["ip"].GetString();
    *nombre= d["nombre"].GetString();
    *tsala=d["tsala"].GetInt();

}

string TraductorServidor::SerializarRespuestaCrearSala(int codigo)
{
    const char* json = "{\"codigo\":123456}";
    Document d;
    d.Parse(json);
    d["codigo"].SetInt(codigo);
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
}

string TraductorServidor::SerializarRespuestaUnirseSala(string iniciales, int turno, int puerto,int tsala)
{
    const char* json = "{\"iniciales\":\"abcdefg\","
                       "\"puerto\":123456,"
                       "\"tsala\":1,"
                       "\"turno\":1}";
    Document d;
    d.Parse(json);
    d["iniciales"].SetString(iniciales.c_str(),sizeof (char)*iniciales.length());
    d["puerto"].SetInt(puerto);
    d["turno"].SetInt(turno);
    d["tsala"].SetInt(tsala);
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
}

void TraductorServidor::DeserializarUnirseSala(string json, string *ip, string *nombre, int *codigo)
{
    Document d;
    d.Parse(json.c_str());
    *ip =d["ip"].GetString();
    *nombre= d["nombre"].GetString();
     *codigo= d["codigo"].GetInt();


}

