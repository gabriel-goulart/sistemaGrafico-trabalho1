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
#include "Iterador.h"
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
    virtual string get_name();
    int get_id();
    
protected:
    string name;
    int id;
    vector<Coordenadas*> coordinates;
    
private:
    
};

#endif /* OBJETO_H */

