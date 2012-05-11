/*
 * pt.hpp
 *
 *  Created on: Jun 22, 2011
 *      Author: loki
 */

#ifndef PT_HPP_
#define PT_HPP_

#include <tr1/memory>

#include "block_statement_node.hpp"
#include "expression_statement_node.hpp"
#include "expression_node.hpp"
#include "statement_node.hpp"
#include "type_cast_expression_node.hpp"
#include "unary_operator_expression_node.hpp"
#include "variable_definition_statement_node.hpp"
#include "int_literal_expression_node.hpp"
#include "double_literal_expression_node.hpp"
#include "program_node.hpp"
#include "binary_operator_expression_node.hpp"
#include "variable_expression_node.hpp"

namespace PT {

template<class OriginalNodeT, class GrammarT>
struct ASTToPTConverterFactory {
  typedef OriginalNodeT original_node_t;
  typedef GrammarT grammar_t;

  ProgramNode buildProgramTree(original_node_t const& node) const {
    if(node.id == grammar_t::BLOCK) {
      BlockStatementNode const statement(makeBlockStatementNode(node));
      return ProgramNode(statement);
    }

    assert(!"wtf");
  }

private:
  bool isExpressionNode(original_node_t const& node) const {
    return
        node.id == grammar_t::EXPRESSION1 ||
        node.id == grammar_t::EXPRESSION2 ||
        node.id == grammar_t::EXPRESSION3 ||
        node.id == grammar_t::EXPRESSION4 ||
        node.id == grammar_t::EXPRESSION5 ||
        node.id == grammar_t::NAME ||
        node.id == grammar_t::INTEGER ||
        node.id == grammar_t::DOUBLE;
  }

  std::shared_ptr<StatementNode const> makeStatementNode(original_node_t const& node) const {
    if(node.id == grammar_t::BLOCK) {
      return std::shared_ptr<StatementNode>(makeBlockStatementNode(node).clone());
    } else if(isExpressionNode(node)) {
      return std::shared_ptr<StatementNode>(makeJustExpressionStatementNode(node).clone());
    } else if(node.id == grammar_t::VARIABLE_DEF) {
      return std::shared_ptr<StatementNode>(makeVariableDefinitionStatementNode(node).clone());
    }

    assert(!"wtf");
  }

  BlockStatementNode makeBlockStatementNode(original_node_t const& node) const {
    std::vector<std::shared_ptr<StatementNode const> > statements;
    for(auto it(node.children.begin()); it != node.children.end(); ++it) {
      std::shared_ptr<StatementNode const> const statement(makeStatementNode(*it));
      statements.push_back(statement);
    }

    return BlockStatementNode(statements);
  }

  ExpressionStatementNode makeJustExpressionStatementNode(original_node_t const& node) const {
    std::shared_ptr<ExpressionNode const> expression(getExpression(node));
    return ExpressionStatementNode(*expression);
  }

  VariableDefinitionStatementNode makeVariableDefinitionStatementNode(original_node_t const& node) const {
    original_node_t const typeNameNode(node.children[0]);
    original_node_t const variableNameNode(node.children[1]);
    original_node_t const initializerExpressionNode(node.children[2]);

    std::string const typeName(getString(typeNameNode));
    std::string const variableName(getString(variableNameNode));
    std::shared_ptr<ExpressionNode> initializerExpression(getExpression(initializerExpressionNode));

    return VariableDefinitionStatementNode(
        typeName,
        variableName,
        *initializerExpression);
  }

  std::string getString(original_node_t const& node) const {
    return std::string(node.first, node.last);
  }

  std::shared_ptr<ExpressionNode> getExpression(original_node_t const& node) const {
    if(node.id == grammar_t::EXPRESSION1) { // unary operator
      return std::shared_ptr<ExpressionNode>(getUnaryOperatorExpression(node).clone());
    } else if(node.id == grammar_t::EXPRESSION2) { // type cast
      return std::shared_ptr<ExpressionNode>(getTypeCastExpression(node).clone());
    } else if(node.id == grammar_t::EXPRESSION3) { // binary div/mul
      return std::shared_ptr<ExpressionNode>(getBinaryExpression(node).clone());
    } else if(node.id == grammar_t::EXPRESSION4) { // binary add/sub
      return std::shared_ptr<ExpressionNode>(getBinaryExpression(node).clone());
    } else if(node.id == grammar_t::EXPRESSION5) { // assign
      return std::shared_ptr<ExpressionNode>(getBinaryExpression(node).clone());
    } else if(node.id == grammar_t::NAME) { // name
      return std::shared_ptr<ExpressionNode>(getVariableExpression(node).clone());
    } else if(node.id == grammar_t::INTEGER) { // integer
      return std::shared_ptr<ExpressionNode>(getIntLiteralExpression(node).clone());
    } else if(node.id == grammar_t::DOUBLE) { // double
      return std::shared_ptr<ExpressionNode>(getDoubleLiteralExpression(node).clone());
    }

    assert(!"wtf");
  }

  VariableExpressionNode getVariableExpression(original_node_t const& node) const {
    std::string const variableName(getString(node));
    return VariableExpressionNode(variableName);
  }

  IntLiteralExpressionNode getIntLiteralExpression(original_node_t const& node) const {
    std::string const literal(getString(node));
    return IntLiteralExpressionNode(literal);
  }

  DoubleLiteralExpressionNode getDoubleLiteralExpression(original_node_t const& node) const {
    std::string const literal(getString(node));
    return DoubleLiteralExpressionNode(literal);
  }

  UnaryOperatorExpressionNode getUnaryOperatorExpression(original_node_t const& node) const {
    std::string const opString(node.first, node.last);
    UnaryOperatorExpressionNode::Operation op;
    if(opString == "+") {
      op = UnaryOperatorExpressionNode::Pos;
    } else if(opString == "-") {
      op = UnaryOperatorExpressionNode::Neg;
    } else {
      assert(!"wtf");
    }

    original_node_t const& expressionNode(node.children[0]);
    std::shared_ptr<ExpressionNode> expression(getExpression(expressionNode));

    return UnaryOperatorExpressionNode(*expression, op);
  }

  TypeCastExpressionNode getTypeCastExpression(original_node_t const& node) const {
    std::string const typeName(node.first, node.last);
    std::shared_ptr<ExpressionNode> expression(getExpression(node.children[0]));
    return TypeCastExpressionNode(typeName, *expression);
  }

  BinaryOperatorExpressionNode getBinaryExpression(original_node_t const& node) const {
    std::string const opString(node.first, node.last);
    BinaryOperatorExpressionNode::Operation op;
    if(opString == "/") {
      op = BinaryOperatorExpressionNode::Div;
    } else if(opString == "*") {
      op = BinaryOperatorExpressionNode::Mul;
    } else if(opString == "+") {
      op = BinaryOperatorExpressionNode::Add;
    } else if(opString == "-") {
      op = BinaryOperatorExpressionNode::Sub;
    } else if(opString == "=") {
      op = BinaryOperatorExpressionNode::Assign;
    } else {
      assert(!"wtf");
    }

    original_node_t const& leftNode(node.children[0]);
    original_node_t const& rightNode(node.children[1]);
    std::shared_ptr<ExpressionNode> leftExpression(getExpression(leftNode));
    std::shared_ptr<ExpressionNode> rightExpression(getExpression(rightNode));

    return BinaryOperatorExpressionNode(
        *leftExpression,
        *rightExpression,
        op);
  }
};

}

#endif /* PT_HPP_ */
