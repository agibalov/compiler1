/* 
 * File:   one_or_more_parser.hpp
 * Author: loki
 *
 * Created on October 18, 2009, 6:02 PM
 */

#ifndef _ONE_OR_MORE_PARSER_HPP
#define	_ONE_OR_MORE_PARSER_HPP

template<class ParserT>
struct OneOrMoreParser
: public Unary<ParserT, Parser<OneOrMoreParser<ParserT> > >
{
  typedef Unary<ParserT, Parser<OneOrMoreParser<ParserT> > > base_t;

  OneOrMoreParser(ParserT const& a)
  : base_t(a)
  {}

  template<class ScannerT>
  typename ScannerT::match_t parse(ScannerT scan) const
  {
    if(scan.at_end(scan))
    {
      return scan.no_match();
    }

    typedef typename ScannerT::match_t match_t;

    match_t m = scan.no_match();
    while(match_t x = this->get().parse(scan))
    {
      scan.concat_match(m, x);
    }
    
    return m;
  }
};

template<class ParserT>
OneOrMoreParser<ParserT>
operator +(Parser<ParserT> const& a)
{
  return OneOrMoreParser<ParserT>(a.derived());
}

#endif	/* _ONE_OR_MORE_PARSER_HPP */

