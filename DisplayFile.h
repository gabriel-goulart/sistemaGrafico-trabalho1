/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DisplayFile.h
 * Author: paulo
 *
 * Created on 16 de Março de 2017, 15:03
 */

#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include "Objeto.h"
#include <vector>

class DisplayFile {
public:
    DisplayFile();
    DisplayFile(const DisplayFile& orig);
    virtual ~DisplayFile();
    
    void add_object(Objeto*);
    vector<Objeto*> get_object_list();
    
private:
    vector<Objeto*> object_list;
};

#endif /* DISPLAYFILE_H */

