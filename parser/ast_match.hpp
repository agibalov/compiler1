/* 
 * File:   ast_match.hpp
 * Author: loki
 *
 * Created on October 21, 2009, 9:54 PM
 */

#ifndef _AST_MATCH_HPP
#define	_AST_MATCH_HPP

#include <vector>
#include "match.hpp"

template<class IterT>
struct AstNode
{
  typedef IterT iter_t;
  typedef AstNode<iter_t> node_t;
  typedef std::vector<node_t> nodes_t;

  iter_t first;
  iter_t last;
  int id;
  nodes_t children;
  bool isRoot;

  AstNode(int id, nodes_t const& children, bool isRoot)
  : first(), last(), id(id), children(children), isRoot(isRoot)
  {}

  AstNode(iter_t first, iter_t last, bool isRoot)
  : first(first), last(last), id(-1), children(), isRoot(isRoot)
  {}
};

template<class IterT>
struct AstMatchValue
{
  typedef IterT iter_t;
  typedef AstMatchValue<iter_t> self_t;
  typedef AstNode<iter_t> node_t;
  typedef typename node_t::nodes_t nodes_t;
  
  nodes_t nodes;

  AstMatchValue()
  : nodes()
  {}  
};

template<class IterT>
struct AstMatchPolicy
{
  typedef IterT iter_t;
  typedef AstMatchValue<iter_t> ast_match_value_t;
  typedef Match<ast_match_value_t> match_t;

  match_t no_match() const
  {
    return match_t();
  }

  match_t empty_match() const
  {
    return match_t(true);
  }
  
  match_t create_match() const
  {
    return match_t(true);
  }
  
  match_t create_match(iter_t first, iter_t last, bool root) const
  {
    match_t m(true);
    typedef typename match_t::value_t::node_t node_t;
    node_t n(first, last, root);
    m.value.nodes.push_back(n);
    return m;
  }

  void concat_match(match_t& a, match_t/* const*/& b) const
  {
    a.hit = a.hit || b.hit;

    // L+R or R+R
    if(!b.value.nodes.empty() && b.value.nodes.front().isRoot)
    {
      // find the deepest one root node
      typename match_t::value_t::node_t* deepest = &b.value.nodes.front();
      while(!deepest->children.empty())
      {
        if(!deepest->children.front().isRoot)
        {
          break;
        }

        deepest = &deepest->children.front();
      }

      // insert A in the beginning of the deepest
      deepest->children.insert(
        deepest->children.begin(), 
        a.value.nodes.begin(),
        a.value.nodes.end()
      );
      std::swap(a.value.nodes, b.value.nodes);
    }
    // R+L
    else if(!a.value.nodes.empty() && a.value.nodes.front().isRoot)
    { 
      std::copy(b.value.nodes.begin(), b.value.nodes.end(),
                std::back_inserter(a.value.nodes.front().children) );
    }
    // L+L
    else
    {
      std::copy(
        b.value.nodes.begin(),
        b.value.nodes.end(),
        std::back_inserter(a.value.nodes)
      );
    }    
  }

  void group_match(match_t& m, int id) const
  {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // нужно доказать, что если в матче несколько узлов либо ID самого первого
    // установлен,
    // то ID могут быть не установлены только у узлов самого верхнего уровня,
    // т.е. глубже лезть не нужно
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // если же узел 1 и его ID не установлен,
    // то нужно лезть в глубину
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // нужно рассмотреть когда такие ситуации происходят,
    // возможно сразу всё станет понятно
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // если есть всего 1 узел и он без id, это означает, что
    // была брутальная рекурсия и там есть несколько узлов,
    // пораждённых одним и тем же правилом - прописываем им ID
    if(m.value.nodes.size() == 1 && m.value.nodes.front().id == -1)
    {
      typename match_t::value_t::nodes_t* p = &m.value.nodes;
      while(!p->empty() && p->front().id == -1)
      {
        p->front().id = id;
        p = &p->front().children;
      }

      // вот это не понимаю
      // почему root становится не root?
      m.value.nodes.front().isRoot = false;
    }
    // у match есть несколько узлов, среди них могут быть и
    // leaf и root. нужно создать новый узел и запихать эти узлы в него.
    // у нового узла будет id, соответствующее этому правилу.
    else
    {
      typedef typename match_t::value_t::node_t node_t;
      typedef typename match_t::value_t::nodes_t nodes_t;
      typedef typename nodes_t::iterator iter_t;
      for(iter_t it = m.value.nodes.begin(); it != m.value.nodes.end(); ++it)
      {
        node_t& node = *it;
        if(node.id == -1)
        {
          node.id = id;
        }
      }

      const bool DO_COLLAPSE_AST = true;

      if(m.value.nodes.size() > 1 || !DO_COLLAPSE_AST)
      {
        // вот это не понимаю
        // почему делаем не root?
        node_t x(id, m.value.nodes, false);
        m.value.nodes.clear();
        m.value.nodes.push_back(x);
      }
    }
  }
};

template<class ParserT, bool ROOT>
struct AstNodeParser
: public Unary<ParserT, Parser<AstNodeParser<ParserT, ROOT> > >
{
  typedef Unary<ParserT, Parser<AstNodeParser<ParserT, ROOT> > > base_t;

  AstNodeParser(ParserT const& a)
  : base_t(a)
  {}

  template<class ScannerT>
  typename ScannerT::match_t parse(ScannerT scan) const
  {
    if(scan.at_end(scan))
    {
      return scan.no_match();
    }

    typedef typename ScannerT::iter_t iter_t;
    typedef BasicIteratorPolicy iterator_policy_t;
    typedef BasicMatchPolicy match_policy_t;
    typedef ScannerPolicy<iterator_policy_t, match_policy_t> scan_policy_t;
    typedef Scanner<iter_t, scan_policy_t> scan_t;
    typedef typename match_policy_t::match_t match_t;

    iterator_policy_t iteratorPolicy;  
    match_policy_t matchPolicy;  
    scan_policy_t scanPolicy(iteratorPolicy, matchPolicy);

    iter_t const orig(scan.first);
    scan_t scanNew(scan.first, scan.last, scanPolicy);
    if(match_t m = this->get().derived().parse(scanNew))
    {      
      return scan.create_match(orig, scanNew.first, ROOT);
    }

    scan.first = orig;
    return scan.no_match();
  }
};

template<bool ROOT>
struct AstNodeParserGen
{
  template<class ParserT>
  AstNodeParser<ParserT, ROOT>
  operator [](Parser<ParserT> const& a)
  {
    return AstNodeParser<ParserT, ROOT>(a.derived() );
  }
};

AstNodeParserGen<false> leaf_node_d;
AstNodeParserGen<true> root_node_d;

#endif	/* _AST_MATCH_HPP */

