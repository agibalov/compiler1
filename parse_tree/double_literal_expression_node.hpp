/*
 * double_literal_expression_node.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef DOUBLE_LITERAL_EXPRESSION_NODE_HPP_
#define DOUBLE_LITERAL_EXPRESSION_NODE_HPP_

#include <tr1/memory>
#include <string>
#include "expression_node.hpp"

namespace PT {

struct DoubleLiteralExpressionNode : ExpressionNode {
  explicit DoubleLiteralExpressionNode(std::string const& literal)
  : literal_(literal)
  {}

  ExpressionNode* clone() const {
    return new DoubleLiteralExpressionNode(*this);
  }

  void accept(ParseTreeVisitor const& visitor) const {
    visitor.visitDoubleLiteralExpression(*this);
  }

  std::string const& literal() const {
    return literal_;
  }

private:
  std::string const literal_;
};

}

#endif /* DOUBLE_LITERAL_EXPRESSION_NODE_HPP_ */
