/*
 * flat_type.cpp
 *
 *  Created on: Sep 12, 2010
 *      Author: loki
 */

#include "logic.hpp"
#include "../type.hpp"

namespace test {

Type const& getFlatType(Type const& type) {
  if(type.getTypeId() == Type::TypeRef) {
    return type.getReferencedType();
  }

  return type;
}

}
