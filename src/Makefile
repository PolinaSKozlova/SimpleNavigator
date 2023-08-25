#all, clean, test, s21_graph.a, s21_graph_algorithms.a
CC = g++
CC_FLAGS = -Wall -Wextra -Werror -std=c++17 #-pedantic-errors
TEST_FLAGS = -lgtest -pthread
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage --coverage
SANITIZER_FLAGS = #-fsanitize=address
SRCS=$(wildcard s21*.cc,*/s21*.cc)
OBJ_FILES=$(patsubst %.cc,%.o,$(SRCS))
REPORT_DIR = report
GRAPH = s21_graph
GRAPH_ALGO = s21_graph_algorithms

run:
	$(CC) $(CC_FLAGS) graph_classes/s21_graph.cc run.cc -o run -g
	./run

all:

clean:
	rm -rf *.o *.gcno *.gcda *.info *.a $(REPORT_DIR) g_tests run *.dSYM

test: 
	clear
	$(CC) $(CC_FLAGS) graph_tests/*_tests.cc -o g_tests $(TEST_FLAGS)
	./g_tests

gcov_report:
	clear
	$(CC) $(CC_FLAGS) $(COVERAGE_FLAGS) graph_tests/*_tests.cc -o g_tests $(TEST_FLAGS)
	./g_tests
	lcov -t "$@" -o $@.info -c -d . --no-external  --ignore-errors mismatch --quiet
	lcov -r $@.info "*include*" -o $@.info  --ignore-errors unused --quiet
	genhtml -o ./$(REPORT_DIR) $@.info
	open ./report/index.html

$(GRAPH).a: 
	$(CC) -c $(FLAGS) graph_classes/s21_graph.cc -o $(GRAPH).o -I .
	ar rcs $(GRAPH).a $(GRAPH).o
	rm *.o

$(GRAPH_ALGO).a:
	$(CC) -c $(FLAGS) graph_classes/s21_graph_algorithms.cc -o $(GRAPH_ALGO).o -I .
	ar rcs $(GRAPH_ALGO).a $(GRAPH_ALGO).o
	rm *.o

%.o:%.cc
	$(CC) -c $(FLAGS) $< -o $@ -I .

valgrind: test
	valgrind --leak-check=full \
        	 --show-leak-kinds=all \
         	 --track-origins=yes \
         	 --verbose \
			 ./g_tests

leaks: run
	CK_FORK=no leaks -atExit -- ./run 

.PHONY:
	all, clean, test, gcov_report s21_graph.a, s21_graph_algorithms.a

clang:
	clang-format -i --style=Google *.cc *.h
	clang-format -n --style=Google *.cc *.h

cppcheck:
	cppcheck --enable=all --language=c++ --std=c++17 --suppress=missingIncludeSystem *.cc *.h

push:
	git push origin graph_branch
