/*
 * variable_definition_statement_node.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef VARIABLE_DEFINITION_STATEMENT_NODE_HPP_
#define VARIABLE_DEFINITION_STATEMENT_NODE_HPP_

#include <tr1/memory>
#include "expression_node.hpp"
#include "statement_node.hpp"

namespace PT {

struct VariableDefinitionStatementNode : StatementNode {
  VariableDefinitionStatementNode(
      std::string const& typeName,
      std::string const& variableName,
      ExpressionNode const& initializerExpression)
  : typeName_(typeName)
  , variableName_(variableName)
  , initializerExpression_(initializerExpression.clone())
  {}

  StatementNode* clone() const {
    return new VariableDefinitionStatementNode(*this);
  }

  void accept(ParseTreeVisitor const& visitor) const {
    visitor.visitVariableDefinitionStatement(*this);
  }

  std::string const& typeName() const {
    return typeName_;
  }

  std::string const& variableName() const {
    return variableName_;
  }

  ExpressionNode const& expression() const {
    return *initializerExpression_;
  }

private:
  std::string const typeName_;
  std::string const variableName_;
  std::shared_ptr<ExpressionNode> initializerExpression_;
};

}

#endif /* VARIABLE_DEFINITION_STATEMENT_NODE_HPP_ */
