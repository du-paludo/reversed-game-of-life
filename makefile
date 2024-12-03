flags = -Wall -std=c99 -lm
nome = conway
objs = main.o helper.o convertFromSAT.o convertToSAT.o

all: $(nome)

conway-normal: conway-normal.o
	gcc -o conway-normal conway-normal.o $(flags)

$(nome): $(objs)
	gcc -o $(nome) $(objs) $(flags)

convertFromSAT.o: convertFromSAT.c
	gcc -c convertFromSAT.c $(flags)

convertToSAT.o: convertToSAT.c
	gcc -c convertToSAT.c $(flags)

helper.o: helper.c
	gcc -c helper.c $(flags)

main.o: main.c
	gcc -c main.c $(flags)

clean:
	rm -f *~ *.o

purge: clean
	rm -f $(nome) convertFromSAT conway-normal SATinput.txt SAToutput.txt