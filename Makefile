CC=g++
EIGEN=eigen-3.4.0

OBJECTS=CKKSEncoder.o CKKSEncryptor.o ciphertext.o utils.o vector_ops.o
LIBRARIES=-lgmp -lgmpxx
DEBUGS=-fsanitize=undefined -Wall

all: ckks

ckks: main.cpp $(OBJECTS)
	$(CC) -o $@ $^ $(LIBRARIES) $(DEBUGS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(LIBRARIES) $(DEBUGS)

.PHONY: clean

clean:
	rm -f *.o ckks
