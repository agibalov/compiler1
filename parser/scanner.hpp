/* 
 * File:   scanner.hpp
 * Author: loki
 *
 * Created on October 2, 2009, 11:53 PM
 */

#ifndef _SCANNER_HPP
#define	_SCANNER_HPP

struct BasicIteratorPolicy
{
  template<class ScannerT>
  void advance(ScannerT const& scan) const
  {
    ++scan.first;
  }

  template<class ScannerT>
  bool at_end(ScannerT const& scan) const
  {
    return scan.first == scan.last;
  }
};

template<class IteratorPolicyT, class MatchPolicyT>
struct ScannerPolicy
: public IteratorPolicyT
, public MatchPolicyT
{
  typedef IteratorPolicyT iterator_policy_t;
  typedef MatchPolicyT match_policy_t;

  ScannerPolicy(iterator_policy_t const& iteratorPolicy = iterator_policy_t(),
                match_policy_t const& matchPolicy = match_policy_t() )
  : iterator_policy_t(iteratorPolicy)
  , match_policy_t(matchPolicy)
  {}

  // iterator policy manipulation
  template<class NewIterPolicyT>
  struct RebindIterPolicy
  {
    typedef ScannerPolicy<NewIterPolicyT, match_policy_t> type;
  };
  
  template<class NewIterPolicyT>
  typename RebindIterPolicy<NewIterPolicyT>::type
  changeIterPolicy(NewIterPolicyT const& newIterPolicy)
  {
    typename RebindIterPolicy<NewIterPolicyT>::type
      newPolicies(newIterPolicy, *this);
    return newPolicies;
  }

  // match policy manipulation
  template<class NewMatchPolicyT>
  struct RebindMatchPolicy
  {
    typedef ScannerPolicy<iterator_policy_t, NewMatchPolicyT> type;
  };

  template<class NewMatchPolicyT>
  typename RebindMatchPolicy<NewMatchPolicyT>::type
  changeMatchPolicy(NewMatchPolicyT const& newMatchPolicy)
  {
    typename RebindMatchPolicy<NewMatchPolicyT>::type
      newPolicies(*this, newMatchPolicy);
    return newPolicies;
  }
};

template<class IterT, class ScannerPolicyT>
struct Scanner
: public ScannerPolicyT
{
  typedef IterT iter_t;
  typedef ScannerPolicyT scanner_policy_t;
  typedef typename std::iterator_traits<iter_t>::value_type value_t;  
  typedef typename scanner_policy_t::iterator_policy_t iterator_policy_t;
  typedef typename scanner_policy_t::match_policy_t match_policy_t;
  typedef typename match_policy_t::match_t match_t;

  iter_t& first;
  iter_t const last;
 
  Scanner(iter_t& first, iter_t last,
          scanner_policy_t const& scannerPolicy = scanner_policy_t())
  : scanner_policy_t(scannerPolicy)
  , first(first)
  , last(last)
  {    
    at_end(*this);
  }
  
  value_t operator *() const
  {    
    return *first;
  }
  
  // 1. advance сдвигает только на 1 символ + skip
  // 2. advance в явном виде вызывают только примитивные парсеры

  void advance()
  {    
    iterator_policy_t::advance(*this);    
  }

  template<class NewPoliciesT>
  struct RebindPolicies
  {    
    typedef Scanner<iter_t, NewPoliciesT> type;
  };

  template<class NewPoliciesT>
  RebindPolicies<NewPoliciesT>
  changePolicies(NewPoliciesT const& newPolicies)
  {    
    typedef typename RebindPolicies<NewPoliciesT>::type new_scan_t;
    return new_scan_t(first, last, newPolicies);
  }  
};

#endif	/* _SCANNER_HPP */

