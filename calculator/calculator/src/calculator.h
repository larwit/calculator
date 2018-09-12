#pragma once

#include <string>
#include <map>
#include <stack>

#include "token.h"

using namespace std;
namespace calculator
{

	class Calculator
	{
	public:
		Calculator();
		~Calculator();

		// parses the input and calculates the result
		// input may contain (infix) equations formed out of single digit numbers, round brackets
		// and these operators: + - * / ( ) 
		int Calculate(string input);

	protected:
		// generates a postfix notation of the input and stores it into tokentree_
		bool Parse(string &input);

		// uses the parser result to actually calculate the equation
		int Evaluate();

		// holds the result of the parsing, i.e. all 
		// parsed token in postfix order
		token::IToken::TPostfix_tokens tokentree_;

		//////////////////////////////////////////////////////////
		// helpers for the parsing process		

		// frees any allocated data
		void FreeParserData();

		void HandleSingleCharacter(char current);
		void HandleOpeningBracket();

		// a map of supported operators for easy lookup
		std::map<char, token::TokenOperator*> operators_;

		// to check if operands and operators are in correct order
		bool is_last_token_digit_ = false;

		// contains the yet unhandled operators that have to be added
		// to the tokentree_ after their operands are handled
		stack<token::TokenOperator *> operator_stack_;

		//
		//////////////////////////////////////////////////////////

	};
}