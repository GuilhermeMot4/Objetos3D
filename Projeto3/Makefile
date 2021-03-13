#Nome: Guilherme Ferreira Mota 
#GRR: 20197268
CFLAGS = -Wall
LDLIBS = -lm
SDL2LIBS = -lSDL2

objects = objread.o perspect.o graphics.o
headers = datatypes.h objread.h perspect.h graphics.h


all: wireframe

wireframe: wireframe.o $(objects)
	gcc wireframe.o $(objects) -o wireframe $(CFLAGS) $(SDL2LIBS) $(LDLIBS)


wireframe.o: wireframe.c $(headers)
	gcc -c wireframe.c $(CFLAGS)

objread.o: objread.c objread.h
	gcc -c objread.c $(CFLAGS)

perspect.o: perspect.c perspect.h
	gcc -c perspect.c $(CFLAGS)

graphics.o: graphics.c graphics.h
	gcc -c graphics.c $(CFLAGS)


clean:
	-rm -f *.o *~

purge: clean
	-rm -f wireframe