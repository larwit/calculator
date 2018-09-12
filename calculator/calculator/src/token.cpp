#include "token.h"
namespace token
{

	int TokenOperator::Evaluate(TPostfix_tokens &remaining_tokens)
	{
		if (remaining_tokens.empty())
			throw invalid_argument("invalid structure");

		IToken *right_token = remaining_tokens.back();
		remaining_tokens.pop_back();
		int right_value = right_token->Evaluate(remaining_tokens);
		delete right_token;

		if (remaining_tokens.empty())
			throw invalid_argument("invalid structure");

		IToken *left_token = remaining_tokens.back();
		remaining_tokens.pop_back();
		int left_value = left_token->Evaluate(remaining_tokens);
		delete left_token;

		switch (type_)
		{
		case kPlus: return left_value + right_value;
		case kMinus: return left_value - right_value;
		case kMultiply: return left_value * right_value;
		case kDivide:
			if (right_value == 0)
				throw invalid_argument("division by zero error");
			return left_value / right_value;
		}

		return 0;
	}

}