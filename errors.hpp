/*
 * errors.hpp
 *
 *  Created on: Jun 18, 2011
 *      Author: loki
 */

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include "unsafe.hpp"

namespace test {

template<class NodeT>
struct NodeError : ErrorBase {
protected:
  typedef ErrorBase base_t;
  typedef NodeT node_t;

  NodeError(node_t const& node, std::string const& message)
  : base_t(message), node_(node)
  {}

  NodeError(node_t const& node, std::string const& message, IErrorContext const& errorContext)
  : base_t(message, errorContext), node_(node)
  {}

  void dump(int n) const {
    for(int i = 0; i < n; ++i) std::cout << " ";
    std::cout << message_ << " at '" << std::string(node_.first, node_.last) << "'";
    if(errorContext_) {
      std::cout << ", because:" << std::endl;
      errorContext_->dump(n + 1);
    } else {
      std::cout << std::endl;
    }
  }

private:
  node_t const& node_;
};

template<class NodeT>
struct BadExpressionError : NodeError<NodeT> {
  typedef NodeError<NodeT> base_t;

  BadExpressionError(NodeT const& node)
  : base_t(node, "bad expression")
  {}

  BadExpressionError(NodeT const& node, IErrorContext const& errorContext)
  : base_t(node, "bad expression", errorContext)
  {}

  IError* clone() const {
    return new BadExpressionError(*this);
  }
};

template<class NodeT>
struct BadIntegerLiteralError : NodeError<NodeT> {
  typedef NodeError<NodeT> base_t;

  BadIntegerLiteralError(NodeT const& node)
  : base_t(node, "bad integer literal")
  {}

  IError* clone() const {
    return new BadIntegerLiteralError(*this);
  }
};

template<class NodeT>
struct BadDoubleLiteralError : NodeError<NodeT> {
  typedef NodeError<NodeT> base_t;

  BadDoubleLiteralError(NodeT const& node)
  : base_t(node, "bad double literal")
  {}

  IError* clone() const {
    return new BadDoubleLiteralError(*this);
  }
};

}

#endif /* ERRORS_HPP_ */
