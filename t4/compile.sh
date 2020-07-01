
echo "Running GCC";
set -x;
g++ matrix.cxx -o matrix-gcc.out -fopenmp

echo "Running Open64, openCC"
~/old-opencc/install/bin/openCC -mp -apo matrix.cxx -o matrix-opencc.out
