#pragma once

#include <list>
using namespace std;

class IToken
{
public:
	// stores the parsed token tree in postfix order 
	// that can be taken out of the list from the back
	typedef list<IToken*> TPostfix_tokens;

	virtual int Evaluate() = 0;
};

class TokenNumber : public IToken
{
public:
	TokenNumber() : value_(0) {};
	TokenNumber(int value) : value_(value) {};

	virtual int Evaluate() override { return value_; }
protected:
	int value_;
};