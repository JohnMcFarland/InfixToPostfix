#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

#include "infix_to_postfix.h"
#include "eval.h"
#include "eval_exception.h"

using namespace std;

int main() {
	//Declares the infix and postfix variables. 
	//Prompts the user for input
	//Lets the user input an infix expression
	//Outputs the infix expession
	string infix, postfixExp = " ";
	cout << "Enter an infix expression: "<<endl;
	getline(cin, infix);
	cout << "Infix is: "<< infix << endl;


	//Tries to convert the infix expression to a postfix expression
	//If the Expression can't be converted, it throws an exception
	try{
		postfixExp = infixToPostfix(infix);
	}catch (EvalException e) {
		cerr << e.getMessage() <<endl;
	}

	//Prints the postfix expression
	cout << "Postfix is " << postfixExp << endl;

	//Tries to evaluate the new postfix expression
	//If the expression fails to evaluate, it throws an exception.
	try {
		cout << "Evaluation is: " << evalPostfix(postfixExp) << endl;
	} catch (EvalException e) {
			cerr << e.getMessage() << endl;
	}
}
