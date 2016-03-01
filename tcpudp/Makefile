CC=gcc
CCFLAGS=-g -std=c99 -D_BSD_SOURCE -Wall

TARGETS=netcatd netcat

all: $(TARGETS)

netcatd: netcatd.o 
	$(CC) $(CCFLAGS) -o $@ $^

netcatd.o: netcatd.c 
	$(CC) $(CCFLAGS) -c $<

netcat: netcat.o 
	$(CC) $(CCFLAGS) -o $@ $^

netcat.o: netcat.c
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -rf *.o $(TARGETS)
