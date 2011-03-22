all: tsvavg tsvsplit samplelines

tsvavg: tsvavg.cpp split.cpp join.h
	g++ -O3 tsvavg.cpp split.cpp -o tsvavg

tsvsplit: tsvsplit.cpp split.cpp join.h
	g++ -O3 tsvsplit.cpp split.cpp -o tsvsplit

samplelines: samplelines.cpp
	g++ -O3 samplelines.cpp -o samplelines

clean:
	rm -f tsvavg tsvsplit samplelines

.PHONY: all clean
