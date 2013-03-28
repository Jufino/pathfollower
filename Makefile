C=$(CROSS_COMPILE)gcc -Wall -g
CPP=$(CROSS_COMPILE)g++ -Wall -g

GFLAGS=`pkg-config --libs --cflags gtk+-2.0 gmodule-2.0`
OFLAGS=`pkg-config --libs --cflags opencv`

rebuild:remove libserial.o blaze.o robot  

robot:robot.cpp
	$(CPP) robot.cpp libserial.o blaze.o -o robot $(OFLAGS)

test:test.cpp
	$(CPP) test.cpp -o test

libserial.o: libserial.c
	$(CPP) -c libserial.c

blaze.o: blaze.c
	$(CPP) -c blaze.c
remove:
	rm libserial.o
	rm blaze.o	
	rm robot
