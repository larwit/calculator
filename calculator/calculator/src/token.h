#pragma once

#include <list>
using namespace std;

namespace token
{
	class IToken
	{
	public:
		// stores the parsed token tree in postfix order 
		// that can be taken out of the list from the back
		typedef list<IToken*> TPostfix_tokens;

		// each token type takes its needed operands from the back of
		// remaining_tokens and calculates the actual value
		virtual int Evaluate(TPostfix_tokens &remaining_tokens) = 0;
	};

	class TokenNumber : public IToken
	{
	public:
		TokenNumber() : value_(0) {};
		TokenNumber(int value) : value_(value) {};

		// numbers don't have additional operands, just return the value_
		virtual int Evaluate(TPostfix_tokens &remaining_tokens) override { return value_; }
	protected:
		int value_;
	};

	class TokenOperator : public IToken
	{
	public:
		enum TokenType {
			kPlus,
			kMinus,
			kMultiply,
			kDivide,
			kBracketsOpen,
			kBracketsClose
		};

		TokenOperator() :type_(kPlus), precedence_(0) {};
		TokenOperator(TokenOperator &other) : type_(other.type_), precedence_(other.precedence_) {};

		// operators always remove two operands from the back
		virtual int Evaluate(TPostfix_tokens &remaining_tokens) override;

		TokenType GetTokenType() { return type_; }
		int GetPrecedence() { return precedence_; }

	protected:
		TokenType type_;
		int precedence_;
	};

	class TokenOperatorPlus : public TokenOperator
	{
	public:
		TokenOperatorPlus() { type_ = kPlus; precedence_ = 1; };
	};
	class TokenOperatorMinus : public TokenOperator
	{
	public:
		TokenOperatorMinus() { type_ = kMinus; precedence_ = 1; };
	};
	class TokenOperatorMultiply : public TokenOperator
	{
	public:
		TokenOperatorMultiply() { type_ = kMultiply; precedence_ = 2; };
	};
	class TokenOperatorDivide : public TokenOperator
	{
	public:
		TokenOperatorDivide() { type_ = kDivide; precedence_ = 2; };
	};

	class TokenBracketsOpen : public TokenOperator
	{
	public:
		TokenBracketsOpen() { type_ = kBracketsOpen; precedence_ = 0; };
	};

	class TokenBracketsClose : public TokenOperator
	{
	public:
		TokenBracketsClose() { type_ = kBracketsClose; precedence_ = 0; };
	};

}