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

#define PI 3.14159265

//Vectores para dibujar en revolución
vector<_vertex3f> rev; //vector de puntos en revolucion
vector<unsigned long> revFaces; //vector con todas las caras de la figura
vector<_vertex3f>::iterator ptrV; //Iterador para estructuras
vector<double>::const_iterator ptrD; //Iterador para estructuras double const
vector<int>::iterator ptrI; //Iterador para estructuras int

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw_cube()
{
    GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_LINES);
    for (unsigned i=0;i<8;i++){
        glVertex3fv((GLfloat *) &Vertices[i]);
        }
    glEnd();
}

//**************************************************************************
// Funcion para cargar vertices
//**************************************************************************

void set_vertices(const vector<double> &Vertices, vector<_vertex3f> &v)
{
  for (ptrD=Vertices.begin();ptrD!=Vertices.end();ptrD+=3){
     _vertex3f _v = _vertex3f((GLfloat) *ptrD,(GLfloat) *(ptrD+1), (GLfloat) *(ptrD+2));
     v.push_back(_v);
  }
}


//**************************************************************************
// Funcion para dibujar figura según opción
//**************************************************************************

void draw_figure(const vector<_vertex3f> &v, const int op, const vector<unsigned long> &Faces){

  switch(op){
	case 1:		
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
  		glPointSize(0.1);

  		glBegin (GL_POINTS);
  		for (unsigned i=0; i<v.size();i++){
		glVertex3f(v[i].x, v[i].y, v[i].z);
 		 }
  		glEnd();
		break;
	case 2:
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		draw_triangles(Faces, v, false);
		break;
	case 3:
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		draw_triangles(Faces, v, false);
		break;
	case 4:
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		draw_triangles(Faces, v, true);
		break;

 }
}

//**************************************************************************
// Funcion para dibujar figura revolucionada según opción
//**************************************************************************
void draw_figure_rev(const int op){

	  draw_figure(rev, op, revFaces);
}
//**************************************************************************
// Funcion para dibujar triángulo (ajedrez == true dibuja color ajedrez)
//**************************************************************************

void draw_triangles(const vector<unsigned long> &Faces, const vector<_vertex3f> &v, const bool ajedrez)
{	

  if(ajedrez == false){
  	glBegin (GL_TRIANGLES);
	  for (unsigned i=0; i<Faces.size();i++){
		glVertex3f((GLfloat) v[Faces[i]].x, (GLfloat) v[Faces[i]].y, (GLfloat) v[Faces[i]].z);
 	 }
 	 glEnd();
  }else{
	glBegin (GL_TRIANGLES);
	  for (unsigned i=0; i<Faces.size();i+=6){
		//Verde
		glColor3f(1,0,0);
		glVertex3f((GLfloat) v[Faces[i]].x, (GLfloat) v[Faces[i]].y, (GLfloat) v[Faces[i]].z);
		glVertex3f((GLfloat) v[Faces[i+1]].x, (GLfloat) v[Faces[i+1]].y, (GLfloat) v[Faces[i+1]].z);
		glVertex3f((GLfloat) v[Faces[i+2]].x, (GLfloat) v[Faces[i+2]].y, (GLfloat) v[Faces[i+2]].z);
		//Rojo
		glColor3f(0,1,0);
		glVertex3f((GLfloat) v[Faces[i+3]].x, (GLfloat) v[Faces[i+3]].y, (GLfloat) v[Faces[i+3]].z);
		glVertex3f((GLfloat) v[Faces[i+4]].x, (GLfloat) v[Faces[i+4]].y, (GLfloat) v[Faces[i+4]].z);
		glVertex3f((GLfloat) v[Faces[i+5]].x, (GLfloat) v[Faces[i+5]].y, (GLfloat) v[Faces[i+5]].z);

 	 }
 	 glEnd();
  }
}

//**************************************************************************
// Funcion para rotar las copias del plano
//**************************************************************************

vector<_vertex3f> rotar(vector<_vertex3f> rot, double rad){

	for(ptrV = rot.begin(); ptrV!=rot.end(); ++ptrV){
		_vertex3f cpy;
		cpy.x = (*ptrV).x * cos(rad) + (*ptrV).z * sin(rad);
		cpy.y = (*ptrV).y;
		cpy.z = (*ptrV).z * cos(rad) - (*ptrV).x * sin(rad);
		*ptrV = cpy;
	}

	return rot;
}

//**************************************************************************
// Funcion para guardar vértices y caras de figura en revolución en las 
//  variables globales una única vez durante la ejecución
//**************************************************************************

void rev_figure(const vector<_vertex3f> &v, vector<unsigned long> &faces, const int N){

	//Meto en un vector de vectores todos los puntos rotados
	for (double rad=0; rad<=2*M_PI; rad+=2*M_PI/N){
		vector<_vertex3f> w;
		w = rotar(v, rad);	
		for(ptrV = w.begin(); ptrV!=w.end(); ++ptrV){
			_vertex3f aux = *ptrV;
     			rev.push_back(aux);
			
		}

	}
	
	//Puntos para las tapas
	_vertex3f tapaSup = _vertex3f( 0, rev[v.size()-1].y, 0);
	rev.push_back(tapaSup);
	_vertex3f tapaInf = _vertex3f( 0, rev[v.size()].y, 0);	
	rev.push_back(tapaInf);

	//Vector con las caras de los laterales
	for(unsigned i=0; i<N; i++){
		for(unsigned j=0; j<v.size()-1; j++){
			//medio cuadrado
			revFaces.push_back(v.size()*i+j);
			revFaces.push_back(v.size()*(i+1)+j);
			revFaces.push_back(v.size()*i+(j+1));
			//medio cuadrado
			revFaces.push_back(v.size()*(i+1)+j);
			revFaces.push_back(v.size()*i+(j+1));
			revFaces.push_back(v.size()*(i+1)+(j+1));
		}
	}

	
	//Caras de la tapa de arriba
	for(unsigned i=0; i<N; i++){
		revFaces.push_back(rev.size()-2);
		revFaces.push_back((v.size()*i)-1);
		revFaces.push_back(v.size()*(i+1)-1);
	}

	 //Caras de la tapa de abajo
	for(unsigned i=0; i<N; i++){
		revFaces.push_back(rev.size()-1);
		revFaces.push_back(v.size()*i);
		revFaces.push_back(v.size()*(i+1));
	}

}
