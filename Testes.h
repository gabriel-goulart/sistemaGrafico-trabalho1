/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Testes.h
 * Author: paulo
 *
 * Created on 16 de Março de 2017, 10:51
 */

#ifndef TESTES_H
#define TESTES_H

#include "Objeto.h"
#include "Ponto.h"
#include "Linha.h"
#include "Poligono.h"
#include "InterfaceGrafica.h"
#include "DisplayFile.h"
#include "Coordenadas.h"
#include <iostream>
#include <vector>

using namespace std;

class Testes {
public:
    Testes();
    Testes(const Testes& orig);
    virtual ~Testes();
    
    void testando_ponto_linha_poligono();
private:

};

#endif /* TESTES_H */

