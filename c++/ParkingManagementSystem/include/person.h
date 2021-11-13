#include <stdint.h>

struct Person {
	char * name;
	int uni_id; // university id
	uint64_t phone;
	int balance;
	int status; // save the car parking status, in or not in
	int car_id; // The id of car parking place

	// The id to get the pointer of instance of the person
	int id;
};
typedef struct Person Person;

struct Users {
	Person ** user;
	int length;
};

extern struct Users user;
