flags = -Wall -std=c99
nome = conway
objs = main.o helper.o

all: $(nome)

$(nome): $(objs)
	gcc -o $(nome) $(objs) $(flags)

main.o: main.c
	gcc -c main.c $(flags)

helper.o: helper.c
	gcc -c helper.c $(flags)

clean:
	rm -f *~ *.o

purge: clean
	rm -f $(nome)