/*
 * namespace_scope.hpp
 *
 *  Created on: Aug 18, 2010
 *      Author: loki
 */

#ifndef NAMESPACE_SCOPE_HPP_
#define NAMESPACE_SCOPE_HPP_

#include <map>

struct NamespaceScopeKeyAlreadyExists {};
struct NamespaceScopeKeyDoesntExist {};

// один уровень для namespace
template<class KeyT, class ValueT>
struct NamespaceScope {
  typedef KeyT key_t;
  typedef ValueT value_t;
  typedef std::map<key_t, value_t> map_t;

  map_t map_;

  void append(key_t const& key, value_t const& value) {
    if(exists(key)) {
      throw NamespaceScopeKeyAlreadyExists();
    }

    map_.insert(typename map_t::value_type(key, value));
  }

  bool exists(key_t const& key) const {
    return map_.find(key) != map_.end();
  }

  value_t const& get(key_t const& key) const {
    if(!exists(key)) {
      throw NamespaceScopeKeyDoesntExist();
    }

    return map_.find(key)->second;
  }

  value_t& get(key_t const& key) {
    if(!exists(key)) {
      throw NamespaceScopeKeyDoesntExist();
    }

    return map_.find(key)->second;
  }
};

#endif /* NAMESPACE_SCOPE_HPP_ */
