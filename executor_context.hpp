/*
 * context.hpp
 *
 *  Created on: Aug 19, 2010
 *      Author: loki
 */

#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include "base/name_context.hpp"
#include "types/type.hpp"
#include "object.hpp"
#include "types_factory.hpp"

struct ExecutorContext {
  typedef std::string name_t;
  typedef Object object_t;
  typedef Type const* const type_t;
  typedef NameContext<name_t, object_t, type_t> name_context_t;

  name_context_t nameContext_;

  ExecutorContext()
  : nameContext_() {
    startScope();
    TypesFactory& typesFactory(TypesFactory::instance());
    nameContext_.addType("int", &typesFactory.getTypeByName("int"));
    nameContext_.addType("double", &typesFactory.getTypeByName("double"));
  }

  ~ExecutorContext() {
    endScope();
  }

  void startScope() {
    nameContext_.startScope();
  }

  void endScope() {
    nameContext_.endScope();
  }

  bool hasNameOnCurrentScope(name_t const& name) const {
    return nameContext_.hasNameOnCurrentScope(name);
  }

  bool hasName(name_t const& name) const {
    return nameContext_.hasName(name);
  }

  bool hasObject(name_t const& name) const {
    return nameContext_.hasObject(name);
  }

  object_t const& getObject(name_t const& name) const {
    return nameContext_.getObject(name);
  }

  object_t& getObject(name_t const& name) {
    return nameContext_.getObject(name);
  }

  void addObject(name_t const& name, object_t const& obj) {
    nameContext_.addObject(name, obj);
  }

  bool hasType(name_t const& name) const {
    return nameContext_.hasType(name);
  }

  type_t const& getType(name_t const& name) const {
    return nameContext_.getType(name);
  }

  type_t& getType(name_t const& name) {
    return nameContext_.getType(name);
  }
};

#endif /* CONTEXT_HPP_ */
