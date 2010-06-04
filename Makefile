CC = gcc
CCC = g++
CCFLAGS = -Wall -O3 -funroll-loops -I. -finline-functions -fomit-frame-pointer
CFLAGS = -Wall -O3 -funroll-loops -I. -finline-functions -fomit-frame-pointer
PROGRAMS = picsong

all: $(PROGRAMS)

picsong: picsong.o
	$(CCC) $(CCFLAGS) -lm -o $@ $<

clean:
	rm -f *.o *~

wipe: clean
	rm -f $(PROGRAMS)
