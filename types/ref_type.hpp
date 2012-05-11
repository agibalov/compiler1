/*
 * ref_type.hpp
 *
 *  Created on: Aug 19, 2010
 *      Author: loki
 */

#ifndef REF_TYPE_HPP_
#define REF_TYPE_HPP_

#include "type.hpp"
#include "logic/logic.hpp"

struct RefTypeRefToRef {};

struct RefType : public Type {
  Type const& innerType_;

  explicit RefType(Type const& innerType)
  : innerType_(innerType) {
    Type::TypeId const typeId(innerType_.getTypeId());
    if(typeId == Type::TypeRef) {
      throw RefTypeRefToRef();
    }
  }

  Type::TypeId getTypeId() const {
    return Type::TypeRef;
  }

  std::string getTypeName() const {
    return innerType_.getTypeName() + "&";
  }

  bool canInstantiate() const {
    return true;
  }

  bool canConstructFromType(Type const& type) const {
    if(test::areEqualTypes(innerType_, type)) {
      return true;
    }

    return false;
  }

  Type const& getReferencedType() const {
    return innerType_;
  }
};


#endif /* REF_TYPE_HPP_ */
