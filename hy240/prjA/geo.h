/********************************************************//**
 * @file   geo.h                                      		*
 * @author Antonis Papaioannou <papaioan@csd.uoc.gr>  		*
 *                                                    		*
 * @brief Header file for the needs of cs-240b project 2017 *
 ***********************************************************/

#ifndef GEO_H_
#define GEO_H_

struct location {
	int lid;
	struct poi *poi_list;
	struct location *next;
};

struct poi {
	int pid;
	int distance;
	int type;
	struct poi *next;
	struct poi *prev;
};

struct user {
	int uid;
	struct user_poi *interesting_poi;
	struct user *next;
};

struct user_poi {
	int upid;
	struct user_poi *next;
};

/* global variable, pointer to the beginning of the locations list*/
struct location *locations_list;

/* global variable, pointer to the beginning of the users list*/
struct user *users_list;

/* global variable, pointer to the sentinel node of the users list */
struct user *users_sentinel;

typedef struct location loc_t;
typedef struct poi poi_t;
typedef struct user usr_t;
typedef struct user_poi pusr_t;

#endif /* GEO_H_ */

