/*
	Author: John Andersen
	Date: 11/8/2014
	Description: forecast class methods
*/

// Include the forecast class definition
#include "forecast.h"


/*
	Class: forecast
	Method: weather
	Use: Returns the weather source
*/
char *forecast::weather( void )
{
	return this->source;
}

/*
	Class: forecast
	Method: from_string
	Use: Parses a csv string into data members
*/
void forecast::from_string( char * forecast_info )
{
	// Create srings for the numbered data types so we can parse
	// the input into seperate strings then convert to numbers
	int number_size = 5;
	char rating[number_size], high[number_size], low[number_size], precipitation[number_size];
	// The string should be in csv format so we just parse it in order
	gen::split_line( forecast_info, this->source, forecast_info, ',' );
	gen::toupper( this->source );
	gen::split_line( forecast_info, this->name, forecast_info, ',' );
	gen::toupper( this->name );
	gen::split_line( forecast_info, this->info, forecast_info, ',' );
	gen::split_line( forecast_info, rating, forecast_info, ',' );
	gen::split_line( forecast_info, high, forecast_info, ',' );
	gen::split_line( forecast_info, low, precipitation, ',' );
	// Convert the strings to intiger values
	this->rating = std::atoi( rating );
	this->high = std::atoi( high );
	this->low = std::atoi( low );
	this->precipitation = std::atoi( precipitation );
	if ( 0 > this->rating )
	{
		this->rating *= -1;
	}
	if ( 0 > this->precipitation )
	{
		this->precipitation *= -1;
	}
	return;
}


/*
	Class: forecast
	Method: prompt
	Use: Propmts user for the values of data members
*/
void forecast::prompt( void )
{
	// Four strings are needed to parse the date into
	// the day, month, and year. Also one to take the
	// whole line in
	int number_size = 5;
	char rating[number_size], high[number_size], low[number_size], precipitation[number_size];
	// Ask the user for their forecast information
	// Remove any commas so it doesn't mess up csv's
	gen::get_line( "What's the weather source(KGW)?# ", this->source, gen::STRING_SIZE );
	gen::toupper( this->source );
	gen::remove_char( this->source, ',' );
	gen::get_line( "What's the forecasts city / name?# ", this->name, gen::STRING_SIZE );
	gen::toupper( this->name );
	gen::remove_char( this->name, ',' );
	do
	{
		gen::get_line( "What's the \% reliability rating?# ", rating, number_size );
		gen::get_line( "What's the high?# ", high, number_size );
		gen::get_line( "What's the low?# ", low, number_size );
		gen::get_line( "What's the \% chance of precipitation?# ", precipitation, number_size );
	}
	while ( !gen::number(rating) || !gen::number(high) ||
			!gen::number(low) || !gen::number(precipitation) );
	gen::get_line( "Any other information?# ", this->info, gen::STRING_SIZE );
	gen::remove_char( this->info, ',' );
	// Convert the strings to intiger values
	this->rating = std::atoi( rating );
	this->high = std::atoi( high );
	this->low = std::atoi( low );
	this->precipitation = std::atoi( precipitation );
	if ( 0 > this->rating )
	{
		this->rating *= -1;
	}
	if ( 0 > this->precipitation )
	{
		this->precipitation *= -1;
	}
	return;
}


/*
	Class: forecast
	Method: print
	Use: Creates a string of the class in json format
		because its easily readable this way
*/
char *forecast::print( void )
{
	// Make the as_string array only about as long as it needs to be
	unsigned int all_lengths = strlen( this->source ) + strlen( this->name ) + gen::STRING_SIZE * 2;
	// Make a pointer and assign it to an array of proper size so it
	// can be referenced outside this function
	char *as_string = new char[all_lengths];
	// Format the string, jsons are very readable
	sprintf( as_string, "{\n\t\"Source\": \"%s\",\n\t\"Name\": \"%s\",\n\t\"Info\": \"%s\",\n\t\"Rating\": %d%%,\n\t\"High\": %d,\n\t\"Low\": %d,\n\t\"Precipitation\": %d%%\n}\n", this->source, this->name, this->info, this->rating, this->high, this->low, this->precipitation );
	return as_string;
}


/*
	Class: forecast
	Method: save
	Use: Creates a string of the class in csv format
*/
char *forecast::save( void )
{
	// Make the as_string array only about as long as it needs to be
	unsigned int all_lengths = strlen( this->source ) + strlen( this->name ) + gen::STRING_SIZE * 2;
	// Make a pointer and assign it to an array of proper size so it
	// can be referenced outside this function
	char *as_string = new char[all_lengths];
	// Format the string, csv is great for parseing in
	sprintf( as_string, "%s,%s,%s,%d,%d,%d,%d\n", this->source, this->name, this->info, this->rating, this->high, this->low, this->precipitation );
	return as_string;
}
