#include "ficha.h"
#include <map>
#include <iostream>
#include <stdlib.h>
#include <QGraphicsSceneMouseEvent>

char Ficha::getLetra() const{
    return letra;
}

void Ficha::setLetra(char value)
{
    letra = value;
}

int Ficha::getFila() const
{
    return Fila;
}

void Ficha::setFila(int value)
{
    Fila = value;
}

int Ficha::getColumna() const
{
    return Columna;
}

void Ficha::setColumna(int value)
{
    Columna = value;
}

int Ficha::getValor() const
{
    return Valor;
}

void Ficha::setValor(int value)
{
    Valor = value;
}



int Ficha::Puntos(char letra)
{
    std::map<char, char> m;
    m['a']=1;
    m['e']=1;
    m['o']=1;
    m['i']=1;
    m['s']=1;
    m['n']=1;
    m['l']=1;
    m['r']=1;
    m['u']=1;
    m['t']=1;

    m['d']=2;
    m['g']=2;

    m['c']=3;
    m['b']=3;
    m['p']=3;
    m['m']=3;

    m['h']=4;
    m['y']=4;
    m['v']=4;
    m['f']=4;
    m['w']=4;

    m['k']=5;

    m['j']=8;
    m['x']=8;

    m['z']=10;
    m['q']=10;

    return m[letra];
}



Ficha::Ficha()
{
    this->Valor=5;
    this->letra='a';
    this->Fila=0;
    this->Columna=0;
}


