/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Poligono3D.cpp
 * Author: gabriel
 * 
 * Created on 3 de Maio de 2017, 18:32
 */

#include "Poligono3D.h"

Poligono3D::Poligono3D(vector<Ponto*> pts, string nome) {
    this->points = pts;
    this->name = "POLIGONO_3D_"+name;
    this->forma_arestas();
}

Poligono3D::Poligono3D(const Poligono3D& orig) {
}

Poligono3D::~Poligono3D() {
}

void Poligono3D::forma_arestas()
{
     int i, index;
        int size = this->points.size();
        //g_print("size 2: %d\n", size);
        for(i = 0; i < size; i++){
            index = i+1;

            if(i == size-1){
                index = 0;
            }
            this->arestas.push_back(new Linha(this->points.at(i),this->points.at(index),"aresta"));
             
        }
}

