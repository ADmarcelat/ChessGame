main: main.o pieces.o graphisme.o interaction.o coordonnee.o Timer.o libisentlib.a
	gcc -Wall -o main main.o pieces.o graphisme.o interaction.o coordonnee.o Timer.o libisentlib.a -lm -lglut -lGL -lX11
# Compile le main.c

main.o: main.c GfxLib.h BmpLib.h ESLib.h interaction.h coordonnee.h graphisme.h pieces.h Timer.h
	gcc -Wall -o main.o -c main.c

graphisme.o: graphisme.c
	gcc -o graphisme.o -c graphisme.c

coordonnee.o: coordonnee.c
	gcc -o coordonnee.o -c coordonnee.c

pieces.o: pieces.c pieces.h coordonnee.h
	gcc -o pieces.o -c pieces.c 

interaction.o: interaction.c interaction.h coordonnee.h
	gcc -o interaction.o -c interaction.c 

Timer.o: Timer.c
	gcc -o Timer.o -c Timer.c

libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o  
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o  
	ranlib libisentlib.a

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc -Wall -O2 -c BmpLib.c

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -c ESLib.c

ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc -Wall -O2 -c ErreurLib.c

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL

OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -c OutilsLib.c




# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c WavLib.c

zip:
	tar -cvzf chessIsen.tgz *.[ch] *.bmp *.pdf makefile

clean:
	rm -f *~ *.o

