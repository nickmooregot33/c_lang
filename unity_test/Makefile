UNITY_FIXTURE_SOURCE_PATH=~/Software/Unity/extras/fixture/src
UNITY_SOURCE_PATH=~/Software/Unity/src
ONLY_COMPILE=-c
ERROR_FLAGS=-Wall -Werror
INCLUDE_DIRECTORY=-I
CC=gcc
OUTPUT_AS=-o
POSITION_INDEPENDENT=-fPIC

all: test main HELLO_WORLD
	$(CC) $(OUTPUT_AS) hello_world main.o hello_world.o $(ERROR_FLAGS)

UNITY: $(UNITY_SOURCE_PATH)
	$(CC) $(ONLY_COMPILE) $(UNITY_SOURCE_PATH)/unity.c $(INCLUDE_DIRECTORY) $(UNITY_SOURCE_PATH) $(POSITION_INDEPENDENT)

UNITY_FIXTURE:
	$(CC)  $(ONLY_COMPILE) $(UNITY_FIXTURE_SOURCE_PATH)/unity_fixture.c $(INCLUDE_DIRECTORY) $(UNITY_FIXTURE_SOURCE_PATH) $(INCLUDE_DIRECTORY) $(UNITY_SOURCE_PATH) $(ERROR_FLAGS)

HELLO_WORLD: hello_world.h hello_world.c
	$(CC) $(ONLY_COMPILE) hello_world.c $(ERROR_FLAGS)

HELLO_WORLD_TEST_RUNNER: hello_world.h hello_world_test_runner.c
	$(CC) $(ONLY_COMPILE) hello_world_test_runner.c $(INCLUDE_DIRECTORY) $(UNITY_FIXTURE_SOURCE_PATH) $(INCLUDE_DIRECTORY) $(UNITY_SOURCE_PATH)

test_hello: UNITY UNITY_FIXTURE HELLO_WORLD HELLO_WORLD_TEST_RUNNER
	$(CC) $(OUTPUT_AS) hello_world_test  hello_world_test_runner.o hello_world.o unity_fixture.o unity.o $(ERROR_FLAGS)
	./hello_world_test

main: main.c
	$(CC) $(ONLY_COMPILE) main.c


.PHONY: clean test test_hello all
	

test: test_hello
	
clean:
	rm -f *.o hello_world_test hello_world_test_runner hello_world
