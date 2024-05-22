CC = g++
CPPFLAGS = -std=c++17 -lgtest -lgtest_main
CHECKFLAGS = -Wall -Werror -Wextra

ifeq ($(shell uname), Linux)
	CPPFLAGS+=-lstdc++ -pthread
else
	CPPFLAGS+=-lpthread 
endif

all: clean tests install dist clang

tests: clean
	@$(CC) $(CHECKFLAGS) tests.cc viewer/strategy/strategy.cc  -o $@ $(CPPFLAGS) && ./tests
	./tests

build:
	@mkdir build	
	@cd build && cmake ../ && cmake --build . --target all

install: uninstall build
	@open build/*.app

uninstall:
	@rm -rf build

dvi:
	open ../README.md

dist:
	@mkdir ./Archive_Viewer_v2.0
	@mkdir ./Archive_Viewer_v2.0/src 
	@cp -r third_party viewer ui ./Archive_Viewer_v2.0/src
	@cp Makefile CMakeLists.txt *.cc ./Archive_Viewer_v2.0/src
	@tar cvzf ./Archive_Viewer_v2.0.tgz Archive_Viewer_v2.0/
	@mv Archive_Viewer_v2.0.tgz $(HOME)/Desktop/
	@rm -rf ./Archive_Viewer_v2.0

clang:
	@cp ../materials/linters/.clang-format .
	@echo "===> Formatting your code for Google Style <==="
	@clang-format -i -style=GOOGLE ui/*.ui *.cc viewer/*.cc viewer/*.cpp viewer/*.h viewer/observer/*.h viewer/strategy/*.cc viewer/strategy/*.h
	@rm -rf .clang-format
	
clean: uninstall
	@rm -rf ./.clang-format tests

leaks: clean tests
	@leaks -atExit -- ./tests

.PHONY: install uninstall clean tests dvi dist clang
