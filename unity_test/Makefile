UNITY_FIXTURE_SOURCE_PATH=unity/extras/fixture/src
UNITY_SOURCE_PATH=unity/src/
ONLY_COMPILE=-c
ERROR_FLAGS=-Wall -Werror
INCLUDE_DIRECTORY=-I
DEBUG=-g
CC=gcc
OUTPUT_AS=-o
POSITION_INDEPENDENT=-fPIC
UNITY_MAJOR=2
UNITY_MINOR=4
UNITY_RELEASE=1
UNITY_REALNAME=$(UNITY_SONAME).$(UNITY_MINOR).$(UNITY_RELEASE)
UNITY_SONAME=libunitytest.so.$(UNITY_MAJOR)
LIB_DIR=/usr/local/lib/
LIB_INSTALL=ldconfig

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

test_hello: HELLO_WORLD HELLO_WORLD_TEST_RUNNER
	$(CC) $(OUTPUT_AS) hello_world_test  hello_world_test_runner.o -lunitytest $(ERROR_FLAGS)
	./hello_world_test

main: main.c
	$(CC) $(ONLY_COMPILE) main.c

library: 
	git clone https://github.com/ThrowTheSwitch/Unity.git unity
	$(CC) $(POSITION_INDEPENDENT) $(DEBUG) $(ONLY_COMPILE) unity/src/unity.c $(INCLUDE_DIRECTORY) unity/src  
	$(CC) $(POSITION_INDEPENDENT) $(DEBUG) $(ONLY_COMPILE) unity/extras/fixture/src/unity_fixture.c $(INCLUDE_DIRECTORY) unity/extras/fixture/src/ $(INCLUDE_DIRECTORY) unity/src/ $(ERROR_FLAGS) 
	$(CC) -shared -Wl,-soname,$(UNITY_SONAME) -o $(UNITY_REALNAME) unity.o unity_fixture.o -lc
	mv $(UNITY_REALNAME) $(LIB_DIR)
	$(LIB_INSTALL) -n $(LIB_DIR)

.PHONY: clean test test_hello all
	
test: test_hello
	
clean:
	rm -f *.o hello_world_test hello_world_test_runner hello_world
	rm -rf unity 
