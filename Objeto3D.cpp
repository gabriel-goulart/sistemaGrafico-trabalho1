/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Objeto3D.cpp
 * Author: gabriel
 * 
 * Created on 3 de Maio de 2017, 18:17
 */

#include "Objeto3D.h"

Objeto3D::Objeto3D() {
   
}

Objeto3D::Objeto3D(const Objeto3D& orig) {
}

Objeto3D::~Objeto3D() {
}

string Objeto3D::get_name(){
    return "OBJETO3D";
}

vector<Ponto*> Objeto3D::get_points(){
    return this->points;
}

vector<Linha*> Objeto3D::get_arestas(){
    return this->arestas;
}

void Objeto3D::set_desenhar(bool eh_para_desenhar)
{
    this->desenhar = eh_para_desenhar;
}

bool Objeto3D::get_desenhar()
{
    return this->desenhar;
}

