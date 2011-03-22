#include <iostream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <vector>
#include "join.h"
#include "split.h"

using namespace std;

int main(int argc, char** argv) {

    if (argc == 1) {
        cerr << "usage: " << argv[0] << " FIELD1 FIELD2 FIELD3 ..." << endl
             << "splits out the fields from the input tab-separated value stream" << endl;
        exit(1);
    }

    vector<string> fieldnames;
    for (int i = 1; i < argc; ++i) {
        fieldnames.push_back(argv[i]);
    }

    string header;
    getline(cin, header);
    if (header.empty()) {
        cerr << "could not get header line" << endl;
        exit(1);
    }

    vector<string> header_fields;
    split(header, '\t', header_fields);

    vector<int> columns;

    for (vector<string>::iterator f = fieldnames.begin(); f != fieldnames.end(); ++f) {
        const string& fieldname = *f;
        int i = 0;
        for (vector<string>::iterator h = header_fields.begin(); h != header_fields.end(); ++h) {
            const string& headername = *h;
            if (headername == fieldname) {
                columns.push_back(i);
                break;
            }
            ++i;
        }
    }

    cout << join(fieldnames, "\t") << endl;

    string line;
    getline(cin, line);
    while (!line.empty()) {
        vector<string> fields = split(line, '\t');
        for (vector<int>::iterator c = columns.begin(); c != columns.end(); ++c) {
            cout << (c == columns.begin() ? "" : "\t") << fields[*c];
        }
        cout << endl;
        getline(cin, line);
    }

    return 0;

}
