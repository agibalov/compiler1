/*
 * namespace.hpp
 *
 *  Created on: Aug 18, 2010
 *      Author: loki
 */

#ifndef NAMESPACE_HPP_
#define NAMESPACE_HPP_

#include <list>
#include "namespace_scope.hpp"

struct NamespaceKeyAlreadyExistsOnTheCurrentScope {};
struct NamespaceKeyDoesntExist {};

// отвечает за хранение пар ключ-значение в виде
// последовательности карт. при чтении поиск осуществляется сначала
// в последней карте, потом в предпоследней, и так до первой
template<class KeyT, class ValueT>
struct Namespace {
  typedef KeyT key_t;
  typedef ValueT value_t;
  typedef NamespaceScope<key_t, value_t> scope_t;
  typedef std::list<scope_t> scopes_t;

  scopes_t scopes_;

  void startScope() {
    scopes_.push_front(scope_t());
  }

  void endScope() {
    scopes_.pop_front();
  }

  void append(key_t const& key, value_t const& value) {
    if(existsOnTheCurrentScope(key)) {
      throw NamespaceKeyAlreadyExistsOnTheCurrentScope();
    }

    scope_t& scope(scopes_.front());
    scope.append(key, value);
  }

  bool exists(key_t const& key) const {
    typedef typename scopes_t::const_iterator iter_t;
    for(iter_t it(scopes_.begin()); it != scopes_.end(); ++it) {
      scope_t const& scope(*it);
      if(scope.exists(key)) {
        return true;
      }
    }

    return false;
  }

  bool existsOnTheCurrentScope(key_t const& key) const {
    scope_t const& scope(scopes_.front());
    return scope.exists(key);
  }

  value_t const& get(key_t const& key) const {
    typedef typename scopes_t::const_iterator iter_t;
    for(iter_t it(scopes_.begin()); it != scopes_.end(); ++it) {
      scope_t const& scope(*it);
      if(scope.exists(key)) {
        return scope.get(key);
      }
    }

    throw NamespaceKeyDoesntExist();
  }

  value_t& get(key_t const& key) {
    typedef typename scopes_t::iterator iter_t;
    for(iter_t it(scopes_.begin()); it != scopes_.end(); ++it) {
      scope_t& scope(*it);
      if(scope.exists(key)) {
        return scope.get(key);
      }
    }

    throw NamespaceKeyDoesntExist();
  }
};

#endif /* NAMESPACE_HPP_ */
