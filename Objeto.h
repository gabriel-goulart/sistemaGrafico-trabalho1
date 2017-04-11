/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Objeto.h
 * Author: paulo
 *
 * Created on 16 de Março de 2017, 09:23
 */

#ifndef OBJETO_H
#define OBJETO_H

#include "Coordenadas.h"
#include <string>
#include <stddef.h>
#include <vector>
using namespace std;

class Objeto {
public:
    Objeto();
    Objeto(const Objeto& orig);
    virtual ~Objeto();
    
    virtual vector<Coordenadas*> get_coordinates();
    virtual vector<Coordenadas*> get_coordinates_normalizadas();
    virtual void set_desenhar(bool);
    virtual bool get_desenhar();
    virtual string get_name();    
    
protected:
    string name;
    vector<Coordenadas*> coordinates;
    vector<Coordenadas*> coordinates_normalizadas;
    bool desenhar;
private:
    
};

#endif /* OBJETO_H */


