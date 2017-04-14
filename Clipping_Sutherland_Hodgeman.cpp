/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clipping_Weiler_Atherton.cpp
 * Author: gabriel
 * 
 * Created on 14 de Abril de 2017, 16:41
 */

#include "Clipping_Sutherland_Hodgeman.h"

Clipping_Sutherland_Hodgeman::Clipping_Sutherland_Hodgeman(Coordenadas* ponto_max, Coordenadas* ponto_min) {
    this->ponto_max_window= ponto_max;
    this->ponto_min_window= ponto_min;
}

Clipping_Sutherland_Hodgeman::Clipping_Sutherland_Hodgeman(const Clipping_Sutherland_Hodgeman& orig) {
}

Clipping_Sutherland_Hodgeman::~Clipping_Sutherland_Hodgeman() {
}

/**
 * processando o clipping de poligonos
 * @param 
 * @return 
 */
Poligono* Clipping_Sutherland_Hodgeman::process(Poligono* obj)
{
    vector<Ponto*> linhas_interseccao = this->get_lines_intersects(obj);
    if(linhas_interseccao.size() >=1)
    {
        Poligono* p = new Poligono(linhas_interseccao,"Poligo clippado");
        p->set_desenhar(true);
        return p;
    }else
    {
        Poligono* p = new Poligono(linhas_interseccao,"Poligo clippado");
        p->set_desenhar(false);
        return p;
    }
}

/**
 * Calculando os pontos de intersecção
 * @param obj
 * @return 
 */
vector<Ponto*> Clipping_Sutherland_Hodgeman::get_lines_intersects(Poligono* obj)
{
    vector<Ponto*> linhas_interseccao;
    int i;
    int index;
    int size = obj->get_coordinates().size();
    
    for(i = 0; i < size; i++){
        index = i+1;
        
        if(i == size-1){
            index = 0;
        }      
        Linha* l = new Linha(new Ponto(obj->get_coordinates().at(i),"ponto 1"),new Ponto(obj->get_coordinates().at(index),"ponto 2"),"ponto avaliacao");      
        Clipping_Sutherland* clipping = new Clipping_Sutherland(this->ponto_max_window,this->ponto_min_window); 
        l = clipping->process(l);
        
        
        if(l->get_desenhar())
        {
            linhas_interseccao.push_back(new Ponto (new Coordenadas(l->get_coordinates().at(0)->get_x(),l->get_coordinates().at(0)->get_y(),0),"ponto"));
            linhas_interseccao.push_back(new Ponto (new Coordenadas(l->get_coordinates().at(1)->get_x(),l->get_coordinates().at(1)->get_y(),0),"ponto"));

        }
        
    }
    
    return linhas_interseccao;
}
