#include <stdlib.h>
#include <time.h>

#include "parksys.h"

struct ParkingLot parkinglot;

int floordiv(int a, int b) {
	return (a - a % b) / b;
}

void init_parkinglot() {
	srand((unsigned)time(NULL));

	parkinglot.cars = (Place *)malloc(PLACES * 12 * 12 * 5);
	parkinglot.ebike = (Place *)malloc(PLACES * 30 * 2);
	parkinglot.nbike = (Place *)malloc(PLACES * 30 * 4);
	parkinglot.frees = (int *)malloc(sizeof(int) * (12 * 12 * 5 + 30 * 6));
	parkinglot.free_counts[PLACE_CAR] = 12 * 12 * 5;
	parkinglot.free_counts[PLACE_EBIKE] = 30 * 2;
	parkinglot.free_counts[PLACE_NBIKE] = 30 * 4;

	int fi = 0;
	int id;

	// Set every parking lot place id
	for (int i = 0; i < 12 * 12 * 5; i++) {
		id = PLACE_CAR | (i << 2);
		parkinglot.cars[i].id = id;
		parkinglot.frees[fi++] = id;
	}

	for (int i = 0; i < 30 * 2; i++) {
		parkinglot.ebike[i].id = (id = PLACE_EBIKE | (i << 2));
		parkinglot.frees[fi++] = id;
	}

	for (int i = 0; i < 30 * 4; i++) {
		parkinglot.nbike[i].id = (id = PLACE_NBIKE | (i << 2));
		parkinglot.frees[fi++] = id;
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
					(buf = floordiv(i, 12) - buf * 12) + 1, // col
					(i % 12) + 1 // row
				);
			return name;
		case PLACE_EBIKE:
			sprintf(name, "Bike with charge parks at col %d row %d\n",
					(buf = floordiv(i, 30)) + 1,
					i - buf * 30 + 1
					);
			return name;
		case PLACE_NBIKE:
			sprintf(name, "Bike without charge parks at col %d row %d\n",
					(buf = floordiv(i, 30)) + 1,
					i - buf * 30 + 1
					);
			return name;
	}
	printf("No such type\n");
	return "";
}

void takeup_place(Place * p) {
	switch (p->id & 0b11) {
		case PLACE_CAR:
			parkinglot.frees[p->id >> 2] = -1;
			break;
		case PLACE_EBIKE:
			parkinglot.frees[12 * 12 * 5 + (p->id >> 2)] = -1;
			break;
		case PLACE_NBIKE:
			parkinglot.frees[12 * 12 * 5 + 30 * 2 + (p->id >> 2)] = -1;
			break;
	}
	if (parkinglot.free_counts[p->id & 0b11] <= 0) {
		fprintf(stderr, "No enough place was left\n");
		return;
	}
	parkinglot.free_counts[p->id & 0b11] -= 1;

	p->avaliable = IN;
}

void leave_place(Place * p) {
	switch (p->id & 0b11) {
		case PLACE_CAR:
			parkinglot.frees[p->id >> 2] = p->id;
			break;
		case PLACE_EBIKE:
			parkinglot.frees[12 * 12 * 5 + (p->id >> 2)] = p->id;
			break;
		case PLACE_NBIKE:
			parkinglot.frees[12 * 12 * 5 + 30 * 2 + (p->id >> 2)] = p->id;
			break;
	}
	parkinglot.free_counts[p->id & 0b11] += 1;
	p->avaliable = NOT_IN;
}

Place * get_place_random(int car_type) {
	int randint;
	if (car_type == PLACE_CAR) {
		int i = (randint = rand() % (12 * 12 * 5));
		while (parkinglot.frees[i] == -1) {
			i++;
			if (i >= 720) {  // 12 * 12 * 5
				i = 0;
			}
			if (randint == i) {
				return NULL;
			}
		};
		printf("Rand ok %d\n", i);
		Place * p = get_place_byid(parkinglot.frees[i]);
		return p;
	} else if (car_type == PLACE_EBIKE) {
		int i = (randint = rand() % (30 * 2) + 12 * 12 * 5);
		while (parkinglot.frees[i] == -1) {
			i++;
			// if (i >= 12 * 12 * 5 + 30 * 2) {}
			if (i >= 780) {
				i = 720; // 12 * 12 * 5
			}
			if (randint == i) {
				return NULL;
			}
		};
		Place * p = get_place_byid(parkinglot.frees[i]);
		return p;
	} else {
		// PLACE_NBIKE
		int i = (randint = rand() % (30 * 4) + 780); // 12 * 12 * 5 + 30 * 2
		while (parkinglot.frees[i] == -1) {
			i++;
			// if (i >= 12 * 12 * 5 + 30 * 2 + 30 * 4) {
			if (i >= 900) {
				i = 780; // 12 * 12 * 5
			}
			if (randint == i) {
				return NULL;
			}
		};
		Place * p = get_place_byid(parkinglot.frees[i]);
		return p;
	}
}

void print_parking_status() {
	int c, eb, nb;
	c = parkinglot.free_counts[PLACE_CAR];
	eb = parkinglot.free_counts[PLACE_EBIKE];
	nb = parkinglot.free_counts[PLACE_NBIKE];

	printf(	"All places left: %d\n"
		"\tCar place left: %d\n"
		"\tBike with an electrical recharge plug left: %d\n"
		"\tBike without an electrical recharge plug left: %d\n",
		c + eb + nb, c, eb, nb);
}
