/* Main algorithms used to change an infix expression to
a postfix expression. Uses the shuntyard algorithm to create
an output queue in reverse polish notation which can then
be solved by the accompanying RPN eval function */

#pragma once

#ifndef SHUNTYARD_H
#define SHUNTYARD_H
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <math.h>
#include <memory>
#include "operations.hpp"

namespace shuntYard
{
    const std::array<const char, 5> OPERATORS{
        '*',
        '/',
        '+',
        '-',
        '^',
    };
    const std::array<const char, 10> NUMBERS{
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
    };

    class Token
    {
    private:
        std::string value;
        char tokenType;
        int precedence;
        long double numValue = 0;

    public:
        Token(std::string);

        void setTokenType()
        {
            for (int i = 0; i < OPERATORS.size(); i++)
            {
                for (int j = 0; j < value.size(); j++)
                {
                    if (value.at(j) == OPERATORS[i] && value.size() == 1)
                    {
                        tokenType = 'o'; // o for operator
                        setPrecedence();
                        return;
                    }
                    else if (value.at(j) == '(' || value.at(j) == ')')
                    {
                        tokenType = 'p'; // p for parenthesis
                        precedence = 0;
                        return;
                    }

                    else
                    {
                        precedence = 0;
                        tokenType = 'n'; // n for number
                    }
                }
            }
        }

        void setPrecedence()
        {
            if (value == "^")
            {
                precedence = 3;
            }
            else if (value == "*" || value == "/")
            {
                precedence = 2;
            }
            else
            {
                precedence = 1;
            }
        }

        void setNumValue(long double& inValue) { numValue = inValue; }

        void setValue(std::string& inValue) { value = inValue; }

        const int& getPrecedence() { return precedence; }

        std::string& getValue() { return value; }

        const char& getType() { return tokenType; }

        const long double& getNValue() { return numValue; }
    };

    Token::Token(std::string v)
    {
        value = v;
        setTokenType();
    }

    class Yard
    {
    private:
        std::string inExpr;
        int numOfNums;
        int numOfOps;
        std::vector<std::shared_ptr<Token>> tokenList;
        std::vector<std::shared_ptr<Token>> opStack;
        std::vector<std::shared_ptr<Token>> outQueue;

        void tokenize() // Converts the input expression string to a vector of tokens
        {
            for (int i = 0; i < inExpr.size(); i++)
            {
                // Check if token is ( or )
                if (inExpr.at(i) == '(' || inExpr.at(i) == ')')
                {
                    std::shared_ptr<Token> token(new Token(inExpr.substr(i, 1)));
                    tokenList.push_back(token);
                }
                // Check if token is a negative operand
                else if ((inExpr.at(i) == '-' && i == 0) ||
                    (inExpr.at(i) == '-' &&
                        std::find(OPERATORS.begin(), OPERATORS.end(), inExpr.at(i - 1)) != std::end(OPERATORS)))
                {
                    for (int j = i; j < inExpr.size(); j++)
                    {
                        if (j == inExpr.size() - 1)
                        {
                            std::shared_ptr<Token> token(new Token(inExpr.substr(i, inExpr.size() - i)));
                            tokenList.push_back(token);
                            i = j;
                            break;
                        }
                        else if (std::find(OPERATORS.begin(), OPERATORS.end(), inExpr.at(j + 1)) != std::end(OPERATORS) || 
                            inExpr.at(j + 1) == '(' || inExpr.at(j + 1) == ')')
                        {
                            std::shared_ptr<Token> token(new Token(inExpr.substr(i, j - i + 1)));
                            tokenList.push_back(token);
                            i = j;
                            break;
                        }
                    }
                }
                // Check if token is a operator
                else if (std::find(OPERATORS.begin(), OPERATORS.end(), inExpr.at(i)) != std::end(OPERATORS))
                {
                    std::shared_ptr<Token> token(new Token(inExpr.substr(i, 1)));
                    tokenList.push_back(token);
                }
                // Otherwise token is an operand
                else
                {
                    for (int j = i; j < inExpr.size(); j++)
                    {
                        if (std::find(OPERATORS.begin(), OPERATORS.end(), inExpr.at(j)) != std::end(OPERATORS) ||
                            inExpr.at(j) == '(' || inExpr.at(j) == ')')
                        {
                            std::shared_ptr<Token> token(new Token(inExpr.substr(i, j - i)));
                            tokenList.push_back(token);
                            i = j - 1;
                            break;
                        }
                        // Handles operand at end of string
                        else if (j == inExpr.size() - 1 && inExpr.at(j - 1) != ')')
                        {
                            std::shared_ptr<Token> token(new Token(inExpr.substr(i, inExpr.size() - i)));
                            tokenList.push_back(token);
                            i = j;
                            break;
                        }
                    }
                }
            }
        }

        void toNumbers()
        {
            // For every 'n' type token place a numValue on token
            for (std::shared_ptr<Token>& token : tokenList)
            {
                if (token->getType() == 'n')
                {
                    long double inValue = std::stold(token->getValue());
                    token->setNumValue(inValue);
                }
            }
        }

        void shunt()
        {
            // While there are tokens to be read
            for (std::shared_ptr<Token>& token : tokenList)
            {
                // Read a token
                // If it's a number add it to queue
                if (token->getType() == 'n')
                {
                    outQueue.push_back(token);
                    numOfNums += 1; // Used later for validation
                }
                // If it's an operator
                else if (token->getType() == 'o')
                {
                    numOfOps += 1; // Used later for validation
                    // While there's an operator on the top of the stack with greater or equal precedence
                    while (!opStack.empty() && opStack.back()->getPrecedence() >= token->getPrecedence())
                    {
                        // Pop operators from the stack onto the output queue
                        outQueue.push_back(opStack.back());
                        opStack.pop_back();
                    }

                    // Push the current operator onto the stack
                    opStack.push_back(token);
                }
                // If it's a left bracket push it onto the stack
                else if (token->getType() == 'p' && token->getValue() == "(")
                {
                    opStack.push_back(token);
                }
                // If it's a right bracket
                else if (token->getType() == 'p' && token->getValue() == ")")
                {
                    // While there's not a left bracket at the top of the stack
                    while (!opStack.empty() && opStack.back()->getValue() != "(")
                    {
                        // Pop operators from the stack onto the output queue
                        outQueue.push_back(opStack.back());
                        opStack.pop_back();
                    }

                    // Pop the left bracket from the stack and discard it
                    if (!opStack.empty()) 
                    {
                        opStack.pop_back();
                    }
                    
                }
            }
            // While there are operators on the stack, pop them to the queue
            for (std::vector<std::shared_ptr<Token>>::reverse_iterator ri = opStack.rbegin(); ri < opStack.rend(); ri++)
            {
                outQueue.push_back(*ri);
            }
            // Expression has been shunted to RPN, clear other token vectors
            tokenList.clear();
            opStack.clear();
            
        }

        

    public:
        Yard(std::string);
        ~Yard();

        bool validateShunt()
        {
            if (numOfOps != numOfNums - 1) {
                return false;
            }

            for (int i = 0; i < outQueue.size(); i++)
            {
                if (outQueue.at(i)->getType() == 'p') {
                    return false;
                }
            }

            return true;

        }

        std::vector<std::shared_ptr<Token>>& getOutQueue() { return outQueue; }
    };

    Yard::Yard(std::string expr)
    {
        inExpr = expr;
        numOfNums = 0;
        numOfOps = 0;
        // Reserve space -> attempt to avoid bad alloc
        tokenList.reserve(inExpr.size());
        opStack.reserve(inExpr.size());
        outQueue.reserve(inExpr.size());
        tokenize();
        toNumbers();
        shunt();
    }

    Yard::~Yard()
    {
    }

    /* Evaluates Yard objects output queue which is a product of the
    shunting yard algorithm, evaluates via Reverse Polish Notation */
    std::string RPNEval(std::vector<std::shared_ptr<Token>>& outQueue)
    {

        // While the output queue size is > 1
        while (outQueue.size() > 1)
        {

            std::vector<std::shared_ptr<Token>>::iterator qIter = outQueue.begin();
            // Look for first operator in queue
            for (int i = 0; i < outQueue.size(); i++)
            {
                if (outQueue.at(i)->getType() == 'o')
                {
                    // Complete that operation on the two prior operands
                    std::string opValue = outQueue.at(i)->getValue();
                    std::shared_ptr<Token>& aToken = outQueue.at(i - 2);
                    std::shared_ptr<Token>& bToken = outQueue.at(i - 1);
                    long double nResult = 0;
                    std::string sResult = "";
                    if (opValue == "^")
                    {
                        nResult = pow(aToken->getNValue(), bToken->getNValue());
                        sResult = std::to_string(nResult);
                    }
                    else if (opValue == "*")
                    {
                        nResult = aToken->getNValue() * bToken->getNValue();
                        sResult = std::to_string(nResult);
                    }
                    else if (opValue == "/")
                    {
                        nResult = aToken->getNValue() / bToken->getNValue();
                        sResult = std::to_string(nResult);
                    }
                    else if (opValue == "+")
                    {
                        nResult = aToken->getNValue() + bToken->getNValue();
                        sResult = std::to_string(nResult);
                    }
                    else if (opValue == "-")
                    {
                        nResult = aToken->getNValue() - bToken->getNValue();
                        sResult = std::to_string(nResult);
                    }
                    // Remove the operator from the queue
                    qIter = outQueue.erase(qIter);

                    // Replace the front value with the result, remove the second value
                    aToken->setValue(sResult);
                    aToken->setNumValue(nResult);
                    qIter = outQueue.erase(qIter - 1);
                    qIter -= 1;
                    i -= 2;
                }
                qIter++;
            }
        }

        // The remaining token = the result
        std::string result = outQueue.front()->getValue();

        return result;
    }

} // namespace shuntYard

#endif // SHUNTYARD_H