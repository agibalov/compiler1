/* 
 * File:   single_char_parser.hpp
 * Author: loki
 *
 * Created on October 3, 2009, 10:13 PM
 */

#ifndef _SINGLE_CHAR_PARSER_HPP
#define	_SINGLE_CHAR_PARSER_HPP

#include "parser.hpp"

template<class TesterT>
struct SingleCharParser
: public Parser<SingleCharParser<TesterT> >
{
  typedef TesterT tester_t;
  TesterT tester;

  SingleCharParser(tester_t const& tester)
  : tester(tester)
  {}

  template<class ScannerT>
  typename ScannerT::match_t parse(ScannerT& scan) const
  {
    if(scan.at_end(scan))
    {
      return scan.no_match();
    }

    typename ScannerT::iter_t const tmp(scan.first);
    typedef typename ScannerT::match_t match_t;
    
    if(tester.test(*scan))
    {
      scan.advance();      
      return scan.create_match();
    }

    scan.first = tmp;
    return scan.no_match();
  }
};

template<class CharT>
struct ConcreteCharTester
{
  typedef CharT char_t;
  char_t value;

  ConcreteCharTester(char_t value)
  : value(value)
  {}

  bool test(char_t other) const
  {
    return other == value;
  }
};

template<class CharT>
struct RangeCharTester
{
  typedef CharT char_t;
  char_t lo;
  char_t hi;

  RangeCharTester(char_t lo, char_t hi)
  : lo(lo), hi(hi)
  {}

  bool test(char_t other) const
  {
    return other >= lo && other <= hi;
  }
};

template<class CharT>
SingleCharParser<ConcreteCharTester<CharT> > ch_p(CharT value)
{
  typedef CharT char_t;
  typedef ConcreteCharTester<char_t> tester_t;
  tester_t tester(value);
  typedef SingleCharParser<tester_t> parser_t;
  parser_t parser(tester);
  return parser;
}

template<class CharT>
SingleCharParser<RangeCharTester<CharT> > range_p(CharT lo, CharT hi)
{
  typedef CharT char_t;
  typedef RangeCharTester<char_t> tester_t;
  tester_t tester(lo, hi);
  typedef SingleCharParser<tester_t> parser_t;
  parser_t parser(tester);
  return parser;
}

#endif	/* _SINGLE_CHAR_PARSER_HPP */

