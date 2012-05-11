/* 
 * File:   grammar.hpp
 * Author: loki
 *
 * Created on February 10, 2010, 7:28 PM
 */

#ifndef _GRAMMAR_HPP
#define	_GRAMMAR_HPP

#include "parser/single_char_parser.hpp"
#include "parser/sequence_parser.hpp"
#include "parser/none_or_more_parser.hpp"
#include "parser/one_or_more_parser.hpp"
#include "parser/action_parser.hpp"
#include "parser/alternative_parser.hpp"
#include "parser/optional_parser.hpp"
#include "parser/rule.hpp"

struct MyGrammar {
  enum {
    NAME,
    INTEGER,
    DOUBLE,
    EXPRESSION1,
    EXPRESSION2,
    EXPRESSION3,
    EXPRESSION4,
    EXPRESSION5,
    VARIABLE_DEF,
    STATEMENT,
    BLOCK,
    PROGRAM
  };

  template<class ScannerT>
  struct definition {
    Rule<NAME, ScannerT> name;
    Rule<INTEGER, ScannerT> integer;
    Rule<DOUBLE, ScannerT> doubl;
    Rule<EXPRESSION1, ScannerT> expression1;
    Rule<EXPRESSION2, ScannerT> expression2;
    Rule<EXPRESSION3, ScannerT> expression3;
    Rule<EXPRESSION4, ScannerT> expression4;
    Rule<EXPRESSION5, ScannerT> expression5;
    Rule<VARIABLE_DEF, ScannerT> var_def;
    Rule<STATEMENT, ScannerT> stmt;
    Rule<BLOCK, ScannerT> block;
    Rule<PROGRAM, ScannerT> program;

    definition() {
      name =
        leaf_node_d[ +range_p('a', 'z') ];

      integer =
        leaf_node_d[ +range_p('0', '9') ];

      doubl =
        leaf_node_d[ +range_p('0', '9') >> ch_p('.') >> *range_p('0', '9') ]
        || leaf_node_d[ *range_p('0', '9') >> ch_p('.') >> +range_p('0', '9') ];

      expression1 =
        integer || doubl || name
        || ( ch_p('(') >> expression5 >> ch_p(')') )
        || ( root_node_d[ch_p('-')] >> expression2) // expression2, потому что дальше идут сложные выражения
        || ( root_node_d[ch_p('+')] >> expression2);

      expression2 =
        expression1 ||
        (ch_p('(') >> root_node_d[ +range_p('a', 'z') ] >> ch_p(')') >> expression2); // type cast

      expression3 =
        expression2
        >> *(root_node_d[ch_p('*') | ch_p('/')] >> expression2);

      expression4 =
        expression3
        >> *(root_node_d[ch_p('+') | ch_p('-')] >> expression3);

      expression5 =
        expression4
        >> *(root_node_d[ch_p('=')] >> expression5);

      var_def =
        name >> name >> root_node_d[ch_p('=')] >> expression5;

      stmt =
        (var_def || expression5) >> ch_p(';');

      block =
        root_node_d[ch_p('{')] >>
          +(block || stmt)
        >> ch_p('}');

      program =
        block;
    }

    Rule<PROGRAM, ScannerT> const& get() const {
      return program;
    }
  };
};

#endif	/* _GRAMMAR_HPP */

