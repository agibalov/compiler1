/* 
 * File:   pt_match.hpp
 * Author: loki
 *
 * Created on October 20, 2009, 9:54 PM
 */

#ifndef _PT_MATCH_HPP
#define	_PT_MATCH_HPP

#include <vector>

template<class IterT>
struct PtNode
{
  typedef IterT iter_t;
  typedef PtNode<iter_t> node_t;
  typedef std::vector<node_t> nodes_t;

  iter_t first;
  iter_t last;
  int id;
  nodes_t children;

  PtNode(int id, nodes_t const& children)
  : first(), last(), id(id), children(children)
  {}

  PtNode(iter_t first, iter_t last)
  : first(first), last(last), id(-1), children()
  {}
};

template<class IterT>
struct PtMatch
{
  typedef IterT iter_t;
  //typedef TokenizerMatch<iter_t> self_t;
  typedef PtNode<iter_t> node_t;
  typedef typename node_t::nodes_t nodes_t;

  bool hit;
  int len;
  nodes_t nodes;

  PtMatch()
  : hit(false), len(0), nodes()
  {}

  PtMatch(bool hit, int len)
  : hit(hit), len(len), nodes()
  {}

  operator bool() const
  {
    return hit;
  }
};

template<class IterT>
struct PtMatchPolicy
{
  typedef IterT iter_t;
  typedef PtMatch<iter_t> match_t;

  match_t no_match() const
  {
    return match_t();
  }

  match_t empty_match() const
  {
    return match_t(true, 0);
  }

  // with no node
  match_t create_match(int len) const
  {
    return match_t(true, len);
  }

  // with node
  match_t create_match_node(int len, iter_t first) const
  {
    match_t m(true, len);
    typedef typename match_t::node_t node_t;
    m.nodes.push_back( node_t(first, first+len) );
    return m;
  }

  void concat_match(match_t& a, match_t const& b) const
  {
    match_t x(a.hit || b.hit, a.len + b.len);
    a.hit = a.hit || b.hit;
    a.len += b.len;
    std::copy(b.nodes.begin(), b.nodes.end(), std::back_inserter(a.nodes) );
  }

  void group_match(match_t& m, int id) const
  {
    typedef typename match_t::node_t node_t;
    typedef typename match_t::nodes_t nodes_t;
    typedef typename nodes_t::iterator nodes_iter_t;
    for(nodes_iter_t it = m.nodes.begin(); it != m.nodes.end(); ++it)
    {
      node_t& node = *it;
      if(node.id == -1)
      {
        node.id = id;
      }
    }

    bool hasMoreThanOneChild = m.nodes.size() > 1;
    bool hasSingleChildWithOtherId =
      m.nodes.size() == 1 &&
      m.nodes.front().id != id;

    if(hasMoreThanOneChild || hasSingleChildWithOtherId)
    {
      node_t x(id, m.nodes);
      m.nodes.clear();
      m.nodes.push_back(x);
    }
  }
};

template<class ParserT>
struct NodeParser
: public Unary<ParserT, Parser<NodeParser<ParserT> > >
{
  typedef Unary<ParserT, Parser<NodeParser<ParserT> > > base_t;

  NodeParser(ParserT const& a)
  : base_t(a)
  {}

  template<class ScannerT>
  typename ScannerT::match_t parse(ScannerT scan) const
  {
    // switch scanner's match policy to basic match policy
    typedef typename ScannerT::template RebindMatchPolicy<
      BasicMatchPolicy
    >::type new_policy_t;
    new_policy_t newPolicy =
      scan.changeMatchPolicy( BasicMatchPolicy() );

    // switch scanner's policies to new policies
    typedef typename ScannerT::template RebindPolicies<
      new_policy_t
    >::type new_scan_t;
    new_scan_t newScan(scan.first, scan.last, newPolicy);

    // try to scan
    typedef typename new_scan_t::match_t new_match_t;
    if(new_match_t m = this->get().parse(newScan) ) // scan is ok
    {
      return scan.create_match_node(m.len, scan.first);
    }

    return scan.no_match();
  }
};

struct NodeParserGen
{
  template<class ParserT>
  NodeParser<ParserT>
  operator[](Parser<ParserT> const& a)
  {
    return NodeParser<ParserT>(a.derived());
  }
};

NodeParserGen node_d;

#endif	/* _PT_MATCH_HPP */

