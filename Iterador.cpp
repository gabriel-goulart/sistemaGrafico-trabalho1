/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Iterador.cpp
 * Author: stt-paulo
 * 
 * Created on 24 de Março de 2017, 13:48
 */

#include "Iterador.h"

static int it;

Iterador::Iterador() {
}

Iterador::Iterador(const Iterador& orig) {
}

Iterador::~Iterador() {
}

int Iterador::iterar(){
    return it++;
}