#ifndef EVAL_EXCEPTION_H
#define EVAL_EXCEPTION_H

#include <string>

class EvalException {
public:
	EvalException(std::string message) : message(message) {}
	std::string getMessage() {return "*** EvalException: " + message;}
private:
	std::string message;
};

#endif
