CC = g++

LIBS = -lm
CCFLAGS = -Wall -ggdb -std=c++11

OBJ = Variable.o Contrainte.o ContrainteDifference.o ContrainteSomme.o

all: kakuroResolver

kakuroResolver: main.cpp $(OBJ)
	$(CC) $(CCFLAGS) -o kakuroResolver main.cpp  $(OBJ)

ContrainteSomme.o: ContrainteSomme.cpp
	$(CC) $(CCFLAGS) -c $^

ContrainteDifference.o: ContrainteDifference.cpp
	$(CC) $(CCFLAGS) -c $^

Contrainte.o: Contrainte.cpp
	$(CC) $(CCFLAGS) -c $^

Variable.o: Variable.cpp 
	$(CC) $(CCFLAGS) -c $^


.PHONY : clean

clean:
	- rm -f $(OBJ)
	- rm -f kakuroResolver