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
#include "Ponto.h"
#include "Transformacao.h"
#include "Poligono.h"
#include "Coordenadas.h"
class Window {
public:
    Window(Ponto* min, Ponto* max);
    Window(const Window& orig);
    virtual ~Window();

    int get_x_min();
    int get_x_max();
    int get_y_min();
    int get_y_max();
    void zoom_in();
    void zoom_out();
    void move_window(char,int);
    Ponto* transformacao_viewport(Ponto*);
    void rotacao(int);
    void normalizacao_world();
    void normalizacao_objeto();
    Poligono* transform_window_em_objeto();
    void gerar_matriz_normalizacao();
    
private:
    Ponto* window_max_point;
    Ponto* window_min_point;
    Transformacao * transformacao;
    int angulo;
    float ** matriz_normalizacao;
    
};

#endif /* WINDOW_H */

