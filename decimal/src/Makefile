CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
GCOVFLAGS:=-fprofile-arcs -ftest-coverage
LDFLAGS:=-lcheck -lgcov -fprofile-arcs --coverage
ifeq ($(shell uname), Linux)
LDFLAGS +=-pthread -lcheck_pic -lrt -lm -lsubunit
endif

SOURCES:= s21_decimal.c s21_from_decimal_to_float.c s21_from_decimal_to_int.c s21_from_float_to_decimal.c s21_from_int_to_decimal.c s21_common_func.c s21_dop_funclion.c

OBJECTS = $(addprefix obj/,$(SOURCES:.c=.o))

OBJECTS_GCOV = $(addprefix gcov_obj/,$(SOURCES:.c=.o))

.PHONY: all clean rebuild

all: test gcov_report s21_decimal_gcov.a s21_decimal.a

s21_decimal.a: $(OBJECTS) 
	ar -src $@ $(OBJECTS)

s21_decimal_gcov.a: $(OBJECTS_GCOV)
	ar -src $@ $(OBJECTS_GCOV)

test: gcov_obj/s21_decimal_test.o s21_decimal_gcov.a
	$(CC) gcov_obj/s21_decimal_test.o s21_decimal_gcov.a -o $@ $(LDFLAGS) $(GCOVFLAGS)
	chmod +x *
	./test

gcov_report: test
	lcov -t "test" -o gcov_obj/test.info -c -d gcov_obj/.  
	genhtml gcov_obj/test.info --output-directory report
	open ./report/index.html

gcov_obj/%.o: %.c
	$(CC) $(GCOVFLAGS) -c $< -o $@

# $(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@
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
	rm -f *.gch
