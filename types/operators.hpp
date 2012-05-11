/*
 * operators.hpp
 *
 *  Created on: Sep 11, 2010
 *      Author: loki
 */

#ifndef OPERATORS_HPP_
#define OPERATORS_HPP_

#include <string>

enum UnaryOp {
  UnaryPlus,
  UnaryMinus
};

enum BinaryOp {
  BinaryAdd,
  BinarySub,
  BinaryMul,
  BinaryDiv
};

UnaryOp unaryOpFromString(std::string const& opStr);
BinaryOp binaryOpFromString(std::string const& opStr);
std::string unaryOpToString(UnaryOp op);
std::string binaryOpToString(BinaryOp op);

#endif /* OPERATORS_HPP_ */
