CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11
GCOVFLAGS := -fprofile-arcs -ftest-coverage
LDFLAGS := -lcheck -lgcov -fprofile-arcs --coverage
ifeq ($(shell uname), Linux)
    LDFLAGS += -lpthread -lrt -lm -lsubunit
    OPEN_CMD := xdg-open
else ifeq ($(shell uname), Darwin)
    OPEN_CMD := open
endif

SRC := $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
OBJ_GCOV = $(patsubst %.c, gcov_obj/%.o, $(SRC))
TEST_SRC := $(wildcard *.c)
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))

TARGET := main_menu

all: clean install
	
obj/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

gcov_obj/%.o: %.c
	@$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

3d_viewer.a: $(OBJ)
	@ar -src $@ $(OBJ)

3d_viewer_gcov.a: $(OBJ_GCOV)
	@ar -src $@ $(OBJ_GCOV)

test: test.o 3d_viewer_gcov.a
	@$(CC) -g $< 3d_viewer_gcov.a -o $@ $(LDFLAGS) $(GCOVFLAGS)
	@clear
	@./$@

install: uninstall
	@clear
	@echo "===>    Installation has started     <==="
	@mkdir -p build
	@cd main_menu/ && qmake && make && make clean && rm -rf Makefile && mv $(TARGET).app ../build
	@cp -R build/$(TARGET).app ~/Desktop/$(TARGET).app
	@echo "===> main_menu V1.0 application installed <==="

uninstall: clean
	@rm -rf ~/Desktop/$(TARGET).app
	@echo "===>  main_menu V1.0 application removed  <==="

dvi:
	@open ../README.md

dist:
	@mkdir -p dist
	@cp -R build/$(TARGET).app dist
	@cp ../README.md dist && cp ../README.md dist
	@cd dist && tar cvzf $(TARGET).tgz *
	@cd dist && rm -rf $(TARGET).app src/README.md

gcov_report: test
	lcov -c -d gcov_obj/. -o gcov_obj/coverage.info
	genhtml gcov_obj/coverage.info --output-directory out
	$(OPEN_CMD) out/index.html

clean:
	@rm -rf build dist gcov_obj/*.o test
	@rm -rf gcov_obj/*.gcda gcov_obj/*.gcno 
	@rm -rf gcov_obj/*.info out *.a *.gcno test.o qt/*
	@rm -rf .DS_Store .DS_Store .vscode view/.DS_Store

ultra_test: clean test gcov_report

clang:
	@clang-format -i *.h *.c main_menu/*.cpp main_menu/*.h main_menu/*.ui

style:
	@clang-format -n *.h *.c main_menu/*.cpp main_menu/*.h main_menu/*.ui

cppcheck: clean test
	@cppcheck --enable=all --suppress=missingIncludeSystem main_menu/

valgrind: clean test
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

leaks: clean test
	@leaks -atExit -- ./test