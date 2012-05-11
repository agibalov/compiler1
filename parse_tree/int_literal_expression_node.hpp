/*
 * int_literal_expression_node.hpp
 *
 *  Created on: Jun 22, 2011
 *      Author: loki
 */

#ifndef INT_LITERAL_EXPRESSION_NODE_HPP_
#define INT_LITERAL_EXPRESSION_NODE_HPP_

#include <tr1/memory>
#include <string>
#include "expression_node.hpp"

namespace PT {

struct IntLiteralExpressionNode : ExpressionNode {
  explicit IntLiteralExpressionNode(std::string const& literal)
  : literal_(literal)
  {}

  ExpressionNode* clone() const {
    return new IntLiteralExpressionNode(*this);
  }

  void accept(ParseTreeVisitor const& visitor) const {
    visitor.visitIntLiteralExpression(*this);
  }

  std::string const& literal() const {
    return literal_;
  }

private:
  std::string const literal_;
};

}

#endif /* INT_LITERAL_EXPRESSION_NODE_HPP_ */
