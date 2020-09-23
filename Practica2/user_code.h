//**************************************************************************
// Práctica 2
//
// Domingo Martin Perandres 2013
//
//Versión: Elena Chaves Hernández, 2019, FEETCE-UGR
//Funciones eliminadas: 
//Funciones creadas:set_vertices(...), draw_figure(...), 
//   draw_figure_rev(...), draw_triangles(...), rotar(...)  rev_figure(...)
// GPL
//**************************************************************************

#ifndef USER_CODE_H
#define USER_CODE_H

#include <GL/gl.h>
#include <iterator>
#include <vector>
#include "vertex.h"

using namespace std;

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************
void draw_cube();

//**************************************************************************
// Funcion para cargar vertices una única vez durante la ejecución
//**************************************************************************

void set_vertices(const vector<double> &Vertices, vector<_vertex3f> &v);

//**************************************************************************
// Funcion para dibujar figura según opción en cada cambio de pantalla
//**************************************************************************

void draw_figure(const vector<_vertex3f> &v, const int op, const vector<unsigned long> &Faces);

//**************************************************************************
// Funcion para dibujar figura revolucionada según opción con las variables
//  globales que se han modificado para vertices y caras de la figura
//**************************************************************************

void draw_figure_rev(const int op);

//**************************************************************************
// Funcion para dibujar los triángulos
//**************************************************************************

void draw_triangles(const vector<unsigned long> &Faces, const vector<_vertex3f> &v, const bool ajedrez);

//**************************************************************************
// Funcion para rotar las copias del plano
//**************************************************************************

vector<_vertex3f> rotar(vector<_vertex3f> rot, double deg);

//**************************************************************************
// Funcion para guardar vértices y caras de figura en revolución en las 
//  variables globales una única vez durante la ejecución
//**************************************************************************

void rev_figure(const vector<_vertex3f> &v, vector<unsigned long> &faces, const int N);

#endif
