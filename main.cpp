#include "InterfaceGrafica.h"
#include "Testes.h"
#include <cstdlib>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    InterfaceGrafica screen;
    screen.load(argc,argv);
    return 0;
    
    Testes t;
    t.testando_id();
    
}
