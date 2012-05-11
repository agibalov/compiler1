/* 
 * File:   parse.hpp
 * Author: loki
 *
 * Created on October 3, 2009, 12:31 AM
 */

#ifndef _PARSE_HPP
#define	_PARSE_HPP

#include "skipper.hpp"
#include "scanner.hpp"
#include "match.hpp"
#include "parser.hpp"

struct BasicParseInfo
{
  bool hit;
  int len;
  
  BasicParseInfo(bool hit, int len)
  : hit(hit)
  , len(len)
  {}
};

template<class IterT, class GrammarT>
BasicParseInfo basic_parse( IterT first, IterT last,
                            GrammarT const& grammar)
{
  typedef BasicIteratorPolicy iterator_policy_t;
  typedef BasicMatchPolicy match_policy_t;
  typedef ScannerPolicy<iterator_policy_t, match_policy_t> scan_policy_t;
  typedef Scanner<IterT, scan_policy_t> scan_t;
  typedef typename GrammarT::template definition<scan_t> gram_def_t;
  typedef typename match_policy_t::match_t match_t;

  iterator_policy_t iteratorPolicy;  
  match_policy_t matchPolicy;  
  scan_policy_t scanPolicy(iteratorPolicy, matchPolicy);  

  IterT end(first);
  scan_t scan(end, last, scanPolicy);
  match_t m = gram_def_t().get().derived().parse(scan);

  return BasicParseInfo(m.hit, end - first);
}

template<class IterT, class GrammarT, class SkipperT>
BasicParseInfo basic_parse( IterT first, IterT last,
                            GrammarT const& grammar,
                            Parser<SkipperT> const& skipper)
{
  typedef SkipperIteratorPolicy<SkipperT> iterator_policy_t;
  typedef BasicMatchPolicy match_policy_t;
  typedef ScannerPolicy<iterator_policy_t, match_policy_t> scan_policy_t;
  typedef Scanner<IterT, scan_policy_t> scan_t;
  typedef typename GrammarT::template definition<scan_t> gram_def_t;
  typedef typename match_policy_t::match_t match_t;

  iterator_policy_t iteratorPolicy(skipper);
  match_policy_t matchPolicy;
  scan_policy_t scanPolicy(iteratorPolicy, matchPolicy);
  
  IterT end(first);
  scan_t scan(end, last, scanPolicy);
  match_t m = gram_def_t().get().derived().parse(scan);

  return BasicParseInfo(m.hit, end - first);
}

#endif	/* _PARSE_HPP */

