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

Coordenadas::Coordenadas(float x, float y, float z) {
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
float Coordenadas::get_x(){
    return this->x;
}

/**
 * Pega o valor y da coordenada
 * @return 
 */
float Coordenadas::get_y(){
    return this->y;
}

/**
 * Pega o valor z da coordenada
 * @return 
 */
float Coordenadas::get_z(){
    return this->z;
}

/**
 * Seta um novo valor para a coordenada x
 * @param val
 */
void Coordenadas::set_x(float val){
    this->x = val;
}

/**
 * Seta um novo valor para a coordenada z
 * @param val
 */
void Coordenadas::set_y(float val){
    this->y=val;
}

/**
 * Seta um novo valor para a coordenada z
 * @param val
 */
void Coordenadas::set_z(float val){
    this->z=val;
}
