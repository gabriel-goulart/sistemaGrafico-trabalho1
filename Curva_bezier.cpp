/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Curva_bezier.cpp
 * Author: gabriel
 * 
 * Created on 18 de Abril de 2017, 01:10
 */

#include "Curva_bezier.h"

Curva_bezier::Curva_bezier() {
}

Curva_bezier::Curva_bezier(const Curva_bezier& orig) {
}

Curva_bezier::~Curva_bezier() {
}

Curva* Curva_bezier::process(vector<Ponto*> pontos, float precisao,string nome)
{
   cout<< "COMEÇOU PROCESSO DA CURVA"<<endl;
   int i,size;
   size = pontos.size();
   float * x= new float[size]; 
   float * y= new float[size];
   
   for(i=0;i<size;i++)
   {
       x[i] = pontos.at(i)->get_x();
       y[i] = pontos.at(i)->get_y();
       cout<< "PONTOS: "<<x[i] << "-" << y[i] <<endl;
      
   }
   
   float t= 0;
   vector<Ponto*> curva_points;
   
   while(t <= 1)
   {
       float result_x = process_curva(x,t);
       float result_y = process_curva(y,t);
       
       cout<< "PONTOS RESULTADO: "<<result_x << "-" << result_y <<endl;
       
       Coordenadas *coord = new Coordenadas(result_x,result_y,0);
       Ponto *p = new Ponto(coord,"ponto curva");
       curva_points.push_back(p);
       
       t += precisao;
   }
   cout << "QUANTIDADE - PONTOS : " << curva_points.size() << endl;
   return new Curva(curva_points,nome);
}

float Curva_bezier::process_curva(float* coords , float t)
{
  float result  = (float) coords[0]*( -1*pow(t,3) + 3*pow(t,2) - 3*t +1 );
        result += (float) coords[1]*( 3*pow(t,3) -6*pow(t,2) + 3*t );
        result += (float) coords[2]*( -3*pow(t,3) + 3*pow(t,2));
        result += (float) coords[3]*pow(t,3);
  return result;      
}
