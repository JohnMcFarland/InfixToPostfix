#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <cmath>
#include <math.h>
#include <complex>

#include <stack>

#include "eval.h"
#include "eval_exception.h"

using namespace std;

bool isOperator(char c);
double evaluate(char optr, double operand1, double operand2);

double evalPostfix(string exp) {
	stack<double> evalStack;

	int pos = 0;
	while (pos < exp.length()) {
		// ------- Ignoring Whitespace
		 if (isspace(exp[pos])) {
		 	while (pos < exp.length() && isspace(exp[pos]))	
				pos++;
		}
	// ------- Operands (numbers)
	else if (isdigit(exp[pos])) {
		stringstream ss;	// Used for the conversion
		while (pos < exp.length() && isdigit(exp[pos])) {
			ss << exp[pos];	// Building up the token in the stream
			pos++;
			if(pos < exp.length() && exp[pos] == '.'){
				ss << '.';
				pos++;
			}
		}
		int num;
		ss >> num;	// Extracting the number from the stream
		evalStack.push(num);
	}
	else if (isOperator(exp[pos])) {
			char optr = exp[pos];
			if (evalStack.empty()) throw EvalException("Missing operand");
			double operand2 =  evalStack.top();
			evalStack.pop();
			if (evalStack.empty()) throw EvalException("Missing operand");
			double operand1 =  evalStack.top();
			evalStack.pop();
			evalStack.push(evaluate(optr, operand1, operand2));
			pos++;
		}
		else
			throw EvalException("Unexpected character");
	}

	double expVal = evalStack.top();
	evalStack.pop();
	if (!evalStack.empty())
		throw EvalException("Too many operands in expression " + exp);

	return expVal;
}



const string OPERATOR_STRING = "+-*/^";

bool isOperator(char c) {return OPERATOR_STRING.find(c) != string::npos;}

double evaluate(char optr, double operand1, double operand2) {
	switch (optr) {
		case '+': return operand1 + operand2;
		case '-': return operand1 - operand2;
		case '*': return operand1 * operand2;
		case '/': 
			if (operand2 == 0)
				throw EvalException("Division by 0");
			return operand1 / operand2;
		case '^': return pow(operand1, operand2);
	}
}	
