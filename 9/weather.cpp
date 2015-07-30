/*
	Author: John Andersen
	Date: 11/4/2014
	Description: weather class methods
*/


// For the weather class
#include "weather.h"


/*
	Class: weather
	Method: add
	Use: Prompts the user for a forecast.
		Returns the index of the added forecast.
*/
unsigned int weather::add( void )
{
	// Allocate memory for and create a pointer to the new forecast
	forecast * forecast_to_add = new forecast;
	// Populate the forecast values fromt the string
	forecast_to_add->prompt();
	// Insert the forecast into the list of forecasts
	this->forecasts.insert( forecast_to_add );
	// Reteurn the index of the last element in the forecasts list
	return this->forecasts.size()-1;
}


/*
	Class: weather
	Method: remove
	Use: Removes the forecast given
*/
void weather::remove( void )
{
	// Create the int to tell us what to delete
	unsigned int delete_this;
	// Ask which forecast to delete
	std::cout << "Which forecast should we delete?# ";
	// Get the number forecast they wantto delete
	std::cin >> delete_this;
	// Remove the index of the number
	// the user thinks 0 is really 1
	this->forecasts.remove( delete_this-1 );
	return;
}


/*
	Class: weather
	Method: list
	Use: Lists all the forecasts for the weather
*/
void weather::list( char * source )
{
	// Uppercase the source because everything else is
	gen::toupper( source );
	// Tell the user how many forecasts they have
	std::cout << "You have " << this->forecasts.size() << " total.\n";
	// Loop through all the forecasts
	for ( unsigned int i = 0; i < this->forecasts.size(); ++i )
	{
		if ( strlen(source) == 0 || 0 == strcmp( source, this->forecasts[i].weather() ) )
		{
			// This returns a new char array
			char * line = this->forecasts[i].print();
			std::cout << line;
			// We created a new char aarry so we have to delete it
			delete [] line;
		}
	}
	return;
}

/*
	Class: weather
	Method: save
	Use: Saves the forecasts in a csv file
*/
bool weather::save( char * file_name )
{
	// The output file object
	std::ofstream save_file;
	// The return code, false if it can't open a file
	bool return_code = false;
	save_file.open( file_name );
	// If the file is open then write
	if ( save_file.is_open() )
	{
		// Then loop through the forecasts list
		save_file << "Source,Name,Rating,High,Low,Precipitation\n";
		for ( unsigned int i = 0; i < this->forecasts.size(); ++i )
		{
			// Save returns a new char array
			char * line = this->forecasts[i].save();
			save_file << line;
			// Delete the new array that was malloc'd
			delete [] line;
		}
		// Echo where we saved to
		std::cout << "Saved to " << file_name << '\n';
		// A file was opened set the return code to true
		return_code = true;
	}
	// Close the currently open file
	save_file.close();
	// Return whether a file was opened or not
	return return_code;
}


/*
	Class: weather
	Method: load
	Use: Loads the forecasts from a csv file
*/
bool weather::load( char * file_name )
{
	// A file input object
	std::ifstream load_file;
	// The size of the current_line array which is read in
	int current_line_size = gen::STRING_SIZE * 2;
	// The current_line array for reading in the file
	char current_line[current_line_size];
	// The return code, false if it can't open a file
	bool return_code = false;
	// Loop twice to use both the file endings
	load_file.open( file_name );
	// If the file is open then read
	if ( load_file.is_open() )
	{
		// Get the first line, it contains the column headers
		// Get a line and store it in the current_line array
		load_file.get( current_line, current_line_size, '\n' );
		// Read in and ignore the newline
		load_file.ignore( current_line_size, '\n' );
		// Then loop until the end of file
		while ( !load_file.eof() )
		{
			// Get a line and store it in the current_line array
			load_file.get( current_line, current_line_size, '\n' );
			// Read in and ignore the newline
			load_file.ignore( current_line_size, '\n' );
			// If the string length of the line is less than 1
			// then it is the last line so break. We don't want
			// to make an empty forecast
			if ( strlen( current_line ) < 1 )
			{
				break;
			}
			else
			{
				// Create a new forecast
				forecast * forecast_to_add = new forecast;
				// Populate the members from the line
				forecast_to_add->from_string( current_line );
				// Insert the forecast
				this->forecasts.insert( forecast_to_add );
			}
		}
		// A file was opened to return true
		return_code = true;
	}
	// Close the currently open file
	load_file.close();
	// Return whether a file was opened
	return return_code;
}
