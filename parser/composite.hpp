/* 
 * File:   composite.hpp
 * Author: loki
 *
 * Created on October 3, 2009, 9:45 PM
 */

#ifndef _COMPOSITE_HPP
#define	_COMPOSITE_HPP

template<class ParserT, class BaseT>
struct Unary
: public BaseT
{
  typedef BaseT base_t;
  typedef typename ParserT::embed_t parser_t;

  parser_t p;

  Unary(parser_t const& p)
  : base_t()
  , p(p)
  {}

  parser_t get() const
  {
    return p;
  }
};

template<class AParserT, class BParserT, class BaseT>
struct Binary
: public BaseT
{
  typedef BaseT base_t;
  typedef typename AParserT::embed_t aparser_t;
  typedef typename BParserT::embed_t bparser_t;

  aparser_t a;
  bparser_t b;

  Binary(aparser_t const& a, bparser_t const& b)
  : base_t()
  , a(a), b(b)
  {}

  aparser_t left() const
  {
    return a;
  }

  bparser_t right() const
  {
    return b;
  }
};

#endif	/* _COMPOSITE_HPP */

