/*
 * logic_unary_op_type.cpp
 *
 *  Created on: Sep 12, 2010
 *      Author: loki
 */

#include "logic.hpp"
#include "../type.hpp"

namespace test {

Type const& getUnaryOpType(Type const& type, UnaryOp const op) {
  Type const& flatType(getFlatType(type));
  if(!flatType.hasUnaryOp(op)) {
    throw TypeHasNoUnaryOp();
  }
  return flatType;
}

}
