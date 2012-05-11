/*
 * type.hpp
 *
 *  Created on: Aug 19, 2010
 *      Author: loki
 */

#ifndef TYPE_HPP_
#define TYPE_HPP_

#include <string>
#include "operators.hpp"

struct TypeNoFeature {};

struct Type {
  enum TypeId {
    TypeInt,
    TypeDouble,
    TypeRef
  };

  virtual TypeId getTypeId() const = 0;
  virtual std::string getTypeName() const = 0;
  virtual bool canInstantiate() const { return false; }
  virtual bool canConstructDefault() const { return false; }
  virtual bool canConstructFromType(Type const& type) const { return false; }
  virtual bool canCastToType(Type const& type) const { return false; }
  virtual bool canAssignFromType(Type const& type) const { return false; }
  virtual bool hasUnaryOp(UnaryOp op) const { return false; }
  virtual bool hasBinaryOp(BinaryOp op) const { return false; }
  virtual Type const& getReferencedType() const { throw TypeNoFeature(); }
  virtual ~Type() {}
};

#endif /* TYPE_HPP_ */
