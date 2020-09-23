//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//
//Versión: Elena Chaves Hernández, 2019, FEETCE-UGR
//Funciones modificadas: 
//Funciones creadas:set_vertices(...), draw_figure(...), 
//   draw_figure_rev(...), draw_triangles(...), rotar(...)  rev_figure(...)
//Variables creadas: entrada, r, op, NRev, v, vertices, faces
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include <math.h>
#include <string.h>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif
#include <ctype.h>

//Movimientos con parámetros
//Variables globales

//Variables bola
double dRadius=5.2;
GLint slices = 20;
GLint stacks = 20;

void Bola(){

    glutSolidSphere(dRadius, slices, stacks);

}

void Rampa();

void Barrera();

void RampaMovil();

void RampaFija();

void BaseBarrera();

void Fijo();

