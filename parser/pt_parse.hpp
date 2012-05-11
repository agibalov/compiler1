/* 
 * File:   pt_parse.hpp
 * Author: loki
 *
 * Created on October 20, 2009, 9:54 PM
 */

#ifndef _PT_PARSE_HPP
#define	_PT_PARSE_HPP

#include "skipper.hpp"
#include "scanner.hpp"
#include "pt_match.hpp"
#include "parser.hpp"

template<class IterT>
struct PtParseInfo
{
  bool hit;
  int len;

  typedef IterT iter_t;
  typedef typename PtMatch<iter_t>::nodes_t nodes_t;
  nodes_t nodes;

  PtParseInfo(bool hit, int len, nodes_t const& nodes)
  : hit(hit)
  , len(len)
  , nodes(nodes)
  {}
};

template<class IterT, class GrammarT, class SkipperT>
PtParseInfo<IterT>
pt_parse( IterT first, IterT last, GrammarT const& grammar,
          Parser<SkipperT> const& skipper)
{
  typedef SkipperIteratorPolicy<SkipperT> iterator_policy_t;
  typedef PtMatchPolicy<IterT> match_policy_t;
  typedef ScannerPolicy<iterator_policy_t, match_policy_t> scan_policy_t;
  typedef Scanner<IterT, scan_policy_t> scan_t;
  typedef typename GrammarT::template definition<scan_t> gram_def_t;
  typedef typename match_policy_t::match_t match_t;

  iterator_policy_t iteratorAdvancePolicy(skipper);
  match_policy_t matchPolicy;
  scan_policy_t scanPolicy(iteratorAdvancePolicy, matchPolicy);
  scan_t scan(first, last, scanPolicy);
  match_t m = gram_def_t().get().derived().parse(scan);

  return PtParseInfo<IterT>(m.hit, m.len, m.nodes);
}

#endif	/* _PT_PARSE_HPP */

