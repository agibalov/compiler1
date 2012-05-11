/*
 * semantic.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef SEMANTIC_HPP_
#define SEMANTIC_HPP_

#include "parse_tree_visitor.hpp"

#include "block_statement_node.hpp"
#include "type_cast_expression_node.hpp"
#include "unary_operator_expression_node.hpp"
#include "variable_definition_statement_node.hpp"
#include "int_literal_expression_node.hpp"
#include "double_literal_expression_node.hpp"
#include "program_node.hpp"
#include "binary_operator_expression_node.hpp"
#include "variable_expression_node.hpp"
#include "expression_statement_node.hpp"

struct SemanticAnalyzerVisitor : ParseTreeVisitor {
  void visitBlockStatement(BlockStatementNode const& node) const {
    // new scope
    // run
    // kill scope
  }

  void visitTypeCastExpression(TypeCastExpressionNode const& node) const {
  }

  void visitUnaryOperatorExpression(UnaryOperatorExpressionNode const& node) const {
  }

  void visitVariableDefinitionStatement(VariableDefinitionStatementNode const& node) const {
    // compute initializer expression
    // add name to scope
    // type checks
    // assign value to variable
  }

  void visitIntLiteralExpression(IntLiteralExpressionNode const& node) const {
  }

  void visitDoubleLiteralExpression(DoubleLiteralExpressionNode const& node) const {
  }

  void visitProgram(ProgramNode const& node) const {
  }

  void visitBinaryOperatorExpression(BinaryOperatorExpressionNode const& node) const {
  }

  void visitVariableExpression(VariableExpressionNode const& node) const {
  }

  void visitExpressionStatement(ExpressionStatementNode const& node) const {
  }
};

#endif /* SEMANTIC_HPP_ */
