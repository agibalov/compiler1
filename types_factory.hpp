/*
 * types_factory.hpp
 *
 *  Created on: Aug 19, 2010
 *      Author: loki
 */

#ifndef TYPES_FACTORY_HPP_
#define TYPES_FACTORY_HPP_

#include <string>
#include <map>
#include <tr1/memory>

#include "types/int_type.hpp"
#include "types/double_type.hpp"
#include "types/ref_type.hpp"

struct TypesFactoryTypeDoesntExist {};
struct TypesFactoryReferenceToReference {};

struct TypesFactory {
  typedef std::string name_t;
  typedef std::shared_ptr<Type> type_ptr_t;
  typedef type_ptr_t type_creator_t();
  typedef type_creator_t* type_creator_ptr_t;
  typedef std::map<name_t, type_creator_ptr_t> type_creators_by_name_t;
  typedef std::map<name_t, type_ptr_t> types_by_name_t;
  typedef std::map<Type const* const, type_ptr_t> ref_types_by_types_t;

  type_creators_by_name_t typeCreatorsByName_;
  types_by_name_t typesByName_;
  ref_types_by_types_t refTypesByTypes_;

  static TypesFactory& instance() {
    static TypesFactory instance;
    return instance;
  }

private:
  TypesFactory() {
    typeCreatorsByName_["int"] = &createIntType;
    typeCreatorsByName_["double"] = &createDoubleType;
  }

  static type_ptr_t createIntType() {
    return type_ptr_t(new IntType());
  }

  static type_ptr_t createDoubleType() {
    return type_ptr_t(new DoubleType());
  }

public:
  bool typeExists(name_t const& name) const {
    type_creators_by_name_t::const_iterator it(typeCreatorsByName_.find(name));
    return it != typeCreatorsByName_.end();
  }

  Type const& getTypeByName(name_t const& name) {
    {
      types_by_name_t::const_iterator it(typesByName_.find(name));
      if(it != typesByName_.end()) {
        return *(it->second);
      }
    }

    if(!typeExists(name)) {
      throw TypesFactoryTypeDoesntExist();
    }

    type_creators_by_name_t::const_iterator it(typeCreatorsByName_.find(name));
    type_ptr_t const type((*it->second)());
    types_by_name_t::value_type const pair(name, type);
    typesByName_.insert(pair);

    return getTypeByName(name);
  }

  Type const& getReferenceType(Type const& type) {
    Type::TypeId const typeId(type.getTypeId());
    if(typeId == Type::TypeRef) {
      throw TypesFactoryReferenceToReference();
    }

    ref_types_by_types_t::const_iterator it(refTypesByTypes_.find(&type));
    if(it != refTypesByTypes_.end()) {
      return *it->second;
    }

    type_ptr_t const refType(type_ptr_t(new RefType(type)));
    ref_types_by_types_t::value_type const pair(&type, refType);
    refTypesByTypes_.insert(pair);

    return getReferenceType(type);
  }
};

#endif /* TYPES_FACTORY_HPP_ */
