/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.h
 * Author: gabriel
 *
 * Created on 17 de Março de 2017, 15:47
 */

#ifndef WINDOW_H
#define WINDOW_H
#include <cstdlib>
#include <iostream>
#include "Ponto.h"
#include "Linha.h"
#include "Transformacao.h"
#include "Objeto.h"
#include "Poligono.h"
#include "Curva.h"
#include "Coordenadas.h"
#include "Clipping.h"
#include "Clipping_Sutherland.h"
#include "Clipping_Liang_Barsky.h"
#include "Clipping_Sutherland_Hodgeman.h"
using namespace std;

class Window {
public:
    Window(Ponto* min, Ponto* max);
    Window(const Window& orig);
    virtual ~Window();

    int get_x_min();
    int get_x_min_normalizado();
    int get_x_max();
    int get_x_max_normalizado();
    int get_y_min();
    int get_y_min_normalizado();
    int get_y_max();
    int get_y_max_normalizado();
    void zoom_in();
    void zoom_out();
    void move_window(char,int);
    Ponto* transformacao_viewport(Ponto*);
    void rotacao(int);
    float* centro_window();
    Ponto* normalizacao_objeto(Ponto*);
    Poligono* transform_window_em_objeto();
    void gerar_matriz_normalizacao();
    Linha* clipping_line(Linha*,int);
    Ponto* clipping_point(Ponto*);
    Poligono* clipping_poligon(Poligono*);
    Curva* clipping_curva(Curva*);
    
private:
    Ponto* window_max_point;
    Ponto* window_min_point;
    Ponto* window_max_point_normalizado;
    Ponto* window_min_point_normalizado;
    Transformacao * transformacao;
    int angulo;
    int zoom;
    float ** matriz_normalizacao;
    
    
};

#endif /* WINDOW_H */

