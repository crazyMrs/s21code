CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
GCOVFLAGS:=-fprofile-arcs -ftest-coverage
LDFLAGS:=-lcheck -lgcov -fprofile-arcs --coverage
ifeq ($(shell uname), Linux)
LDFLAGS +=-pthread -lcheck_pic -lrt -lm -lsubunit
endif

SOURCES:= s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memset.c s21_strcat.c s21_strncat.c s21_strchr.c s21_strcpy.c s21_strerror.c s21_strlen.c s21_strncmp.c s21_strncpy.c s21_to_upper.c s21_to_lower.c s21_strcspn.c s21_strrchr.c s21_strstr.c s21_strtok.c s21_insert.c s21_trim.c s21_strpbrk.c s21_sprintf.c

OBJECTS = $(addprefix obj/,$(SOURCES:.c=.o))

OBJECTS_GCOV = $(addprefix gcov_obj/,$(SOURCES:.c=.o))

.PHONY: all clean rebuild

all: test gcov_report s21_string_gcov.a s21_string.a

s21_string.a: $(OBJECTS)
	ar -src $@ $(OBJECTS)

s21_string_gcov.a: $(OBJECTS_GCOV)
	ar -src $@ $(OBJECTS_GCOV)

test: gcov_obj/s21_string_test.o s21_string_gcov.a
	$(CC) gcov_obj/s21_string_test.o s21_string_gcov.a -o $@ $(LDFLAGS) $(GCOVFLAGS)
	./test

gcov_report: test
	lcov -t "test" -o gcov_obj/test.info -c -d gcov_obj/.  
	genhtml gcov_obj/test.info --output-directory report
	open ./report/index.html

gcov_obj/%.o: %.c
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rebuild: clean all

clean:
	rm -rf report
	rm -f obj/*.o
	rm -f gcov_obj/*.o
	rm -f gcov_obj/*.gc*
	rm -f ./test
	rm -f -r out
	rm -f gcov_obj/*.info
	rm -f .DS_Store
	rm -f *.a
