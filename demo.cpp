#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

#include "infix_to_postfix.h"
#include "eval.h"
#include "eval_exception.h"

using namespace std;

int main() {
	string infix, postfixExp = " ";
	cout << "Enter an infix expression: "<<endl;
	getline(cin, infix);
	cout << "Infix is: "<< infix << endl;

	try{
		postfixExp = infixToPostfix(infix);
	}catch (EvalException e) {
		cerr << e.getMessage() <<endl;
	}

	cout << "Postfix is " << postfixExp << endl;

	try {
		cout << "Evaluation is: " << evalPostfix(postfixExp) << endl;
	} catch (EvalException e) {
			cerr << e.getMessage() << endl;
	}
	return 0;
}
