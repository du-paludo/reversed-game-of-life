flags = -Wall -std=c99 -lm
nome = conway
objs = main.o helper.o convertFromSAT.o

all: $(nome)

$(nome): $(objs)
	gcc -o $(nome) $(objs) $(flags)

convertFromSAT.o: convertFromSAT.c
	gcc -c convertFromSAT.c $(flags)

main.o: main.c
	gcc -c main.c $(flags)

helper.o: helper.c
	gcc -c helper.c $(flags)

clean:
	rm -f *~ *.o

purge: clean
	rm -f $(nome) convertFromSAT