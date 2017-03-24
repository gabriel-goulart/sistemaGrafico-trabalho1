#include <cstring>

#include "InterfaceGrafica.h"


GtkWidget *window_add;      /*Janela auxiliar para adicionar as formas geométricas*/
GtkWidget *window_main;     /*Janela principal do programa*/
GtkWidget * window_transformacao;     /*Janela de transformacao de objeto*/
GtkWidget *viewport;        /*Viewport*/
GtkBuilder *gtkBuilder;     /*Demais itens do programa contidos no glade*/
 GtkWidget *drawing_area;   /*Área de desenho */
Window *window_layout;      /*window de visualização (modelo) */
DisplayFile *display_file;  /*Lista de obejetos do mundo*/
Transformacao *transformacao; /* realiza transformações nos objetos*/
int point_size = 10; /*defini o tamanho do ponto (essencial para o zoom em um ponto) */
static cairo_surface_t *surface = NULL;

/******** FUNÇÕES DE AÇÕES DOS BOTÕES ***********/

/**
 *  zoom in na tela de desenho
 */

extern "C" G_MODULE_EXPORT void btn_zoom_in_clicked(){
    point_size ++;
   window_layout->zoom_in();
}

/**
 *  zoom out na tela de desenho
 */

extern "C" G_MODULE_EXPORT void btn_zoom_out_clicked(){
    point_size --;
   window_layout->zoom_out();
}

/**
 *  movimentação para cima na window
 */

extern "C" G_MODULE_EXPORT void btn_move_up_clicked(){
   
   window_layout->move_window('y',30);
}

/**
 *  movimentação para baixo na window
 */

extern "C" G_MODULE_EXPORT void btn_move_down_clicked(){
   
   window_layout->move_window('y',-30);
}
/**
 *  movimentação para o lado esquerdo na window
 */

extern "C" G_MODULE_EXPORT void btn_move_left_clicked(){
   
   window_layout->move_window('x',-30);
}
/**
 *  movimentação para o lado direito na window
 */

extern "C" G_MODULE_EXPORT void btn_move_right_clicked(){
   
   window_layout->move_window('x',30);
}
/**
 * Habilita a tela de criação de formas geométricas.
 */
extern "C" G_MODULE_EXPORT void btn_add_object_clicked(){
     gtk_widget_show(window_add);
}

/**
 * Ação do botão de fechar e cancelar na tela de adicionar objetos.
 */
extern "C" G_MODULE_EXPORT void close_window_add_object(){     
     gtk_widget_hide(window_add);
 } 
extern "C" G_MODULE_EXPORT void btn_transform_clicked()
{
    gtk_widget_show(window_transformacao);
}
extern "C" G_MODULE_EXPORT void close_window_transform(){     
     gtk_widget_hide(window_transformacao);
 } 

/**
 * Aplica translacao em um objeto selecionado
 */
extern "C" G_MODULE_EXPORT void btn_aplicar_transform_translacao_clicked(){ 
    GtkWidget *spin_button_point_coord_x = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbutton_transform_translacao_dx") );
    GtkWidget *spin_button_point_coord_y = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbutton_transform_translacao_dy") );
    
    float * coords_obj = new float[3];
    coords_obj[0] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_x));
    coords_obj[1] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_y));
    coords_obj[2] = 1;
    cout<<"TRANSLACAO - X : " << coords_obj[0] << " Y : " <<coords_obj[1]<<endl;
     gtk_widget_hide(window_transformacao);
 } 
/**
 * Aplica escalonamento em um objeto selecionado
 */
extern "C" G_MODULE_EXPORT void btn_aplicar_transform_escalonamento_clicked(){ 
    GtkWidget *spin_button_point_coord_x = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbutton_transform_escalonamento_sx") );
    GtkWidget *spin_button_point_coord_y = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbutton_transform_escalonamento_sy") );
    
    float * coords_obj = new float[3];
    coords_obj[0] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_x));
    coords_obj[1] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_y));
    coords_obj[2] = 1;
    cout<<"ESCALONAMENTO - X : " << coords_obj[0] << " Y : " <<coords_obj[1]<<endl;
     gtk_widget_hide(window_transformacao);
 } 
/**
 * Aplica escalonamento em um objeto selecionado
 */
extern "C" G_MODULE_EXPORT void btn_aplicar_transform_rotacao_clicked(){ 
   
    bool centro = false;
    float * coords_obj = new float[3];
    GtkWidget *angulo;
    GtkNotebook *notebook = GTK_NOTEBOOK(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "nt_transform_rotacao") );
    switch(gtk_notebook_get_current_page (notebook)){
        // rotacao na origem
        case 0 : 
            angulo = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbutton_transform_rotacao_origem_angulo") );
            
            coords_obj[0] = 0;
            coords_obj[1] = 0;
            coords_obj[2] = 1; 
            
        break;
        // rotacao no centro do objeto
        case 1 : 
             angulo = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbutton_transform_rotacao_centro_angulo") );
             centro = true; 
        break;
        
        case 2:  
            GtkWidget *coord_x = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbutton_transform_rotacao_ponto_coord_x") );
            GtkWidget *coord_y = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbutton_transform_rotacao_ponto_coord_y") );
            angulo = GTK_WIDGET(gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbutton_transform_rotacao_ponto_angulo") );
            
            coords_obj[0] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(coord_x));
            coords_obj[1] = gtk_spin_button_get_value(GTK_SPIN_BUTTON(coord_y));
            coords_obj[2] = 1; 
        break;
        
    }
    
    cout<<"ESCALONAMENTO - X : " << coords_obj[0] << " Y : " <<coords_obj[1] << " Angulo: " << (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(angulo)) << "centro: " << centro<<endl;
    //transformacao->rotacao(objeto,coords_obj,(int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(angulo)),centro);

     gtk_widget_hide(window_transformacao);
 } 

/**
 * Pega ação do click do botão para adicionar um objeto ponto.
 * @param g
 * @param data
 */
extern "C" G_MODULE_EXPORT void window_add_object_btn_add_point(GtkWidget* g, gpointer data){
    GtkWidget *spin_button_point_coord_x = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbtn_add_object_point_coord_x") );
    GtkWidget *spin_button_point_coord_y = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbtn_add_object_point_coord_y") );
    GtkWidget *entry_name = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "entry_add_object_point_name") );
    
    Coordenadas *coord = new Coordenadas((int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_x)),(int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_y)),0);
    Ponto *p = new Ponto(coord,gtk_entry_get_text(GTK_ENTRY(entry_name)));
    

    InterfaceGrafica::add_display_file(p);
    InterfaceGrafica::drawing_point(p);
 } 

/**
 * Pega ação do click do botão para adicionar um objeto linha.
 * @param g
 * @param data
 */
extern "C" G_MODULE_EXPORT void window_add_object_btn_add_line(GtkWidget* g, gpointer data){    
    GtkWidget *spin_button_point_coord_x = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbtn_add_object_line_point1_coord_x") );
    GtkWidget *spin_button_point_coord_y = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbtn_add_object_line_point_coord_y") );
    GtkWidget *entry_name = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "entry_add_object_line_name") );
    
    //ponto 1 da linha
    Coordenadas *coord = new Coordenadas((int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_x)),(int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_y)),0);
    Ponto *p1 = new Ponto(coord,gtk_entry_get_text(GTK_ENTRY(entry_name)));
    
    spin_button_point_coord_x = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbtn_add_object_line_point2_coord_x") );
    spin_button_point_coord_y = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbtn_add_object_line_point2_coord_y") );
    
   Coordenadas *coord2 = new Coordenadas((int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_x)),(int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_y)),0);
   Ponto *p2 = new Ponto(coord2,gtk_entry_get_text(GTK_ENTRY(entry_name)));
   
    Linha *l = new Linha(
           p1,
           p2,
           gtk_entry_get_text(GTK_ENTRY(entry_name)));
    
    InterfaceGrafica::add_display_file(l);
    InterfaceGrafica::drawing_line(l);    
}

/**
 * Pega ação do click do botão para adicionar um objeto poligono.
 * @param g
 * @param data
 */
vector<Ponto*> polygon_points;
extern "C" G_MODULE_EXPORT void window_add_object_btn_add_polygon(GtkWidget* g, gpointer data)
{
     GtkWidget *entry_name = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "entry_add_object_polygon_name") );
    
    if(std::strcmp(gtk_button_get_label (GTK_BUTTON(g)),"Adicionar Ponto") == 0){
        GtkWidget *spin_button_point_coord_x = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbtn_add_object_polygon_point_coord_x") );
        GtkWidget *spin_button_point_coord_y = GTK_WIDGET( 
            gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "spinbtn_add_object_polygon_point1_coord_y") );
        
        Coordenadas *coord = new Coordenadas((int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_x)),(int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_point_coord_y)),0);
        Ponto *p = new Ponto(coord, gtk_entry_get_text(GTK_ENTRY(entry_name)));
        polygon_points.push_back(p);
        
    }else{
        Poligono *p = new Poligono(polygon_points, gtk_entry_get_text(GTK_ENTRY(entry_name)));
        polygon_points.clear();
	InterfaceGrafica::add_display_file(p);
        InterfaceGrafica::drawing_polygon(p);
    }
}

/******** FIM DAS FUNÇÕES DE AÇÕES DOS BOTÕES ***********/

/**
 * Limpa a camada de desenho.
 */
void InterfaceGrafica::clear_surface (){
  cairo_t *cr;
  cr = cairo_create (surface);
  
  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

/**
 * Cria a camada para desenhar.
 * @param widget
 * @param event
 * @param data
 * @return 
 */
gboolean InterfaceGrafica::create_surface (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
  if (surface)
    cairo_surface_destroy (surface);

  surface = gdk_window_create_similar_surface (
          gtk_widget_get_window (widget),
          CAIRO_CONTENT_COLOR,
          gtk_widget_get_allocated_width (widget),
          gtk_widget_get_allocated_height (widget));
  
  clear_surface ();
  return TRUE;
}

/**
 * Posiciona a superfície de desenho
 * @param widget
 * @param cr
 * @param data
 * @return 
 */
gboolean InterfaceGrafica::redraw (GtkWidget *widget, cairo_t *cr,  gpointer data){
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);
  clear_surface ();
  int size = display_file->get_object_list().size();
  //g_print("sizeDF: %d\n", size);
  
  for(int i=0; i < size;i++)
  {
      if(Ponto* vp = dynamic_cast<Ponto*>(display_file->get_object_list().at(i))) {
          InterfaceGrafica::drawing_point(vp);
      }else if(Linha* vl = dynamic_cast<Linha*>(display_file->get_object_list().at(i))){
          InterfaceGrafica::drawing_line(vl);
      }else if(Poligono* vpol = dynamic_cast<Poligono*>(display_file->get_object_list().at(i))){
          InterfaceGrafica::drawing_polygon(vpol);
          //g_print("redraw: %d", i);
      }
  } 
  
  return FALSE;
}

/*********** FUNÇÕES DE DESENHO ***********/

/**
 * Desenha o ponto.
 * @param x
 * @param y
 */
void InterfaceGrafica::drawing_point(Ponto *p){
    Ponto *p2 = InterfaceGrafica::transform_viewport(p);
    cairo_t *cr;
    cr = cairo_create (surface);
    
    cairo_set_line_width (cr, point_size);
    cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND); /* Round dot*/    
    cairo_move_to (cr, p2->get_coordinates().at(0)->get_x(), p2->get_coordinates().at(0)->get_y()); cairo_line_to (cr, p2->get_coordinates().at(0)->get_x(), p2->get_coordinates().at(0)->get_y());/* a very short line is a dot */
    cairo_stroke(cr);
    
    gtk_widget_queue_draw (window_main);
    cairo_destroy (cr);
}

/**
 * Desenha a linha.
 * @param linha
 */
void InterfaceGrafica::drawing_line(Linha * linha){
    Ponto* p1 = InterfaceGrafica::transform_viewport(new Ponto(linha->get_coordinates().at(0),"ponto transformacao"));
    Ponto* p2 = InterfaceGrafica::transform_viewport(new Ponto(linha->get_coordinates().at(1),"ponto transformacao"));
    cairo_t *cr;
    cr = cairo_create (surface);
 
    cairo_move_to(cr,p1->get_x(), p1->get_y()); //pega o ponto 1 da linha
    cairo_line_to(cr,p2->get_x(), p2->get_y()); //pega o ponto 2 da linha
    cairo_stroke(cr);
    
    gtk_widget_queue_draw (window_main);
    cairo_destroy (cr);
}

/**
 * Desenha um poligono.
 * @param *poligono
 */
void InterfaceGrafica::drawing_polygon(Poligono *poligono){
    cairo_t *cr;
    cr = cairo_create (surface);    
    int i, index;
    int size = poligono->get_coordinates().size();
    //g_print("size 2: %d\n", size);
    for(i = 0; i < size; i++){
        index = i+1;
        
        if(i == size-1){
            index = 0;
        }
         Ponto* p1 = InterfaceGrafica::transform_viewport(new Ponto(poligono->get_coordinates().at(i),"ponto transformacao"));
         Ponto* p2 = InterfaceGrafica::transform_viewport(new Ponto(poligono->get_coordinates().at(index),"ponto transformacao"));
        
        cairo_move_to(cr, p1->get_x(), p1->get_y());
        cairo_line_to(cr, p2->get_x(), p2->get_y());
       // g_print("teste %d\n", i);
        
        cairo_stroke(cr);
       
    }
   // g_print("aqui");   
   
    gtk_widget_queue_draw (window_main);
    cairo_destroy (cr);
}

/**
 * transformacao da window para viewport
 * @param p
 * @return ponto transformado
 */

Ponto* InterfaceGrafica::transform_viewport(Ponto* ponto){    
    /*double aux0, aux1, aux2, x, y;  
    Ponto *vp_min = new Ponto(new Coordenadas(0,0,0),"pviewportMIN");
    Ponto *vp_max = new Ponto(new Coordenadas(480,500,0),"pviewportMAX");

    aux0 = ponto->get_x() - window_layout->get_x_min();
    aux1 = window_layout->get_x_max() - window_layout->get_x_min();
    aux2 = vp_max->get_coordinates().at(0)->get_x() - vp_min->get_coordinates().at(0)->get_x();  
    x = (aux0/aux1)*(aux2);

    aux0 = ponto->get_y() - window_layout->get_y_min();
    aux1 = window_layout->get_y_max() - window_layout->get_y_min();
    aux2 = vp_max->get_coordinates().at(0)->get_y() - vp_min->get_coordinates().at(0)->get_y();
    y = (1-(aux0/aux1))*(aux2);
    
    g_print("x window = %d, ",window_layout->get_x_max());
    g_print("y window = %d\n",window_layout->get_y_max());
      
    g_print("x orig = %d, ", ponto->get_x());
    g_print("y orig = %d\n", ponto->get_y());
    g_print("x trans = %f, ", x);
    g_print("y trans = %f\n", y);

    return new Ponto(new Coordenadas(x,y,0),"ponto transformado"); */
    return transformacao->transformacao_viewport(ponto,window_layout);
}

/**
 * Adiciona um objeto no displayFile 
 * @param obj
 */
void InterfaceGrafica::add_display_file(Objeto *obj){
    display_file->add_object(obj);
}
/********* FIM DAS FUNÇÕES DE DESENHO *********/

InterfaceGrafica::InterfaceGrafica() {
}

InterfaceGrafica::InterfaceGrafica(const InterfaceGrafica& orig) {
}

InterfaceGrafica::~InterfaceGrafica() {
}

/**
 * Destroi a tela.
 */
void InterfaceGrafica::destroy_screen(){
    gtk_main_quit ();
}

/**
 * Carrega a interface.
 * @param argc
 * @param argv
 */
void InterfaceGrafica::load(int argc, char** argv){     
  gtk_init(&argc, &argv);

  gtkBuilder = gtk_builder_new();
  gtk_builder_add_from_file(gtkBuilder, "window.glade", NULL);
  window_main = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "window_main") );
  viewport = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "viewport1") );
  window_add = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "window_add_object") );
  window_transformacao = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "window_transformacao") );
  drawing_area = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawing_area") );
 
  g_signal_connect (window_main, "destroy",G_CALLBACK (destroy_screen), NULL);
  g_signal_connect (drawing_area, "draw", G_CALLBACK (redraw), NULL);
  g_signal_connect (drawing_area, "configure-event", G_CALLBACK (create_surface), NULL); 
  

  Coordenadas *coord_ponto_max = new Coordenadas(480,500,0);
  Coordenadas *coord_ponto_min = new Coordenadas(0,0,0);
  
  // criando a window de visualização (modelo)
  window_layout = new Window(new Ponto(coord_ponto_min,"min_window"), new Ponto(coord_ponto_max,"max_window"));
  
  // criando o displayFile
  display_file = new DisplayFile();
  
  transformacao = new Transformacao(2);
 
  gtk_builder_connect_signals(gtkBuilder, NULL);
  gtk_widget_show_all(window_main);

  gtk_main ();
}