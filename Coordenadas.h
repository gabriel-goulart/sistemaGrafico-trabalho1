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
    Coordenadas(int x, int y, int z = 0);
    Coordenadas(const Coordenadas& orig);
    virtual ~Coordenadas();
    
    int get_x();
    int get_y();
    int get_z();
    void set_x(int);
    void set_y(int);
    void set_z(int);
private:
    int x;
    int y;
    int z;

};

#endif /* COORDENADAS_H */

