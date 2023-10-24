CC= gcc
CFLAGS:= -Wall -Werror -Wextra -lm
LDFLAGS= -o
SOURCES= s21_math.c
OBJECTS= $(patsubst %.c, %.o, $(SOURCES))
SOURCES_TEST= test/s21_test_set2.c test/test_main.c
EXECUTABLE= math

LIBRARY= s21_math.a
ifeq ($(OS), Linux)
	CHECK_FLAGS= -lcheck_pic -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS= -lcheck
endif

all: clean $(LIBRARY)

$(LIBRARY): clean $(OBJECTS)
	ar rcs $(LIBRARY) $(OBJECTS)
	ranlib $(LIBRARY)
	rm -rf $(OBJECTS)

gcov_report: clean
	$(CC) --coverage $(CFLAGS) $(SOURCES_TEST) $(CHECK_FLAGS) $(SOURCES) $(LDFLAGS) gcov
	./gcov
	lcov -t "gcov" -o gcov_report.info --no-external -c -d .
	genhtml -o report gcov_report.info
	open report/index.html
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf gcov
	rm -rf gcov_report.info

test:$(LIBRARY)
	$(CC) $(CFLAGS) $(SOURCES_TEST) $(CHECK_FLAGS) -L. $(LIBRARY) $(LDFLAGS) $(EXECUTABLE)
	clear
	./$(EXECUTABLE)

clean:
	rm -rf *.gcda *.gcno gcov gcov_report.info $(EXECUTABLE) report $(LIBRARY)

build:
	$(CC) $(SOURCES) main_hands/s21_math.c -lm $(LDFLAGS) $(EXECUTABLE)
	./$(EXECUTABLE)

clang:
	cp ../materials/linters/.clang-format test
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c *.h test/*.c test/*.h
	rm -f test/.clang-format .clang-format