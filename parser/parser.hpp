/* 
 * File:   parser.hpp
 * Author: loki
 *
 * Created on October 3, 2009, 9:46 PM
 */

#ifndef _PARSER_HPP
#define	_PARSER_HPP

template<class ParserT, class ActionT>
struct ActionParser;

template<class ParserT>
struct Parser
{
  typedef ParserT derived_t;
  typedef ParserT embed_t;

  derived_t const& derived() const
  {
    return *static_cast<derived_t const*>(this);
  }

  template<class ActionT>
  ActionParser<derived_t, ActionT> operator [](ActionT const& action)
  {
    return ActionParser<derived_t, ActionT>(derived(), action);
  }
};

#endif	/* _PARSER_HPP */

