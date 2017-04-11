/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clipping_sutherland.cpp
 * Author: gabriel
 * 
 * Created on 8 de Abril de 2017, 16:21
 */

#include "Clipping_Sutherland.h"


Clipping_Sutherland::Clipping_Sutherland(Coordenadas* ponto_max, Coordenadas* ponto_min) {
    this->ponto_max_window= ponto_max;
    this->ponto_min_window= ponto_min;
}

Clipping_Sutherland::Clipping_Sutherland(const Clipping_Sutherland& orig) {
}

Clipping_Sutherland::~Clipping_Sutherland() {
    delete this;
}

Linha* Clipping_Sutherland::process(Linha* obj)
{
    int *rc1 = avalia_ponto(obj->get_coordinates().at(0));
    int *rc2 = avalia_ponto(obj->get_coordinates().at(1));
    cout<< "Ponto 1 - " << obj->get_coordinates().at(0)->get_x() << " - " << obj->get_coordinates().at(0)->get_y() << endl;
    cout<< "Ponto 2 - " << obj->get_coordinates().at(1)->get_x() << " - " << obj->get_coordinates().at(1)->get_y() << endl;

    cout<<"RC1 - " << rc1[0] << rc1[1] << rc1[2] << rc1[3]<<endl;
    cout<<"RC2 - " << rc2[0] << rc2[1] << rc2[2] << rc2[3]<<endl;
    
    if(this->completamente_contido(rc1,rc2))
    {
        obj->set_desenhar(true);
        return obj;
    }
    
    if(this->completamente_fora(rc1,rc2))
    {
        obj->set_desenhar(false);
        return obj;
    }
    
   float m = (float)(obj->get_coordinates().at(1)->get_y() - obj->get_coordinates().at(0)->get_y()) / (obj->get_coordinates().at(1)->get_x() - obj->get_coordinates().at(0)->get_x());
    
    cout<< "ponto1: " << obj->get_coordinates().at(0)->get_x() << "-" << obj->get_coordinates().at(0)->get_y()<<endl;
    cout<< "ponto2: " << obj->get_coordinates().at(1)->get_x() << "-" << obj->get_coordinates().at(1)->get_y()<<endl;
    
    cout<< "m : " << m <<endl;
    
    float * coords_clippadas1 = avalia_rc(rc1,m,obj->get_coordinates().at(0));
    
    if(coords_clippadas1[0] > this->ponto_max_window->get_x() || coords_clippadas1[0] < this->ponto_min_window->get_x()
       || coords_clippadas1[1] > this->ponto_max_window->get_y() || coords_clippadas1[1] < this->ponto_min_window->get_y())
    {
        obj->set_desenhar(false);
        return obj;
    }
    
    float * coords_clippadas2 = avalia_rc(rc2,m,obj->get_coordinates().at(1));
    
    if(coords_clippadas2[0] > this->ponto_max_window->get_x() || coords_clippadas2[0] < this->ponto_min_window->get_x()
       || coords_clippadas2[1] > this->ponto_max_window->get_y() || coords_clippadas2[1] < this->ponto_min_window->get_y())
    {
        obj->set_desenhar(false);
        return obj;
    }
   
   Linha * new_line = new Linha(new Ponto(new Coordenadas(coords_clippadas1[0],coords_clippadas1[1],0),"p1"), new Ponto(new Coordenadas(coords_clippadas2[0],coords_clippadas2[1],0),"p2"), "l");
   new_line->set_desenhar(true);
   return new_line;
}

int* Clipping_Sutherland::avalia_ponto(Coordenadas * coords)
{
   int * rc = new int[4];
   rc[0]=0; rc[1]=0; rc[2]=0; rc[3]=0;
   
   if(coords->get_x() < this->ponto_min_window->get_x() )
       rc[3]=1;
   
   if(coords->get_x() > this->ponto_max_window->get_x() )
       rc[2]=1;
   
   if(coords->get_y() < this->ponto_min_window->get_y() )
       rc[1]=1;
   
   if(coords->get_y() > this->ponto_max_window->get_y() )
       rc[0]=1;
   
   return rc;
}

bool Clipping_Sutherland::completamente_contido(int* rc1, int* rc2)
{
    int i;
    for(i=0; i < 4; i++)
    {
        if(rc1[i] != 0 or rc2[i] !=0 )
        {
            return false;
        }
    }
    return true;
}

bool Clipping_Sutherland::completamente_fora(int* rc1, int* rc2)
{
    int i;
    for(i=0; i < 4; i++)
    {
        int cont = rc1[i] * rc2[i];
        if( cont !=0 )
        {
            return true;
        }
    }
    return false;
}

float* Clipping_Sutherland::avalia_rc(int* rc, float m, Coordenadas* coord_obj)
{
    float x,y;
    float * coords = new float[2];
    // dentro da window
    if(rc[0] ==0 && rc[1] ==0 && rc[2] ==0 && rc[3] ==0)
    {
      coords[0] = coord_obj->get_x(); coords[1] = coord_obj->get_y();
      cout<< "rc : entrou em 0000" << endl;
      return coords;
      

    }else if(rc[0] ==0 && rc[1] ==0 && rc[2] ==1 && rc[3] ==0)//á direita da window
    {
        coords[0] = this->ponto_max_window->get_x();
        coords[1] = m * (this->ponto_max_window->get_x() - coord_obj->get_x()) + coord_obj->get_y(); 
        cout<< "rc : entrou em 0010" << endl;
        return coords;
        
    }else if(rc[0] ==0 && rc[1] ==1 && rc[2] ==1 && rc[3] ==0) //á direita e abaixo da window 
    {
        float y_direita =  m * (this->ponto_max_window->get_x() - coord_obj->get_x()) + coord_obj->get_y();
        if(y_direita < this->ponto_max_window->get_y() && y_direita > this->ponto_min_window->get_y())
        {
            coords[0] = this->ponto_max_window->get_x();
            coords[1] = y_direita;       
        }else{
            coords[0] = coord_obj->get_x() + (1/m)*(this->ponto_min_window->get_y() - coord_obj->get_y()); 
            coords[1] = this->ponto_min_window->get_y();
        }
        
        cout<< "rc : entrou em 0011" << endl;
        return coords;
        
    }else if(rc[0] ==0 && rc[1] ==0 && rc[2] ==0 && rc[3] ==1) // á esquerda da window
    {
        coords[0] = this->ponto_min_window->get_x();
        coords[1]= m * (this->ponto_min_window->get_x() - coord_obj->get_x()) + coord_obj->get_y();
        cout<< "rc : entrou em 0001" << endl;
        return coords;
        
    }else if(rc[0] ==1 && rc[1] ==0 && rc[2] ==0 && rc[3] ==1)// á esquedar e acima da window
    {
        float y_esquerda = m * (this->ponto_min_window->get_x() - coord_obj->get_x()) + coord_obj->get_y();
        
        if(y_esquerda < this->ponto_max_window->get_y() && y_esquerda > this->ponto_min_window->get_y())
        {
            coords[0] = this->ponto_min_window->get_x();
            coords[1] = y_esquerda;
        }else
        {
            coords[0] = coord_obj->get_x() + (1/m)*(this->ponto_max_window->get_y() - coord_obj->get_y()); 
            coords[1] = this->ponto_max_window->get_y();
        }
        cout<< "rc : entrou em 1001" << endl;
        return coords;
        
    }else if(rc[0] ==1 && rc[1] ==0 && rc[2] ==0 && rc[3] ==0)// acima da window
    {
        coords[0] = coord_obj->get_x() + (1/m)*(this->ponto_max_window->get_y() - coord_obj->get_y()); 
        coords[1] = this->ponto_max_window->get_y();
        cout<< "rc : entrou em 1000" << endl;
        return coords;
        
    }else if(rc[0] ==1 && rc[1] ==0 && rc[2] ==1 && rc[3] ==0) // á direita e acima da window 
    {
         float y_direita =  m * (this->ponto_max_window->get_x() - coord_obj->get_x()) + coord_obj->get_y();
        if(y_direita < this->ponto_max_window->get_y() && y_direita > this->ponto_min_window->get_y())
        {
            coords[0] = this->ponto_max_window->get_x();
            coords[1] = y_direita;       
        }else{
            coords[0] = coord_obj->get_x() + (1/m)*(this->ponto_max_window->get_y() - coord_obj->get_y()); 
            coords[1] = this->ponto_max_window->get_y();
        }
        cout<< "rc : entrou em 1100" << endl;
        return coords;
        
    }else if(rc[0] ==0 && rc[1] ==1 && rc[2] ==0 && rc[3] ==0) // abaixo da window 
    {
        coords[0] = coord_obj->get_x() + (1/m)*(this->ponto_min_window->get_y() - coord_obj->get_y()); 
        coords[1] = this->ponto_min_window->get_y();
        cout<< "rc : entrou em 0100" << endl;
        return coords;
        
    }else if(rc[0] ==0 && rc[1] ==1 && rc[2] ==0 && rc[3] ==1) // á esquerda e abaixo da window
    {
        float y_esquerda = m * (this->ponto_min_window->get_x() - coord_obj->get_x()) + coord_obj->get_y();
        
        if(y_esquerda < this->ponto_max_window->get_y() && y_esquerda > this->ponto_min_window->get_y())
        {
            coords[0] = this->ponto_min_window->get_x();
            coords[1] = y_esquerda;
        }else
        {
           coords[0] = coord_obj->get_x() + (1/m)*(this->ponto_min_window->get_y() - coord_obj->get_y()); 
           coords[1] = this->ponto_min_window->get_y();
        }
        cout<< "rc : entrou em 0110" << endl;
        return coords;
    }
    return NULL;
    /*
    if(rc[3] == 1)
    {
        x = this->ponto_min_window->get_x();
        y = m * (this->ponto_min_window->get_x() - coord_obj->get_x()) + coord_obj->get_y();
    }
    
    if(rc[2] == 1)
    {
       x = this->ponto_max_window->get_x();
       y = m * (this->ponto_max_window->get_x() - coord_obj->get_x()) + coord_obj->get_y(); 
    }
    
    if(rc[1] == 1)
    {
       x = this->ponto_max_window->get_x();
       y = m * (this->ponto_max_window->get_x() - coord_obj->get_x()) + coord_obj->get_y(); 
    } */
}

