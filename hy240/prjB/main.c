/****************************************************************
 * @file   main.c                                      	        *
 * @author Nikolaos <batsaras@csd.uoc.gr>                       *
 *                                                              *
 * @brief Header function for the needs of cs-240b project 2017 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "geo.h"

#define BUFFER_SIZE 1024  /**< Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */


/**
* @brief Add a new location to the system
*
* @param lid The location's id
*
* @return 1 on success
*         0 on failure
*/
int add_location(int lid)
{
  return 1;
}

/**
* @brief Add point-of-interest (POI) to a location
* 
* @param pid      POI's id
* @param type     The type of the POI
* @param distance The distance of POI from the locations reference point
* @param lid      The location of the POI
*
* @return 1 on success
*         0 on failure
*/
int add_poi_to_location(int pid, int type, int distance, int lid)
{
  return 1;
}

/**
* @brief A POI is unavailable to visitors
*
* @param pid The POI's id
* @param lid The location's id
* 
* @return 1 on success
*         0 on failure
*/
int unavailable_poi(int pid, int lid)
{
  return 1;
}

/**
* @brief Register user
*
* @param uid The user's id
* 
* @return 1 on success
*         0 on failure
*/
int register_user(int uid)
{
  return 1;
}

/**
* @brief User is interested in POI
* 
* @param uid The user's id
* @param pid The POI's id
*
* @return 1 on success
*         0 on failure
*/
int interesting_poi(int uid, int pid)
{
  return 1;
}

/**
* @brief Group users
* 
* @param uid1 The id of the 1st user
* @param uid2 The id of the 2nd user
*
* @return 1 on success
*         0 on failure
*/
int group_users(int uid1, int uid2)
{
  return 1;
}

/**
* @brief Find the inorder successors from one pid the other
* 
* @param lid  The location's id
* @param pid1 A point of interest
* @param pid2 A point of interest
*
* @return 1 on success
*         0 on failure
*/
int inorder_successors(int lid, int pid1, int pid2)
{
  return 1;
}

/**
* @brief Print all locations
*
* @return 1 on success
*         0 on failure
*/
int print_locations()
{
  return 1;
}

/**
* @brief Print all users
*
* @return 1 on success
*         0 on failure
*/
int print_users()
{
  return 1;
}

/**
* @brief Search for user
* 
* @param uid The id of the user we are looking for
*
* @return 1 on success
*         0 on failure
*/
int search_user(int uid)
{
  return 1;
}

/**
* @brief Cleanup resources
* 
* @return 1 on success
*         0 on failure
*/
int free_world()
{
  return 1;
}


/**
* @brief Initialize hash parameters
* 
* @return null
*/
void initialize()
{

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


  /* Check command buff arguments */
  if ( argc != 2 ) {
    fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
    return EXIT_FAILURE;
  }

  /* Open input file */
  if (( fin = fopen(argv[1], "r") ) == NULL ) {
    fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
    perror("Opening test file\n");
    return EXIT_FAILURE;
  }

  /* Read input file buff-by-buff and handle the events */
  while ( fgets(buff, BUFFER_SIZE, fin) ) {

    DPRINT("\n>>> Event: %s", buff);

    switch(buff[0]) {

      /* Comment */
    case '#':
      break;

      /* Maximum users */
    case '0':
      {
	sscanf(buff, "%c %u", &event, &max_users_g);
	DPRINT("%c %u\n", event, max_users_g);
	break;
      }

      /* Maximum user id */
    case '1':
      {
	sscanf(buff, "%c %u", &event, &max_uid_g);
	DPRINT("%c %u\n", event, max_uid_g);
	initialize();
	break;
      }

      /* Add location
       * L <lid> */
    case 'L':
      {
	int lid;
	sscanf(buff, "%c %d", &event, &lid);
	DPRINT("%c %d\n", event, lid);


	if ( add_location(lid) ) {
	  DPRINT("L %d succeeded\n", lid);
	} else {
	  fprintf(stderr, "L %d failed\n", lid);
	}

	break;
      }

      /* Add POI to location
       * P <pid> <type> <distance> <lid> */
    case 'P':
      {
	int pid, type, distance, lid;

	sscanf(buff, "%c %d %d %d %d", &event, &pid, &type, &distance, &lid);
	DPRINT("%c\n", event);

	if ( add_poi_to_location(pid, type, distance, lid) ) {
	  DPRINT("%c %d %d %d %d succeeded\n", event, pid, type, distance, lid);
	} else {
	  fprintf(stderr,
		  "%c %d %d %d %d failed\n", event, pid, type, distance, lid);
	}

	break;
      }

      /* POI is not available
       * A <pid> <lid> */
    case 'A':
      {
	int pid;
	int lid;
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
    case 'R':
      {
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
    case 'I':
      {
	int uid, pid;
	sscanf(buff, "%c %d %d", &event, &uid, &pid);
	DPRINT("%c %d %d\n", event, uid, pid);

	if ( interesting_poi(uid, pid) ) {
	  DPRINT("%c %d %d succeeded\n", event, uid, pid);
	} else {
	  fprintf(stderr, "%c %d %d failed\n", event, uid, pid);
	}

	break;
      }

      /* Group users
       * G <uid1> <uid2> */
    case 'G':
      {
	int uid1, uid2;
	sscanf(buff, "%c %d %d", &event, &uid1, &uid2);
	DPRINT("%c %d %d\n", event, uid1, uid2);

	if ( group_users(uid1, uid2) ) {
	  DPRINT("%c %d %d succeeded\n", event, uid1, uid2);
	} else {
	  fprintf(stderr, "%c %d %d failed\n", event, uid1, uid2);
	}

	break;
      }

      /* Find inorder successors
       * B <lid> <pid1> <pid2> */
    case 'B':
      {
	int lid, pid1, pid2;
	sscanf(buff, "%c %d %d %d\n", &event, &lid, &pid1, &pid2);
	DPRINT("%c %d %d %d\n", event, lid, pid1, pid2);

	if ( inorder_successors(lid, pid1, pid2) ) {
	  DPRINT("%c %d %d %d succeeded\n", event, lid, pid1, pid2);
	} else {
	  fprintf(stderr, "%c %d %d %d failed\n", event, lid, pid1, pid2);
	}

	break;
      }

      /* Print locations
       * X */
    case 'X':
      {
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
    case 'Y':
      {
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
    case 'Z':
      {
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
