/* Main algorithms used to change an infix expression to
a postfix expression. Uses the shuntyard algorithm to create
an output queue in reverse polish notation which can then
be solved by the accompanying RPN eval function 
------------------------------------------------------------
No .cpp file created to provide some future portability */

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
    {// Represents part of the expression ie -> number, parenthesis, operator
    private:
        std::string value;
        char tokenType;
        int precedence;
        long double numValue = 0;

    public:
        explicit Token(const std::string&);

        void setTokenType()
        {// Sets what kind of token it is based on length and contents
            for (char op : OPERATORS)
            {
                if (value.front() == op && value.size() == 1)// check for size 1 due to negative numbers
                {
                    tokenType = 'o'; // o for operator
                    setPrecedence();
                    return;
                }
                else if (value == "(" || value == ")")
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

        void setPrecedence()
        {// Sets token precedence -> used to order a shuntyard -> higher number = higher precedence
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

        void setNumValue(const long double& inValue) { numValue = inValue; }
        void setValue(const std::string_view& inValue) { value = inValue; }
        const int& getPrecedence() const { return precedence; }
        std::string& getValue() { return value; }
        const char& getType() const { return tokenType; }
        const long double& getNValue() const { return numValue; }
    };

    Token::Token(const std::string& value) : value(value)
    {
        setTokenType();
    }

    class Yard
    { // Represents a list of tokens to be used for calculations
    private:
        std::string inExpr;
        int numOfNums = 0;
        int numOfOps = 0;
        std::vector<std::shared_ptr<Token>> tokenList;
        std::vector<std::shared_ptr<Token>> opStack;
        std::vector<std::shared_ptr<Token>> outQueue; // Final queue to be sent to RPN evaluation

        void tokenize() // Converts the input expression string to a vector of tokens
        {
            for (int i = 0; i < inExpr.size(); i++)
            {
                // Check if token is ( or )
                if (inExpr.at(i) == '(' || inExpr.at(i) == ')')
                {
                    auto token = std::make_shared<Token>(inExpr.substr(i, 1));
                    tokenList.push_back(token);
                }
                // Check if token is a negative operand, looks for a operator at i-1 also to confirm
                else if ((inExpr.at(i) == '-' && i == 0) || (inExpr.at(i) == '-' &&
                        std::find(OPERATORS.begin(), OPERATORS.end(), inExpr.at(i - 1)) != std::end(OPERATORS)))
                {
                     for (int j = i; j < inExpr.size(); j++)
                     {// Look right until end of the expression
                        if (j == inExpr.size() - 1)
                        {// If at the end make that range a token
                            auto token = std::make_shared<Token>(inExpr.substr(i, inExpr.size() - i));
                            tokenList.push_back(token);
                            i = j;
                            break;
                        }// Or we hit a parethesis or operator
                        else if (std::find(OPERATORS.begin(), OPERATORS.end(), inExpr.at(j + 1)) != std::end(OPERATORS) || 
                            inExpr.at(j + 1) == '(' || inExpr.at(j + 1) == ')')
                        {// If at a parenthesis or operator make that range a token
                            auto token = std::make_shared<Token>(inExpr.substr(i, j - i + 1));
                            tokenList.push_back(token);
                            i = j;
                            break;
                        }
                     }
                }
                // Check if token is a operator
                else if (std::find(OPERATORS.begin(), OPERATORS.end(), inExpr.at(i)) != std::end(OPERATORS))
                {
                    auto token = std::make_shared<Token>(inExpr.substr(i, 1));
                    tokenList.push_back(token);
                }
                // Otherwise token is an operand
                else
                {
                    for (int j = i; j < inExpr.size(); j++)
                    {// Go right until we hit an operator, parenthesis or end of the string and make that range a token
                        if (std::find(OPERATORS.begin(), OPERATORS.end(), inExpr.at(j)) != std::end(OPERATORS) ||
                            inExpr.at(j) == '(' || inExpr.at(j) == ')')
                        {
                            auto token = std::make_shared<Token>(inExpr.substr(i, j - i));
                            tokenList.push_back(token);
                            i = j - 1;
                            break;
                        }
                        // Handles operand at end of string
                        else if (j == inExpr.size() - 1 && inExpr.at(j - 1) != ')')
                        {
                            auto token = std::make_shared<Token>(inExpr.substr(i, inExpr.size() - i));
                            tokenList.push_back(token);
                            i = j;
                            break;
                        }
                    }
                }
            }
        }

        void toNumbers() const
        {// For every 'n' type token place a numValue on token
            for (const std::shared_ptr<Token>& token : tokenList)
            {
                if (token->getType() == 'n')
                {
                    std::string tVal = token->getValue();
                    if (tVal == "." || tVal == "-.") // In the event of a lone decimal add a 0 to it
                        tVal += "0";
                    long double inValue = std::stold(tVal);
                    token->setNumValue(inValue);
                }
            }
        }

        void shunt()
        {
            // While there are tokens to be read
            for (const std::shared_ptr<Token>& token : tokenList)
            {
                // Read a token
                // If it's a number add it to queue
                if (token->getType() == 'n')
                {
                    outQueue.push_back(token);
                    numOfNums += 1; // Used later for shunt validation
                }
                // If it's an operator
                else if (token->getType() == 'o')
                {
                    numOfOps += 1; // Used later for shunt validation
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
            for (auto ri = opStack.rbegin(); ri < opStack.rend(); ri++)
            {
                outQueue.push_back(*ri);
            }
            // Expression has been shunted to RPN, clear other token vectors
            tokenList.clear();
            opStack.clear();
            
        }

    public:
        explicit Yard(const std::string_view&);
        ~Yard();
        std::vector<std::shared_ptr<Token>>& getOutQueue() { return outQueue; }


        bool validateShunt() const
        {// Used to ensure the produced shunt is valid
            // There must be more numbers than operators in a shunt
            if (numOfOps != numOfNums - 1) {
                return false;
            }
            // If a parenthesis is still present after shunting it is not a valid shunt
            if (std::any_of(outQueue.cbegin(), outQueue.cend(), 
                [](std::shared_ptr<Token> token) { return token->getType() == 'p'; }))
            {
                return false;
            }
            // Otherwise its a valid shunt
            return true;
        }
    };

    Yard::Yard(const std::string_view &expr) : inExpr(expr)
    {
        // Reserve space -> attempt to avoid bad alloc
        tokenList.reserve(inExpr.size());
        opStack.reserve(inExpr.size());
        outQueue.reserve(inExpr.size());
        // On constuction change expression to tokens, give number tokens number values and create a shunt
        tokenize();
        toNumbers();
        shunt();
    }

    Yard::~Yard() = default;

    /* Evaluates Yard objects output queue which is a product of the
    shunting yard algorithm, evaluates via Reverse Polish Notation */
    std::string RPNEval(std::vector<std::shared_ptr<Token>>& outQueue)
    {// Could change loops to use two iterators and start from last token removed?

        // While the output queue size is > 1
        while (outQueue.size() > 1)
        {

            auto qIter = outQueue.begin();
            // Look for first operator in queue
            for (int i = 0; i < outQueue.size(); i++)
            {
                if (outQueue.at(i)->getType() == 'o')
                {
                    // Complete that operation on the two prior operands
                    std::string opValue = outQueue.at(i)->getValue();
                    const std::shared_ptr<Token>& aToken = outQueue.at(i - 2);
                    const std::shared_ptr<Token>& bToken = outQueue.at(i - 1);
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
                    // Adjust index and iterator to account for the tokens removed
                    qIter -= 1;
                    i -= 2;
                }
                // Follow for loop index with iterator
                qIter++;
            }
        }

        // The remaining token = the result
        std::string result = outQueue.front()->getValue();

        return result;
    }

} // namespace shuntYard

#endif // SHUNTYARD_H