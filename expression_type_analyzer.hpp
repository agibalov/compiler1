/*
 * expression_type_analyzer.hpp
 *
 *  Created on: Sep 7, 2010
 *      Author: loki
 */

#ifndef EXPRESSION_TYPE_ANALYZER_HPP_
#define EXPRESSION_TYPE_ANALYZER_HPP_

#include <boost/lexical_cast.hpp>
#include <tr1/memory>
#include "types/type.hpp"
#include "types/logic/logic.hpp"
#include "unsafe.hpp"
#include "errors.hpp"

namespace test {

template<class NodeT, class GrammarT, class ContextT>
struct ExpressionTypeAnalyzer {
  typedef NodeT node_t;
  typedef GrammarT grammar_t;
  typedef ContextT context_t;

  context_t const& context_;

  explicit ExpressionTypeAnalyzer(context_t const& context)
  : context_(context)
  {}

  Type const& getExpressionType(node_t const& node) const {
    try {
      if(node.id == grammar_t::EXPRESSION4 || node.id == grammar_t::EXPRESSION3) {
        return analyzeBinaryExpression(node);
      } else if(node.id == grammar_t::INTEGER) {
        return analyzeInteger(node);
      } else if(node.id == grammar_t::DOUBLE) {
        return analyzeDouble(node);
      }
    } catch(IErrorContext const& errorContext) {
      throw BadExpressionError<node_t>(node, errorContext);
    }

    assert(!"wtf");
  }

private:
  Type const& analyzeBinaryExpression(node_t const& node) const {
    BinaryOp op;
    Type const* ptypeA;
    Type const* ptypeB;

    unsafe([&op, &node] {
        std::string const opStr(node.first, node.last);
        op = binaryOpFromString(opStr);
    }, [&node, &ptypeA, this] {
        node_t const& exprA(node.children[0]);
        ptypeA = &this->getExpressionType(exprA);
    }, [&node, &ptypeB, this] {
        node_t const& exprB(node.children[1]);
        ptypeB = &this->getExpressionType(exprB);
    });

    Type const& typeA(*ptypeA);
    Type const& typeB(*ptypeB);
    Type const* pexprType;
    unsafe([&pexprType, &typeA, &typeB, &op] {
        pexprType = &getBinaryOpType(typeA, typeB, op);
    });

    Type const& exprType(*pexprType);

    return exprType;
  }

  Type const& analyzeInteger(node_t const& node) const {
    std::string const str(node.first, node.last);
    try {
      boost::lexical_cast<int>(str);
      Type const& type(*context_.getType("int"));
      return type;
    } catch(boost::bad_lexical_cast& e) {
      throw BadIntegerLiteralError<node_t>(node);
    }
  }

  Type const& analyzeDouble(node_t const& node) const {
    std::string const str(node.first, node.last);
    try {
      boost::lexical_cast<double>(str);
      Type const& type(*context_.getType("double"));
      return type;
    } catch(boost::bad_lexical_cast& e) {
      throw BadIntegerLiteralError<node_t>(node);
    }
  }
};

}

#endif /* TEST_HPP_ */
