#all, clean, test, s21_graph.a, s21_graph_algorithms.a
CC = g++
CC_FLAGS = -Wall -Wextra -Werror -std=c++17 #-pedantic-errors
MFLAGS=-MMD -MP
TEST_FLAGS = -lgtest -pthread
COVERAGE_FLAGS = --coverage -fprofile-arcs -ftest-coverage 
SANITIZER_FLAGS = #-fsanitize=address
SRCS=$(wildcard s21*.cc,*/s21*.cc)
OBJ_FILES=$(patsubst %.cc,%.o,$(SRCS))
REPORT_DIR = report
GRAPH = s21_graph
GRAPH_ALGO = s21_graph_algorithms


all: app_console

app_console:
	$(CC) $(CC_FLAGS) $(MFLAGS) graph_classes/*.cc console_app.cc -o console_app
	rm -rf console_app.dSYM & clear
	./console_app

clean:
	rm -rf *.o *.gcno *.gcda *.info *.a $(REPORT_DIR) g_tests run *.dSYM *.dot *.gv console_app *.d

test: 
	clear
	$(CC) $(CC_FLAGS) $(SANITIZER_FLAGS) $(MFLAGS) graph_classes/*.cc graph_tests/graph_*.cc -o g_tests $(TEST_FLAGS) 
	./g_tests

gcov_report:
	clear
	$(CC) $(CC_FLAGS) $(MFLAGS) $(COVERAGE_FLAGS) graph_classes/*.cc graph_tests/graph_*.cc -o g_tests $(TEST_FLAGS)
	./g_tests
	lcov -t "$@" -o $@.info -c -d . --no-external  --ignore-errors mismatch --quiet
	lcov -r $@.info "*include*" -o $@.info  --ignore-errors unused --quiet
	genhtml -o ./$(REPORT_DIR) $@.info
	open ./report/index.html

$(GRAPH).a: 
	$(CC) -c $(FLAGS) $(MFLAGS) graph_classes/s21_graph.cc -o $(GRAPH).o -I .
	ar rcs $(GRAPH).a $(GRAPH).o
	rm *.o

$(GRAPH_ALGO).a:
	$(CC) -c $(FLAGS) $(MFLAGS) graph_classes/s21_graph_algorithms.cc -o $(GRAPH_ALGO).o -I .
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

leaks: app_console test
	CK_FORK=no leaks -atExit -- ./g_tests
	CK_FORK=no leaks -atExit -- ./console_app

.PHONY:
	all, clean, test, gcov_report, s21_graph.a, s21_graph_algorithms.a, app_console

clang:
	clang-format -i --style=Google graph_classes/*.cc graph_classes/*.h
	clang-format -n --style=Google graph_classes/*.cc graph_classes/*.h

cppcheck:
	cppcheck --enable=all --language=c++ --std=c++17 --suppress=missingIncludeSystem graph_classes/*.cc graph_classes/*.h console/console.h
