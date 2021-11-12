#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// define payment here
#define BIKE_NOCHARGING 	10
#define BIKE_WITHCHARGING 	15
#define CAR			20

struct Person {
	char * name;
	int id;
	int phone;
	int balance;
	int status;
};
typedef struct Person Person;
