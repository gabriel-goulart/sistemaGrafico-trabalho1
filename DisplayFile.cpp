/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DisplayFile.cpp
 * Author: paulo
 * 
 * Created on 16 de Março de 2017, 15:03
 */

#include "DisplayFile.h"

DisplayFile::DisplayFile() {
}

DisplayFile::DisplayFile(const DisplayFile& orig) {
}

DisplayFile::~DisplayFile() {
}

/**
 * Adiciona um Objeto(Ponto, Linha ou Poligono) à lista de objetos do mundo.
 * @param obj
 */
void DisplayFile::add_object(Objeto* obj){
    this->object_list.push_back(obj);
}

/**
 * Retorna a lista de objetos do mundo.
 * @return 
 */
vector<Objeto*> DisplayFile::get_object_list(){
    return this->object_list;
}
