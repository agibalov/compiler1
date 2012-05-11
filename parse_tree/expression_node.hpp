/*
 * expression_node.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef EXPRESSION_NODE_HPP_
#define EXPRESSION_NODE_HPP_

#include <tr1/memory>

#include "parse_tree_node.hpp"

namespace PT {

struct ExpressionNode : ParseTreeNode {
  virtual ExpressionNode* clone() const = 0;
  virtual ~ExpressionNode() {}
};

}

#endif /* EXPRESSION_NODE_HPP_ */
