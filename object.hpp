/*
 * object.hpp
 *
 *  Created on: Aug 19, 2010
 *      Author: loki
 */

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "types/type.hpp"

struct Object {
private:
  Type const& type_;

public:
  explicit Object(Type const& type)
  : type_(type)
  {}

  Type const& type() const {
    return type_;
  }
};

#endif /* OBJECT_HPP_ */
