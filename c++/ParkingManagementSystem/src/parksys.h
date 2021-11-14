#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// define payment here
#define BIKE_NOCHARGING 	10
#define BIKE_WITHCHARGING 	15
#define CAR			20

// define Place type here
#define PLACE_CAR	0
#define PLACE_EBIKE	1
#define PLACE_NBIKE	2

// define Person status
#define NOT_IN	0
#define IN 1

// definations for users
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
extern struct Users users;

// definations for parking lot
struct Place {
	int avaliable;
	int id; // 32bits, last 2 bits for type
	int user_id;
};
typedef struct Place Place;
#define PLACES sizeof(Place)

struct ParkingLot {
	Place * cars;
	Place * ebike;
	Place * nbike;
	int * frees;
	int free_counts[3];
};
extern struct ParkingLot parkinglot;

// declare the functions here

// for submodule parking lot
void init_parkinglot();
Place * get_place_byid(int id);
// remember to free the pointer after use, it's allocated by malloc
char * get_place_name(Place * p); 
void print_parking_status();
void takeup_place(Place * p);
void leave_place(Place * p);
Place * get_place_random(int car_type);

// for submodule users
void init_users();
Person * new_person(const char * name, const char * uni_id, const char * phonenumber);
Person * get_person_byname(const char * name);
void print_person_info(Person * user);

// to combine users and parking lot submodules together
void __parkin(Person * user, int car_type, int x, int y, int z); // z is only used in parking cars
void _parkin(Person * user, Place * p);
void parkin(Person * user, int);
