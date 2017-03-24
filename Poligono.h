/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Poligono.h
 * Author: paulo
 *
 * Created on 16 de Março de 2017, 10:31
 */

#ifndef POLIGONO_H
#define POLIGONO_H

#include "Objeto.h"
#include "Ponto.h"
#include <vector>
#include <iostream>

using namespace std;

class Poligono : public Objeto{
public:
    Poligono(const Poligono& orig);
    virtual ~Poligono();
    Poligono(vector<Ponto*>, string);
    
    vector<Coordenadas*> get_coordinates();
    string get_name();
    
private:
    vector<Ponto*> points;
};

#endif /* POLIGONO_H */

