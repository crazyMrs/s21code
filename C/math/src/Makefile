CC = gcc -Wall -Wextra -Werror -std=c11
PROJECTNAME= s21_math
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LIBS= -lcheck
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
	TEST_FLAGS = $(LIBS)
endif
ifeq ($(OS), Linux)
	CC += -D OS_LINUX
	TEST_FLAGS =-lpthread $(LIBS) -pthread -lrt -lm -lsubunit
endif

all: $(PROJECTNAME).a

$(PROJECTNAME).a: clean
	${CC} -c ./s21_*.c
	ar rc $(PROJECTNAME).a s21_*.o
	ranlib $(PROJECTNAME).a

test: $(PROJECTNAME).a
	$(CC) test.c $(PROJECTNAME).a -o test $(TEST_FLAGS)
	./test

gcov_report: clean
	@gcc $(GCOVFLAGS) s21_*.c test.c $(TEST_FLAGS) -o test -lcheck
	@./test
	@lcov -t test -o test.info -c -d .
	@genhtml -o report test.info
	@open ./report/index-sort-f.html

rebuild: clean all

clear:
	clear

clean:
	-rm -rf ${PROJECTNAME}
	-rm -rf unit_test
	-rm -rf unit_tests
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -f .clang-format
	-rm -rf print

clang:
	clang-format --style=Google -n ./*.h ./s21_*.c test.c

.PHONY: all test clean gcov_report check rebuild clear clang