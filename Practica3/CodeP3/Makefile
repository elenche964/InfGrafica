# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica2

#variable para los objetos que se utilizarán en el programa principal
OBJS= file_ply_stl.o user_code.o

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraci�n
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default : $(OBJS) $(TARGETS)

# regla de ejecucion
#
$(TARGETS) : practica3.o
	$(CC) -o $@ $(CXXFLAGS) practica3.o $(OBJS) $(LDFLAGS)

%.o: %.cc %.h
	$(CC) $(CFLAGS) -c $< -o $@

#
#
clean:
	rm -f *.o
	rm -f $(TARGETS) $(OBJS)

#
#
redo:
	touch *.cpp
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS) $(OBJS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS) $(OBJS)
	tar -zcvf $(TARGETS).tgz  $(OBJS).tgz *
