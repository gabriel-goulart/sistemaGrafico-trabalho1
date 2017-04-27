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
    
    this->transformacao = new Transformacao(2);
    this->angulo = 0;
    this->gerar_matriz_normalizacao();
}

Window::Window(const Window& orig) {
}

/**
 * Destrutor da Window.
 */
Window::~Window() {
    delete transformacao;
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
       this->window_max_point->get_coordinates().at(0)->set_x(this->get_x_max() - 20);
       this->window_min_point->get_coordinates().at(0)->set_x(this->get_x_min() + 20);

    }
    
    if(this->get_y_max() > 2*this->get_y_min())
    {
       this->window_max_point->get_coordinates().at(0)->set_y(this->get_y_max() - 20);
       this->window_min_point->get_coordinates().at(0)->set_y(this->get_y_min() + 20); 
    }
    
}

/**
 * Mudando os pontos da window para aplicar zoom out 
 */
void Window::zoom_out()
{
    this->window_max_point->get_coordinates().at(0)->set_x(this->get_x_max() + 20);
    this->window_max_point->get_coordinates().at(0)->set_y(this->get_y_max() + 20);
    
    this->window_min_point->get_coordinates().at(0)->set_x(this->get_x_min() - 20);
    this->window_min_point->get_coordinates().at(0)->set_y(this->get_y_min() - 20);
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

Ponto* Window::transformacao_viewport(Ponto* ponto)
{
    double aux0, aux1, aux2, x, y;  
    Ponto *vp_min = new Ponto(new Coordenadas(0,0,0),"pviewportMIN");
    Ponto *vp_max = new Ponto(new Coordenadas(500,500,0),"pviewportMAX");

    aux0 = ponto->get_x() - this->get_x_min();
    aux1 = this->get_x_max() - this->get_x_min();
    aux2 = vp_max->get_coordinates().at(0)->get_x() - vp_min->get_coordinates().at(0)->get_x();  
    x = (aux0/aux1)*(aux2);

    aux0 = ponto->get_y() - this->get_y_min();
    aux1 = this->get_y_max() - this->get_y_min();
    aux2 = vp_max->get_coordinates().at(0)->get_y() - vp_min->get_coordinates().at(0)->get_y();
    y = (1-(aux0/aux1))*(aux2);
    /*
    g_print("x window = %d, ",window_layout->get_x_max());
    g_print("y window = %d\n",window_layout->get_y_max());
      
    g_print("x orig = %d, ", ponto->get_x());
    g_print("y orig = %d\n", ponto->get_y());
    g_print("x trans = %f, ", x);
    g_print("y trans = %f\n", y); */

    return new Ponto(new Coordenadas(x,y,0),"ponto transformado"); 
}

Poligono * Window::transform_window_em_objeto()
{
    vector<Ponto*> window_points;
    window_points.push_back(this->window_min_point);
    
    Coordenadas * coord1 = new Coordenadas(this->window_max_point->get_x(), this->window_min_point->get_y(),0);
    Ponto *p = new Ponto(coord1,"ponto window");
    window_points.push_back(p);
    
    window_points.push_back(this->window_max_point);
    
    Coordenadas * coord2 = new Coordenadas(this->window_min_point->get_x(), this->window_max_point->get_y(),0);
    Ponto *p2 = new Ponto(coord2,"ponto window");
    window_points.push_back(p2);
    
   return new Poligono(window_points,"object window");
    
}

void Window::rotacao(int angulo)
{
    this->angulo += angulo;
}


void Window::gerar_matriz_normalizacao()
{
    float** matriz_resultante = new float*[3];
    for(int i = 0; i < 3; ++i)
        matriz_resultante[i] = new float[3];
        
    float* coord_centro = this->transformacao->get_objeto_centro(this->transform_window_em_objeto());
    
    float* coord_centro_negativo = new float[3];
    coord_centro_negativo[0] = -1*coord_centro[0];
    coord_centro_negativo[1] = -1*coord_centro[1];
    coord_centro_negativo[2] =  coord_centro[2];
    
    float** matriz_translacao = this->transformacao->get_matriz_translacao(coord_centro_negativo);
    
    float* coord_escalonamento = new float[3];
    coord_escalonamento[0] = this->get_x_max() / 2;
    coord_escalonamento[1] = this->get_y_max() /2;
    coord_escalonamento[2] = 1;
    
    float** matriz_escalonamento = this->transformacao->get_matriz_escalonamento(coord_escalonamento);
    
    if(this->angulo != 0)
    {
        float** matriz_rotacao =this->transformacao->get_matriz_rotacao(this->angulo);
        matriz_resultante = this->transformacao->transformar(matriz_translacao,matriz_rotacao);
        matriz_resultante = this->transformacao->transformar(matriz_resultante,matriz_escalonamento);
    }else{
         matriz_resultante = this->transformacao->transformar(matriz_translacao,matriz_escalonamento);
    }
    
    this->matriz_normalizacao = matriz_resultante;
}


void Window::normalizacao_world()
{
    
}

void Window::normalizacao_objeto()
{
    
}