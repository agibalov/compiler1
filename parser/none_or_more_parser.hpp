/* 
 * File:   none_or_more_parser.hpp
 * Author: loki
 *
 * Created on October 18, 2009, 5:44 PM
 */

#ifndef _NONE_OR_MORE_PARSER_HPP
#define	_NONE_OR_MORE_PARSER_HPP

#include "parser.hpp"
#include "composite.hpp"

template<class ParserT>
struct NoneOrMoreParser
: public Unary<ParserT, Parser<NoneOrMoreParser<ParserT> > >
{
  typedef Unary<ParserT, Parser<NoneOrMoreParser<ParserT> > > base_t;

  NoneOrMoreParser(ParserT const& a)
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
    
    match_t m = scan.empty_match();
    while(match_t x = this->get().parse(scan))
    {      
      scan.concat_match(m, x);      
    }

    return m;
  }
};

template<class ParserT>
NoneOrMoreParser<ParserT>
operator *(Parser<ParserT> const& a)
{
  return NoneOrMoreParser<ParserT>(a.derived());
}

#endif	/* _NONE_OR_MORE_PARSER_HPP */

