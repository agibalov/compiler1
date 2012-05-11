/*
 * logic_equal_types.cpp
 *
 *  Created on: Sep 12, 2010
 *      Author: loki
 */

#include "logic.hpp"
#include "../type.hpp"

namespace test {

/*
 * ссылки сравниваются по внутренним типам,
 * остальные сравниваются как есть
 */

bool areEqualTypes(Type const& typeA, Type const& typeB) {
  bool const comparingRefTypes(
      typeA.getTypeId() == Type::TypeRef &&
      typeB.getTypeId() == Type::TypeRef);
  if(comparingRefTypes) {
    Type const& flatA(getFlatType(typeA));
    Type const& flatB(getFlatType(typeB));
    return areEqualTypes(flatA, flatB);
  } else {
    return typeA.getTypeId() == typeB.getTypeId();
  }
}

}
