
/* 
 * File:   Curva_B_Spline.cpp
 * Author: gabriel
 * 
 * Created on 26 de Abril de 2017, 16:50
 */

#include "Curva_B_Spline.h"

Curva_B_Spline::Curva_B_Spline() {
}

Curva_B_Spline::Curva_B_Spline(const Curva_B_Spline& orig) {
}

Curva_B_Spline::~Curva_B_Spline() {
}

/**
 * Processa os pontos juntando de 4 em 4 para formar as curvas
 * @param pontos
 * @param precisao
 * @param nome
 * @return 
 */
Curva* Curva_B_Spline::process(vector<Ponto*> pontos, float precisao, string nome)
{
    vector<Ponto*> points_process;
    points.clear();
    int i,size;
    size = pontos.size();
    cout <<"Inicio" <<endl;
    for(i=3; i < size; i++)
    {
        cout <<"processo = " << i  <<endl;
        points_process.clear();
        points_process.push_back(pontos.at(i-3));
        points_process.push_back(pontos.at(i-2));
        points_process.push_back(pontos.at(i-1));
        points_process.push_back(pontos.at(i));
        
        process_curva(points_process,precisao);
        
    }
    
    return new Curva(points,nome);
}

/**
 * Processa os pontos de uma curva
 * @param pontos
 * @param precisao
 */
void Curva_B_Spline::process_curva(vector<Ponto*> pontos, float precisao)
{
    cout <<"Processo curva "<<endl;
   int i,size;
   size = pontos.size();
   float * x= new float[size]; 
   float * y= new float[size];
   float * z= new float[size];
   
   for(i=0;i < size;i++)
   {
       x[i] = pontos.at(i)->get_x();
       y[i] = pontos.at(i)->get_y();
       z[i] = pontos.at(i)->get_z();
       
      
   }
   cout <<"Processo curva 2 "<<endl;
   float t= 0;
   vector<Ponto*> curva_points;
   
   
       cout <<"Coords X :" << x[0] << " ; "<< x[1] << " ; "<< x[2] << " ; "<< x[3]<<endl;
       cout <<"Coords Y :" << y[0] << " ; "<< y[1] << " ; "<< y[2] << " ; "<< y[3]<<endl;
       float* Cx = get_C(x,t);
       float* Cy = get_C(y,t);
       float* Cz = get_C(z,t);
       
        cout <<"C x :" << Cx[0] << " ; "<< Cx[1] << " ; "<< Cx[2] << " ; "<< Cx[3]<<endl;
        cout <<"C y :" << Cy[0] << " ; "<< Cy[1] << " ; "<< Cy[2] << " ; "<< Cy[3]<<endl;

       
       float* f_delta_x = execute_E_x_C(Cx,precisao);
       float* f_delta_y = execute_E_x_C(Cy,precisao);
       float* f_delta_z = execute_E_x_C(Cz,precisao);
       
       cout <<"Delta x :" << f_delta_x[0] << " ; "<< f_delta_x[1] << " ; "<< f_delta_x[2] << " ; "<< f_delta_x[3]<<endl;
       cout <<"Delta y :" << f_delta_y[0] << " ; "<< f_delta_y[1] << " ; "<< f_delta_y[2] << " ; "<< f_delta_y[3]<<endl;
       
       Ponto *ponto_inicial = new Ponto(new Coordenadas(x[0],y[0],z[0]),"ponto curva");
       //this->points.push_back(ponto_inicial);
       
       fwdDiff(1/precisao,f_delta_x[0],f_delta_x[1],f_delta_x[2],f_delta_x[3],f_delta_y[0],f_delta_y[1],f_delta_y[2],f_delta_y[3],f_delta_z[0],f_delta_z[1],f_delta_z[2],f_delta_z[3]);
       
       Ponto *ponto_final = new Ponto(new Coordenadas(x[3],y[3],z[3]),"ponto curva");
      // this->points.push_back(ponto_final);
       
   
}

/**
 * Calcula os coeficientes de A á D
 * @param coords
 * @param t
 * @return 
 */
float* Curva_B_Spline::get_C(float* coords , float t)
{
  //cout <<"Processo curva - get C "<<endl;
  //cout <<"Coords X :" << coords[0] << " ; "<< coords[1] << " ; "<< coords[2] << " ; "<< coords[3]<<endl;
  float * result= new float[4]; 
        result[0] = (float) coords[0]*((float)-1/6) + coords[1]*((float)0.5);
        result[0] += coords[2]*((float)-0.5) + coords[3]*((float)1/6);
        
        result[1] = (float) (coords[0]*(0.5)) + (coords[1]*(-1)) + (coords[2]*(0.5)) + coords[3]*(0);
        result[2] = (float) coords[0]*((float)-(0.5))  + coords[1]*(0)     + coords[2]*((float)(0.5))   + coords[3]*(0);
        result[3] = (float) coords[0]*(((float)1/6))   + coords[1]*((float)2/3)   + coords[2]*(((float)1/6))   + coords[3]*(0);
       
       // cout <<"result :" << result[0] << " ; "<< result[1] << " ; "<< result[2] << " ; "<< result[3]<<endl;
        return result;      
}

/**
 * Realiza a multiplicação entre a matriz E(precisao) e a matriz dos Coeficientes
 * @param coords
 * @param precisao
 * @return 
 */
float* Curva_B_Spline::execute_E_x_C(float* coords, float precisao)
{
    cout <<"Processo curva - execute_E_x_C "<<endl;
    float * result= new float[4]; 
    
    result[0] = coords[3];
    result[1] = coords[0]*pow(precisao,3) + coords[1]*pow(precisao,2) + coords[2]*precisao;
    result[2] = 6*coords[0]*pow(precisao,3) + 2*coords[1]*pow(precisao,2);
    result[3] = 6*coords[0]*pow(precisao,3);
    
    return result;
}

/**
 * Realiza os calculos da forwarding difference
 * @param n
 * @param x
 * @param delta_x
 * @param delta_2_x
 * @param delta_3_x
 * @param y
 * @param delta_y
 * @param delta_2_y
 * @param delta_3_y
 * @param z
 * @param delta_z
 * @param delta_2_z
 * @param delta_3_z
 */
void Curva_B_Spline::fwdDiff(float n, float x, float delta_x, float delta_2_x, float delta_3_x, float y, float delta_y, float delta_2_y, float delta_3_y,float z, float delta_z, float delta_2_z, float delta_3_z)
{
    int i =0;
    float xVelho,yVelho,zVelho;
   
    
    xVelho=x;
    yVelho=y;
    zVelho=z;
    Coordenadas *coord = new Coordenadas(xVelho,yVelho,zVelho);
    Ponto *p = new Ponto(coord,"ponto curva");
    this->points.push_back(p);

    
    //cout <<"n - " << "x - " << "dx - " << "d2x - " << "d3x - " <<"y - " << "dy - " << "d2y - " << "d3y" <<endl;
    //cout <<i << x << delta_x << delta_2_x << delta_3_x << y << delta_y << delta_2_y << delta_3_y <<endl;
    while(i < n)
    {
        i ++;
        x = x + delta_x; delta_x = delta_x + delta_2_x; delta_2_x = delta_2_x + delta_3_x;
        y = y + delta_y; delta_y = delta_y + delta_2_y; delta_2_y = delta_2_y + delta_3_y;
        z = z + delta_z; delta_z = delta_z + delta_2_z; delta_2_z = delta_2_z + delta_3_z;
        
       cout <<i << x << delta_x << delta_2_x << delta_3_x << y << delta_y << delta_2_y << delta_3_y <<endl;
       
        
        
        Coordenadas *coord2 = new Coordenadas(x,y,z);
        Ponto *p2 = new Ponto(coord2,"ponto curva");
        this->points.push_back(p2);
        xVelho=x;
        yVelho=y;
        zVelho=z;
    }
}
