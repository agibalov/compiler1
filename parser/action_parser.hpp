/* 
 * File:   action_parser.hpp
 * Author: loki
 *
 * Created on October 3, 2009, 10:52 PM
 */

#ifndef _ACTION_PARSER_HPP
#define	_ACTION_PARSER_HPP

#include "parser.hpp"
#include "composite.hpp"

template<class ParserT, class ActionT>
struct ActionParser
: public Unary<ParserT, Parser<ActionParser<ParserT, ActionT> > >
{
  typedef Unary<ParserT, Parser<ActionParser<ParserT, ActionT> > > base_t;
  typedef ActionT action_t;

  action_t action;

  ActionParser(ParserT const& a, action_t const& action)
  : base_t(a)
  , action(action)
  {}

  template<class ScannerT>
  typename ScannerT::match_t parse(ScannerT scan) const
  {
    typename ScannerT::match_t m = this->get().parse(scan);
    if(m.hit)
    {
      action(scan.first, scan.first + m.len);
    }

    return m;
  }
};

#endif	/* _ACTION_PARSER_HPP */

