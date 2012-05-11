/*
 * unsafe.hpp
 *
 *  Created on: Jun 18, 2011
 *      Author: loki
 */

#ifndef UNSAFE_HPP_
#define UNSAFE_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <tr1/memory>

struct IErrorContext {
  virtual ~IErrorContext() {}
  virtual IErrorContext* clone() const = 0;
  virtual void dump(int n) const = 0;
};

struct IError {
  virtual IError* clone() const = 0;
  virtual ~IError() {}
  virtual void dump(int n) const = 0;
};

struct ErrorBase : IError {
  explicit ErrorBase(std::string const& message)
  : message_(message)
  {}

  ErrorBase(std::string const& message, IErrorContext const& errorContext)
  : message_(message), errorContext_(errorContext.clone())
  {}

  void dump(int n) const {
    for(int i = 0; i < n; ++i) std::cout << " ";
    std::cout << message_;
    if(errorContext_) {
      std::cout << " because:" << std::endl;
      errorContext_->dump(n + 1);
    } else {
      std::cout << std::endl;
    }
  }

protected:
  std::string const message_;
  std::shared_ptr<IErrorContext> const errorContext_;
};

struct ErrorContext : IErrorContext {
  typedef std::shared_ptr<IError> error_ptr_t;
  typedef std::vector<error_ptr_t> errors_t;
  errors_t errors_;

  void Throw(IError const& error) {
    errors_.push_back(error_ptr_t(error.clone()));
  }

  IErrorContext* clone() const {
    return new ErrorContext(*this);
  }

  void dump(int n) const {
    for(auto it(errors_.begin()); it != errors_.end(); ++it) {
      (*it)->dump(n);
    }
  }
};

void unsafe_impl(ErrorContext& ec);

template<class T, class... Args>
void unsafe_impl(ErrorContext& ec, T const& t, Args const&... args) {
  try {
    t();
  } catch(IError const& error) {
    ec.Throw(error);
  }
  unsafe_impl(ec, args...);
}

template<class T, class... Args>
void unsafe(T const& t, Args const&... args) {
  ErrorContext ec;
  unsafe_impl(ec, t, args...);
  if(ec.errors_.size() > 0) {
    throw ec;
  }
}

#endif /* UNSAFE_HPP_ */
