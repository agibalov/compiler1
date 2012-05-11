/*
 * statement_node.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef STATEMENT_NODE_HPP_
#define STATEMENT_NODE_HPP_

#include <tr1/memory>
#include "parse_tree_node.hpp"

namespace PT {

struct StatementNode : ParseTreeNode {
  virtual StatementNode* clone() const = 0;
  virtual ~StatementNode() {}
};

}

#endif /* STATEMENT_NODE_HPP_ */
