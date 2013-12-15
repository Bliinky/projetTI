CC=g++
CFLAGS=-g

compress: Coding.o  principal.o TabCodingHuffman.o CodingHuffman.o TabCodingLZW.o StringFile.o
	$(CC) -o prog Coding.o  principal.o TabCodingHuffman.o CodingHuffman.o TabCodingLZW.o StringFile.o

principal.o : principal.cc 
	$(CC) $(CFLAGS) -c principal.cc

Coding.o: Coding.cc
	$(CC) $(CFLAGS) -c Coding.cc

CodingHuffman.o:CodingHuffman.cc
	$(CC) $(CFLAGS) -c CodingHuffman.cc

TabCodingHuffman.o: TabCodingHuffman.cc
	$(CC) $(CFLAGS) -c TabCodingHuffman.cc

TabCodingLZW.o: TabCodingLZW.cc
	$(CC) $(CFLAGS) -c TabCodingLZW.cc

StringFile.o: other/StringFile.cc
	$(CC) $(CFLAGS) -c other/StringFile.cc