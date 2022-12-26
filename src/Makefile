.PHONY: all clean test s21_math.a check rebuild open gcov_report
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

all: s21_math.a test gcov_report

s21_math.a: s21_math.o
	ar rcs s21_math.a s21_math.o
	cp s21_math.a libs21_math.a
	cp s21_math.a ls21_math.a
	ranlib libs21_math.a
	ranlib ls21_math.a

s21_math.o: s21_math.c
	$(CC) -c s21_math.c -o s21_math.o

test: s21_math.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) s21_math_test.c s21_math.a -o test.out $(LIBS)
	./test.out
else
	$(CC) $(CFLAGS) s21_math_test.c s21_math.a -o test.out $(LIBS) $(LINUX)
	./test.out
endif

gcov_report: gcov_test.info
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) s21_math_test.c s21_math.c -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) s21_math_test.c s21_math.c -o test.out $(LIBS) $(LINUX)
endif
	./test.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ gcov_test.info
	open report/index.html 

gcov_test.info: gcov_test gcov_test.gcda
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: s21_math_test.c s21_math.a

ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) s21_math_test.c s21_math.c -o gcov_test $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) s21_math_test.c s21_math.c -o gcov_test $(LIBS) $(LINUX)
endif

gcov_test.gcda: gcov_test
	chmod +x *
	./gcov_test

open: gcov_report
	open report/index.html

rebuild: clean all

check:
	cppcheck *.c
	clang-format -n *.c *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind ./test.out --leak-check=full
endif
	make clean

clean:
	rm -rf *.o *.a *.info test.out gcov_test
	rm -rf report
	rm *.gcno
	rm *.gcda
