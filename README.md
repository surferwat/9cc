This is the reference implementation of https://www.sigbus.info/compilerbook.

This is how to run the program from terminal:
Step 1: docker run -it --rm --platform linux/amd64 -v "$PWD":/work -w /work ubuntu bash
Step 2: apt update && apt install -y build-essential 
Step 3: make
Step 4: ./test.sh

Interesting
pointer arithmetic
assert 1 'int main() { int x[2][3]; int *y=x; *(y+1)=1; return *(*x+1); }'s
string literal
assert 97 'int main() { return "abc"[0]; }'
string literals and pointer arithmetic
efficiency of string literals implementation