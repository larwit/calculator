#pragma once

#include <string>
#include <map>

#include "token.h"

using namespace std;
namespace calculator
{

	class Calculator
	{
	public:
		Calculator();
		~Calculator();

		int Calculate(string sInput);

	protected:
		bool Parse(string &input);
		int Evaluate();

		// holds all the parsed token in postfix order
		token::IToken::TPostfix_tokens tokentree_;

		// a map of supported operators for easy lookup
		std::map<char, token::TokenOperator*> operators_;

	};
}