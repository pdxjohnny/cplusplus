/*
	Author: John Andersen
	Date: 10/14/2014
	Description: Program to track the fitness goals of a user.
*/
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
	goal
	A goal holds its name, target value, and current value.
*/
class goal
{
	public:
		char name[40];
		// The name of a goal
		float target_float_val;
		// The target value of the goal
		float float_val;
		// The current progress towards the target
};


/*
	person
	The person class holds the username and goals of the user.
*/
class person
{
	public:
		char username[100];
		// The persons name or username
		std::vector<goal> goals;
		// All the persons goals
		bool list_goals();
		bool add_goals();
		bool track_goals();
		bool update_goals();
		bool login();
		bool handle_input();
};


/*
	person.handle_input()
	Determines what the user want to do to their goals.
*/
bool person::handle_input()
{
	char selection[10];
	// What the user input
	do
	{
		std::cout << "What would you like to do to your goals? ( list, add, track, update, exit )" << std::endl;
		std::cin >> selection;
		if ( strcmp( selection, "exit" ) == 0 )
		{
			std::cout << "Bye" << std::endl;
			return false;
		}
		else if ( strcmp( selection, "list" ) == 0 )
		{
			this->list_goals();
		}
		else if ( strcmp( selection, "add" ) == 0 )
		{
			this->add_goals();
		}
		else if ( strcmp( selection, "track" ) == 0 )
		{
			this->track_goals();
		}
		else if ( strcmp( selection, "update" ) == 0 )
		{
			this->update_goals();
		}
	} while ( true );
	return false;
}


/*
	person.list_goals()
	Allows a user to add their goals to the system.
*/
bool person::add_goals()
{
	char user_input[40];
	// What the user input
	do
	{
		std::cout << "What is the name of your goal? ( calories, hours exercised, \'exit\' to exit to menu )" << std::endl;
		std::cin >> user_input;
		if ( strcmp( user_input, "exit" ) == 0 )
		{
			std::cout << "Goals added" << std::endl;
			return false;
		}
		goal new_goal;
		strcpy( new_goal.name, user_input);
		printf("What is the target for your %s goal per day? ( \'exit\' to exit to menu )\n", new_goal.name);
		memset(user_input, 0, sizeof user_input);
		std::cin >> user_input;
		new_goal.target_float_val = atof(user_input);
		new_goal.float_val = 0.0;
		this->goals.push_back( new_goal );
	} while ( true );
	return true;
}


/*
	person.list_goals()
	Lists a users goals with name percent complete and the total points they have earned.
*/
bool person::list_goals()
{
	if ( this->goals.size() == 0 )
	{
		printf("Sorry you need to add some goals first\n");
		return false;
	}
	unsigned int all_percent_complete = 0;
	// Holds the total of the percent progresses towards each goal
	printf("Goal name\t|Target \t|Current\t|%% Complete\t\t|\n");
	for ( unsigned int i = 0; i < this->goals.size(); ++i )
	{
		int percent_complete = (int)((this->goals[i].float_val/this->goals[i].target_float_val)*100);
		// The current progress devided by the target
		printf("%s\t|%f\t|%f\t|%d%%\t|\n", this->goals[i].name, this->goals[i].target_float_val, this->goals[i].float_val, percent_complete);
		all_percent_complete += percent_complete;
	}
	int points = (all_percent_complete/this->goals.size()*30)/100;
	// The percent compelte out of thirty instead of one hundered
	printf("You are %d%% complete and have %d points ( earn more by getting closer to your targets )\n", (int)(all_percent_complete/this->goals.size()), points );
	if ( points >= 30 )
	{
		printf("You're at 30 points for today! Here's a cupon! Go buy something healthy!");
	}
	return true;
}


/*
	person.track_goals()
	Allows a user to change the value of their current progress on a goal.
*/
bool person::track_goals()
{
	char user_input[40];
	// What the user input
	do
	{
		std::cout << "Which goal would you like to track? ( \'exit\' to exit to menu )" << std::endl;
		std::cin >> user_input;
		if ( strcmp( user_input, "exit" ) == 0 )
		{
			return false;
		}
		unsigned int goal_position;
		for ( goal_position = 0; goal_position < this->goals.size(); ++goal_position )
		{
			if ( strcmp( this->goals[goal_position].name, user_input ) == 0 )
			{
				int percent_complete = (int)((this->goals[goal_position].float_val/this->goals[goal_position].target_float_val)*100);
				// The current progress devided by the target
				printf("Goal name\t|Target \t|Current\t|%% Complete\t\t|\n");
				printf("%s\t|%f\t|%f\t|%d%%\t|\n", this->goals[goal_position].name, this->goals[goal_position].target_float_val, this->goals[goal_position].float_val, percent_complete);
				break;
			}
		}
		printf("What is your current progress on this goal?\n");
		memset(user_input, 0, sizeof user_input);
		std::cin >> user_input;
		this->goals[goal_position].float_val = atof(user_input);
	} while ( true );
	return true;
}


/*
	person.update_goals()
	Allows a user to update the target value of their goal.
*/
bool person::update_goals()
{
	char user_input[40];
	// What the user input
	do
	{
		std::cout << "Which goal would you like to update? ( \'exit\' to exit to menu )" << std::endl;
		std::cin >> user_input;
		if ( strcmp( user_input, "exit" ) == 0 )
		{
			return false;
		}
		unsigned int goal_position;
		for ( goal_position = 0; goal_position < this->goals.size(); ++goal_position )
		{
			if ( strcmp( this->goals[goal_position].name, user_input ) == 0 )
			{
				int percent_complete = (int)((this->goals[goal_position].float_val/this->goals[goal_position].target_float_val)*100);
				// The current progress devided by the target
				printf("Goal name\t|Target \t|Current\t|%% Complete\t\t|\n");
				printf("%s\t|%f\t|%f\t|%d%%\t|\n", this->goals[goal_position].name, this->goals[goal_position].target_float_val, this->goals[goal_position].float_val, percent_complete);
				break;
			}
		}
		printf("What is your new target for this goal?\n");
		memset(user_input, 0, sizeof user_input);
		std::cin >> user_input;
		this->goals[goal_position].target_float_val = atof(user_input);
	} while ( true );
	return true;
}


/*
	person.login()
	Gets the usernam and password of the user.
*/
bool person::login()
{
	std::cout << "Username: ";
	std::cin >> this->username;
	return true;
}


/*
	main
	Logs in the user and get input until the user 'exit's.
*/
int main( int argc, char *argv[] )
{
	std::cout << "Hello, this program is used to track your health and fitness.\n";
	person user;
	if ( !user.login() )
	{
		std::cout << "New user created.\n";
	}
	std::cout << "Welcome " << user.username << std::endl;
	while ( user.handle_input() )
	{
		// Continue to call handle_input until it returns false when the user types exit
	}
	return 0;
}
