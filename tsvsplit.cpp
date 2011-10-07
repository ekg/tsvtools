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
        cerr << "usage: " << argv[0] << " [-v] FIELD1 FIELD2 FIELD3 ..." << endl
             << "splits out the fields from the input tab-separated value stream"
             << "specifying '-v' inverts the split, excluding the listed fields" << endl;
        exit(1);
    }

    int i = 1;
    bool invert = false;
    if (string(argv[i]) == "-v") {
        invert = true;
        i = 2;
    }

    vector<string> fieldnames;
    for (; i < argc; ++i) {
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

    // if we are inverting the selection, invert the list of fieldnames
    if (invert) {
        map<string, bool> fieldnamesToRemove;
        for (vector<string>::iterator f = fieldnames.begin(); f != fieldnames.end(); ++f) {
            fieldnamesToRemove[*f] = true;
        }
        fieldnames.clear();
        for (vector<string>::iterator h = header_fields.begin(); h != header_fields.end(); ++h) {
            if (fieldnamesToRemove.find(*h) == fieldnamesToRemove.end()) {
                fieldnames.push_back(*h);
            }
        }
    }

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
