CCGW = g++ -Wall -g
NAME = liga

all: $(NAME) clean

$(NAME): main.o equipo.o liga.o jornada.o
	$(CCGW) main.o equipo.o liga.o jornada.o -o $(NAME)

main.o: main.cpp equipo.h liga.h
	$(CCGW) -c main.cpp equipo.h liga.h

liga.o: liga.cpp equipo.h jornada.h liga.h
	$(CCGW) -c liga.cpp equipo.h jornada.h liga.h

jornada.o: jornada.cpp equipo.h liga.h jornada.h
	$(CCGW) -c jornada.cpp equipo.h liga.h jornada.h

equipo.o: equipo.cpp equipo.h
	$(CCGW) -c equipo.cpp equipo.h

.PHONY: clean
clean:
	-rm -f *.o

