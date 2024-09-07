GCC=gcc
SRC=s21_matrix_oop.cc
OBJ=s21_matrix_oop.o
CFLAGS=--std=c++17 -lstdc++ -lm
TESTFLAGS=-lgtest -lgcov
GCOVFLAGS=--coverage
HTML=lcov -t test -o rep.info -c -d ./


all: clean gcov

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM *.out

test: s21_matrix_oop.a
	$(GCC) -g tests.cc s21_matrix_oop.a $(CFLAGS) $(TESTFLAGS) -o test
	./test

s21_matrix_oop.a: clean
	$(GCC) $(GCOVFLAGS) -c $(SRC)
	ar rcs s21_matrix_oop.a $(OBJ)
	ranlib s21_matrix_oop.a


gcov: test
	$(HTML)
	genhtml -o report rep.info
	open report/index.html

clang: 
	clang-format -style=Google -i *.cc *.h
