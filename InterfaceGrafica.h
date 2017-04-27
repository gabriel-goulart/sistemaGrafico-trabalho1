#ifndef INTERFACEGRAFICA_H
#define INTERFACEGRAFICA_H

#include <gtk-3.0/gtk/gtk.h>
#include <vector>
#include "Window.h"
#include "Ponto.h"
#include "Objeto.h"
#include "Poligono.h"
#include "Linha.h"
#include "Coordenadas.h"
#include "DisplayFile.h"
#include "Transformacao.h"
class InterfaceGrafica {
public:
    InterfaceGrafica();
    InterfaceGrafica(const InterfaceGrafica& orig);
    virtual ~InterfaceGrafica();
    
    void load(int argc, char** argv);
    static void destroy_screen();
    static void drawing_point(Ponto *ponto);
    static void drawing_line(Linha *linha);
    static void drawing_polygon(Poligono *p);
    static gboolean create_surface (GtkWidget *widget, GdkEventConfigure *event, gpointer data);
    static void clear_surface ();
    static gboolean redraw (GtkWidget *widget, cairo_t   *cr,  gpointer   data);  
    static Ponto* transform_viewport(Ponto *p);
    static void add_display_file(Objeto *obj);
    static void add_object_list_view(int index);
private:
   
};

#endif /* INTERFACEGRAFICA_H */
