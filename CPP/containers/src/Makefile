CC = g++
CPPFLAGS = -std=c++17 -lgtest -lgtest_main
CHECKFLAGS = -Wall -Werror -Wextra

ifeq ($(shell uname), Linux)
	CPPFLAGS+=-lgtest -lgtest_main -lstdc++ -pthread -fprofile-arcs -ftest-coverage
else
	CPPFLAGS+=-lgtest -lgtest_main -lpthread -fprofile-arcs -ftest-coverage -lstdc++
endif

all: clean test style

test: clean
	@$(CC) $(CHECKFLAGS) tests.cc -o $@ $(CPPFLAGS) && ./test -lgcov --coverage

gcov_report: test
	lcov -t "gcov_report" --ignore-errors mismatch -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	
clean:
	@rm -rf *.o *.a test *.gcno *.gcda *.gcov report *.info tests_RB_tree.out *.filtered ../.DS_Store test .DS_Store

style:
	clang-format -style=Google -n */*.cc */*.h s21_containers.h s21_containersplus.h tests.cc

clang:
	clang-format -style=Google -i */*.cc */*.h s21_containers.h s21_containersplus.h tests.cc

leaks: clean
	@$(CC) $(CHECKFLAGS) tests.cc -o test $(CPPFLAGS)
	@leaks -atExit -- ./test

valgrind:
	@$(CC) $(CHECKFLAGS) tests.cc -o test $(CPPFLAGS)
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

.PHONY: all test style clang clean leaks valgrind