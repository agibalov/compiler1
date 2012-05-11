/*
 * double_type.hpp
 *
 *  Created on: Aug 19, 2010
 *      Author: loki
 */

#ifndef DOUBLE_TYPE_HPP_
#define DOUBLE_TYPE_HPP_

#include "type.hpp"

struct DoubleType : public Type {
  Type::TypeId getTypeId() const {
    return Type::TypeDouble;
  }

  std::string getTypeName() const {
    return "double";
  }

  bool canInstantiate() const {
    return true;
  }

  bool canConstructDefault() const {
    return true;
  }

  bool canConstructFromType(Type const& type) const {
    Type::TypeId const typeId(type.getTypeId());
    if(typeId == Type::TypeInt) {
      return true;
    } else if(typeId == Type::TypeDouble) {
      return true;
    }

    return false;
  }

  bool canCastToType(Type const& type) const {
    Type::TypeId const typeId(type.getTypeId());
    if(typeId == Type::TypeInt) {
      return true;
    } else if(typeId == Type::TypeDouble) {
      return true;
    }

    return false;
  }

  bool canAssignFromType(Type const& type) const {
    Type::TypeId const typeId(type.getTypeId());
    if(typeId == Type::TypeInt) {
      return true;
    } else if(typeId == Type::TypeDouble) {
      return true;
    }

    return false;
  }

  bool hasUnaryOp(UnaryOp op) const {
    if(op == UnaryPlus) {
      return true;
    } else if(op == UnaryMinus) {
      return true;
    }

    return false;
  }

  bool hasBinaryOp(BinaryOp op) const {
    if(op == BinaryAdd) {
      return true;
    } else if(op == BinarySub) {
      return true;
    } else if(op == BinaryMul) {
      return true;
    } else if(op == BinaryDiv) {
      return true;
    }

    return false;
  }
};

#endif /* DOUBLE_TYPE_HPP_ */
