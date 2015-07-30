#include "cs163_graph.h"
using namespace std;

int main( int argc, char ** argv )
{
	my_table my_journal;
	journal_entry * to_add;
	char title[100], connected[100];
	char notes[300];
	
	//Let's add some items ot the journal First
	// do
	// {
	// 	cout <<"Please enter a title: ";
	// 	cin.get(title, 100); cin.ignore(100,'\n');
	// 	cout <<"Please enter the notes: ";
	// 	cin.get(notes, 300); cin.ignore(100,'\n');
	// 	to_add.create_entry(title, notes);

	// 	//now insert it into the graph
	// 	my_journal.insert_vertex(to_add);

	// } while (again());
   
	//Let's add some connections
	// do
	// {
	// 	cout <<"Enter two titles that are related (connected): ";
	// 	cin.get(title, 100); cin.ignore(100,'\n');
	// 	cin.get(connected, 100); cin.ignore(100,'\n');
	// 	my_journal.insert_edge(title, connected);
	// 	my_journal.insert_edge(connected, title); //not a directed graph
	// } while (again());
	to_add = new journal_entry;
	char First [] = "First"; char First_notes [] = "First notes";
	to_add->create_entry(First, First_notes);
	my_journal.insert_vertex(* to_add);
	delete to_add;

	to_add = new journal_entry;
	char Second [] = "Second"; char Second_notes [] = "Second notes";
	to_add->create_entry(Second, Second_notes);
	my_journal.insert_vertex(* to_add);
	delete to_add;

	to_add = new journal_entry;
	char Third [] = "Third"; char Third_notes [] = "Third notes";
	to_add->create_entry(Third, Third_notes);
	my_journal.insert_vertex(* to_add);
	delete to_add;

	to_add = new journal_entry;
	char Fourth [] = "Fourth"; char Fourth_notes [] = "Fourth notes";
	to_add->create_entry(Fourth, Fourth_notes);
	my_journal.insert_vertex(* to_add);
	delete to_add;

	// First adjacent
	my_journal.insert_edge( First, Fourth );
	my_journal.insert_edge( First, Second );
	my_journal.insert_edge( First, Third );

	// Second adjacent
	my_journal.insert_edge( Second, Fourth );
	my_journal.insert_edge( Second, First );
	my_journal.insert_edge( Second, Third );

	// Third adjacent
	my_journal.insert_edge( Third, Fourth );
	my_journal.insert_edge( Third, First );
	my_journal.insert_edge( Third, Second );

	// Fourth adjacent
	my_journal.insert_edge( Fourth, Second );
	my_journal.insert_edge( Fourth, First );
	my_journal.insert_edge( Fourth, Third );
   
	//Display direct connections (call your function)
	// cout <<"Display adjacent entrys for entry: ";
	// cin.get(title, 100); cin.ignore(100,'\n');
	my_journal.find_adjacent( argv[ 1 ] );
	std::cout << "\n";
	// my_journal.all_paths( argv[ 1 ] );
	// my_journal.display_adjacent( argv[ 1 ] );
		
	//Let's display what we have  (this function was provided for you)
	// cout <<"\n\nThis is the contents of the table:\n";
	// my_journal.display_all();
	
	
	return 0;
}
