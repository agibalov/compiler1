/*
 * variable_expression_node.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef VARIABLE_EXPRESSION_NODE_HPP_
#define VARIABLE_EXPRESSION_NODE_HPP_

#include <tr1/memory>
#include <string>
#include "expression_node.hpp"

namespace PT {

struct VariableExpressionNode : ExpressionNode {
  explicit VariableExpressionNode(std::string const& variableName)
  : variableName_(variableName)
  {}

  ExpressionNode* clone() const {
    return new VariableExpressionNode(*this);
  }

  void accept(ParseTreeVisitor const& visitor) const {
    visitor.visitVariableExpression(*this);
  }

  std::string const& variableName() const {
    return variableName_;
  }

private:
  std::string const variableName_;
};

}

#endif /* VARIABLE_EXPRESSION_NODE_HPP_ */
