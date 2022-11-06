.PHONY: all re s21_matrix clean check test
#.PHONY если есть файлы с именем как цель, они игнорируются

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wno-unused -pedantic -std=c++17 -lstdc++ -g
TST_LIBS := -lgtest -lm -lpthread

# цели all, clean, test, s21_matrix_oop.a

all: test

re: clean test

test: s21_matrix_oop.a s21_test.o
	$(CC) $(CFLAGS) s21_test.o s21_matrix_oop.a $(TST_LIBS) -o test
	@./test

s21_test.o: s21_test.cc
	$(CC) $(CFLAGS) -c s21_test.cc -o s21_test.o

s21_matrix_oop.a: s21_matrix_oop.o
	@ar rcs s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a

s21_matrix_oop.o: s21_matrix_oop.cc
	$(CC) $(CFLAGS) -c s21_matrix_oop.cc -o s21_matrix_oop.o

gcov_report: gcov_test.info
	@genhtml -o report/ gcov_test.info
	@open report/index.html

gcov_test.info: gcov_test gcov_test.gcda
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: s21_test.cc s21_matrix_oop.cc
	$(CC) $(CFLAGS) --coverage s21_test.cc s21_matrix_oop.cc $(TST_LIBS) -o gcov_test

gcov_test.gcda:
	@chmod +x *
	@./gcov_test

clean: 
	@rm -rf *.o *.a test gcov_test *.gcno *.gcda *.info report *.dSYM
	
style:
	# cp ../materials/linters/.clang-format ./
	clang-format -i *.h *.cc
	clang-format -n *.h *.cc

leak:
	CK_FORK=no leaks -atExit -- ./test
