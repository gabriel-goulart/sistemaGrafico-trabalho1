/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Curva.h
 * Author: gabriel
 *
 * Created on 18 de Abril de 2017, 01:04
 */

#ifndef CURVA_H
#define CURVA_H
#include <vector>
#include "Objeto.h"
#include "Ponto.h"

class Curva: public Objeto {
public:
    Curva(vector<Ponto*> pts, string name);
    Curva(const Curva& orig);
    virtual ~Curva();
    vector<Coordenadas*> get_coordinates();
    string get_name();
private:
    vector<Ponto*> points;
};

#endif /* CURVA_H */

