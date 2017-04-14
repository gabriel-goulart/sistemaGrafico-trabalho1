/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clipping_sutherland.h
 * Author: gabriel
 *
 * Created on 8 de Abril de 2017, 16:21
 */

#ifndef CLIPPING_SUTHERLAND_H
#define CLIPPING_SUTHERLAND_H
#include <cstdlib>
#include <iostream>
#include "Clipping.h"
#include "Coordenadas.h"
#include "Linha.h"
using namespace std;

class Clipping_Sutherland: public Clipping{
public:
    Clipping_Sutherland(Coordenadas*,Coordenadas*);
    Clipping_Sutherland(const Clipping_Sutherland& orig);
    virtual ~Clipping_Sutherland();
    Linha* process(Linha*);
private:
    int* avalia_ponto(Coordenadas *);
    float* avalia_rc(int*,float,Coordenadas*);
    bool completamente_contido(int*,int*);
    bool completamente_fora(int*,int*);
   
    
    
};

#endif /* CLIPPING_SUTHERLAND_H */

