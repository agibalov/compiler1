/* 
 * File:   tokenizer_parse.hpp
 * Author: loki
 *
 * Created on October 18, 2009, 11:22 PM
 */

#ifndef _TOKENIZER_PARSE_HPP
#define	_TOKENIZER_PARSE_HPP

#include "skipper.hpp"
#include "scanner.hpp"
#include "tokenizer_match.hpp"
#include "parser.hpp"

template<class IterT>
struct TokenizerParseInfo
{
  bool hit;
  int len;

  typedef IterT iter_t;
  typedef typename TokenMatchValue<iter_t>::tokens_t tokens_t;
  tokens_t tokens;

  TokenizerParseInfo(bool hit, int len, tokens_t const& tokens)
  : hit(hit)
  , len(len)
  , tokens(tokens)
  {}
};

template<class IterT, class GrammarT, class SkipperT>
TokenizerParseInfo<IterT>
tokenizer_parse(IterT first, IterT last,
                GrammarT const& grammar,
                Parser<SkipperT> const& skipper)
{
  typedef SkipperIteratorPolicy<SkipperT> iterator_policy_t;
  typedef TokenizerMatchPolicy<IterT> match_policy_t;
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

  return TokenizerParseInfo<IterT>(m.hit, end - first, m.value.tokens);
}

#endif	/* _TOKENIZER_PARSE_HPP */

