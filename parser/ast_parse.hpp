/* 
 * File:   ast_parse.hpp
 * Author: loki
 *
 * Created on October 21, 2009, 9:54 PM
 */

#ifndef _AST_PARSE_HPP
#define	_AST_PARSE_HPP

#include "skipper.hpp"
#include "scanner.hpp"
#include "ast_match.hpp"
#include "parser.hpp"

template<class IterT>
struct AstParseInfo
{
  typedef IterT iter_t;
  typedef typename AstMatchValue<iter_t>::node_t node_t;
  typedef typename AstMatchValue<iter_t>::nodes_t nodes_t;

  bool hit;
  int len;
  nodes_t nodes;

  AstParseInfo(bool hit, int len, nodes_t const& nodes)
  : hit(hit)
  , len(len)
  , nodes(nodes)
  {}
};

template<class IterT, class GrammarT, class SkipperT>
AstParseInfo<IterT> ast_parse(IterT first, IterT last,
                              GrammarT const& grammar,
                              Parser<SkipperT> const& skipper)
{
  typedef SkipperIteratorPolicy<SkipperT> iterator_policy_t;
  typedef AstMatchPolicy<IterT> match_policy_t;
  typedef ScannerPolicy<iterator_policy_t, match_policy_t> scan_policy_t;
  typedef Scanner<IterT, scan_policy_t> scan_t;
  typedef typename GrammarT::template definition<scan_t> gram_def_t;
  typedef typename match_policy_t::match_t match_t;

  iterator_policy_t iteratorAdvancePolicy(skipper);
  match_policy_t matchPolicy;
  scan_policy_t scanPolicy(iteratorAdvancePolicy, matchPolicy);

  IterT end(first);
  scan_t scan(end, last, scanPolicy);
  match_t m = gram_def_t().get().derived().parse(scan);  

  return AstParseInfo<IterT>(m.hit, end - first, m.value.nodes);
}

#endif	/* _AST_PARSE_HPP */

