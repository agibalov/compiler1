/*
 * expression_statement_node.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef EXPRESSION_STATEMENT_NODE_HPP_
#define EXPRESSION_STATEMENT_NODE_HPP_

#include <tr1/memory>
#include "statement_node.hpp"
#include "expression_node.hpp"

namespace PT {

struct ExpressionStatementNode : StatementNode {
  ExpressionStatementNode(ExpressionNode const& expression)
  : expression_(expression.clone())
  {}

  StatementNode* clone() const {
    return new ExpressionStatementNode(*this);
  }

  void accept(ParseTreeVisitor const& visitor) const {
    visitor.visitExpressionStatement(*this);
  }

  ExpressionNode const& expression() const {
    return *expression_;
  }

private:
  std::shared_ptr<ExpressionNode> expression_;
};

}

#endif /* EXPRESSION_STATEMENT_NODE_HPP_ */
