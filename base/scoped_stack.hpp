/*
 * scoped_stack.hpp
 *
 *  Created on: Aug 18, 2010
 *      Author: loki
 */

#ifndef SCOPED_STACK_HPP_
#define SCOPED_STACK_HPP_

#include <stack>

// отвечает за хранение значение в порядке стека с разделением на части.
// т.е. кроме обычных операций стека есть ещё такие операции как:
// начать новую часть, убить текущую часть
template<class ValueT>
struct ScopedStack {
  typedef ValueT value_t;
  typedef std::stack<value_t> data_stack_t;
  typedef std::stack<typename data_stack_t::size_type> scope_stack_t;

  data_stack_t data_;
  scope_stack_t scopes_;

  void startScope() {
    scopes_.push(data_.size());
  }

  void endScope() {
    typename data_stack_t::size_type const prevSize(scopes_.top());
    scopes_.pop();
    while(data_.size() > prevSize) {
      data_.pop();
    }
  }

  void push(value_t const& value) {
    data_.push(value);
  }

  value_t const& top() const {
    return data_.top();
  }

  value_t& top() {
    return data_.top();
  }
};

#endif /* SCOPED_STACK_HPP_ */
