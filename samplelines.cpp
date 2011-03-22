#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "mt19937ar.h"
#include <cmath>
#include <fstream>

using namespace std;

int main (int argc, char** argv) {

    if (argc != 2) {
        cerr << "usage: " << argv[0] << " sample_rate" << endl
             << "samples lines from stdin at sample_rate rate" << endl;
        exit(1);
    }

    double sample_rate = atof(argv[1]);

    // seed prng with random bits from /dev/random
    fstream random;
    random.open("/dev/random", fstream::in);
    int seed;
    random.get((char*) &seed, sizeof(int));

    init_genrand(seed);

    string line;
    getline(cin, line);
    while (!line.empty()) {
        if (genrand_real1() < sample_rate) {
            cout << line << endl;
        }
        getline(cin, line);
    }

    return 0;

}
