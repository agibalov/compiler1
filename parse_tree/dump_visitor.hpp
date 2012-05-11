/*
 * dump_visitor.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef DUMP_VISITOR_HPP_
#define DUMP_VISITOR_HPP_

#include <iostream>

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

namespace PT { namespace Utils {

struct DumpParseTreeVisitor : ParseTreeVisitor {
  void visitBlockStatement(BlockStatementNode const& node) const {
    std::cout << "block start" << std::endl;
    for(auto it(node.statements().begin()); it != node.statements().end(); ++it) {
      (*it)->accept(*this);
    }
    std::cout << "block end" << std::endl;
  }

  void visitTypeCastExpression(TypeCastExpressionNode const& node) const {
    std::cout << "type cast of" << std::endl;
    node.expression().accept(*this);
    std::cout << "to type " << node.typeName() << std::endl;
  }

  void visitUnaryOperatorExpression(UnaryOperatorExpressionNode const& node) const {
    std::cout << "unary operator" << std::endl;
  }

  void visitVariableDefinitionStatement(VariableDefinitionStatementNode const& node) const {
    std::cout
    << "define variable of type "
    << node.typeName()
    << " with name "
    << node.variableName()
    << " and initializer:" << std::endl;
    node.expression().accept(*this);
  }

  void visitIntLiteralExpression(IntLiteralExpressionNode const& node) const {
    std::cout << "int literal" << std::endl;
  }

  void visitDoubleLiteralExpression(DoubleLiteralExpressionNode const& node) const {
    std::cout << "double literal" << std::endl;
  }

  void visitProgram(ProgramNode const& node) const {
    std::cout << "program start" << std::endl;
    node.statement().accept(*this);
    std::cout << "program end" << std::endl;
  }

  void visitBinaryOperatorExpression(BinaryOperatorExpressionNode const& node) const {
    std::cout << "binary operator" << std::endl;
  }

  void visitVariableExpression(VariableExpressionNode const& node) const {
    std::cout << "variable ref - " << node.variableName() << std::endl;
  }

  void visitExpressionStatement(ExpressionStatementNode const& node) const {
    std::cout << "expression" << std::endl;
  }
};

void dumpProgramNode(ProgramNode const& node) {
  DumpParseTreeVisitor const visitor;
  node.accept(visitor);
}

}}

#endif /* DUMP_VISITOR_HPP_ */
