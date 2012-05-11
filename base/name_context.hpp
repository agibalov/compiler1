/*
 * name_context.hpp
 *
 *  Created on: Aug 18, 2010
 *      Author: loki
 */

#ifndef NAMECONTEXT_HPP_
#define NAMECONTEXT_HPP_

#include <string>

#include "namespace.hpp"

struct NameContextNameDoesntExist {};
struct NameContextObjectNameDoesntExist {};
struct NameContextObjectNameAlreadyExistsOnTheCurrentScope {};
struct NameContextTypeNameDoesntExist {};
struct NameContextTypeNameAlreadyExistsOnTheCurrentScope {};
struct NameContextFuncNameDoesntExist {};
struct NameContextFuncNameAlreadyExistsOnTheCurrentScope {};

// контекст имён. управляет всеми возможными именами.
// ТОЛЬКО именами - значения только ссылочные.
template<class NameT, class ObjectT, class TypeT>
struct NameContext {
  typedef NameT name_t;
  typedef enum {
    ContextEntityObject,
    ContextEntityType,
    ContextEntityFunc
  } context_entity_t;
  typedef ObjectT object_t;
  typedef TypeT type_t;
  typedef int func_t;

  typedef Namespace<name_t, context_entity_t> entity_type_namespace_t;
  typedef Namespace<name_t, object_t> object_namespace_t;
  typedef Namespace<name_t, type_t> type_namespace_t;
  typedef Namespace<name_t, func_t> func_namespace_t;

  entity_type_namespace_t entityTypesNS_;
  object_namespace_t objectsNS_;
  type_namespace_t typesNS_;
  func_namespace_t funcsNS_;

  void startScope() {
    entityTypesNS_.startScope();
    objectsNS_.startScope();
    typesNS_.startScope();
    funcsNS_.startScope();
  }

  void endScope() {
    entityTypesNS_.endScope();
    objectsNS_.endScope();
    typesNS_.endScope();
    funcsNS_.endScope();
  }

  bool hasName(name_t const& name) const {
    return entityTypesNS_.exists(name);
  }

  bool hasNameOnCurrentScope(name_t const& name) const {
    return entityTypesNS_.existsOnTheCurrentScope(name);
  }

  context_entity_t getNameType(name_t const& name) const {
    if(!entityTypesNS_.exists(name)) {
      throw NameContextNameDoesntExist();
    }

    return entityTypesNS_.get(name);
  }

  bool hasObject(name_t const& name) const {
    return objectsNS_.exists(name);
  }

  object_t const& getObject(name_t const& name) const {
    if(!objectsNS_.exists(name)) {
      throw NameContextObjectNameDoesntExist();
    }

    return objectsNS_.get(name);
  }

  object_t& getObject(name_t const& name) {
    if(!objectsNS_.exists(name)) {
      throw NameContextObjectNameDoesntExist();
    }

    return objectsNS_.get(name);
  }

  void addObject(name_t const& name, object_t const& obj) {
    if(objectsNS_.existsOnTheCurrentScope(name)) {
      throw NameContextObjectNameAlreadyExistsOnTheCurrentScope();
    }

    objectsNS_.append(name, obj);
  }

  bool hasType(name_t const& name) const {
    return typesNS_.exists(name);
  }

  type_t const& getType(name_t const& name) const {
    if(!typesNS_.exists(name)) {
      throw NameContextTypeNameDoesntExist();
    }

    return typesNS_.get(name);
  }

  type_t& getType(name_t const& name) {
    if(!typesNS_.exists(name)) {
      throw NameContextTypeNameDoesntExist();
    }

    return typesNS_.get(name);
  }

  void addType(name_t const& name, type_t const& type) {
    if(typesNS_.existsOnTheCurrentScope(name)) {
      throw NameContextTypeNameAlreadyExistsOnTheCurrentScope();
    }

    typesNS_.append(name, type);
  }

  bool hasFunc(name_t const& name) const {
    return funcsNS_.exists(name);
  }

  func_t const& getFunc(name_t const& name) const {
    if(!funcsNS_.exists(name)) {
      throw NameContextFuncNameDoesntExist();
    }

    return funcsNS_.get(name);
  }

  func_t& getFunc(name_t const& name) {
    if(!funcsNS_.exists(name)) {
      throw NameContextFuncNameDoesntExist();
    }

    return funcsNS_.get(name);
  }

  void addFunc(name_t const& name, func_t const& func) {
    if(funcsNS_.existsOnTheCurrentScope(name)) {
      throw NameContextFuncNameAlreadyExistsOnTheCurrentScope();
    }

    funcsNS_.append(name, func);
  }
};

#endif /* CONTEXT_HPP_ */
