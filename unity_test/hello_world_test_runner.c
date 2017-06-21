#include "unity_fixture.h"
#include "unity.h"
#include "hello_world.h"
#include <string.h>


TEST_GROUP(hello_world);

static char result[100];

static char *HELLO_WORLD = "Hello world!\n";
static char *HELLO_NICK = "Hello nick!\n";
static char *NICK = "nick";
static char *EMPTY_STRING = "";
static char *EMPTY_ARGV[2] = {0};
static char *HELLO_NICK_ARGV[2] = {0};

TEST_SETUP(hello_world){
	memset(result,0xff,sizeof result);
	EMPTY_ARGV[0] = EMPTY_STRING;
	EMPTY_ARGV[1] = EMPTY_STRING;
	HELLO_NICK_ARGV[0] = EMPTY_STRING;
	HELLO_NICK_ARGV[1] = NICK;
}

TEST_TEAR_DOWN(hello_world){

}
	
TEST(hello_world,hello_outputs_hello_world){
	TEST_ASSERT_EQUAL_STRING(HELLO_WORLD,hello(1,EMPTY_ARGV));
}

TEST(hello_world,hello_outputs_hello_nick){
	TEST_ASSERT_EQUAL_STRING(HELLO_NICK,hello(2,HELLO_NICK_ARGV));
}

TEST_GROUP_RUNNER(hello_world){
	RUN_TEST_CASE(hello_world,hello_outputs_hello_world);
	RUN_TEST_CASE(hello_world,hello_outputs_hello_nick);
}

static void run_all_tests(void){
	RUN_TEST_GROUP(hello_world);
}

int main(int argc, char *argv[]){
	return UnityMain(argc, (const char **)argv, run_all_tests);
}

