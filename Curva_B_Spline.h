/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Curva_B_Spline.h
 * Author: gabriel
 *
 * Created on 26 de Abril de 2017, 16:49
 */

#ifndef CURVA_B_SPLINE_H
#define CURVA_B_SPLINE_H
#include <iostream>
#include <vector>
#include <math.h> 
#include "Curva.h"
#include "Ponto.h"
#include "Coordenadas.h"
class Curva_B_Spline {
public:
    Curva_B_Spline();
    Curva_B_Spline(const Curva_B_Spline& orig);
    virtual ~Curva_B_Spline();
    Curva* process(vector<Ponto*>,float,string);
private:
    vector<Ponto*> points;
    void process_curva(vector<Ponto*>, float);
    float* get_C(float*, float t);
    float* execute_E_x_C(float*,float);
    void fwdDiff(float n, float x, float delta_x, float delta_2_x, float delta_3_x, float y, float delta_y, float delta_2_y, float delta_3_y,float z, float delta_z, float delta_2_z, float delta_3_z);
};

#endif /* CURVA_B_SPLINE_H */

