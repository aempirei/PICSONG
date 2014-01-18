CC = gcc
CCC = g++
CCFLAGS = -Wall -O3 -funroll-loops -I. -finline-functions -fomit-frame-pointer
CFLAGS = -Wall -O3 -funroll-loops -I. -finline-functions -fomit-frame-pointer
SONGFILE = risingsun.txt

.PHONY: clean flash

flash: picsong.hex
	picp -c /dev/ttyS0 12f675 -ef
	picp -c /dev/ttyS0 12f675 -wp $<

picsong.hex: picsong.a picsong.inc
	gpasm $<

picsong.inc: picsong $(SONGFILE)
	./picsong < $(SONGFILE) > $@

picsong: picsong.o
	$(CCC) $(CCFLAGS) -lm -o $@ $<

clean:
	rm -f *.o *~ picsong.hex picsong.inc picsong.lst picsong.cod picsong
