/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Linha.h
 * Author: paulo
 *
 * Created on 16 de Março de 2017, 09:48
 */

#ifndef LINHA_H
#define LINHA_H

#include "Objeto.h"
#include "Ponto.h"

class Linha : public Objeto{
public:
    Linha(const Linha& orig);
    virtual ~Linha();
    Linha(Ponto*, Ponto*, string);
    
    vector<Coordenadas*> get_coordinates();
    string get_name();
    
private:    
    Ponto* point1;
    Ponto* point2;
};

#endif /* LINHA_H */

