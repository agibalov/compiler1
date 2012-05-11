/* 
 * File:   optional_parser.hpp
 * Author: loki
 *
 * Created on November 24, 2009, 12:14 AM
 */

#ifndef _OPTIONAL_PARSER_HPP
#define	_OPTIONAL_PARSER_HPP

#include "parser.hpp"
#include "composite.hpp"

template<class ParserT>
struct OptionalParser
: public Unary<ParserT, Parser<OptionalParser<ParserT> > >
{
  typedef Unary<ParserT, Parser<OptionalParser<ParserT> > > base_t;

  OptionalParser(ParserT const& a)
  : base_t(a)
  {}

  template<class ScannerT>
  typename ScannerT::match_t parse(ScannerT& scan) const
  {
    if(scan.at_end(scan))
    {
      return scan.empty_match();
    }

    typedef typename ScannerT::match_t match_t;

    if(match_t x = this->get().parse(scan))
    {
      return x;
    }

    return scan.empty_match();
  }
};

template<class ParserT>
OptionalParser<ParserT>
operator !(Parser<ParserT> const& a)
{
  return OptionalParser<ParserT>(a.derived());
}

#endif	/* _OPTIONAL_PARSER_HPP */

