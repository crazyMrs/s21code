CC := g++
CPPFLAGS := -lgtest -std=c++17
CHECKFLAGS := -Wall -Werror -Wextra
SRC := ./model/model.cc test.cc
OS := $(shell uname)
ifeq ($(OS), Darwin)
	OPEN_CMD := open
else
	OPEN_CMD := xdg-open
endif
TARGET := SmartCalc_v2.0

all: tests style install open

install: uninstall
	@make clean
	@cd ../ && mkdir build
	@cd view && qmake6 && make && make clean && rm Makefile && cd ../ && mv view/$(TARGET).app ../build/

open:
	@echo "Opening application..."	
	@$(OPEN_CMD) ../build/$(TARGET).app

uninstall:
	@rm -rf ./../build ./out

clean: uninstall
	@rm -rf ./build-view-* ./report ../.vscode ../dist
	@rm -rf $(TARGET).tar.gz
	@rm -rf *.o *.a test
	@rm -rf *.dSYM
	@rm -rf view/*.o

tests: clean
	@$(CC) $(CHECKFLAGS) test.cc -lgtest -lgtest_main -o test $(CPPFLAGS) && ./test

dvi:
	@$(OPEN_CMD) ./dvi.html

dist:
	@tar -cvf $(TARGET).tar.gz dvi.html Makefile test.cc

clang:
	@echo "===> Formatting your code for Google Style <==="
	@clang-format -i -style=GOOGLE $(SRC) model/*.h model/*.cc controller/*.h view/*.cc view/*.h view/*.ui

style:
	@echo "===> Checking your code for Google Style <==="
	@clang-format -n -style=GOOGLE $(SRC) model/*.h controller/*.h view/*.cc view/*.h view/*.ui

leaks: clean tests
	@leaks -atExit -- ./test

valgrind: clean tests
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

.PHONY: install open uninstall clean tests dvi dist clang style