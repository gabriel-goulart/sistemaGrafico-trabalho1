/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Poligono.cpp
 * Author: paulo
 * 
 * Created on 16 de Março de 2017, 10:31
 */

#include "Poligono.h"

Poligono::Poligono(const Poligono& orig) {
}

Poligono::~Poligono() {
}

Poligono::Poligono(vector<Ponto*> pts, string name) {
    this->points = pts;
    this->name = "POLIGONO_"+name;
}

vector<Coordenadas*> Poligono::get_coordinates(){
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
string Poligono::get_name(){
    return this->name;
}
