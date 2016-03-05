CC=gcc
CCFLAGS=-g -std=c99 -D_BSD_SOURCE -Wall

TARGETS=netcatd netcat spdtestd spdtest

all: $(TARGETS)

netcatd: netcatd.o 
	$(CC) $(CCFLAGS) -o $@ $^


netcatd.o: netcatd.c 
	$(CC) $(CCFLAGS) -c $<

netcat: netcat.o 
	$(CC) $(CCFLAGS) -o $@ $^

netcat.o: netcat.c
	$(CC) $(CCFLAGS) -c $<

spdtestd: spdtestd.o 
	$(CC) $(CCFLAGS) -o $@ $^

spdtestd.o: spdtestd.c 
	$(CC) $(CCFLAGS) -c $<

spdtest: spdtest.o 
	$(CC) $(CCFLAGS) -o $@ $^

spdtest.o: spdtest.c 
	$(CC) $(CCFLAGS) -c $<


clean:
	rm -rf *.o $(TARGETS)
