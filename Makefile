OBJS	= 16BitsPrimes.o 8BitsPrimes.o hashing.o primes.o 32BitsPrimes.o converters.o mainFunctions.o rsa.o
SOURCE	= 16BitsPrimes.c 8BitsPrimes.c hashing.c primes.c 32BitsPrimes.c converters.c mainFunctions.c rsa.c
HEADER	= 16BitsPrimes.h 8BitsPrimes.h hashing.h primes.h 32BitsPrimes.h converters.h mainFunctions.h rsa.h
OBJ1    = keyPairGenerator.o
SRC1    = keyPairGenerator.c
OUT1	= keys-generator.o
OUT2	= sign-file.o
OBJ2    = signFile.o
SRC2    = signFile.c
OUT3	= validate-key-and-file.o
OBJ3    = validateSignature.o
SRC3    = validateSignature.c
OUT4	= validate-signed-file.o
OBJ4    = validateSignedFile.o
SRC4    = validateSignedFile.c
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

#all: $(OBJS)
#	$(CC) -g $(OBJS) -g $(OBJ1) -o $(OUT1) $(LFLAGS)
#	$(CC) -g $(OBJS) $(OBJ2) -o $(OUT2) $(LFLAGS)
#	$(CC) -g $(OBJS) $(OBJ3) -o $(OUT3) $(LFLAGS)
#	$(CC) -g $(OBJS) $(OBJ4) -o $(OUT4) $(LFLAGS)

#all: $(OBJS) 
#	$(program1) $(program2) $(program3) $(program4) 

all: program1 program2 program3 program4
	 chmod 777 ./$(OUT1) ./$(OUT2) ./$(OUT3) ./$(OUT4)

program1: $(SRC1) $(OBJS)
	$(CC) -g $(OBJS)  $(SRC1) -o $(OUT1) $(LFLAGS)

program2: $(SRC2) $(OBJS)
	$(CC) -g $(OBJS)  $(SRC2) -o $(OUT2) $(LFLAGS)

program3: $(SRC3) $(OBJS)
	$(CC) -g $(OBJS)  $(SRC3) -o $(OUT3) $(LFLAGS)

program4: $(SRC4) $(OBJS)
	$(CC) -g $(OBJS)  $(SRC4) -o $(OUT4) $(LFLAGS)

signFile.o: signFile.c
	$(CC) $(FLAGS) signFile.c 

validateSignature.o: validateSignature.c
	$(CC) $(FLAGS) validateSignature.c 

validateSignedFile.o: validateSignedFile.c
	$(CC) $(FLAGS) validateSignedFile.c 

keyPairGenerator.o: keyPairGenerator.c
	$(CC) $(FLAGS) keyPairGenerator.c 

16BitsPrimes.o: 16BitsPrimes.c
	$(CC) $(FLAGS) 16BitsPrimes.c 

8BitsPrimes.o: 8BitsPrimes.c
	$(CC) $(FLAGS) 8BitsPrimes.c 

hashing.o: hashing.c
	$(CC) $(FLAGS) hashing.c 

primes.o: primes.c
	$(CC) $(FLAGS) primes.c 

32BitsPrimes.o: 32BitsPrimes.c
	$(CC) $(FLAGS) 32BitsPrimes.c 

converters.o: converters.c
	$(CC) $(FLAGS) converters.c 

mainFunctions.o: mainFunctions.c
	$(CC) $(FLAGS) mainFunctions.c 

rsa.o: rsa.c
	$(CC) $(FLAGS) rsa.c 


clean:
	rm -f $(OBJS) $(OUT1) $(OUT2) $(OUT3) $(OUT4) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)

keys-generator: $(OUT1)
	./$(OUT1)

sign-file: $(OUT2)
	./$(OUT2)

validate-key-and-file: $(OUT3)
	./$(OUT3)

validate-signed-file: $(OUT4)
	./$(OUT4)