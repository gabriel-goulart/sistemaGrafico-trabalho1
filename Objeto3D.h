/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Objeto3D.h
 * Author: gabriel
 *
 * Created on 3 de Maio de 2017, 18:16
 */

#ifndef OBJETO3D_H
#define OBJETO3D_H
#include "Coordenadas.h"
#include "Linha.h"
#include "Ponto.h"
#include <string>
#include <stddef.h>
#include <vector>
class Objeto3D {
public:
    Objeto3D();
    Objeto3D(const Objeto3D& orig);
    virtual ~Objeto3D();
    virtual vector<Ponto*> get_points();
    virtual vector<Linha*> get_arestas();
   // virtual void forma_arestas();
    virtual void set_desenhar(bool);
    virtual bool get_desenhar();
    virtual string get_name();  
protected:
    string name;
    vector<Ponto*> points;
    vector<Linha*> arestas;
    bool desenhar;
private:    
};

#endif /* OBJETO3D_H */

