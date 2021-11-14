#include <string.h>
#include <ctype.h>

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
	user->car_id = p->id;
	user->status = IN;
}

void parkin(Person * user, int car_type) {
	Place * p = get_place_random(car_type);
	_parkin(user, p);
}

void parkout(Person * user) {
	Place * p = get_place_byid(user->car_id);
	leave_place(p);
	user->status = NOT_IN;
}

char * readline(char * input) {
	if (input == NULL) {
		input = (char *)malloc(0);
	}

	rewind(stdin);

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

Person * ask_person() {
	char * name = NULL;
__ask_person:
	printf("Please enter your name: ");
	name = readline(name);
	Person * p = get_person_byname(name);
	free(name);
	if (p == NULL) {
		printf("All validate names here:\n");
		for (int i = 0; i < users.length; i++) {
			printf("\t%s\n", users.user[i]->name);
		}
		goto __ask_person;
	}
	return p;
}

int main() {
	init_users();
	init_parkinglot();

	Person * me = new_person("Fu", "10", "15982274089");

	Person * tme = get_person_byname("Fu");
	if (tme != me) {
		fprintf(stderr, "Get Person By Name function doesn't run correctly\n");
	}

	print_person_info(me);
	
	// Now for cli
	char * input = (char *)malloc(sizeof(char) * 20);
	printf( // Print Help message first
			"Parking Management System Cli\n"
			"Made By jeefy, sources see github.com/jeefies/study/tree/master/c++/ParkingManagementSystem\n"
			"Help at managers methods:\n"
			"Parking operations:\n"
			"\tpark: select a person and park his car or bike in\n"
			"\tleave: select a person and move his car out\n"
			"Personnal operations:\n"
			"\tadd: add a new person in\n"
			"\tperson: select a person and print his infomation, including parkng status\n"
			"\tlist: list all registered users\n"
			"Parking lot operations:\n"
			"\tstatus: view current car-park occupation and number of free spaces\n"
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
			Person * p = ask_person();
			if (p->status == IN) {
				printf("You are already parking!\n");
				continue;
			}

			char * cartype;
			int type;
__parkcar:
			printf("What's your car type ? [car or bike]: ");
			cartype = readline(NULL);
			if (strcmp(cartype, "car") == 0) {
				// CAR
				type = PLACE_CAR;
				free(cartype);
			} else if (strcmp(cartype, "bike") == 0) {
				printf("Need charge or not [Y\\n]: ");
				cartype = readline(cartype);
				if (tolower(cartype[0]) == 'y') {
					// EBIKE
					type = PLACE_EBIKE;
				} else {
					// NBKIE
					type = PLACE_NBIKE;
				}
				free(cartype);
			} else {
				printf("Unknow car type, please enter again\n");
				goto __parkcar;
			}
			printf("Car type : %d\n", type);

			parkin(p, type);

			print_person_info(p);

		} else if (strcmp(input, "leave") == 0) {
			Person * p = ask_person();
			if (p->status != IN) {
				printf("You don't have to leave\n");
				continue;
			}

			parkout(p);
			printf("Park out successfully\n");
		} else if (strcmp(input, "person") == 0) {
			print_person_info(ask_person());
		} else if (strcmp(input, "list") == 0) {
			for (int i = 0; i < users.length; i++) {
				printf(
						"name: %s\n"
						"\tuni_id: %d\n"
						"\tphone number: %ld\n",
						users.user[i]->name, users.user[i]->uni_id, users.user[i]->phone
					);
			}
		} else if (strcmp(input, "status") == 0) {
			print_parking_status();
		}

	}

__done:

	return 0;
}
