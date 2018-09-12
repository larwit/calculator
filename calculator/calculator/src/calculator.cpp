#include "calculator.h"
#include <stack>

namespace calculator
{
	using namespace std;
	using namespace token;

	Calculator::Calculator()
	{
		operators_['+'] = new TokenOperatorPlus();
		operators_['-'] = new TokenOperatorMinus();
		operators_['*'] = new TokenOperatorMultiply();
		operators_['/'] = new TokenOperatorDivide();
	}

	Calculator::~Calculator()
	{
		for (auto p : operators_)
			delete p.second;
		operators_.clear();
	}

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

		// contains the yet unhandled operators that have to be added
		// to the tokentree_ after their operands are handled
		stack<TokenOperator *> operator_stack;

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
				auto op = operators_.find(current);
				if (op == operators_.end())
					throw invalid_argument("invalid character detected (neither number nor operator)");

				// make sure that new operator has highest precedence
				while (!operator_stack.empty() && operator_stack.top()->GetPrecedence() >= op->second->GetPrecedence())
				{
					tokentree_.push_back(operator_stack.top());
					operator_stack.pop();
				}

				// put the operator on our "todo list"
				operator_stack.push(new TokenOperator(*op->second));
			}
		}

		// now we can move all unhandled operators to the postfix tree
		while (!operator_stack.empty())
		{
			auto top_operator = operator_stack.top();

			tokentree_.push_back(top_operator);
			operator_stack.pop();
		}

		return true;
	}

	int Calculator::Evaluate()
	{
		if (!tokentree_.empty())
		{
			IToken *token = tokentree_.back();
			tokentree_.pop_back();
			int result = token->Evaluate(tokentree_);
			delete token;
			return result;
		}
		return 0;
	}

}