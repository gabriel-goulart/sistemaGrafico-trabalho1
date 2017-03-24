/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ponto.cpp
 * Author: paulo
 * 
 * Created on 16 de Março de 2017, 09:26
 */

#include "Ponto.h"

Ponto::Ponto(const Ponto& orig) {
}

Ponto::~Ponto() {
    delete this;
}

/**
 * Criação do objeto Ponto.
 * @param coord_x
 * @param coord_y
 */
Ponto::Ponto(Coordenadas* coord, string name) {
    this->coordinates.push_back(coord);
    this->name = "PONTO_"+name;
}

/**
 * Recupera a coordenada x do ponto.
 * @return x
 */
int Ponto::get_x(){
    return this->coordinates.at(0)->get_x();
}

/**
 * Recupera a coordenada y do ponto.
 * @return y
 */
int Ponto::get_y(){
    return this->coordinates.at(0)->get_y();
}
/**
 * Seta um novo valor para a coordenada x do ponto
 * @param val
 */
void Ponto::set_x(int val){
    this->coordinates.at(0)->set_x(val);
}

/**
 * Seta um novo valor para a coordenada y do ponto
 * @param val
 */
void Ponto::set_y(int val){
    this->coordinates.at(0)->set_y(val);
}

/**
 * Recupera o nome do Ponto
 * @return 
 */
string Ponto::get_name(){
    return this->name;
}


