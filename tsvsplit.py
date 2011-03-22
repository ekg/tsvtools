#!/usr/bin/python

import sys
import os
import subprocess
import signal

import signal


if len(sys.argv) < 2:
    print "usage:", sys.argv[0], " <tsv file> [field names]"
    print "prints a tsv file with only the fields provided on the command line"
    print "assumes the first line of the tab-separated values file is the header"
    print "<tsv file> may be specifed as '-' for stdin"
    exit()

tsvfilename = sys.argv[1]
if tsvfilename == '-':
    tsvfile = sys.stdin
else:
    tsvfile = open(sys.argv[1])

fieldnames = sys.argv[2:]

header = tsvfile.readline()
header_fields = header.strip().split('\t')
columns = [] # array of fields to keep, true if we keep false otherwise

for fieldname in fieldnames:
    i = 0
    for headername in header_fields:
        if headername == fieldname:
            columns.append(i)
            break
        i += 1

sys.stdout.write('\t'.join(fieldnames) + '\n')

for line in tsvfile:
    fields = line.strip().split('\t')
    filtered = []
    for column in columns:
        filtered.append(fields[column])
    sys.stdout.write('\t'.join(filtered) + '\n')
