/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clipping_Liang_Barsky.h
 * Author: gabriel
 *
 * Created on 8 de Abril de 2017, 16:26
 */

#ifndef CLIPPING_LIANG_BARSKY_H
#define CLIPPING_LIANG_BARSKY_H
#include <cstdlib>
#include <iostream>
#include "Clipping.h" 
#include "Linha.h"
#include "Coordenadas.h"
using namespace std;
class Clipping_Liang_Barsky : public Clipping{
public:
    Clipping_Liang_Barsky(Coordenadas*, Coordenadas*);
    Clipping_Liang_Barsky(const Clipping_Liang_Barsky& orig);
    virtual ~Clipping_Liang_Barsky();
    Linha* process(Linha*);
    float u1(float*,float*);
    float u2(float*,float*);
private:

};

#endif /* CLIPPING_LIANG_BARSKY_H */

