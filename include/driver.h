/*
 * Manager of available drivers.
 * 
 * 
 * Copyright (C) 2018 by Peter Drozda
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef DRIVER_H
#define DRIVER_H

#define MAX_DRIVERS 10

typedef struct driver {
    int id;
    char name[10];
	char description[100];    
    int(*init)();
    void (*deinit)();
    int (*transmit)(int);
} drivert;

/* declarations of available drivers*/
#define DRIVERS \
		DECL(rpiook) \
		DECL(dummy)


#define DECL(name) extern drivert name;
	DRIVERS
#undef DECL

/**
 * Returns driver with id passed as parameter
 * 
 * @param id identifier of the required driver
*/

drivert* getDriverById(int id);

/**
 * Returns driver with name passed as parameter
 * 
 * @param name string name of the required driver
*/
drivert* getDriverByName(char* name);

/**
 * Returns all available drivers
*/
drivert** getDrivers();

/**
 * Returns number of available drivers
*/
int getDriverCount();

#endif
