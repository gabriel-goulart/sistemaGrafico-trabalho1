/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transformacao.cpp
 * Author: gabriel
 * 
 * Created on 23 de Março de 2017, 00:44
 */

#include "Transformacao.h"
#include <cstdlib>

using namespace std;
Transformacao::Transformacao(int dim) {
    this->dimensao = dim;
}

Transformacao::Transformacao(const Transformacao& orig) {
}

Transformacao::~Transformacao() {
}

/**
 * Translação para 2d e 3d
 * @param obj
 * @param coords
 * @return 
 */
Objeto* Transformacao::translacao(Objeto* obj,float* coords)
{
    int i;
    float** matriz = get_matriz_translacao(coords);
    int size = this->dimensao +1;  
    Objeto * obj_transformacao = obj;
    
    for(i=0; i < obj_transformacao->get_coordinates().size();i++)
    {
        float * coords_obj = new float[size];
        coords_obj[0]= obj_transformacao->get_coordinates().at(i)->get_x();
        coords_obj[1]= obj_transformacao->get_coordinates().at(i)->get_y();
        
        if(size > 3)
        {
          coords_obj[2]= obj_transformacao->get_coordinates().at(i)->get_z();
          coords_obj[3]= 1;
        }else{
          coords_obj[2]= 1;  
        }
        
        coords_obj = transformar(matriz,coords_obj);
        
        obj_transformacao->get_coordinates().at(i)->set_x(coords_obj[0]);
        obj_transformacao->get_coordinates().at(i)->set_y(coords_obj[1]);
        obj_transformacao->get_coordinates().at(i)->set_z(coords_obj[2]);
        
    }
   
    obj= obj_transformacao;
    return obj;
}

/**
 * translaçao usando coordenadas ao inves de objetos 
 * @param coords_point
 * @param coords
 * @return 
 */
float* Transformacao::translacao(float* coords_point,float* coords)
{
    int i;
    float** matriz = get_matriz_translacao(coords);
    int size = this->dimensao +1;  
    
    float *coord = transformar(matriz,coords_point);
    return coord;
}
/**
 * Realiza o escalonamento do objeto
 * @param obj
 * @param coords
 * @return 
 */
Objeto* Transformacao::escalonamento(Objeto* obj,float* coords)
{
   int i;int size = this->dimensao +1; 
   float** matriz = get_matriz_escalonamento(coords);
   float* coord_centro = get_objeto_centro(obj);
   float* coord_centro_negativo = new float[size];
   coord_centro_negativo[0] = -1*coord_centro[0];
   coord_centro_negativo[1] = -1*coord_centro[1];
   
   if(size > 3)
       {
          coord_centro_negativo[2]= -1*coord_centro[2];
          coord_centro_negativo[3]= coord_centro[3];
       }else{
          coord_centro_negativo[2]= coord_centro[2];  
       }
  
    
   Objeto * obj_transformacao = obj;
   
   for(i=0; i<obj_transformacao->get_coordinates().size();i++)
   {
       float * coords_obj = new float[size];
       coords_obj[0]= obj_transformacao->get_coordinates().at(i)->get_x();
       coords_obj[1]= obj_transformacao->get_coordinates().at(i)->get_y();
       
       if(size > 3)
       {
          coords_obj[2]= obj_transformacao->get_coordinates().at(i)->get_z();
          coords_obj[3]= 1;
       }else{
          coords_obj[2]= 1;  
       }
       
       float ** m = get_matriz_translacao(coord_centro_negativo);   
       
    
       coords_obj = transformar(get_matriz_translacao(coord_centro_negativo),coords_obj);
       coords_obj = transformar(matriz,coords_obj);
       
       coords_obj = transformar(get_matriz_translacao(coord_centro),coords_obj);
       
       obj_transformacao->get_coordinates().at(i)->set_x(coords_obj[0]);
       obj_transformacao->get_coordinates().at(i)->set_y(coords_obj[1]);
       obj_transformacao->get_coordinates().at(i)->set_z(coords_obj[2]);
   }
   
   obj= obj_transformacao;
   return obj;
}

float* Transformacao::escalonamento(float* coord_obj,float* coords)
{
   int i;int size = this->dimensao +1; 
   float** matriz = get_matriz_escalonamento(coords);
   
   
   float * coords_obj = new float[size];
   coords_obj = transformar(matriz,coord_obj);
   return coords_obj;
}

Objeto* Transformacao::rotacao(Objeto* obj,float* coords,int angulo, bool centro)
{
    int i;int size = this->dimensao +1; 
    float** matriz = get_matriz_rotacao(angulo);
    if(centro)
    {coords = get_objeto_centro(obj);}
    
    float* coords_negativo = new float[3];
    coords_negativo[0] = -1*coords[0];
    coords_negativo[1] = -1*coords[1];
    coords_negativo[2] =  coords[2];
    
    Objeto * obj_transformacao = obj;
    for(i=0; i< obj_transformacao->get_coordinates().size();i++)
    {
       float * coords_obj = new float[size];
       coords_obj[0]= obj_transformacao->get_coordinates().at(i)->get_x();
       coords_obj[1]= obj_transformacao->get_coordinates().at(i)->get_y();
       coords_obj[2]= 1;  
       
      
       
       coords_obj = transformar(get_matriz_translacao(coords_negativo),coords_obj);
       coords_obj = transformar(matriz,coords_obj);
       coords_obj = transformar(get_matriz_translacao(coords),coords_obj);
       
       obj_transformacao->get_coordinates().at(i)->set_x(coords_obj[0]);
       obj_transformacao->get_coordinates().at(i)->set_y(coords_obj[1]);
       obj_transformacao->get_coordinates().at(i)->set_z(coords_obj[2]);
    }
   
   obj= obj_transformacao;
   return obj;
}

float* Transformacao::rotacao(float* coord_obj,float* coords,int angulo)
{
    int i;int size = this->dimensao +1; 
    float** matriz = get_matriz_rotacao(angulo);
    float * coords_obj = new float[size];
    coords_obj = transformar(matriz,coord_obj);
    return coords_obj;
   
}
/**
 * Realiza a multiplicação de matrizes para qualquer tipo de transformação
 * @param m
 * @param coords
 * @return 
 */
float* Transformacao::transformar(float** m, float* coords)
{
    int i,y;
    float soma;
    int size = this->dimensao +1;  
    float * coords_transformadas = new float[size];
    
    for(y=0;y < size; y++)
    {
        soma=0;
        for(i=0; i<size;i++)
        {
            soma += (coords[i]*m[i][y]);
        }
        coords_transformadas [y] = soma;
    }
    
    return coords_transformadas;
}

/**
 * Faz a multiplicação de matrizes quadradas
 * @param m1
 * @param m2
 * @return 
 */
float ** Transformacao::transformar(float** m1, float** m2)
{
    int i,j,X;
    
    float Aux =0;
    int size = this->dimensao +1;  
    float** matriz_resultante = new float*[size];
    for(int i = 0; i < size; ++i)
        matriz_resultante[i] = new float[size];
    // percorre a linha na matriz m1
    for(i=0; i<size; i++)
    {
        //percorre a coluna na matriz m2
        for(j=0; j<size; j++)
        {
                 matriz_resultante[i][j]=0;
                 // percorre a coluna na matriz m1 e a linha na matriz m2
                 for(X=0; X<size; X++)
                 {
                    Aux += m1[i][X] * m2[X][j];
                 }
                 matriz_resultante[i][j]=Aux;
                 Aux=0;
         }
    }
        
    return  matriz_resultante;
}

/**
 * Retorna as coordenadas centrais do objeto
 * @param coord
 * @return 
 */
float* Transformacao::get_objeto_centro(Objeto* obj)
{
    int i;
    float somaX=0; float somaY = 0;float somaZ;
    int size = this->dimensao +1;  
    float * coords_centro = new float[size];
    for(i=0; i < obj->get_coordinates().size(); i++)
    {
        somaX += obj->get_coordinates().at(i)->get_x();
        somaY += obj->get_coordinates().at(i)->get_y();
        somaZ += obj->get_coordinates().at(i)->get_z();
    }
    coords_centro[0] = somaX / obj->get_coordinates().size();
    coords_centro[1] = somaY / obj->get_coordinates().size();
    if(size > 3)
       {
          coords_centro[2]= somaY / obj->get_coordinates().size();
          coords_centro[3]= 1;
       }else{
          coords_centro[2]= 1;  
       }
    return coords_centro;
}
/**
 * gerando a matriz para realizar a translação
 * @param d
 * @return 
 */
float** Transformacao::get_matriz_translacao(float * d)
{
  int size = this->dimensao +1;  
  //int **matriz_translacao= new int**[3][3];  
  float** matriz_translacao = new float*[size];
    for(int i = 0; i < size; ++i)
        matriz_translacao[i] = new float[size];
  int i,y;
  
  for(i=0; i < size; i++ )
  {
      
      for(y=0; y < size; y++)
      {
          if(i == y)
          {
              matriz_translacao [i][y] = 1;
          }else{
              if(i == size-1){
                  matriz_translacao [i][y] = d[y];
              }else{
                   matriz_translacao [i][y] = 0;
              }
             
          }
      }
       
  }
  
  return matriz_translacao;
}
/**
 * gerando a matriz para realizar o escalonamento
 * @param r
 * @return 
 */
float ** Transformacao::get_matriz_escalonamento(float * r)
{
  int size = this->dimensao +1;  

  float** matriz_escalonamento = new float*[size];
  for(int i = 0; i < size; ++i)
        matriz_escalonamento[i] = new float[size];
  int i,y;
  
  for(i=0; i < size; i++)
  {
      for(y=0; y < size; y++)
      {
          if(y == i)
          {
              if(i == size-1)
              {
                matriz_escalonamento [i][y] = 1;  
              }else{
                matriz_escalonamento [i][y] = r[y];
              }
          }else{
              matriz_escalonamento [i][y] = 0;
          }
      }
  }
  return matriz_escalonamento;
}

/**
 * gerando a matriz para realizar rotacao
 * @param angulo
 * @return 
 */
float ** Transformacao::get_matriz_rotacao(int angulo)
{
  int size = this->dimensao +1;  

  float** matriz_rotacao = new float*[size];
  for(int i = 0; i < size; ++i)
        matriz_rotacao[i] = new float[size];
  int i,y;
  
  for(i=0;i<size;i++)
  {
      for(y=0;y<size;y++)
      {
          if(y == i)
          {
              if(i == size-1)
              {
                  matriz_rotacao[i][y] = 1;
              }else
              {
                 matriz_rotacao[i][y] = (float) cos(angulo); 
              }
          }else{
              if(i != size-1 and y != size-1)
              {
                 if(i == 0)
                 {
                    matriz_rotacao[i][y] = (float) -1* sin(angulo); 
                 }else
                 {
                     matriz_rotacao[i][y] = (float) sin(angulo);
                 }
              }else{
                  matriz_rotacao[i][y] = 0;
              }
          }
      }
  }
  return matriz_rotacao;
}
