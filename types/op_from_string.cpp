/*
 * op_from_string.cpp
 *
 *  Created on: Sep 12, 2010
 *      Author: loki
 */

#include <assert.h>
#include "operators.hpp"

UnaryOp unaryOpFromString(std::string const& opStr) {
  if(opStr == "+") {
    return UnaryPlus;
  } else if(opStr == "-") {
    return UnaryMinus;
  }

  assert(!"Can't get unary op from string");
}

BinaryOp binaryOpFromString(std::string const& opStr) {
  if(opStr == "+") {
    return BinaryAdd;
  } else if(opStr == "-") {
    return BinarySub;
  } else if(opStr == "*") {
    return BinaryMul;
  } else if(opStr == "/") {
    return BinaryDiv;
  }

  assert(!"Can't get binary op from string");
}

std::string unaryOpToString(UnaryOp op) {
  if(op == UnaryPlus) {
    return "+";
  } else if(op == UnaryMinus) {
    return "-";
  }

  assert(!"Can't get unary op str from op");
}

std::string binaryOpToString(BinaryOp op) {
  if(op == BinaryAdd) {
    return "+";
  } else if(op == BinarySub) {
    return "-";
  } else if(op == BinaryMul) {
    return "*";
  } else if(op == BinaryDiv) {
    return "/";
  }

  assert(!"Can't get binary op str from op");
}
