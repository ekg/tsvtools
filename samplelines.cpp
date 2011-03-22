#include <iostream>
#include <algorithm>
#include <string>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include "mt19937ar.h"
#include <cmath>
#include <fstream>

using namespace std;

int main (int argc, char** argv) {

    if (argc < 2) {
        cerr << "usage: " << argv[0] << " -r sample_rate" << endl
             << "samples lines from stdin at sample_rate rate" << endl
             << "specify -H to always print header line" << endl;
        exit(1);
    }

    double sample_rate = 1.0;
    bool header = false;

    while (true) {
        static struct option long_options[] =
        {  
            {"header", no_argument, 0, 'H'},
            {"rate",   required_argument, 0, 'r'},

        };
        int option_index = 0;

        int c = getopt_long (argc, argv, "Hr:", long_options, &option_index);

          if (c == -1)
            break;

          switch (c) {
            case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0)
              break;
            printf ("option %s", long_options[option_index].name);
            if (optarg)
              printf (" with arg %s", optarg);
            printf ("\n");
            break;

          case 'H':
            header = true;
            break;

          case 'r':
            sample_rate = atof(optarg);
            break;

          default:
            abort();
            break;

        }
    }


    // seed prng with random bits from /dev/random
    fstream random;
    random.open("/dev/random", fstream::in);
    int seed;
    random.get((char*) &seed, sizeof(int));
    random.close();

    init_genrand(seed);

    string line;
    getline(cin, line);
    if (header) {
        cout << line << endl;
    }
    getline(cin, line);

    while (!line.empty()) {
        cout << line << endl;
        if (genrand_real1() < sample_rate) {
            cout << line << endl;
        }
        getline(cin, line);
    }

    return 0;

}
