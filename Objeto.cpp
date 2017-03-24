/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Objeto.cpp
 * Author: paulo
 * 
 * Created on 16 de Março de 2017, 09:23
 */

#include "Objeto.h"

Objeto::Objeto() {
}

Objeto::Objeto(const Objeto& orig) {
}

Objeto::~Objeto() {
}

/**
 * Recupera o nome do Objeto(Ponto, Linha, Poligono)
 * @return Nome do Objeto
 */
string Objeto::get_name(){
    return "OBJETO";
}

vector<Coordenadas*> Objeto::get_coordinates(){
    return this->coordinates;
}
