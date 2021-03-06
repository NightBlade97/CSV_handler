CC=g++

all: csv_handler

csv_handler: main.o CSV_handler.o CSV_Reader.o
	$(CC) main.o CSV_handler.o CSV_Reader.o -o csv_handler

main.o: main.cpp
	$(CC) -c  main.cpp

CSV_handler.o: CSV_handler.cpp CSV_handler.h
	$(CC) -c CSV_handler.cpp CSV_handler.h

CSV_Reader.o: CSV_Reader.cpp CSV_Reader.h
	$(CC) -c  CSV_Reader.cpp CSV_Reader.h

clean:
	rm -rf *.o csv_handler
