/* 
 * File:   rule.hpp
 * Author: loki
 *
 * Created on October 3, 2009, 11:25 PM
 */

#ifndef _RULE_HPP
#define	_RULE_HPP

#include <boost/scoped_ptr.hpp>
#include "parser.hpp"
#include "scanner.hpp"

template<class ScannerT>
struct AbstractParser
{
  virtual ~AbstractParser() {}
  virtual typename ScannerT::match_t parse(ScannerT scan) const = 0;
};

template<class ParserT, class ScannerT>
struct ConcreteParser
: public AbstractParser<ScannerT>
{
  typename ParserT::embed_t p;

	explicit ConcreteParser(Parser<ParserT> const& p)
  : p(p.derived())
	{}

  typename ScannerT::match_t parse(ScannerT scan) const
	{
		return p.parse(scan);
	}
};

template<int ID, class ScannerT>
struct Rule
: public Parser<Rule<ID, ScannerT> >
{
  typedef Rule const& embed_t; // override parser::embed_t !!!

  Rule()
  : par()
	{}

	template<class ParserT>
	Rule(Parser<ParserT> const& p)
	: par(new ConcreteParser<ParserT, ScannerT>(p.derived()) )
	{}

	template<class ParserT>
	Rule& operator =(Parser<ParserT> const& p)
	{
		par.reset(new ConcreteParser<ParserT, ScannerT>(p.derived()) );
		return *this;
	}

  Rule(Rule const& r)
  : par(new ConcreteParser<Rule, ScannerT>(r))
	{}  
  
  typename ScannerT::match_t parse(ScannerT& scan) const
	{
    typename ScannerT::match_t m = par->parse(scan);
    scan.group_match(m, ID);
	  return m;
	}

private:
  typedef const AbstractParser<ScannerT> abstract_parser_t;
	boost::scoped_ptr<abstract_parser_t> par;
};

#endif	/* _RULE_HPP */

