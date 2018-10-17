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
 
#include <stdio.h>
#include <string.h>
#include "driver.h"

drivert* drivers[] = {
#define DECL(name) &name,
	DRIVERS
#undef DECL
};

int driversCount = sizeof drivers/sizeof drivers[0];

drivert* getDriverById(int id) {
	int i=0;
	
	for(i=0; i<driversCount; i++) {
		if(drivers[i]->id == id) {
			return drivers[i];
		}
	}
	
	return NULL;
}

drivert* getDriverByName(char* name) {
	int i=0;
	
	for(i=0; i<driversCount; i++) {
		if(strcmp(drivers[i]->name, name) == 0) {
			return drivers[i];
		}
	}
	
	return NULL;
}
