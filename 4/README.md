Oscars Voting System

This lets you vote for people who played in different movies and want to get awards.

Argument 1:	File
You always have to provide the filename as the first argument so it knows where to load from and save to. With just this argument the program will list all the nominations in alphabetical order.

Argument 2:	Search
Type a string, make sure to escape spaces, and the program will list all the matches found.
You can sreach for movie titles, actor names, or category titles.

Argument 3:	Action
Either set, add, or remove. Set and add both require the number argument. Remove will remove the nominations found in the search from the file.

Argument 4:	Number
The number to set the votes of all the nominations found to. Or the number of vote to add to a nomination. To subtract votes add a negative number.


Build
To build you have two options:
make
g++ main.cpp gen.cpp vote.cpp

