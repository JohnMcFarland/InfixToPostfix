#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

#include <stack>

#include "infix_to_postfix.h"
#include "eval_exception.h"

using namespace std;

bool isOperator(char c);
int precLevel(char optr);

//Function to convert the infix expression to a postfix expression
//I:Takes in an infix expression. 
//P:Uses a stack to reorder the characters in the expression from infix to postfix.
//O:Returns a postfix expression ready to be evaluated. 
string infixToPostfix(string infix) {
	stack<char> opStack;

	string postfix = "";

	int pos = 0;
	while (pos < infix.length()) {
		if (isspace(infix[pos])) {// Skip whitespace
			while (pos < infix.length() && isspace(infix[pos]))
				pos++;
		}       
		else if (isdigit(infix[pos])) {
			string operand;
			while (pos < infix.length() && isdigit(infix[pos])) {
				operand += infix[pos];
				pos++;
				if(pos < infix.length() && infix[pos] == '.'){
					operand += infix[pos];
					pos++;
				}
			}       
			postfix += operand + " ";
			
		}       
		else if (infix[pos] == '(') {// '(' always gets pushed
			opStack.push(infix[pos]);
			pos++;
		}
		else if (isOperator(infix[pos])) {
			char optr = infix[pos];
			// Output any higher-prec operator on stack
			while(!opStack.empty() && opStack.top() != '(' && precLevel(opStack.top()) > precLevel(optr) || !opStack.empty() && precLevel(opStack.top()) == precLevel(optr)&& isLeftAssociative(opStack.top())) {
			 	postfix += opStack.top();
			 	postfix += " ";
			 	opStack.pop();
			}
			opStack.push(optr);// push current operator
			pos++;
		}
		// Output all operators on stack until '('
		else if (infix[pos] == ')') {	
			while (!opStack.empty() && opStack.top() != '(') {
				postfix += opStack.top();
				postfix += " ";
				opStack.pop();
			}
			if (opStack.empty()) throw EvalException("Unexpected )");
			opStack.pop();
			pos++;
		}
		else
			throw EvalException("Unexpected character");
	}
	//Output any remaining operators
	while (!opStack.empty()) {
		postfix += opStack.top();
		postfix += " ";
		opStack.pop();
		cout<<"Stack pop" <<endl;
	}
	
	return postfix;
}

//Details and determines an operators precedence level
int precLevel(char optr) {
	switch (optr) {
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		case '/': return 2;
		case '^': return 3;
	}
}		

//Determines is the operand is left associative. 
bool isLeftAssociative (char optr){

	switch (optr) {
		case '+': return true;
		case '-': return true;
		case '*': return true;
		case '/': return true;
		case '^': return false;
			
	}
}
