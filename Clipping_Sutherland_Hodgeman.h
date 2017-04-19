/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clipping_Weiler_Atherton.h
 * Author: gabriel
 *
 * Created on 14 de Abril de 2017, 16:41
 */

#ifndef CLIPPING_WEILER_ATHERTON_H
#define CLIPPING_WEILER_ATHERTON_H
#include "Clipping.h"
#include "Coordenadas.h"
#include <vector>
#include "Poligono.h"
#include "Linha.h"
#include "Ponto.h"
#include "Curva.h"
#include "Clipping_Sutherland.h"

class Clipping_Sutherland_Hodgeman : public Clipping {
public:
    Clipping_Sutherland_Hodgeman(Coordenadas*, Coordenadas*);
    Clipping_Sutherland_Hodgeman(const Clipping_Sutherland_Hodgeman& orig);
    virtual ~Clipping_Sutherland_Hodgeman();
    Poligono* process(Poligono*);
    Curva* process(Curva*);
private:
    vector<Ponto*> get_lines_intersects(Poligono*);
    vector<Ponto*> get_lines_intersects(Curva*);
};

#endif /* CLIPPING_WEILER_ATHERTON_H */

