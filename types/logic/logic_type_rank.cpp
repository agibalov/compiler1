/*
 * logic_type_rank.cpp
 *
 *  Created on: Sep 12, 2010
 *      Author: loki
 */

#include <assert.h>
#include "logic.hpp"
#include "../type.hpp"

namespace test {

int getTypeRank(Type const& type) {
  Type::TypeId const typeId(type.getTypeId());
  if(typeId == Type::TypeInt) {
    return 1;
  } else if(typeId == Type::TypeDouble) {
    return 2;
  } else if(typeId == Type::TypeRef) {
    Type const& flatType(getFlatType(type));
    return getTypeRank(flatType);
  }

  assert(!"Can't get rank for this type");
}

}
