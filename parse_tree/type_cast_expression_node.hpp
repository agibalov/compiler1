/*
 * type_cast_expression_node.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef TYPE_CAST_EXPRESSION_NODE_HPP_
#define TYPE_CAST_EXPRESSION_NODE_HPP_

#include <tr1/memory>
#include "expression_node.hpp"

namespace PT {

struct TypeCastExpressionNode : ExpressionNode {
  TypeCastExpressionNode(
      std::string const& typeName,
      ExpressionNode const& expression)
  : typeName_(typeName)
  , expression_(expression.clone())
  {}

  ExpressionNode* clone() const {
    return new TypeCastExpressionNode(*this);
  }

  void accept(ParseTreeVisitor const& visitor) const {
    visitor.visitTypeCastExpression(*this);
  }

  std::string const& typeName() const {
    return typeName_;
  }

  ExpressionNode const& expression() const {
    return *expression_;
  }

private:
  std::string const typeName_;
  std::shared_ptr<ExpressionNode const> expression_;
};

}

#endif /* TYPE_CAST_EXPRESSION_NODE_HPP_ */
