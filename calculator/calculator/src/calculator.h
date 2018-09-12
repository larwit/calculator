#pragma once

#include <string>

#include "token.h"

using namespace std;
namespace calculator
{

	class Calculator
	{
	public:
		int Calculate(string sInput);

	protected:
		bool Parse(string &input);
		int Evaluate();

		IToken::TPostfix_tokens tokentree_;
	};
}