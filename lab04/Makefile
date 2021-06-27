CC = gcc
CFLAGS = -Wall -Wpedantic

FILE = ./main.c
COMMON = ./common
OPTIMIZED = ./optimized

DATA_COMMON = data-common.csv
DATA_OPTIMIZED = data-optimized.csv

all: clean run-common run-optimized

run-common: compile-common
	$(COMMON).o $(DATA_COMMON)

run-optimized: compile-optimized
	$(OPTIMIZED).o $(DATA_OPTIMIZED)

compile-common:
	$(CC) $(CFLAGS) $(FILE) -o $(COMMON).o -L/usr/local/lib -lgsl -lgslcblas

compile-optimized:
	$(CC) $(CFLAGS) -O2 $(FILE) -o $(OPTIMIZED).o -L/usr/local/lib -lgsl -lgslcblas

clean:
	rm *.o *.csv || true