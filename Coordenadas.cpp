/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Coordenadas.cpp
 * Author: stt-paulo
 * 
 * Created on 17 de Março de 2017, 14:24
 */

#include "Coordenadas.h"

Coordenadas::Coordenadas(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Coordenadas::Coordenadas(const Coordenadas& orig) {
}

Coordenadas::~Coordenadas() {
}

/**
 * Pega o valor x da coordenada
 * @return 
 */
int Coordenadas::get_x(){
    return this->x;
}

/**
 * Pega o valor y da coordenada
 * @return 
 */
int Coordenadas::get_y(){
    return this->y;
}

/**
 * Pega o valor z da coordenada
 * @return 
 */
int Coordenadas::get_z(){
    return this->z;
}

/**
 * Seta um novo valor para a coordenada x
 * @param val
 */
void Coordenadas::set_x(int val){
    this->x = val;
}

/**
 * Seta um novo valor para a coordenada z
 * @param val
 */
void Coordenadas::set_y(int val){
    this->y=val;
}

/**
 * Seta um novo valor para a coordenada z
 * @param val
 */
void Coordenadas::set_z(int val){
    this->z=val;
}
