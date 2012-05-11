/*
 * parse_tree_visitor.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef PARSE_TREE_VISITOR_HPP_
#define PARSE_TREE_VISITOR_HPP_

namespace PT {

struct BlockStatementNode;
struct TypeCastExpressionNode;
struct UnaryOperatorExpressionNode;
struct VariableDefinitionStatementNode;
struct IntLiteralExpressionNode;
struct DoubleLiteralExpressionNode;
struct ProgramNode;
struct BinaryOperatorExpressionNode;
struct VariableExpressionNode;
struct ExpressionStatementNode;

struct ParseTreeVisitor {
  virtual ~ParseTreeVisitor() {}

  virtual void visitBlockStatement(BlockStatementNode const& node) const = 0;
  virtual void visitTypeCastExpression(TypeCastExpressionNode const& node) const = 0;
  virtual void visitUnaryOperatorExpression(UnaryOperatorExpressionNode const& node) const = 0;
  virtual void visitVariableDefinitionStatement(VariableDefinitionStatementNode const& node) const = 0;
  virtual void visitIntLiteralExpression(IntLiteralExpressionNode const& node) const = 0;
  virtual void visitDoubleLiteralExpression(DoubleLiteralExpressionNode const& node) const = 0;
  virtual void visitProgram(ProgramNode const& node) const = 0;
  virtual void visitBinaryOperatorExpression(BinaryOperatorExpressionNode const& node) const = 0;
  virtual void visitVariableExpression(VariableExpressionNode const& node) const = 0;
  virtual void visitExpressionStatement(ExpressionStatementNode const& node) const = 0;
};

struct ParseTreeVisitable {
  virtual ~ParseTreeVisitable() {}
  virtual void accept(ParseTreeVisitor const& visitor) const = 0;
};

}

#endif /* PARSE_TREE_VISITOR_HPP_ */
