flags = -Wall -std=c99 -lm
nome = conway
objs = main.o helper.o

all: $(nome) convertFromSAT

$(nome): $(objs)
	gcc -o $(nome) $(objs) $(flags)

convertFromSAT: convertFromSAT.c
	gcc -o convertFromSAT convertFromSAT.c $(flags)

main.o: main.c
	gcc -c main.c $(flags)

helper.o: helper.c
	gcc -c helper.c $(flags)

clean:
	rm -f *~ *.o

purge: clean
	rm -f $(nome) convertFromSAT