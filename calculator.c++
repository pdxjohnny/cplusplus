#include <iostream>
#include <string>
using  namespace std;

class Calculator {
	public:
		string sum, difference, product, quotient;
		float add( float a, float b ) {
			return a+b;
			}
		float subtract( float a, float b ) {
			return a-b;
			}
		float multiply( float a, float b ) {
			return a*b;
			}
		float divide( float a, float b ) {
			return a/b;
			}
	};

bool calaculate(){
	// Initialize instance of calaculator object
	Calculator clac;
	// Declare strings
	clac.sum = "The sum of your two numbers is ", 
	clac.difference = "The difference of your two numbers is ", 
	clac.product = "The product of your two numbers is ",
	clac.quotient = "The quotient of your two numbers is ";
	// Choose Operator
	char grade;
	cout << "Would you like to add, subtract, multiply, divide, or exit? (+,-,*,/,e)\n";
	cin >> grade;
   	if ( grade == 'e')
		return false;
	// Gets a,b
	float a, b;
	cout << "Enter the first number ";	cin >> a;
	cout << "Enter the second number ";	cin >> b;
   	switch(grade) {
   		case '+' :
    		cout << clac.sum << clac.add(a,b) << endl;
    		return true;
    		break;
   		case '-' :
    		cout << clac.difference << clac.subtract(a,b) << endl;
    		return true;
    		break;
   		case '*' :
    		cout << clac.product << clac.multiply(a,b) << endl;
    		return true;
    		break;
   		case '/' :
    		cout << clac.quotient << clac.divide(a,b) << endl;
    		return true;
    		break;
   		default :
    		return true;
   		}
   	}

int main() {
	while( calaculate() ){}
   	return 0;
	}