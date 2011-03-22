all: tsvavg tsvsplit samplelines tsvbootstrap

tsvavg: tsvavg.cpp split.cpp join.h
	g++ -O3 tsvavg.cpp split.cpp -o tsvavg

tsvsplit: tsvsplit.cpp split.cpp join.h
	g++ -O3 tsvsplit.cpp split.cpp -o tsvsplit

tsvbootstrap: tsvbootstrap.cpp split.cpp join.h
	g++ -O3 tsvbootstrap.cpp split.cpp -o tsvbootstrap

samplelines: samplelines.cpp
	g++ -O3 samplelines.cpp -o samplelines

clean:
	rm -f tsvavg tsvsplit samplelines

.PHONY: all clean
