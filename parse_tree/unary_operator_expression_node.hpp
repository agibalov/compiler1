/*
 * unary_operator_expression_node.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef UNARY_OPERATOR_EXPRESSION_NODE_HPP_
#define UNARY_OPERATOR_EXPRESSION_NODE_HPP_

#include <tr1/memory>
#include "expression_node.hpp"

namespace PT {

struct UnaryOperatorExpressionNode : ExpressionNode {
  enum Operation {
    Neg,
    Pos
  };

  UnaryOperatorExpressionNode(
      ExpressionNode const& expression,
      Operation const op)
  : expression_(expression.clone())
  , operation_(op)
  {}

  ExpressionNode* clone() const {
    return new UnaryOperatorExpressionNode(*this);
  }

  void accept(ParseTreeVisitor const& visitor) const {
    visitor.visitUnaryOperatorExpression(*this);
  }

  ExpressionNode const& expression() const {
    return *expression_;
  }

  Operation operation() const {
    return operation_;
  }

private:
  std::shared_ptr<ExpressionNode const> expression_;
  Operation const operation_;
};

}

#endif /* UNARY_OPERATOR_EXPRESSION_NODE_HPP_ */
