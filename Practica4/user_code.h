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
// Funcion para cargar vertices una única vez durante la ejecución
//**************************************************************************

void set_vertices(const vector<double> &Vertices, vector<_vertex3f> &v);

//**************************************************************************
// Funcion para dibujar figura según opción en cada cambio de pantalla
//**************************************************************************

void draw_figure(const vector<_vertex3f> &v, const vector<unsigned long> &Faces);

//**************************************************************************
// Funcion para dibujar figura revolucionada según opción con las variables
//  globales que se han modificado para vertices y caras de la figura
//**************************************************************************

void draw_figure_rev(const int op);


//**************************************************************************
// Funcion para rotar las copias del plano
//**************************************************************************

vector<_vertex3f> rotar(vector<_vertex3f> rot, double deg);

//**************************************************************************
// Funcion para guardar vértices y caras de figura en revolución en las 
//  variables globales una única vez durante la ejecución
//**************************************************************************

void rev_figure(const vector<_vertex3f> &v, const int N, vector<_vertex3f> rev, vector<unsigned long> revFaces);


void Lata(const vector<_vertex3f> &vInf, const vector<_vertex3f> &vSup, const vector<_vertex3f> &vCue, const int N);

#endif
