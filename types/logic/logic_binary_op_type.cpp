/*
 * logic_binary_op_type.cpp
 *
 *  Created on: Sep 12, 2010
 *      Author: loki
 */

#include "logic.hpp"
#include "../type.hpp"
#include "../../unsafe.hpp"

namespace test {

Type const& getBinaryOpType(Type const& typeA, Type const& typeB, BinaryOp const op) {
  Type const* pflatA;
  Type const* pflatB;

  unsafe([&pflatA, &typeA] {
      pflatA = &getFlatType(typeA);
  }, [&pflatB, &typeB] {
      pflatB = &getFlatType(typeB);
  });

  Type const& flatA(*pflatA);
  Type const& flatB(*pflatB);

  int rankA;
  int rankB;
  unsafe([&rankA, &flatA] {
      rankA = getTypeRank(flatA);
  }, [&rankB, &flatB] {
      rankB = getTypeRank(flatB);
  });



  if(rankA == rankB) {
    if(flatA.hasBinaryOp(op)) {
      return flatA;
    } else {
      throw 123;
      //return TypeResult(TypeHasNoBinaryOpError(flatA, op));
    }
  } else if(rankA > rankB) {
    if(flatA.hasBinaryOp(op)) {
      if(flatA.canConstructFromType(flatB)) {
        return flatA;
      } else {
        throw 123;
        //return TypeACantConstructFromTypeBError(flatA, flatB);
      }
    } else {
      throw 123;
      //return TypeResult(TypeHasNoBinaryOpError(flatA, op));
    }
  } else {
    if(flatB.hasBinaryOp(op)) {
      if(flatB.canConstructFromType(flatA)) {
        return flatB;
      } else {
        throw 123;
        //return TypeACantConstructFromTypeBError(flatB, flatA);
      }
    } else {
      throw 123;
      //return TypeResult(TypeHasNoBinaryOpError(flatB, op));
    }
  }
}

}
