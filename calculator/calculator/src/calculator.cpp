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
		operators_['('] = new TokenBracketsOpen();
		operators_[')'] = new TokenBracketsClose();
	}

	Calculator::~Calculator()
	{
		FreeParserData();

		for (auto p : operators_)
			delete p.second;
		operators_.clear();
	}

	int Calculator::Calculate(string input)
	{
		if (Parse(input))
			return Evaluate();

		throw invalid_argument("could not parse input");
	}

	bool Calculator::Parse(string & input)
	{
		FreeParserData();
		is_last_token_digit_ = false;


		for (auto current : input)
		{
			if (current == ' ')
				continue;

			HandleSingleCharacter(current);
		}

		// now we can move all unhandled operators to the postfix tree
		while (!operator_stack_.empty())
		{
			auto top_operator = operator_stack_.top();

			tokentree_.push_back(top_operator);
			operator_stack_.pop();
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

			if (!tokentree_.empty())
				throw invalid_argument("invalid structure");

			return result;
		}
		return 0;
	}

	void Calculator::FreeParserData()
	{
		for (auto t : tokentree_)
			delete t;
		tokentree_.clear();

		while (!operator_stack_.empty())
		{
			auto op = operator_stack_.top();
			operator_stack_.pop();
			delete op;
		}
	}

	void Calculator::HandleSingleCharacter(char current)
	{
		if (isdigit(current))
		{
			if (is_last_token_digit_)
				throw invalid_argument("only numbers with one digit allowed");
			is_last_token_digit_ = true;

			int value = stoi(string(1, current));
			tokentree_.push_back(new TokenNumber(value));
		}
		else
		{
			auto op = operators_.find(current);
			if (op == operators_.end())
				throw invalid_argument("invalid character detected (neither number nor operator)");

			// when we encounter a closing bracket there must be the matching
			// opening bracket on the operator stack
			if (op->second->GetTokenType() == TokenOperator::kBracketsClose)
			{
				HandleOpeningBracket();

				// make sure we do not push this token to operator_stack
				return;
			}
			// opening brackets we push right away to operators stack, no need to check
			// for preceedence
			else if (op->second->GetTokenType() == TokenOperator::kBracketsOpen)
			{
				if (is_last_token_digit_)
					throw invalid_argument("opening brackets must not follow directly after a number");
			}
			else
			{
				// here we have to handle "real" operators like + 

				if (!is_last_token_digit_)
					throw invalid_argument("an operator must not follow another operator");

				// a real operator invalidates a previous digit token, while opening brackets 
				is_last_token_digit_ = false;

				// make sure that new operator has highest precedence
				while (!operator_stack_.empty() && operator_stack_.top()->GetPrecedence() >= op->second->GetPrecedence())
				{
					tokentree_.push_back(operator_stack_.top());
					operator_stack_.pop();
				}
			}

			// put the operator on our "todo list"
			operator_stack_.push(new TokenOperator(*op->second));
		}
	}

	void Calculator::HandleOpeningBracket()
	{
		if (!is_last_token_digit_)
			throw invalid_argument("closing brackets must follow a number");

		// a whole expression within brackets counts as a digit
		is_last_token_digit_ = true;

		while (!operator_stack_.empty() && operator_stack_.top()->GetTokenType() != TokenOperator::kBracketsOpen)
		{
			tokentree_.push_back(operator_stack_.top());
			operator_stack_.pop();
		}
		// check if we found the opening bracket, otherwise it's a syntax error
		if (!operator_stack_.empty() && operator_stack_.top()->GetTokenType() == TokenOperator::kBracketsOpen)
		{
			delete(operator_stack_.top());
			operator_stack_.pop();
		}
		else
			throw invalid_argument("missing opening bracket");
	}
}