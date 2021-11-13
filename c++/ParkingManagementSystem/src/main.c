#include <string.h>

#include "parksys.h"

void parkin(Person * user, int car_type, int x, int y, int z) {
	int c_id = 0; // cars parking id
	x--; y--; z--; // index changes

	// Generate the parking places id
	switch (car_type) {
		case CAR:
			c_id = PLACE_CAR | ((z * 12 * 12 + y * 12 + x) << 2);
			// printf("car type = CAR\n");
			break;
		case BIKE_NOCHARGING:
			c_id = PLACE_EBIKE | ((y * 30 + x) << 2);
			// printf("car type = EBKIE\n");
			break;
		case BIKE_WITHCHARGING:
			c_id = PLACE_EBIKE | ((y * 30 + x) << 2);
			// printf("car type = NBIKE\n");
			break;
	}
	// printf("car should id: %d\n", c_id);

	Place * p = get_place_byid(c_id);
	if (p == NULL) {
		fprintf(stderr, "Fucking NULL Pointer!\n");
	}
	if (p->avaliable == IN) {
		fprintf(stderr, "Parkin place is already in use.\n");
		return;
	}

	p->user_id = user->id;
	p->avaliable = IN;
	user->car_id = c_id;
	user->status = IN;
}

int main() {
	init_users();
	init_parkinglot();

	// BUG: type long could only save number under 4294967295 (2 ^ 64)
	Person * me = new_person("Fu", "10", "15982274089");
	// print_person_info(me);

	Person * tme = get_person_byname("Fu");
	if (tme != me) {
		fprintf(stderr, "Get Person By Name function doesn't run correctly\n");
	}

	parkin(me, CAR, 1, 1, 1);
	// printf("park in ok\n");
	// Place * p = get_place_byid(me->car_id);
	// printf("Get place ok, p id = %d\n\n", p->id);
	print_person_info(me);
	// printf("car place id: %o\n", p->id);


	return 0;
}
