/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Testes.cpp
 * Author: paulo
 * 
 * Created on 16 de Março de 2017, 10:51
 */

#include "Testes.h"

Testes::Testes() {
}

Testes::Testes(const Testes& orig) {
}

Testes::~Testes() {
}

void Testes::testando_ponto_linha_poligono(){
    
    Ponto *p1 = new Ponto(new Coordenadas(100,20), "1");
    Ponto *p2 = new Ponto(new Coordenadas(200,200), "2");
    Ponto *p3 = new Ponto(new Coordenadas(300,20000), "3");
    
    Linha *l1 = new Linha(p2, p3, "1");
    
    vector<Ponto*> polygon_points;    
        polygon_points.push_back(p3);
        polygon_points.push_back(p2);
        polygon_points.push_back(p1);
        
    Poligono* pol = new Poligono(polygon_points, "1");
    
    DisplayFile* df = new DisplayFile();
    df->add_object(p1);
    df->add_object(l1);
    df->add_object(pol);
    
   
    //=========================================================================   
    vector<Objeto*> class_test;    
        class_test.push_back(p1);
        class_test.push_back(l1);
        class_test.push_back(pol);
        
    Objeto* ob0 = df->get_object_list().at(0);
    Objeto* ob1 = df->get_object_list().at(1);
    Objeto* ob2 = df->get_object_list().at(2);
    
    cout << ob0->get_coordinates().at(0)->get_x()  << endl;
    cout << ob1->get_coordinates().at(0)->get_x()  << endl;
    cout << ob2->get_coordinates().at(0)->get_x()  << endl;
    //=========================================================================
            
}

void Testes::testando_id(){
    Ponto *p1 = new Ponto(new Coordenadas(100,20), "1");
    Ponto *p2 = new Ponto(new Coordenadas(200,200), "2");
    Ponto *p3 = new Ponto(new Coordenadas(300,20000), "3");
    
    Linha *l1 = new Linha(p2, p3, "1");
    
    vector<Ponto*> polygon_points;    
        polygon_points.push_back(p3);
        polygon_points.push_back(p2);
        polygon_points.push_back(p1);
        
    Poligono* pol = new Poligono(polygon_points, "1");
    
    DisplayFile* df = new DisplayFile();
    df->add_object(p1);
    df->add_object(l1);
    df->add_object(pol);

}

