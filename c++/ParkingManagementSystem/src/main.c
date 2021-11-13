#include <string.h>

#include "parksys.h"

void __parkin(Person * user, int car_type, int x, int y, int z) {
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

}

void _parkin(Person * user, Place * p) {
	if (p == NULL) {
		fprintf(stderr, "Fucking NULL Pointer!\n");
		return;
	}
	if (p->avaliable == IN) {
		fprintf(stderr, "Parkin place is already in use.\n");
		return;
	}

	p->user_id = user->id;
	takeup_place(p);
	user->car_id = c_id;
	user->status = IN;
}

void parkin(Person * user, int car_type) {
	Place * p = get_place_random(car_type);
	_parkin(user, p);
}

char * readline(char * input) {
	if (input == NULL) {
		input = (char *)malloc(0);
	}

	int i = 0;
	char buf;
	while ((buf = getchar()) != '\n') {
		input = (char *)realloc(input, sizeof(char) * (i + 1));
		input[i] = buf;
		i++;
	}
	input[i] = '\0';

	return input;
}

int main() {
	init_users();
	init_parkinglot();

	Person * me = new_person("Fu", "10", "15982274089");

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
	
	// Now for cli
	char * input = (char *)malloc(sizeof(char) * 20);
	printf( // Print Help message first
			"Parking Management System Cli\n"
			"Made By jeefy, sources see github.com/jeefies/study/tree/master/c++/ParkingManagementSystem\n"
			"Help at methods:\n"
			"\tadd: add a new person in\n"
			"\tpark: select a person and park his car or bike in\n"
			"\tleave: select a person and move his car out\n"
			"\tperson: select a person and print his infomation\n"
	      );
	while (1) {
		// BUG could not read more than 50 characters
		// Now get the line
		printf(">>> ");
		rewind(stdin);
		input = readline(input);

		if (strcmp(input, "add") == 0) {
			printf("Please enter your name: ");
			char * name = readline(NULL);
			printf("Please enter your university id: ");
			char * uni_id = readline(NULL);
			printf("Please enter your phone number: ");
			char * phonenumber = readline(NULL);

			Person * p = new_person(name, uni_id, phonenumber);
			printf("New info created!");
			print_person_info(p);

			free(name); free(uni_id); free(phonenumber);
		} else if (strcmp(input, "park") == 0) {
__parkcar1:
			printf("Please enter your name: ");
			char * name = readline(NULL);
			Person * p = get_person_byname(name);
			free(name);
			if (p == NULL) {
				printf("All validate names here:\n");
				for (i = 0; i < users.length; i++) {
					printf("\t%s\n", users.user[i]->name);
				}
				goto __parkcar1;
			}

			char * cartype;
			int type;
__parkcar2:
			printf("What's your car type ? [car or bike]: ");
			cartype = readline(NULL);
			if (strcmp(cartype, "car")) {
				// CAR
				type = PLACE_CAR;
			} else if (strcmp(cartype, "bike")) {
				printf("Need charge or not [Y\\n]: ");
				if (strcmp(cartype, "y")) {
					// EBIKE
					type = PLACE_EBIKE;
				} else {
					// NBKIE
					type = PLACE_NBIKE;
				}
			} else {
				printf("Unknow car type, please enter again\n");
				goto __parkcar2;
			}

			parkin(p, type);

			print_person_info(p);

		} else if (strcmp(input, "leave") == 0) {
		} else if (strcmp(input, "person") == 0) {
		}

	}

__done:

	return 0;
}
