/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Linha.cpp
 * Author: paulo
 * 
 * Created on 16 de Março de 2017, 09:48
 */

#include "Linha.h"

Linha::Linha(const Linha& orig){
}

Linha::~Linha() {
}

/**
 * Criação do objeto Linha
 * @param p1 ponto inicial
 * @param p2 ponto final
 */
Linha::Linha(Ponto* p1, Ponto* p2, string name){
    this->point1 = p1;
    this->point2 = p2;
    this->name = "LINHA_"+name;
}

vector<Coordenadas*> Linha::get_coordinates(){
    this->coordinates.clear();
    this->coordinates.push_back(this->point1->get_coordinates().at(0));
    this->coordinates.push_back(this->point2->get_coordinates().at(0));
    return this->coordinates;
}

/**
 * Recupera o nome da Linha
 * @return 
 */
string Linha::get_name(){
    return this->name;
}


