#include <iostream>
#include <getopt.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include "join.h"
#include "split.h"
#include "mt19937ar.h"
#include <iomanip>

using namespace std;

vector<double> subsetavg(vector<vector<double>* >& subset) {

    vector<double> sums;
    vector<int> counts;

    vector<vector<double>* >::iterator s = subset.begin();
    for (int i = 0; i < (*s)->size(); ++i) {
        sums.push_back((*s)->at(i));
        counts.push_back(1);
    }
    ++s;

    for (; s != subset.end(); ++s) {
        const vector<double>& record = **s;
        for (int i = 0; i < record.size(); ++i) {
            sums.at(i) += record.at(i);
            ++counts.at(i);
        }
    }

    vector<double> results;
    for (int i = 0; i < counts.size(); ++i) {
        if (counts.at(i) != 0) {
            results.push_back(sums.at(i) / counts.at(i));
        } else {
            results.push_back(0);
        }
    }

    return results;

}

vector<vector<double>* > randomsubset(vector<vector<double> >& lines, unsigned int samplesize) {
    map<int, bool> hits;
    vector<vector<double>* > results;
    if (lines.size() < samplesize) {
        samplesize = lines.size();
    }
    while (results.size() < samplesize) {
        int pos = genrand_int32() % lines.size();
        map<int, bool>::iterator seen = hits.find(pos);
        if (seen == hits.end()) {
            hits[pos] = true;
            results.push_back(&lines.at(pos));
        }
    }
    return results;
}

int main(int argc, char** argv) {

    if (argc < 2) {
        cerr << "usage: " << argv[0] << " -c sample_count -n sample_size" << endl
             << "bootstraps a new table by randomly sampling subsets of tab-separated" << endl
             << "records from stdin.  generates sample_count subsets of sample_size" << endl
             << "randomly selected from lines of input.  for each sampled subset, outputs." << endl
             << "a row of tab-separated averaged values for each value in the table." << endl;
        exit(1);
    }

    unsigned int sample_size = 1;
    unsigned int sample_count = 1;

    while (true) {
        static struct option long_options[] =
        {   
            {"sample-count", required_argument, 0, 'c'},
            {"sample-size",   required_argument, 0, 'n'},

        };
        int option_index = 0;

        int c = getopt_long (argc, argv, "n:c:", long_options, &option_index);

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

          case 'n':
            sample_size = atoi(optarg);
            break;

          case 'c':
            sample_count = atoi(optarg);
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


    string header;
    vector<string> header_fields;
    getline(cin, header);

    if (header.empty()) {
        cerr << "could not get header line" << endl;
        exit(1);
    }

    split(header, '\t', header_fields);
    vector<vector<double> > lines;

    map<string, unsigned int> counts;
    map<string, long double> totals;

    string line;
    getline(cin, line);
    while (!line.empty()) {
        vector<string> fields = split(line, '\t');
        int i = 0;
        vector<double> vals;
        for (vector<string>::iterator f = fields.begin(); f != fields.end(); ++f) {
            vals.push_back(atof(f->c_str()));
        }
        lines.push_back(vals);
        getline(cin, line);
    }

    cout << header << endl;

    for (int i = 0; i < sample_count; ++i) {
        vector<vector<double>* > subset = randomsubset(lines, sample_size);
        vector<double> avgs = subsetavg(subset);
        cout << join(avgs, "\t") << endl;
    }

    return 0;

}
