/*
 * binary_operator_expression_node.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef BINARY_OPERATOR_EXPRESSION_NODE_HPP_
#define BINARY_OPERATOR_EXPRESSION_NODE_HPP_

#include <tr1/memory>

namespace PT {

struct BinaryOperatorExpressionNode : ExpressionNode {
  enum Operation {
    Add,
    Sub,
    Div,
    Mul,
    Assign
  };

  BinaryOperatorExpressionNode(
      ExpressionNode const& left,
      ExpressionNode const& right,
      Operation const operation)
  : left_(left.clone())
  , right_(right.clone())
  , operation_(operation)
  {}

  ExpressionNode* clone() const {
    return new BinaryOperatorExpressionNode(*this);
  }

  void accept(ParseTreeVisitor const& visitor) const {
    visitor.visitBinaryOperatorExpression(*this);
  }

  ExpressionNode const& left() const {
    return *left_;
  }

  ExpressionNode const& right() const {
    return *right_;
  }

  Operation operation() const {
    return operation_;
  }

private:
  std::shared_ptr<ExpressionNode const> const left_;
  std::shared_ptr<ExpressionNode const> const right_;
  Operation const operation_;
};

}

#endif /* BINARY_OPERATOR_EXPRESSION_NODE_HPP_ */
