/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.cpp
 * Author: gabriel
 * 
 * Created on 17 de Março de 2017, 15:47
 */
#include <cstring>
#include "Window.h"

/**
 * Construtor da Window.
 * @param max
 * @param min
 */
Window::Window(Ponto* min, Ponto* max) {
    this->window_max_point = max;
    this->window_min_point = min;
}

Window::Window(const Window& orig) {
}

/**
 * Destrutor da Window.
 */
Window::~Window() {
}

/**
 * Recupera o x do ponto mínimo.
 * @return x_minimo
 */
int Window::get_x_min(){
    return this->window_min_point->get_coordinates().at(0)->get_x();
}

/**
 * Recupera o x do ponto máximo.
 * @return x_maximo
 */
int Window::get_x_max(){
    return this->window_max_point->get_coordinates().at(0)->get_x();
}

/**
 * Recupera o y do ponto mínimo.
 * @return y_minimo
 */
int Window::get_y_min(){
    return this->window_min_point->get_coordinates().at(0)->get_y();
}

/**
 * Recupera o y do ponto máximo.
 * @return y_maximo
 */
int Window::get_y_max(){
    return this->window_max_point->get_coordinates().at(0)->get_y();
}

/**
 * mudando os pontos da window para aplicar zoom in
 */
void Window::zoom_in(){
    
    if(this->get_x_max() > 2*this->get_x_min())
    {
       this->window_max_point->get_coordinates().at(0)->set_x(this->get_x_max() - 10);
       this->window_min_point->get_coordinates().at(0)->set_x(this->get_x_min() + 30);

    }
    
    if(this->get_y_max() > 2*this->get_y_min())
    {
       this->window_max_point->get_coordinates().at(0)->set_y(this->get_y_max() - 10);
       this->window_min_point->get_coordinates().at(0)->set_y(this->get_y_min() + 30); 
    }
    
}

/**
 * Mudando os pontos da window para aplicar zoom out 
 */
void Window::zoom_out()
{
    this->window_max_point->get_coordinates().at(0)->set_x(this->get_x_max() + 10);
    this->window_max_point->get_coordinates().at(0)->set_y(this->get_y_max() + 10);
    
    this->window_min_point->get_coordinates().at(0)->set_x(this->get_x_min() - 30);
    this->window_min_point->get_coordinates().at(0)->set_y(this->get_y_min() - 30);
}

/**
 * movimentacao da window
 * @param type
 * @param val
 */
void Window::move_window(char type, int val)
{
    if(type == 'x')
    {
      this->window_max_point->get_coordinates().at(0)->set_x(this->get_x_max() + val);
      this->window_min_point->get_coordinates().at(0)->set_x(this->get_x_min() + val);

    }else if(type == 'y')
    {
        this->window_max_point->get_coordinates().at(0)->set_y(this->get_y_max() + val);
        this->window_min_point->get_coordinates().at(0)->set_y(this->get_y_min() + val);
    }
}