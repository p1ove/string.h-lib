CFLAGS=-std=c11 -Wall -Werror -Wextra 
TESTS=tests/test*.c
FLAG_TEST=-lcheck
SRCS=$(wildcard s21_*.c)
OBJS=$(SRCS:.c=.o)

ifeq ($(shell uname), Linux)
	FLAG_TEST +=-lsubunit -lm
endif

all: clean s21_string.a gcov_report

s21_string.a:$(OBJS)
	ar -rc s21_string.a $^
	ranlib s21_string.a
	rm -rf *.o

test: clean s21_string.a
	gcc --coverage $(CFLAGS) $(TESTS) s21_string.a $(FLAG_TEST) -o test -g
	./test

gcov_report:
	gcc --coverage $(SRCS) $(TESTS) $(FLAG_TEST) -o greport
	./greport
	lcov -t "test" -o s21_string.info -c -d .
	genhtml -o ./report s21_string.info
	open ./report/index.html

clean:
	-rm -rf *.o *.gcno *.gcda *.info  test s21_string.a gcov_report report greport a.out *.txt *.dSYM

style:
	clang-format -n *.c *.h ./tests/*.c ./tests/*.h
	clang-format -i *.c *.h ./tests/*.c ./tests/*.h
