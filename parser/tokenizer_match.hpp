/* 
 * File:   tokenizer_match.hpp
 * Author: loki
 *
 * Created on October 18, 2009, 11:16 PM
 */

#ifndef _TOKENIZER_MATCH_HPP
#define	_TOKENIZER_MATCH_HPP

#include <vector>

template<class IterT>
struct Token
{
  typedef IterT iter_t;
  
  iter_t first;
  iter_t last;
  int id;

  Token(iter_t first, iter_t last)
  : first(first), last(last), id(-1)
  {}
};

template<class IterT>
struct TokenMatchValue
{
  typedef IterT iter_t;
  typedef Token<iter_t> token_t;
  typedef std::vector<token_t> tokens_t;

  tokens_t tokens;

  TokenMatchValue()
  : tokens()
  {}

  TokenMatchValue(Token<iter_t> const& token)
  : tokens()
  {    
    tokens.push_back(token);
  }
};

template<class IterT>
struct TokenizerMatchPolicy
{
  typedef IterT iter_t;
  typedef TokenMatchValue<iter_t> match_value_t;
  typedef Match<match_value_t> match_t;

  match_t no_match() const
  {
    return match_t();
  }

  match_t empty_match() const
  {
    return match_t(true);
  }
  
  match_t create_match() const
  {
    return match_t(true);
  }
  
  match_t create_match_token(iter_t first, iter_t last) const
  {
    typedef typename match_value_t::token_t token_t;    
    return match_t(true, token_t(first, last));
  }

  void concat_match(match_t& a, match_t const& b) const
  {
    a.hit = a.hit || b.hit;
    std::copy(b.value.tokens.begin(), b.value.tokens.end(),
              std::back_inserter(a.value.tokens) );
  }

  void group_match(match_t& m, int id) const
  {
    typedef typename match_value_t::tokens_t tokens_t;
    typedef typename tokens_t::iterator iter_t;
    for(iter_t it = m.value.tokens.begin(); it != m.value.tokens.end(); ++it)
    {
      if((*it).id == -1)
      {
        (*it).id = id;
      }
    }
  }
};

template<class ParserT>
struct TokenParser
: public Unary<ParserT, Parser<TokenParser<ParserT> > >
{
  typedef Unary<ParserT, Parser<TokenParser<ParserT> > > base_t;

  TokenParser(ParserT const& a)
  : base_t(a)
  {}

  // token - это basic_match + basic_iterator_policy

  template<class ScannerT>
  typename ScannerT::match_t parse(ScannerT& scan) const
  {
    if(scan.at_end(scan))
    {
      return scan.no_match();
    }

    typedef typename ScannerT::iter_t iter_t;
    typedef BasicIteratorPolicy iterator_policy_t;
    typedef BasicMatchPolicy match_policy_t;
    typedef ScannerPolicy<iterator_policy_t, match_policy_t> scan_policy_t;
    typedef Scanner<iter_t, scan_policy_t> scan_t;
    typedef typename match_policy_t::match_t match_t;

    iterator_policy_t iteratorPolicy;  
    match_policy_t matchPolicy;  
    scan_policy_t scanPolicy(iteratorPolicy, matchPolicy);

    iter_t const orig(scan.first);
    scan_t scanNew(scan.first, scan.last, scanPolicy);
    if(match_t m = this->get().derived().parse(scanNew))
    {      
      return scan.create_match_token(orig, scanNew.first);
    }

    scan.first = orig;
    return scan.no_match();
  }
};

struct TokenParserGen
{
  template<class ParserT>
  TokenParser<ParserT>
  operator[](Parser<ParserT> const& a)
  {
    return TokenParser<ParserT>(a.derived());
  }
};

TokenParserGen token_d;

#endif	/* _TOKENIZER_MATCH_HPP */

