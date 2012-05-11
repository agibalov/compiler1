/* 
 * File:   sequence_parser.hpp
 * Author: loki
 *
 * Created on October 3, 2009, 10:30 PM
 */

#ifndef _SEQUENCE_PARSER_HPP
#define	_SEQUENCE_PARSER_HPP

#include "parser.hpp"
#include "composite.hpp"

template<class AParserT, class BParserT>
struct SequenceParser
: public Binary<
  AParserT, BParserT,
  Parser<SequenceParser<AParserT, BParserT> >
>
{
  typedef Binary<
    AParserT, BParserT,
    Parser<SequenceParser<AParserT, BParserT> >
  > base_t;

  SequenceParser(AParserT const& a, BParserT const& b)
  : base_t(a, b)
  {}

  template<class ScannerT>
  typename ScannerT::match_t parse(ScannerT& scan) const
  {
    if(scan.at_end(scan))
    {
      return scan.no_match();
    }

    typename ScannerT::iter_t tmp(scan.first);
    typedef typename ScannerT::match_t match_t;

    if(match_t ma = this->left().parse(scan))
    {
      if(match_t mb = this->right().parse(scan))
      {        
        scan.concat_match(ma, mb);
        return ma;
      }
    }

    scan.first = tmp;
    return scan.no_match();
  }
};

template<class AParserT, class BParserT>
SequenceParser<AParserT, BParserT>
operator >>(Parser<AParserT> const& a, Parser<BParserT> const& b)
{
  return SequenceParser<AParserT, BParserT>(a.derived(), b.derived());
}

#endif	/* _SEQUENCE_PARSER_HPP */

