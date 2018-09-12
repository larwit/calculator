#include "calculator.h"

namespace calculator
{
	using namespace std;

	int Calculator::Calculate(string sInput) 
	{
		if (Parse(sInput))
			return Evaluate();

		throw invalid_argument("could not parse input");
	}

	bool Calculator::Parse(string & input)
	{
		for (auto t : tokentree_)
			delete t;
		tokentree_.clear();

		for (auto current : input)
		{
			if (current == ' ')
				continue;

			if (isdigit(current))
			{
				int value = stoi(string(1, current));
				tokentree_.push_back(new TokenNumber(value));
			}
			else
			{
				throw invalid_argument("invalid character detected");
			}
		}

		return true;
	}

	int Calculator::Evaluate()
	{
		if (!tokentree_.empty())
		{
			IToken *token = tokentree_.back();
			tokentree_.pop_back();
			int result = token->Evaluate();
			delete token;
			return result;
		}
		return 0;
	}

}