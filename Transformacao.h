/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transformacao.h
 * Author: gabriel
 *
 * Created on 23 de Março de 2017, 00:44
 */

#ifndef TRANSFORMACAO_H
#define TRANSFORMACAO_H
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Ponto.h"
#include "Coordenadas.h"
#include "Objeto.h"
using namespace std;
class Transformacao {
public:
    Transformacao(int);
    Transformacao(const Transformacao& orig);
    virtual ~Transformacao();
    float* transformar(float **,float*);
    float** transformar(float**,float**);
    Objeto* translacao(Objeto*,float*);
    Objeto* escalonamento(Objeto*,float*);
    Objeto* rotacao(Objeto*,float*,int,bool);
    
    float** get_matriz_translacao(float *);
    float** get_matriz_escalonamento(float *);
    float** get_matriz_rotacao(int);
    float* get_objeto_centro(Objeto*);
private:
    int dimensao;
    
};

#endif /* TRANSFORMACAO_H */

