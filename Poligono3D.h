/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Poligono3D.h
 * Author: gabriel
 *
 * Created on 3 de Maio de 2017, 18:32
 */

#ifndef POLIGONO3D_H
#define POLIGONO3D_H
#include "Objeto3D.h"
class Poligono3D : public Objeto3D{
public:
    Poligono3D(vector<Ponto*>, string);
    Poligono3D(const Poligono3D& orig);
    virtual ~Poligono3D();
    
    void forma_arestas();
    
private:

};

#endif /* POLIGONO3D_H */

