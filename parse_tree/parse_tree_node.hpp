/*
 * parse_tree_node.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: loki
 */

#ifndef PARSE_TREE_NODE_HPP_
#define PARSE_TREE_NODE_HPP_

#include "parse_tree_visitor.hpp"

namespace PT {

struct ParseTreeNode : ParseTreeVisitable {
  virtual ~ParseTreeNode() {}
};

}

#endif /* PARSE_TREE_NODE_HPP_ */
