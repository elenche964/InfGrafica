//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//
//Versión: Elena Chaves Hernández, 2019, FEETCE-UGR
//Funciones modificadas: draw_objects() a draw_objects(op, est),
//   normal_keys(...) y main(..)
//Funciones creadas: draw_tetrahedron(), draw_cube(), draw_tetrahedron_chess(),
//  draw_cube_chess(), SelectMenu()
//Variables creadas: opcion, estilo
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>

// tamaño de los ejes
const int AXIS_SIZE=5000;

//Variables globales para opciones
int opcion;
int estilo;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funciones que dibujan el tetraedro y cubo
//***************************************************************************

void draw_tetrahedron(){
	glBegin(GL_TRIANGLES);
		glVertex3f(1,1,0);
		glVertex3f(1,4,0);
		glVertex3f(2.5,2.5,3.7);
		glVertex3f(4,1,0);
		glVertex3f(1,4,0);
		glVertex3f(2.5,2.5,3.7);
		glVertex3f(1,1,0);
		glVertex3f(4,1,0);
		glVertex3f(2.5,2.5,3.7);
		glVertex3f(1,1,0);
		glVertex3f(4,1,0);
		glVertex3f(1,4,0);
	glEnd();
}

void draw_cube(){
	//Primer abanico
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(2,2,2);
		glVertex3f(-2,2,2);
		glVertex3f(-2,-2,2);
		glVertex3f(2,-2,2);
		glVertex3f(2,-2,-2);
		glVertex3f(2,2,-2);
		glVertex3f(-2,2,-2);
		glVertex3f(-2,2,2);
	glEnd();
	//Segundo abanico
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-2,-2,-2);
		glVertex3f(-2,2,2);
		glVertex3f(-2,-2,2);
		glVertex3f(2,-2,2);
		glVertex3f(2,-2,-2);
		glVertex3f(2,2,-2);
		glVertex3f(-2,2,-2);
		glVertex3f(-2,2,2);
	glEnd();
}


//**************************************************************************
// Funciones que dibujan el tetraedro y cubo con relleno ajedrez
//***************************************************************************

void draw_tetrahedron_chess(){

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);
		glColor3f(0,1,0);
		glVertex3f(1,1,0);
		glVertex3f(1,4,0);
		glVertex3f(2.5,2.5,3.7);
		glColor3f(1,1,0);
		glVertex3f(4,1,0);
		glVertex3f(1,4,0);
		glVertex3f(2.5,2.5,3.7);
		glColor3f(0,0,1);
		glVertex3f(1,1,0);
		glVertex3f(4,1,0);
		glVertex3f(2.5,2.5,3.7);
		glColor3f(1,0,0);
		glVertex3f(1,1,0);
		glVertex3f(4,1,0);
		glVertex3f(1,4,0);
		glEnd();
}

void draw_cube_chess(){

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Primer abanico de triángulos
	glBegin(GL_TRIANGLES);
	 glColor3f(1,0,0);
	 glVertex3f(2,2,-2);
	 glVertex3f(-2,2,-2);
	 glVertex3f(2,2,2);
	 glColor3f(0,1,0);
	 glVertex3f(2,2,2);
	 glVertex3f(-2,2,-2);
	 glVertex3f(-2,2,2);
	 glColor3f(1,0,0);
	 glVertex3f(2,2,2);
	 glVertex3f(-2,2,2);
	 glVertex3f(-2,-2,2);
	 glColor3f(0,1,0);
	 glVertex3f(2,2,2);
	 glVertex3f(-2,-2,2);
	 glVertex3f(2,-2,2);
	 glColor3f(1,0,0);
	 glVertex3f(2,2,2);
	 glVertex3f(2,-2,2);
	 glVertex3f(2,-2,-2);
	 glColor3f(0,1,0);
	 glVertex3f(2,2,-2);
	 glVertex3f(2,2,2);
	 glVertex3f(2,-2,-2);
	glEnd();
	//Segundo abanico de triángulos
	glBegin(GL_TRIANGLES);
	 glColor3f(1,0,0);
	 glVertex3f(-2,-2,-2);
	 glVertex3f(2,2,-2);
	 glVertex3f(2,-2,-2);
	 glColor3f(0,1,0);
	 glVertex3f(-2,-2,-2);
	 glVertex3f(2,-2,-2);
	 glVertex3f(2,-2,2);
	 glColor3f(1,0,0);
	 glVertex3f(-2,-2,-2);
	 glVertex3f(2,-2,2);
	 glVertex3f(-2,-2,2);
	 glColor3f(0,1,0);
	 glVertex3f(-2,-2,-2);
	 glVertex3f(-2,-2,2);
	 glVertex3f(-2,2,2);
	 glColor3f(1,0,0);
	 glVertex3f(-2,-2,-2);
	 glVertex3f(-2,2,2);
	 glVertex3f(-2,2,-2);
	 glColor3f(0,1,0);
	 glVertex3f(-2,-2,-2);
	 glVertex3f(2,2,-2);
	 glVertex3f(-2,2,-2);
	glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects(int op, int est)
{

glColor3f(0.99,0.914,0.31);
glPointSize(6);

	switch (est){
		case 1:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		case 2:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 3:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case 4:
			if (op==1){
				draw_tetrahedron_chess();
				op=3;
			}
			if(op==2){
				draw_cube_chess();
				op=3;
			}
			break;
	}

	switch (op){
		case 1:
			draw_tetrahedron();
			break;

		case 2:
			draw_cube();
			break;
	}
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects(opcion, estilo);
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
if (toupper(Tecla1)=='Q') exit(0);

//Opciones:
//1.Tetraedro puntos
//2.Tetraedro alambre
//3.Tetraedro sólido
//4.Tetraedro ajedrez
//5.Cubo puntos
//6.Cubo alambre
//7.Cubo sólido
//8.Cubo ajedrez

else if (Tecla1=='1'){
	opcion=1;
	estilo=1;
}
else if (Tecla1=='2'){
	opcion=1;
	estilo=2;
}
else if (Tecla1=='3'){
	opcion=1;
	estilo=3;
}
else if (Tecla1=='4'){
	opcion=1;
	estilo=4;
}
else if (Tecla1=='5'){
	opcion=2;
	estilo=1;
}
else if (Tecla1=='6'){
	opcion=2;
	estilo=2;
}
else if (Tecla1=='7'){
	opcion=2;
	estilo=3;
}
else if (Tecla1=='8'){
	opcion=2;
	estilo=4;
}

//Para que pinte en cuanto pulso la tecla, sin tener que cambiar vista
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}

void SelectMenu(){
	printf("%s\n", "Opciones:\n1.Tetraedro puntos\n2.Tetraedro alambre\n3.Tetraedro sólido\n4.Tetraedro ajedrez\n5.Cubo puntos\n6.Cubo alambre\n7.Cubo sólido\n8.Cubo ajedrez\n");
}
//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
SelectMenu();

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Practica 1-Elena Chaves Hernandez");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
