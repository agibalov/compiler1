/*
 * block_statement_node.hpp
 *
 *  Created on: Jun 22, 2011
 *      Author: loki
 */

#ifndef BLOCK_STATEMENT_NODE_HPP_
#define BLOCK_STATEMENT_NODE_HPP_

#include <tr1/memory>
#include <vector>

#include "parse_tree_visitor.hpp"
#include "statement_node.hpp"

namespace PT {

struct BlockStatementNode : StatementNode {
  explicit BlockStatementNode(std::vector<std::shared_ptr<StatementNode const> > const& statements)
  : statements_(statements)
  {}

  StatementNode* clone() const {
    return new BlockStatementNode(*this);
  }

  void accept(ParseTreeVisitor const& visitor) const {
    visitor.visitBlockStatement(*this);
  }

  std::vector<std::shared_ptr<StatementNode const> > const& statements() const {
    return statements_;
  }

private:
  std::vector<std::shared_ptr<StatementNode const> > const statements_;
};

}

#endif /* BLOCK_STATEMENT_NODE_HPP_ */
