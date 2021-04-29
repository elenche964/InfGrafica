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
//Poner las normales para dentro y para fuera, calcularlas y poner todas
//multiplicadas por menos uno para encontrar la contraria(sentido opuesto)
//Las luces en una direccion no se pueden mover, lo suyo es poner varias
//luces para que se vean
//**************************************************************************

#include "user_code.h"
#include "vertex.h"
#include <math.h>
#include <string.h>

#define PI 3.14159265

//Vectores para dibujar en revolución
vector<_vertex3f>::iterator ptrV; //Iterador para estructuras
vector<double>::const_iterator ptrD; //Iterador para estructuras double const
vector<int>::iterator ptrI; //Iterador para estructuras int

class Figura{
    
    public:  
        vector<_vertex3f> rev;
        vector<unsigned long> revFaces;
        vector<_vertex3f> normalCaras;
        vector<_vertex3f> normalVertices;
}

Figura lata = new Figura();

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

void draw_figure(const vector<_vertex3f> &v, const vector<unsigned long> &Faces){

		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  		glPointSize(0.1);

  		glBegin (GL_TRIANGLES);
	  for (unsigned i=0; i<Faces.size();i++){
		glVertex3f((GLfloat) v[Faces[i]].x, (GLfloat) v[Faces[i]].y, (GLfloat) v[Faces[i]].z);
 	 }
 	 glEnd();


}

//**************************************************************************
// Funcion para dibujar figura revolucionada según opción
//**************************************************************************
void draw_figure_rev(const int op){

	  draw_figure(lata.rev, lata.revFaces);
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

void rev_figure(const vector<_vertex3f> &v, const int N, vector<_vertex3f> rev, vector<unsigned long> revFaces){

	//Meto en un vector de vectores todos los puntos rotados
	for (double rad=0; rad<=2*M_PI; rad+=2*M_PI/N){
		vector<_vertex3f> w;
		w = rotar(v, rad);	
		for(ptrV = w.begin(); ptrV!=w.end(); ++ptrV){
			_vertex3f aux = *ptrV;
     			rev.push_back(aux);
			
		}

	}

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


}

void Lata(const vector<_vertex3f> &vInf, const vector<_vertex3f> &vSup, const vector<_vertex3f> &vCue, const int N){

    rev_figure(vInf, N, lata.rev, lata.revFaces);
}
