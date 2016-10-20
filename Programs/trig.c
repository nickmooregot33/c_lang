#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define FUNCTION 1
#define INPUT	2
#define INPUT2	3
#define TRUE 	1
#define NUMFUNCTIONS 22
#define TAN	"tan"
#define SIN	"sin"
#define COS	"cos"
#define ASIN	"asin"
#define ACOS	"acos"
#define ATAN	"atan"
#define ATAN2	"atan2"
#define SINH	"sinh"
#define COSH	"cosh"
#define TANH	"tanh"
#define EXP	"exp"
#define LOG	"log"
#define LOG10	"log10"
#define POW	"pow"
#define SQRT	"sqrt"
#define CEIL	"ceil"
#define FLOOR	"floor"
#define FABS	"fabs"
#define LDEXP	"ldexp"
#define FREXP	"frexp"
#define MODF 	"modf"
#define FMOD	"fmod"

char *function_names[] = {TAN,SIN,COS, ASIN, ACOS, ATAN, ATAN2, SINH, COSH, TANH, EXP, LOG, LOG10, POW, SQRT, CEIL, FLOOR, FABS, LDEXP, FREXP, MODF, FMOD};

typedef double (*function_pointer)(double);
function_pointer functions[] = {tan, sin, cos, asin, acos, atan, NULL, sinh, cosh, tanh, exp, log, log10, NULL, sqrt, ceil, floor, fabs, };

int main(int argc, char *argv[]){

	/*argc is the number of arguments, including the actual name of the program being called as the shell sees it*/
	/*argv is the array of each of the arguments, one for each argument that was counted by argc*/

	int selection, i, exp;
	double fraction, integral;
	 
	if(argc != 3 && argc != 4) {
		printf("Usage:\t%s <function> <input1>  [<input2>]\n",argv[0]);
		exit(0);
	}

	for(i = 0; i < 22; i++){
		if(!strcmp(argv[FUNCTION], function_names[i])){
			selection = i;
			break;
		}
	}

	if(i>=22){
		printf("ERROR: invalid trigonometric function: %s",argv[0]);
		exit(1);
	}
		
	switch (selection){
	case 0: case 1:	case 2:	case 3:	case 4:	case 5:	
		printf("The %s of %f is %f.\n", argv[FUNCTION],atof(argv[INPUT]), functions[selection](atof(argv[INPUT])));
		break;
	case 6:	
		printf("The %s of %s and %s is %f.\n",argv[FUNCTION], argv[INPUT], argv[INPUT2], atan2(atof(argv[INPUT]),atof(argv[INPUT2])));
		break;
	case 7:	case 8:	case 9:	case 10: case 11: case 12: 
		printf("The %s of %f is %f.\n", argv[FUNCTION],atof(argv[INPUT]), functions[selection](atof(argv[INPUT])));
		break;
	case 13:
		printf("The %s of %f is %f.\n", argv[FUNCTION],atof(argv[INPUT]), pow(atof(argv[INPUT]),atof(argv[INPUT2])));
		break;
	case 14: case 15: case 16: case 17:
		printf("The %s of %f is %f.\n", argv[FUNCTION],atof(argv[INPUT]), functions[selection](atof(argv[INPUT])));
		break;
	case 18:
		printf("The %s of %f is %f.\n", argv[FUNCTION],atof(argv[INPUT]), ldexp(atof(argv[INPUT]),atoi(argv[INPUT2])));
		break;
	case 19:
		fraction = frexp(atof(argv[INPUT]),&exp);
		printf("The exponent is %d and the fraction of %s in the interval [1/2,1] is %f\n",exp,argv[INPUT], fraction);
		break;
	case 20:
		fraction = modf(atof(argv[INPUT]),&integral);
		printf("The fractional part of %s is %f and the integral part is %f\n",argv[INPUT], fraction, integral);
		break;
	default:
		printf("The floating-point remainder of %s / %s is %f, unless y is 0.\n",argv[INPUT], argv[INPUT2],fmod(atof(argv[INPUT]),atof(argv[INPUT2])) );
	}

	exit(0);
}

