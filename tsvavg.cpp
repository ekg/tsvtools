#include <iostream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <vector>
#include "join.h"
#include "split.h"

using namespace std;

int main(void) {

    string header;
    vector<string> header_fields;
    getline(cin, header);

    if (header.empty()) {
        cerr << "could not get header line" << endl;
        exit(1);
    }

    split(header, '\t', header_fields);
    map<string, unsigned int> counts;
    map<string, long double> totals;

    string line;
    getline(cin, line);
    while (!line.empty()) {
        vector<string> fields = split(line, '\t');
        int i = 0;
        for (vector<string>::iterator f = header_fields.begin(); f != header_fields.end(); ++f) {
            const string& field = *f;
            ++counts[field];
            totals[field] += atof(fields[i++].c_str());
        }
        getline(cin, line);
    }

    vector<string> averages;
    for (vector<string>::iterator f = header_fields.begin(); f != header_fields.end(); ++f) {
        const string& field = *f;
        if (counts[field] != 0) {
            stringstream s;
            s << totals[field] / counts[field];
            averages.push_back(s.str());
        }
    }

    cout << header << endl
         << join(averages, "\t") << endl;

    return 0;

}
