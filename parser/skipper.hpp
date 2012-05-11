/* 
 * File:   skipper_iterator_advance_policy.hpp
 * Author: loki
 *
 * Created on October 4, 2009, 1:43 AM
 */

#ifndef _SKIPPER_ITERATOR_ADVANCE_POLICY_HPP
#define	_SKIPPER_ITERATOR_ADVANCE_POLICY_HPP

#include "parser.hpp"
#include "scanner.hpp"
#include "match.hpp"
#include "scanner.hpp"
#include "composite.hpp"

template<class SkipperT>
struct SkipperIteratorPolicy
{
  typedef typename SkipperT::embed_t skipper_t;
  skipper_t skipper;
    
  SkipperIteratorPolicy(Parser<SkipperT> const& skipper)
  : skipper(skipper.derived())  
  {}
  
  // проблема заключается в том, что смещении scan.first на
  // какое-то расстоние, match остаётся неисправленным
  // это означает что "a b" имеет длину 2 вместо 3.
  // из-за этого match.len тоже каким-то образом нужно корректировать   

  template<class ScannerT>
  void advance(ScannerT const& scan)
  {
    ++scan.first;
    at_end(scan);
  }

  template<class ScannerT>
  bool at_end(ScannerT const& scan) const
  {
    skip(scan);
    return scan.first == scan.last;
  }

  template<class ScannerT>
  void skip(ScannerT const& scan) const
  {    
    typedef BasicIteratorPolicy iterator_policy_t;
    typedef BasicMatchPolicy match_policy_t;
    typedef ScannerPolicy<iterator_policy_t, match_policy_t> scan_policy_t;
    typedef Scanner<typename ScannerT::iter_t, scan_policy_t> scan_t;
    typedef typename match_policy_t::match_t match_t;

    iterator_policy_t iteratorPolicy;
    match_policy_t matchPolicy;
    scan_policy_t scanPolicy(iteratorPolicy, matchPolicy);    
    scan_t skipScan(scan.first, scan.last, scanPolicy);
    /*match_t m =*/ skipper.parse(skipScan);
  }
};

template<class ParserT>
struct NoSkipParser
: public Unary<ParserT, Parser<NoSkipParser<ParserT> > >
{
  typedef Unary<ParserT, Parser<NoSkipParser<ParserT> > > base_t;

  NoSkipParser(ParserT const& a)
  : base_t(a)
  {}

  template<class ScannerT>
  typename ScannerT::match_t parse(ScannerT& scan) const
  {
    typename ScannerT::iter_t orig(scan.first);
    
    // switch scanner's iterator policy to no-skip iterator policy
    typedef typename ScannerT::template RebindIterPolicy<
      BasicIteratorPolicy
    >::type new_policy_t;
    new_policy_t newPolicy =
      scan.changeIterPolicy( BasicIteratorPolicy() );

    // switch scanner's policies to new policies
    typedef typename ScannerT::template RebindPolicies<
      new_policy_t
    >::type new_scan_t;    
    new_scan_t newScan(scan.first, scan.last, newPolicy);

    // try to scan
    typedef typename new_scan_t::match_t new_match_t;
    if(new_match_t m = this->get().parse(newScan) ) // scan is ok
    {
      return scan.create_match();
    }

    scan.first = orig;
    return scan.no_match();
  }
};

struct NoSkipParserGen
{
  template<class ParserT>
  NoSkipParser<ParserT>
  operator[](Parser<ParserT> const& a)
  {
    return NoSkipParser<ParserT>(a.derived());
  }
};

NoSkipParserGen no_skip_d;

#endif	/* _SKIPPER_ITERATOR_ADVANCE_POLICY_HPP */

