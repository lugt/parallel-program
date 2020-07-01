#!/usr/bin/env bash
#set -x;
one_case() {
          g++ -fopenmp -O0 lu.cxx -o lu.out -lomp -lm -DNUM_OF_THREADS=$1
          echo "NUM_OF_THREAD = $1, $(./lu.out)";
}
one_case 1;
one_case 2;
one_case 4;
one_case 8;
one_case 16;
one_case 32;

