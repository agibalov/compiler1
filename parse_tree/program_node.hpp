/*
 * program_node.hpp
 *
 *  Created on: Jun 22, 2011
 *      Author: loki
 */

#ifndef PROGRAM_NODE_HPP_
#define PROGRAM_NODE_HPP_

#include <tr1/memory>
#include "statement_node.hpp"
#include "parse_tree_node.hpp"

namespace PT {

struct ProgramNode : ParseTreeNode {
  explicit ProgramNode(StatementNode const& statement)
  : statement_(statement.clone())
  {}

  void accept(ParseTreeVisitor const& visitor) const {
    visitor.visitProgram(*this);
  }

  StatementNode const& statement() const {
    return *statement_;
  }

private:
  std::shared_ptr<StatementNode const> statement_;
};

}

#endif /* PROGRAM_NODE_HPP_ */
