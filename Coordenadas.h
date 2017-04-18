/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Coordenadas.h
 * Author: stt-paulo
 *
 * Created on 17 de Março de 2017, 14:24
 */

#ifndef COORDENADAS_H
#define COORDENADAS_H

class Coordenadas {
public:
    Coordenadas(float x, float y, float z = 0);
    Coordenadas(const Coordenadas& orig);
    virtual ~Coordenadas();
    
    float get_x();
    float get_y();
    float get_z();
    void set_x(float);
    void set_y(float);
    void set_z(float);
private:
    float x;
    float y;
    float z;

};

#endif /* COORDENADAS_H */

