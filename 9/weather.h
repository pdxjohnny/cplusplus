/*
	Author: John Andersen
	Date: 11/4/2014
	Description: weather class
*/

#include <cstdio>
#include <fstream>


#ifndef GENERAL_INCLUDED
	#include "general.h"
#endif

#ifdef ARRAY
	#pragma message "Compiling using array.h"
	#include "array.h"
#endif
#ifdef LIST
	#pragma message "Compiling using dlist.h"
	#include "dlist.h"
#endif

#include "forecast.h"

/*
	Class: weather
	Use: Stores all of the forecasts and
		methods for accessing, creating
		and deleting them
*/
class weather
{
public:
	// Propmts and adds a forecast the the array
	unsigned int add( void );
	// Removes a forecast
	void remove( void );
	// Lists all of the forecasts
	void list( char * source );
	// Saves all forecasts to a file
	bool save( char * file_name );
	// Parses a csv string into forecasts
	bool load( char * file_name );
private:
	// The dynamicly alocated array of forecasts
	#ifdef ARRAY
		array< forecast > forecasts;
	#endif
	#ifdef LIST
		dlist< forecast > forecasts;
	#endif
};
