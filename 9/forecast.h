/*
	Author: John Andersen
	Date: 11/8/2014
	Description: forecast class definition
*/

#ifndef GENERAL_INCLUDED
	#include "general.h"
#endif
#include <cstdio>
#include <fstream>


/*
	Class: forecast
	Use: Holds a forecast and the scource is it assinged to
*/
class forecast
{
public:
	// Returns the weather source
	char *weather( void );
	// Parses a csv string into data members
	void from_string( char * forecast_info );
	// Prompts user for the values of data members
	void prompt( void );
	// Creates a string of the class in json format
	char * print( void );
	// Creates a string of the class in csv format
	char * save( void );
private:
	// The weather source associated with the forecast
	char source[gen::STRING_SIZE];
	// The name of the forecast
	char name[gen::STRING_SIZE];
	// Any other information associated
	char info[gen::STRING_SIZE];
	// The rating percentage of the forecast
	int rating;
	// The high level of the forecast
	int high;
	// The low level of the forecast
	int low;
	// The precipitation chance of the forecast
	int precipitation;
};
