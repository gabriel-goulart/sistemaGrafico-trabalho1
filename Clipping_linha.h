/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clipping.h
 * Author: gabriel
 *
 * Created on 8 de Abril de 2017, 16:10
 */

#ifndef CLIPPING_H
#define CLIPPING_H
#include "Linha.h"
#include "Coordenadas.h"
class Clipping_linha {
public:
    Clipping_linha();
    Clipping_linha(const Clipping_linha& orig);
    virtual ~Clipping_linha();
protected:
    Coordenadas* ponto_max_window;
    Coordenadas* ponto_min_window;
private:

};

#endif /* CLIPPING_H */

