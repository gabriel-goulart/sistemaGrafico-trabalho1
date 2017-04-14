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
    
    this->window_max_point_normalizado = new Ponto(new Coordenadas(1,1,0),"pwinNormalizadoMAX");
    this->window_min_point_normalizado = new Ponto(new Coordenadas(-1,-1,0),"pwinNormalizadoMIN");

    this->transformacao = new Transformacao(2);
    this->angulo = 0;
    this->zoom = 1;
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
 * Recupera o x do ponto mínimo normalizado.
 * @return x_minimo
 */
int Window::get_x_min_normalizado(){
    return this->window_min_point_normalizado->get_coordinates().at(0)->get_x();
}

/**
 * Recupera o x do ponto máximo.
 * @return x_maximo
 */
int Window::get_x_max(){
    return this->window_max_point->get_coordinates().at(0)->get_x();
}

/**
 * Recupera o x do ponto máximo normalizado.
 * @return x_maximo
 */
int Window::get_x_max_normalizado(){
    return this->window_max_point_normalizado->get_coordinates().at(0)->get_x();
}

/**
 * Recupera o y do ponto mínimo.
 * @return y_minimo
 */
int Window::get_y_min(){
    return this->window_min_point->get_coordinates().at(0)->get_y();
}

/**
 * Recupera o y do ponto mínimo normalizado.
 * @return y_minimo
 */
int Window::get_y_min_normalizado(){
    return this->window_min_point_normalizado->get_coordinates().at(0)->get_y();
}

/**
 * Recupera o y do ponto máximo.
 * @return y_maximo
 */
int Window::get_y_max(){
    return this->window_max_point->get_coordinates().at(0)->get_y();
}

/**
 * Recupera o y do ponto máximo normalizado.
 * @return y_maximo
 */
int Window::get_y_max_normalizado(){
    return this->window_max_point_normalizado->get_coordinates().at(0)->get_y();
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
  // cout<<"OBJETO TRANSFORMACAO VIEW antes coord orginal" << ponto->get_coordinates().at(0)->get_x() << " - " << ponto->get_coordinates().at(0)->get_y() << endl;

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
    
    //cout<<"OBJETO TRANSFORMACAO VIEW" << x << " - " << y << endl;
    //cout<<"OBJETO TRANSFORMACAO VIEW coord orginal NORMALIZADO" << ponto->get_x_normalizado()<< " - " << ponto->get_y_normalizado() << endl;

   // cout<<"OBJETO TRANSFORMACAO VIEW coord orginal" << ponto->get_coordinates().at(0)->get_x() << " - " << ponto->get_coordinates().at(0)->get_y() << endl;

    //return new Ponto(ponto->get_coordinates().at(0),new Coordenadas(x,y,0),"ponto transformado"); 
    return new Ponto (new Coordenadas(x,y,0),"ponto transformado");
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


float* Window::centro_window()
{
    return this->transformacao->get_objeto_centro(this->transform_window_em_objeto());
}

Ponto* Window::normalizacao_objeto(Ponto *obj)
{
    int i;
    cout<<"OBJETO ANTES" << obj->get_x() << " - " << obj->get_y() << endl;
    Ponto *obj_transformacao = new Ponto(obj->get_coordinates().at(0),"ponto");
    // translacao
    float* coord_centro = this->centro_window();
    float* coord_centro_negativo = new float[3];
    coord_centro_negativo[0] = -1*coord_centro[0];
    coord_centro_negativo[1] = -1*coord_centro[1];
    coord_centro_negativo[2] =  coord_centro[2];
    
    // escalonamento
    float* coord_escalonamento= new float[3];
    coord_escalonamento[0] =(this->get_x_max())/2;
    coord_escalonamento[1] =(this->get_y_max())/2;
    coord_escalonamento[2] = 1;
    
    // rotacao
    float* coord_rotacao= new float[3];
    coord_rotacao[0] =0;
    coord_rotacao[1] =0;
    coord_rotacao[2] = 1;
    
    // coordenadas objeto
    float* coord_objeto= new float[3];
    coord_objeto[0] = obj_transformacao->get_x();
    coord_objeto[1] = obj_transformacao->get_y();
    coord_objeto[2] = 1;
    
    cout<<"COORD CENTRO" << coord_centro_negativo[0] << " - " << coord_centro_negativo[1] << endl;

    float *p = this->transformacao->translacao(coord_objeto,coord_centro_negativo);
    cout<<"P1" << p[0] << " - " << p[1] << endl;
    p =this->transformacao->rotacao(p,coord_rotacao,-this->angulo);
    cout<<"P2" << p[0] << " - " << p[1] << endl;
    p = this->transformacao->escalonamento(p,coord_escalonamento);
    cout<<"P3" << coord_escalonamento[0] << " - " << coord_escalonamento[1] << endl;
    Ponto *obj_transformacao2 = new Ponto(obj->get_coordinates().at(0),new Coordenadas(p[0],p[1],0),"ponto normalizado");
    cout<<"OBJETO DEPOIS" << obj_transformacao2->get_x_normalizado() << " - " << obj_transformacao2->get_y_normalizado() << endl;
    cout<<"OBJETO DEPOIS coord original" << p[0] << " - " << p[1] << endl;

    obj = obj_transformacao2;
    return obj;
}

/**
 * Clippando um objeto linha de ocordo com o método escolhido
 * @param linha
 * @param type
 * @return 
 */
Linha* Window::clipping_line(Linha* linha,int type)
{
    if(type == 0)
    {
      Clipping_Sutherland *clipping = new Clipping_Sutherland(this->window_max_point->get_coordinates().at(0),this->window_min_point->get_coordinates().at(0));
        Linha * result = clipping->process(linha);
        
        return result;
    }else
    {
      Clipping_Liang_Barsky *clipping = new Clipping_Liang_Barsky(this->window_max_point->get_coordinates().at(0),this->window_min_point->get_coordinates().at(0));  
        Linha * result = clipping->process(linha);
        
        return result;
    }
    
   
}

Ponto* Window::clipping_point(Ponto* ponto)
{
    if(ponto->get_x() > this->window_min_point->get_x() && ponto->get_x() < this->window_max_point->get_x() &&
       ponto->get_y() > this->window_min_point->get_y() && ponto->get_y() < this->window_max_point->get_y())
    {
        ponto->set_desenhar(true);
    }else
    {
        ponto->set_desenhar(false);
    }
    
    return ponto;
}

Poligono* Window::clipping_poligon(Poligono* poligono)
{
    Clipping_Sutherland_Hodgeman* clipping = new Clipping_Sutherland_Hodgeman(this->window_max_point->get_coordinates().at(0),this->window_min_point->get_coordinates().at(0));
    Poligono* result = clipping->process(poligono);
    return result;
}