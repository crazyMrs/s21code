CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11
OBJ = s21_stack.c s21_calculate.c
TESTFLAGS = -lcheck -coverage -lpthread -pthread
LDFLAGS := -lcheck -lgcov -fprofile-arcs --coverage
ifeq ($(shell uname), Linux)
    LDFLAGS += -lpthread -lrt -lm -lsubunit
    OPEN_CMD := xdg-open
else ifeq ($(shell uname), Darwin)
    OPEN_CMD := open
endif


all: clean install test gcov_report dvi style dist

rebuild: clean all

Smart_Calc.a:
	$(CC) $(CFLAGS) -c $(OBJ)
	ar -rv Smart_Calc.a *.o
	ranlib Smart_Calc.a

test: Smart_Calc.a
	$(CC) $(CFLAGS) -o test smart_calc_test.c  -L. $(TESTFLAGS) Smart_Calc.a 
	./test

gcov_report:
	lcov -t "./gcov" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

install: uninstall
	make clean
	mkdir -p build
	cd s21_calculate && qmake && make && make clean && rm Makefile && cd ../ && mv s21_calculate/s21_calculate.app build

uninstall:
	cd s21_calculate && rm -rf Makefile s21_calculate.app s21_calculate.pro.user .qmake.stash .qtc_clangd .tmp .qm *.o
	rm -rf build
	
clean: uninstall dist_clean
	@rm -rf *.o *.a test
	@rm -rf *.gcno *gcda *.gcov gcov
	@rm -rf report report.info
	@rm -rf *.dSYM
	@rm -rf *.a

dvi:
	open dvi.html

dist: 
	tar -cvf s21_calculate.tar.gz dvi.html Makefile smart_calc_test.c

dist_clean: 
	rm -rf s21_calculate.tar.gz

style:
	@clang-format -n *.c *.h main_menu/*.cpp main_menu/*.h main_menu/*.ui

leaks: clean test
	@leaks -atExit -- ./test
