/*
	Author: John Andersen
	Date: 10/15/2014
	Description: Program to put phrases together
	Algoritham: This program will take in serveral phrases
		It will then error check them
		Insert them into the list
		Prompt the user on what they would like to do
		List all the phrases
		Combine as requested
*/
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cctype>
#include "dlist.cpp"


const unsigned int PHRASE_SIZE = 131;

/*
	Class: phrases
	Use: Stores all of the phrases and methods to:
	 add, get, modify, or combine them.
	 Also contains the handle_input method.
*/
class phrases
{
private:
	dlist phrases;
public:
	int add();
	int number();
	char* get(unsigned int phrase_num);
	bool handle_input();
	void combine();
	void list();
	void error_check(char *user_input);
	void get_line( const char *output, char *input, unsigned int input_size );
};


/*
	Class: phrases
	Method: error_check
	Use: Uppercases the first letter adds the period.
	 Essures single spacing between words.
*/
void phrases::error_check(char *user_input)
{
	while ( user_input[0] == ' ' )
	{
		for (unsigned int j = 0; j < strlen(user_input); ++j)
		{
			user_input[j] = user_input[j+1];
		}
	}

	user_input[0] = toupper(user_input[0]);

	for (unsigned int i = 1; i < strlen(user_input); ++i)
	{
		if ( user_input[i-1] == ' ' && user_input[i] == ' ' )
		{
			while ( user_input[i] == ' ' )
			{
				for (unsigned int j = i-1; j < strlen(user_input); ++j)
				{
					user_input[j] = user_input[j+1];
				}
			}
			--i;
		}
	}
	user_input[strlen(user_input)] = '.';
	user_input[strlen(user_input)+1] = '\0';
}

void phrases::get_line( const char *output, char *input, unsigned int input_size )
{
	bool redo = false;
	do
	{
		if ( redo )
		{
			std::cout << "Sorry that was more than " << input_size-1 << " characters.\n";
		}
		std::cout << output;
		if ( (char)std::cin.peek() == '\n' )
		{
			std::cin.ignore(1);
			redo = true;
		}
		std::cin.get( input, input_size, '\n' );
		if ( (char)std::cin.peek() != '\n' )
		{
			std::cin.ignore(input_size,'\n');
			for ( unsigned int i = 0; i < input_size; ++i )
			{
				input[i] = 0;
			}
			redo = true;
		}
		else
		{
			redo = false;
		}
	}
	while ( redo );
	redo = false;
	std::cin.ignore(input_size,'\n');
	return;
}

/*
	Class: phrases
	Method: add
	Use: Prompts the user for a phrase.
	 Returns the index of the added phrase.
*/
int phrases::add()
{
	char user_input[PHRASE_SIZE] = "";
	char ask[PHRASE_SIZE];
	sprintf(ask, "What's the phrase? ( %d Character Maximum ) \n# ", PHRASE_SIZE-1 );
	this->get_line( ask, user_input, PHRASE_SIZE );
	this->error_check(user_input);
	phrase *add=(phrase *) malloc(sizeof(phrase));
	add->make( user_input );
	add->val = phrases.size();
	this->phrases.insert( add );
	return this->phrases.size()-1;
}


/*
	Class: phrases
	Method: number
	Use: Returns the size of the private vector "phrases"
*/
int phrases::number()
{
	return this->phrases.size();
}


/*
	Class: phrases
	Method: Combine
	Use: Prompts user for the numbers of phrases they wish to combine.
	 Prints the combined phrases.
*/
void phrases::combine()
{
	char user_input[PHRASE_SIZE];
	this->get_line( "What's phrases are we combining? ( 1,2,3 or 3,2,5 etc ) \n# ", user_input, PHRASE_SIZE );
	std::cout << '\n';
	for (unsigned int i = 0; i < strlen(user_input); ++i)
	{
		if ( 0 < user_input[i]-'0' )
		{
			int phrase_number = 0;
			if ( 0 < user_input[i+1]-'0' )
			{
				char not_single_didget[10] = "";
				for (int digits = 0; i < strlen(user_input) && 0 <= user_input[i]-'0' ; ++i)
				{
					not_single_didget[digits] = user_input[i];
					++digits;
				}
				phrase_number = atoi(not_single_didget);
			}
			else
			{
				phrase_number = (int)(user_input[i]-'0');
			}
			if ( this->get( phrase_number-1 ) != NULL )
			{
				std::cout << this->get( phrase_number-1 ) << ' ';
			}
		}
	}
	std::cout << "\n\n";
}


/*
	Class: phrases
	Method: list
	Use: Lists all the phrases in the private vector "phrases"
*/
void phrases::list()
{
	for (int i = 0; i < this->number(); ++i)
	{
		std::cout << i+1 << "\t:\t" << this->get( i ) << '\n';
	}
}


/*
	Class: phrases
	Method: get
	Use: Returns the text of a phrase given the index
*/
char* phrases::get( unsigned int phrase_num)
{
	if ( this->phrases.size() > phrase_num )
	{
		return this->phrases[ phrase_num ]->get();
	}
	return NULL;
}


/*
	Class: phrases
	Method: handle_input
	Use: Prompts the user for what they want to do.
	Calls the appropriate method.
	 Returns false if the user wants to exit.
*/
bool phrases::handle_input()
{
	char user_input[PHRASE_SIZE];
	// What the user input
	this->get_line("What would you like to do to your phrases? ( list, add, combine, exit )\n# ", user_input, PHRASE_SIZE);
	if ( strcmp( user_input, "exit" ) == 0 )
	{
		return false;
	}
	else if ( strcmp( user_input, "list" ) == 0 )
	{
		this->list();
	}
	else if ( strcmp( user_input, "add" ) == 0 )
	{
		this->add();
	}
	else if ( strcmp( user_input, "combine" ) == 0 )
	{
		this->combine();
	}
	return true;
}


int main(int argc, char const *argv[])
{
	phrases all_phrases;
	while ( all_phrases.handle_input() )
	{
		// Loop while input is not exit
	}
	std::cout << "Bye\n";
	return 0;
}


