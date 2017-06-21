#include<stdio.h>
#include "hello_world.h"
#include<string.h>

#define BUFFER_SIZE  1028

static const char* HELLO= "Hello ";
static const char* WORLD= "world";

static char output[BUFFER_SIZE];

char* hello(int count, char** strings){
	char* tmp = strcat(strcpy(output,HELLO), count > 1 ? strings[1]:WORLD);
	return strcat(tmp,"!\n");
}

int hello_world(int argc, char** argv){
	printf(hello(argc,argv));
	return 0;
}

