#ifndef FICHA_H
#define FICHA_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "bolsa.h"
#include <QDebug>


class Ficha: public QObject, public QGraphicsPixmapItem
{
private:
    char letra;
    int Fila;
    int Columna;
    int Valor;
public:
    Ficha();
    char getLetra() const;
    void setLetra(char value);
    int getFila() const;
    void setFila(int value);
    int getColumna() const;
    void setColumna(int value);
    int getValor() const;
    void setValor(int value);
    static int Puntos(char letra);
    void setUnplayed();
    void setPlayed();
};
#endif // FICHA_H

