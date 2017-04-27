/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ponto.h
 * Author: paulo
 *
 * Created on 16 de Março de 2017, 09:26
 */

#ifndef PONTO_H
#define PONTO_H

#include "Objeto.h"
#include "Coordenadas.h"

class Ponto : public Objeto{
public:
    Ponto(const Ponto& orig);
    virtual ~Ponto();
    Ponto(Coordenadas*, string);
    Ponto(Coordenadas*,Coordenadas*, string);
    int get_x();
    int get_y();
    int get_z();
    void set_x(int);
    void set_y(int);
    void set_z(int);
    
    int get_x_normalizado();
    int get_y_normalizado();
    void set_x_normalizado(int);
    void set_y_normalizado(int);
    string get_name();

private:
};

#endif /* PONTO_H */

