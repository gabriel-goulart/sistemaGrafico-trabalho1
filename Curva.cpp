/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Curva.cpp
 * Author: gabriel
 * 
 * Created on 18 de Abril de 2017, 01:04
 */

#include "Curva.h"

Curva::Curva(vector<Ponto*> pts, string name) {
     this->points = pts;
    this->name = "CURVA_"+name;
}

Curva::Curva(const Curva& orig) {
}

Curva::~Curva() {
}

vector<Coordenadas*> Curva::get_coordinates(){
    int i;
    this->coordinates.clear();
    int size = this->points.size();
    
    for(i = 0; i < size; i++){
        this->coordinates.push_back(this->points.at(i)->get_coordinates().at(0));
    }
    return this->coordinates;
}


/**
 * Recupera o nome do Poligono.
 * @return 
 */
string Curva::get_name(){
    return this->name;
}
