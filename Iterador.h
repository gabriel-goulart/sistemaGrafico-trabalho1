/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Iterador.h
 * Author: stt-paulo
 *
 * Created on 24 de Março de 2017, 13:48
 */

#ifndef ITERADOR_H
#define ITERADOR_H

class Iterador {
public:
    Iterador();
    Iterador(const Iterador& orig);
    virtual ~Iterador();
    
    static int iterar();
    
private:
    
};

#endif /* ITERADOR_H */