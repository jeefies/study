#include <stdlib.h>

#include "parksys.h"

struct ParkingLot parkinglot;

int floordiv(int a, int b) {
	return (a - a % b) / b;
}

void init_parkinglot() {
	parkinglot.cars = (Place *)malloc(PLACES * 12 * 12 * 5);
	parkinglot.ebike = (Place *)malloc(PLACES * 30 * 2);
	parkinglot.nbike = (Place *)malloc(PLACES * 30 * 4);

	// Set every parking lot place id
	for (int i = 0; i < 12 * 12 * 5; i++) {
		parkinglot.cars[i].id = PLACE_CAR | (i << 2);
	}

	for (int i = 0; i < 30 * 2; i++) {
		parkinglot.ebike[i].id = PLACE_EBIKE | (i << 2);
		parkinglot.nbike[i].id = PLACE_NBIKE | (i << 2);
		parkinglot.nbike[i * 2].id = PLACE_NBIKE | (i * 2 << 2);
	}

}

Place * get_place_byid(int id) {
	// printf("? id >> 2 = %d, id|0b11 = %d\n", id >> 2, id & 0b11);
	switch (id & 0b11) {
		case PLACE_CAR:
			return &parkinglot.cars[id >> 2];
		case PLACE_EBIKE:
			return &parkinglot.ebike[id >> 2];
		case PLACE_NBIKE:
			return &parkinglot.nbike[id >> 2];
	}
}
char * get_place_name(Place * p) {
	char * name = (char *)malloc(sizeof(char) * 50);
	int i = p->id >> 2;
	int buf;
	// printf("place id = %d, & 0b11 = %d\n", p->id, p->id & 0b11);
	switch (p->id & 0b11) {
		case PLACE_CAR:
			sprintf(name, "Car parks at floor %d col %d row %d",
					(buf = floordiv(i, 12 * 12)) + 1, // floor
					(buf += floordiv(i - buf, 12)) + 1, // col
					(i - buf) + 1 // row
				);
			return name;
		case PLACE_EBIKE:
			sprintf(name, "Bike with charge parks at col %d row %d\n",
					(buf = floordiv(i, 30)) + 1,
					i - buf + 1
					);
			return name;
		case PLACE_NBIKE:
			sprintf(name, "Bike without charge parks at col %d row %d\n",
					(buf = floordiv(i, 30)) + 1,
					i - buf + 1
					);
			return "";
	}
	printf("No such type\n");
	return "";
}
