/*
 * type_logic.hpp
 *
 *  Created on: Sep 11, 2010
 *      Author: loki
 */

#ifndef TYPE_LOGIC_HPP_
#define TYPE_LOGIC_HPP_

#include <string>
#include "../type.hpp"

namespace test {

Type const& getFlatType(Type const& type);

// BoolResult
bool areEqualTypes(Type const& typeA, Type const& typeB);

// RankResult
int getTypeRank(Type const& type);

// TypeResult
struct TypeHasNoUnaryOp {};
Type const& getUnaryOpType(Type const& type, UnaryOp const op);

// TypeResult
Type const& getBinaryOpType(Type const& typeA, Type const& typeB, BinaryOp const op);

}

#endif /* TYPE_LOGIC_HPP_ */
