#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parksys.h"

struct Users users;

void init_users() {
	// allocate a place for saving every person's info
	users.user = (Person **)malloc(0);
	users.length = 0;
}

Person * new_person(const char * name, const char * uni_id, const char * phonenumber) {
	Person * new = (Person *)malloc(sizeof(Person));
	new->name = (char *)malloc(sizeof(char) * strlen(name) + sizeof(char));
	strcpy(new->name, name);

	new->uni_id = atoi(uni_id);
	/*
	uint64_t phone;
	uint64_t multmp = 1;
	for (int i = strlen(phonenumber) - 1; i >= 0; i--) {
		phone += (phonenumber[i] - 48) * multmp; // according to ascii
		printf("n = %d, mul = %d\n", phonenumber[i] - 48, multmp);
		multmp *= 10;
	}
	new->phone = phone;
	*/
	new->phone = atoll(phonenumber);

	// Set default
	new->balance = 0;
	new->status = NOT_IN;
	new->id = users.length;

	// Add to users list
	users.length += 1;
	users.user = (Person **)realloc(users.user, sizeof(Person *) * users.length);
	users.user[new->id] = new;

	return new;
}

Person * get_person_byname(const char * name) {
	for (int i = 0; i < users.length; i++) {
		if (strcmp(name, users.user[i]->name) == 0) {
			return users.user[i];
		}
	}
	fprintf(stderr, "Could not get the person's info by name: %s\n", name);
	return NULL;
}

void print_person_info(Person * user) {
	printf(	"Name: %s\n"
		"University Id: %d\n"
		"Phone number: %ld\n"
		"Balance: %d\n",
		user->name, user->uni_id, user->phone, user->balance
	      );
	if (user->status == IN) {
		char * placename = get_place_name(get_place_byid(user->car_id));
		printf("Status: Parking\nParking Place: %s\n", placename);
		free(placename);
	} else {
		printf("Status: Not parking\n");
	}
}
