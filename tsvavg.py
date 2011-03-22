#!/usr/bin/python

import sys


if len(sys.argv) < 2:
    print "usage:", sys.argv[0], " <tsv file>"
    print "prints a tsv row with the average values of  with only the fields provided on the command line"
    print "assumes the first line of the tab-separated values file is the header"
    print "assumes the input columns are all convertible to floats"
    print "<tsv file> may be specifed as '-' for stdin"
    exit()

tsvfilename = sys.argv[1]
if tsvfilename == '-':
    tsvfile = sys.stdin
else:
    tsvfile = open(sys.argv[1])

header = tsvfile.readline()
header_fields = header.strip().split('\t')
columns = [] # array of fields to keep, true if we keep false otherwise

count = {}
total = {}
for field in header_fields:
    count[field] = 0
    total[field] = 0

sys.stdout.write('\t'.join(header_fields) + '\n')

for line in tsvfile:
    fields = line.strip().split('\t')
    i = 0
    for field in header_fields:
        try:
            count[field] += float(fields[i])
            total[field] += 1
        except:
            continue
        i += 1

print '\t'.join([str(total[field] / count[field] if count[field] > 0 else 0) for field in header_fields])
