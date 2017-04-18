/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Curva_bezier.h
 * Author: gabriel
 *
 * Created on 18 de Abril de 2017, 01:10
 */

#ifndef CURVA_BEZIER_H
#define CURVA_BEZIER_H
#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h> 
#include "Ponto.h"
#include "Curva.h"
#include "Coordenadas.h"
using namespace std;
class Curva_bezier {
public:
    Curva_bezier();
    Curva_bezier(const Curva_bezier& orig);
    virtual ~Curva_bezier();
    Curva* process(vector<Ponto*>,float,string);
private:
    float process_curva(float*, float);
    
};

#endif /* CURVA_BEZIER_H */

