/* 
 * File:   alternative_parser.hpp
 * Author: loki
 *
 * Created on October 23, 2009, 12:05 AM
 */

#ifndef _ALTERNATIVE_PARSER_HPP
#define	_ALTERNATIVE_PARSER_HPP

#include "parser.hpp"
#include "composite.hpp"

template<class AParserT, class BParserT, class AltImplT>
struct AlternativeParser
: public Binary<
  AParserT, BParserT,
  Parser<AlternativeParser<AParserT, BParserT, AltImplT> >
>
, public AltImplT
{
  typedef AltImplT impl_t;

  typedef Binary<
    AParserT, BParserT,
    Parser<AlternativeParser<AParserT, BParserT, AltImplT> >
  > base_t;

  AlternativeParser(
    AParserT const& a,
    BParserT const& b,
    impl_t const& impl = impl_t() )
  : base_t(a, b)
  , impl_t(impl)
  {}

  template<class ScannerT>
  typename ScannerT::match_t parse(ScannerT& scan) const
  {
    return do_parse(this->left(), this->right(), scan);
  }
};

struct SimpleAltImpl
{
  template<class AParserT, class BParserT, class ScannerT>
  typename ScannerT::match_t
  do_parse(AParserT const& a, BParserT const& b, ScannerT& scan) const
  {
    if(scan.at_end(scan))
    {
      return scan.no_match();
    }

    typename ScannerT::iter_t const tmp(scan.first);
    typedef typename ScannerT::match_t match_t;
    
    match_t ma = a.parse(scan);
    if(ma)
    {
      return ma;
    }

    scan.first = tmp;
    match_t mb = b.parse(scan);
    if(mb)
    {
      return mb;
    }

    scan.first = tmp;
    return scan.no_match();    
  }
};

struct LongestAltImpl
{
  template<class AParserT, class BParserT, class ScannerT>
  typename ScannerT::match_t 
  do_parse(AParserT const& a, BParserT const& b, ScannerT& scan) const
  {
    if(scan.at_end(scan))
    {
      return scan.no_match();
    }

    typedef typename ScannerT::iter_t iter_t;
    typedef typename ScannerT::match_t match_t;

    iter_t const tmp(scan.first);

    match_t ma = a.parse(scan);
    iter_t ita(scan.first);
    int maLen = ita - tmp;

    scan.first = tmp;
    match_t mb = b.parse(scan);
    iter_t itb(scan.first);
    int mbLen = itb - tmp;

    if(ma && mb)
    {
      if(maLen >= mbLen)
      {
        scan.first = ita;
        return ma;
      }
      else
      {
        scan.first = itb;
        return mb;
      }      
    }
    else if(ma)
    {
      scan.first = ita;
      return ma;
    }
    else if(mb)
    {
      scan.first = itb;
      return mb;
    }
    else
    {
      scan.first = tmp;
      return scan.no_match();
    }
  }
};

template<class AParserT, class BParserT>
AlternativeParser<AParserT, BParserT, SimpleAltImpl>
operator |(Parser<AParserT> const& a, Parser<BParserT> const& b)
{
  typedef AlternativeParser<AParserT, BParserT, SimpleAltImpl> alt_parser_t;
  return alt_parser_t(a.derived(), b.derived() );
}

template<class AParserT, class BParserT>
AlternativeParser<AParserT, BParserT, LongestAltImpl>
operator ||(Parser<AParserT> const& a, Parser<BParserT> const& b)
{
  typedef AlternativeParser<AParserT, BParserT, LongestAltImpl> alt_parser_t;
  return alt_parser_t(a.derived(), b.derived() );
}

#endif	/* _ALTERNATIVE_PARSER_HPP */

