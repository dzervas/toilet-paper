/************************************************************//**
 * @file   main.c                                      			*
 * @author Antonis Papaioannou <papaioan@csd.uoc.gr>  			*
 *                                                    			*
 * @brief Header function for the needs of cs-240b project 2017 *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "geo.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

/*_print_list(loc->poi_list, &loc->poi_list->pid - &loc->poi_list, &loc->poi_list->next - &loc->poi_list);*/
/*void _print_list(void *list, unsigned int print_offset, unsigned int next_offset) {*/
	/*void *it;*/

	/*for (it = list; it; it = (it + next_offset)) {*/
		/*if (it + next_offset)*/
			/*printf("%d, ", (int) (it + print_offset));*/
		/*else*/
			/*printf("%d", (int) (it + print_offset));*/
	/*}*/
	/*printf("\nDONE\n");*/
/*}*/

/**
* @brief Add a new location to the system
*
* @param lid The location's id
*
* @return true on success
*         false on failure
*/
int add_location(int lid) {
	loc_t *tmp, *it, *prev = NULL;
	unsigned char for_broken = 0;

	/* Initialize the new node */
	tmp = malloc(sizeof(loc_t));

	if (!tmp) {
		fprintf(stderr, "Failed to allocate new node for loc_t!\n");
		return 0;
	}

	tmp->lid = lid;
	tmp->poi_list = NULL;
	tmp->next = NULL;

	/* Place the new node */
	if (!locations_list)
		/* In the start if list is empty */
		locations_list = tmp;
	else {
		/* Search the list for the next bigger lid and shove it */
		for (it = locations_list; it->next; prev = it, it = it->next) {
			if (it->lid > lid) {
				if (prev)
					prev->next = tmp;
				else
					locations_list = tmp;

				/* Make current node next */
				tmp->next = it;
				for_broken = 1;
				break;
			}
		}

		/* If not done in the loop, place the node last */
		if (!for_broken)
			it->next = tmp;
	}

	printf("L %d\n\tLocations = ", lid);
	for (it = locations_list; it; it = it->next) {
		if (it->next)
			printf("%d, ", it->lid);
		else
			printf("%d", it->lid);
	}
	printf("\nDONE\n");

	return 1;
}

/**
* @brief Add point-of-interest (POI) to a location
* 
* @param pid POI's id
* @param type The type of the POI
* @param distance The distance of POI from the locations reference point
* @param lid The location of the POI
*
* @return true on success
*         false on failure
*/
int add_poi_to_location(int pid, int type, int distance, int lid) {
	poi_t *tmp, *it, *prev = NULL;
	loc_t *loc;
	unsigned char for_broken = 0;

	/* Initialize the new node */
	tmp = malloc(sizeof(poi_t));

	if (!tmp) {
		fprintf(stderr, "Failed to allocate new node for poi_t!\n");
		return 0;
	}

	tmp->pid = pid;
	tmp->distance = distance;
	tmp->type = type;
	tmp->next = NULL;
	tmp->prev = NULL;

	/* Search for the location based on lid */
	for (loc = locations_list; loc && loc->lid != lid; loc = loc->next);

	if (!loc) {
		fprintf(stderr, "Could not find %d lid to add poi %d\n", lid, pid);
		return 0;
	}

	/* Place the new node */
	if (!loc->poi_list) {
		/* In the start if list is empty */
		loc->poi_list = tmp;
	} else {
		/* Search the list for the next bigger distance and shove it */
		for (it = loc->poi_list; it; prev = it, it = it->next) {
			/* Keep count of total and relative distance */
			tmp->distance -= it->distance;


			if (tmp->distance < 0) {
				tmp->distance += it->distance;

				if (it->prev)
					it->prev->next = tmp;
				else
					loc->poi_list = tmp;

				/* Make current node next and fix relative distance */
				tmp->next = it;
				tmp->prev = it->prev;
				it->prev = tmp;
				it->distance -= tmp->distance;

				for_broken = 1;
				break;
			}
		}

		/* If not done in the loop, place the node last */
		if (!for_broken) {
			DPRINT("Put after %d\n", prev->pid);
			prev->next = tmp;
			tmp->prev = prev;
		}
	}

	printf("P %d %d %d\n\tLocations = ", pid, lid, distance);
	for (it = loc->poi_list; it; it = it->next) {
		if (it->next)
			printf("%d:%d:%d->%d, ", it->pid, it->type, it->distance, (it->prev) ? it->prev->pid : -1);
		else
			printf("%d:%d:%d->%d", it->pid, it->type, it->distance, (it->prev) ? it->prev->pid : -1);
	}
	printf("\nDONE\n");

	return 1;
}

/**
* @brief A POI is unavailable to vistors
*
* @param pid The POI's id
* @param lid The location's id
* 
* @return true on success
*         false on failure
*/
int unavailable_poi(int pid, int lid) {
	return 1;
}

/**
* @brief Register user
*
* @param uid The user's id
* 
* @return true on success
*         false on failure
*/
int register_user(int uid) {
	return 1;
}
        
/**
* @brief User is interested in POI
* 
* @param uid The user's id
* @param pid The POI's id
*
* @return true on success
*         false on failure
*/
int interesting_poi(int uid, int upid) {
	return 1;
}
        
/**
* @brief Group users
* 
* @param uid1 The id of the 1st user
* @param uid2 The id of the 2nd user
* @param uid3 The id of the 3rd user
*
* @return true on success
*         false on failure
*/
int group_users(int uid1, int uid2, int uid3) {
	return 1;
}
        
/**
* @brief Calculate the distance between locations
* 
* @param lid The location's id
* @param pid1 The id of the 1st POI
* @param pid1 The id of the 2nd POI
* @param pid1 The id of the 3rd POI
*
* @return true on success
*         false on failure
*/
int sightseeing_distance(int lid, int pid1, int pid2, int pid3) {
	return 1;
}
        
/**
* @brief Print all locations
*
* @return true on success
*         false on failure
*/
int print_locations() {
	return 1;
}
        
/**
* @brief Print all users
*
* @return true on success
*         false on failure
*/
int print_users() {
	return 1;
}
        
/**
* @brief Search for user
* 
* @param uid The id of the user we are looking for
*
* @return true on success
*         false on failure
*/
int search_user(int uid) {
	return 1;
}

int free_world() {
	return 1;
}


/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Initialize global vars */
	users_sentinel = malloc(sizeof(usr_t));
	users_list = users_sentinel;
	users_sentinel->uid = -1;
	users_sentinel->interesting_poi = NULL;
	users_sentinel->next = NULL;

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if ((fin = fopen(argv[1], "r")) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		/*DPRINT("\n>>> Event: %s", buff);*/

		switch(buff[0]) {
			/* Add location
			 * L <lid> */
			case 'L': {
				int lid;
				sscanf(buff, "%c %d", &event, &lid);
				DPRINT("%c %d\n", event, lid);


				if (add_location(lid)) {
					DPRINT("L %d succeeded\n", lid);
				} else {
					fprintf(stderr, "L %d failed\n", lid);
				}

				break;
			}

			/* Add POI to location
			 * P <pid> <type> <distance> <lid> */
			case 'P': {
				int pid, type, distance, lid;

				sscanf(buff, "%c %d %d %d %d", &event, &pid, &type, &distance, &lid);
				DPRINT("%c\n", event);

				if ( add_poi_to_location(pid, type, distance, lid) ) {
					DPRINT("%c %d %d %d %d succeeded\n", event, pid, type, distance, lid);
				} else {
					fprintf(stderr, "%c %d %d %d %d failed\n", event, pid, type, distance, lid);
				}

				break;
			}

			/* POI is not available
			 * A <pid> <lid> */
			case 'A': {
				int pid, lid;

				sscanf(buff, "%c %d %d", &event, &pid, &lid);
				DPRINT("%c %d %d\n", event, pid, lid);

				if ( unavailable_poi(pid, lid) ) {
					DPRINT("%c %d %d succeeded\n", event, pid, lid);
				} else {
					fprintf(stderr, "%c %d %d failed\n", event, pid, lid);
				}

				break;
			}

			/* Register user
			 * R <uid> <hotel-id> */
			case 'R': {
				int uid;

				sscanf(buff, "%c %d", &event, &uid);
				DPRINT("%c %d\n", event, uid);

				if ( register_user(uid) ) {
					DPRINT("%c %d succeeded\n", event, uid);
				} else {
					fprintf(stderr, "%c %d failed\n", event, uid);
				}

				break;
			}

			/* User interested in poi
			 * I <uid> <pid> */
			case 'I': {
				int uid, upid;

				sscanf(buff, "%c %d %d", &event, &uid, &upid);
				DPRINT("%c %d %d\n", event, uid, upid);

				if ( interesting_poi(uid, upid) ) {
					DPRINT("%c %d %d succeeded\n", event, uid, upid);
				} else {
					fprintf(stderr, "%c %d %d failed\n", event, uid, upid);
				}

				break;
			}

			/* Group users
			 * G <uid1> <uid2> <uid3> */
			case 'G': {
				int uid1, uid2, uid3;

				sscanf(buff, "%c %d %d %d", &event, &uid1, &uid2, &uid3);
				DPRINT("%c %d %d %d\n", event, uid1, uid2, uid3);

				if ( group_users(uid1, uid2, uid3) ) {
					DPRINT("%c %d %d %d succeeded\n", event, uid1, uid2, uid3);
				} else {
					fprintf(stderr, "%c %d %d %dfailed\n", event, uid1, uid2, uid3);
				}

				break;
			}

			/* Sightseeing distance
			 * B <lid> <pid1> <pid2> <pid3> */
			case 'B': {
				int lid, pid1, pid2, pid3;

				sscanf(buff, "%c %d %d %d %d\n", &event, &lid, &pid1, &pid2, &pid3);
				DPRINT("%c %d %d %d %d\n", event, lid, pid1, pid2, pid3);

				if ( sightseeing_distance(lid, pid1, pid2, pid3) ) {
					DPRINT("%c %d %d %d %d succeeded\n", event, lid, pid1, pid2, pid3);
				} else {
					fprintf(stderr, "%c %d %d %d %d failed\n", event, lid, pid1, pid2, pid3);
				}

				break;
			}

			/* Print locations
			 * X */
			case 'X': {
				sscanf(buff, "%c", &event);
				DPRINT("%c\n", event);

				if ( print_locations() ) {
					DPRINT("%c succeeded\n", event);
				} else {
					fprintf(stderr, "%c failed\n", event);
				}

				break;
			}

			/* Print users
			 * Y */
			case 'Y': {
				sscanf(buff, "%c", &event);
				DPRINT("%c\n", event);

				if ( print_users() ) {
					DPRINT("%c succeeded\n", event);
				} else {
					fprintf(stderr, "%c failed\n", event);
				}

				break;
			}

			/* Search user
			 * Z */
			case 'Z': {
				int uid;

				sscanf(buff, "%c %d", &event, &uid);
				DPRINT("%c\n", event);

				if ( search_user(uid) ) {
					DPRINT("%c %d succeeded\n", event, uid);
				} else {
					fprintf(stderr, "%c %d failed\n", event, uid);
				}

				break;
			}

			/* Comment */
			case '#':
				break;

			/* Empty line */
			case '\n':
				break;

			/* Ignore everything else */
			default:
				DPRINT("Ignoring buff: %s \n", buff);

				break;
		}
	}

	free_world();
	return (EXIT_SUCCESS);
}
