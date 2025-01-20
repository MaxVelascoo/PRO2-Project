
FLAGS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Cluster.o Area_de_espera.o Procesador.o Proceso.o
	g++ -o program.exe program.o Cluster.o Area_de_espera.o Procesador.o Proceso.o
program.o: program.cc Cluster.hh Area_de_espera.hh Procesador.hh Proceso.hh
	g++ -c program.cc $(FLAGS)
Cluster.o: Cluster.cc Cluster.hh Procesador.hh Proceso.hh
	g++ -c Cluster.cc $(FLAGS)
Area_de_espera.o: Area_de_espera.cc Area_de_espera.hh Proceso.hh Cluster.hh Procesador.hh
	g++ -c Area_de_espera.cc $(FLAGS)
Procesador.o: Procesador.cc Procesador.hh Proceso.hh
	g++ -c Procesador.cc $(FLAGS)
Proceso.o: Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(FLAGS)
practica.tar:
	tar -cvf practica.tar program.cc Cluster.cc Cluster.hh Area_de_espera.cc Area_de_espera.hh Procesador.cc Procesador.hh Proceso.cc Proceso.hh Makefile html.zip
	
clean:
	rm -f *.o
	rm -f *.exe
