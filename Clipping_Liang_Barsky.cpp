/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Clipping_Liang_Barsky.cpp
 * Author: gabriel
 * 
 * Created on 8 de Abril de 2017, 16:26
 */

#include "Clipping_Liang_Barsky.h"

Clipping_Liang_Barsky::Clipping_Liang_Barsky(Coordenadas* ponto_max, Coordenadas* ponto_min) {
    this->ponto_max_window= ponto_max;
    this->ponto_min_window= ponto_min;
}

Clipping_Liang_Barsky::Clipping_Liang_Barsky(const Clipping_Liang_Barsky& orig) {
}

Clipping_Liang_Barsky::~Clipping_Liang_Barsky() {
}

Linha* Clipping_Liang_Barsky::process(Linha* obj)
{
    float p1,p2,p3,p4,q1,q2,q3,q4;
    
    p1 =(float) -1*(obj->get_coordinates().at(1)->get_x() - obj->get_coordinates().at(0)->get_x());
    p2 =(float)    (obj->get_coordinates().at(1)->get_x() - obj->get_coordinates().at(0)->get_x());
    p3 =(float) -1*(obj->get_coordinates().at(1)->get_y() - obj->get_coordinates().at(0)->get_y());
    p4 =(float)    (obj->get_coordinates().at(1)->get_y() - obj->get_coordinates().at(0)->get_y());
    
   cout<< "P1 Á P4 : " << p1 << ":" << p2 << ":"<<p3 << ":"<<p4 <<endl;
   
   q1 = obj->get_coordinates().at(0)->get_x() - this->ponto_min_window->get_x();
   q2 = this->ponto_max_window->get_x() - obj->get_coordinates().at(0)->get_x();
   q3 = obj->get_coordinates().at(0)->get_y() - this->ponto_min_window->get_y();
   q4 = this->ponto_max_window->get_y() - obj->get_coordinates().at(0)->get_y();
   
   cout<< "Q1 Á Q4 : " << q1 << ":" << q2 << ":"<<q3 << ":"<<q4 <<endl;
   
   float* p_valores_negativos = new float[2];
   float* p_valores_positivos = new float[2];
   float* q_valores_negativos = new float[2];
   float* q_valores_positivos = new float[2];
   
   if(p1 < 0)
   {
       p_valores_negativos[0] = p1;
       q_valores_negativos[0] = q1;
       
       p_valores_positivos[0] = p2;
       q_valores_positivos[0] = q2;
   }else
   {
       p_valores_negativos[0] = p2;
       q_valores_negativos[0] = q2;
       
       p_valores_positivos[0] = p1;
       q_valores_positivos[0] = q1;
   }
   
   if(p3 < 0)
   {
       p_valores_negativos[1] = p3;
       q_valores_negativos[1] = q3;
       
       p_valores_positivos[1] = p4;
       q_valores_positivos[1] = q4;
   }else
   {
       p_valores_negativos[1] = p4;
       q_valores_negativos[1] = q4;
       
       p_valores_positivos[1] = p3;
       q_valores_positivos[1] = q3;
   }
   
   float fator_u1,fator_u2,x1,x2,y1,y2;
   
   fator_u1 = this->u1(p_valores_negativos,q_valores_negativos);
   fator_u2 = this->u2(p_valores_positivos,q_valores_positivos);
   
   cout<<"U1: " << fator_u1 <<endl;
   cout<<"U2: " << fator_u2 <<endl;
   if(fator_u1 > fator_u2)
   {
      //obj->set_desenhar(false);
      Linha * l = new Linha(NULL,NULL,"");
        l->set_desenhar(false);        
        return l;
   }
   if(fator_u1 != 0)
   {
       x1 =(float) obj->get_coordinates().at(0)->get_x() + (fator_u1 *-1* p_valores_negativos[0]);
       y1 =(float) obj->get_coordinates().at(0)->get_y() + (fator_u1 *-1*p_valores_negativos[1]);
   }else{
       x1 =(float) obj->get_coordinates().at(0)->get_x();
       y1 =(float) obj->get_coordinates().at(0)->get_y();
   }
     
   if(fator_u2 != 1)
   {
     x2 =(float) obj->get_coordinates().at(1)->get_x() + (fator_u2 *-1* p_valores_positivos[0]);
     y2 =(float) obj->get_coordinates().at(1)->get_y() + (fator_u2 *-1*p_valores_positivos[1]);  
   }else{
     x2 =(float) obj->get_coordinates().at(1)->get_x();
     y2 =(float) obj->get_coordinates().at(1)->get_y();
   }
   
   
   cout<<"PONTO 1: " << x1 << ": " << y1 <<endl;
   cout<<"PONTO 2: " << x2 << ": " << y2 <<endl;
   
   if(x1 > this->ponto_max_window->get_x() || x1 < this->ponto_min_window->get_x()
       || y1 > this->ponto_max_window->get_y() ||y1 < this->ponto_min_window->get_y())
    {
       
        //obj->set_desenhar(false);
        Linha * l = new Linha(NULL,NULL,"");
        l->set_desenhar(false);        
        return l;
    }
   
   if(x2 > this->ponto_max_window->get_x() || x2 < this->ponto_min_window->get_x()
       || y2 > this->ponto_max_window->get_y() ||y2 < this->ponto_min_window->get_y())
    {
       
       // obj->set_desenhar(false);
       Linha * l = new Linha(NULL,NULL,"");
        l->set_desenhar(false);        
        return l;
    }
   
   Linha * new_line = new Linha(new Ponto(new Coordenadas(x1,y1,0),"p1"), new Ponto(new Coordenadas(x2,y2,0),"p2"), "l");
   new_line->set_desenhar(true);
   return new_line;
   
}

float Clipping_Liang_Barsky::u1(float* p, float*q)
{
    float r1 =0;float r2=0;
    
    if(p[0] != 0)
    {
     r1 = (float) q[0] / p[0];   
    }
    
    if(p[1] != 0)
    {
      r2  = (float) q[1] / p[1];
    }
    
   
   if(r1 > 0 && r1 >= r2)
   {
       return r1;
   }else if(r2 > 0 && r2 > r1)
   {
       return r2;
   }else{
       return 0;
   }
}

float Clipping_Liang_Barsky::u2(float* p, float*q)
{
   float r1 =1;float r2=1;
    
    if(p[0] != 0)
    {
     r1 = (float) q[0] / p[0];   
    }
    
    if(p[1] != 0)
    {
      r2  = (float) q[1] / p[1];
    }
   
   cout << "R1 E R2 : " << r1 <<" : "  <<r2 <<endl;
   if(r1 < 1 && r1 <= r2)
   {
       return r1;
   }else if(r2 < 1 && r2 < r1)
   {
       return r2;
   }else{
       return 1;
   }
}