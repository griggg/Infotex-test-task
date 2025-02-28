CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pthread
LIB_NAME = liblog.so

all: library app test run_rests

library:
	$(CC) $(CFLAGS) -fPIC -shared log_library/log.cpp -o log_library/$(LIB_NAME)

app:
	$(CC) $(CFLAGS) -o test_app/test_app test_app/main.cpp -Llog_library -llog -Ilog_library

test: app library
	$(CXX) $(CXXFLAGS) tests/test_logger.cpp log_library/log.cpp -o test

run_rests: test
	./test

clean:
	rm -f log_library/$(LIB_NAME) test_app/test_app
	rm -f test
	find . -name "*.txt" -type f -delete
	
