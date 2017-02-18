all: clean build

LDFLAGS = -lglut -lGL -lGLU

build: 
	gcc -o test.bin   test.c   $(LDFLAGS)
	g++ -o testpp.bin test.cpp $(LDFLAGS)
clean:
	rm -rf test.bin
	rm -rf testpp.bin
