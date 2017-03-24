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
private:
    Ponto* window_max_point;
    Ponto* window_min_point;
};

#endif /* WINDOW_H */

