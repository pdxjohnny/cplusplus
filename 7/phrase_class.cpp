/*
	Author: John Andersen
	Date: 10/15/2014
	Description: Phrase class
*/

/*
		Class: phrase
		Use: Essentially a string wrapper.
		 Also has pointers for use in linked list
*/
class phrase
{
private:
	char value[131];
	// Stores the text of the phrase
public:
	int val;
	struct phrase *next;
	struct phrase *prev;
	phrase(const char *new_phrase)
	{
		strcpy(this->value, new_phrase);
	};
	char* get();
	void make(const char *new_phrase);
};


/*
		Class: phrase
		Method: get
		Use: Returns the value of the private char* "value"
*/
char* phrase::get()
{
	return this->value;
}


/*
		Class: phrase
		Method: make
		Use: Makes the value of the private char* "value" into "new_phrase"
*/
void phrase::make(const char *new_phrase)
{
	strcpy(this->value, new_phrase);
};