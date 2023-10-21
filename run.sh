#!/bin/sh

set +x
taskset -c 1-3 ./pr -f benchmark/graphs/raw/twitter.sg -i1000 -t1e-4 -n2
