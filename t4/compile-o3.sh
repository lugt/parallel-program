
echo "Running GCC";
set -x;
g++ matrix.cxx -o matrix-gcc.out -fopenmp -O3 -fno-tree-vectorize -march=x86-64
g++ matrix.cxx -o matrix-gcc.s -S -fopenmp -O3 -fno-tree-vectorize -march=x86-64

echo "Running Open64, openCC"
~/old-opencc/install/bin/openCC -mp -apo matrix.cxx -O3 -fno-tree-vectorize -o matrix-opencc.out
~/old-opencc/install/bin/openCC -mp -apo matrix.cxx -O3 -S -fno-tree-vectorize -o matrix-opencc.s
