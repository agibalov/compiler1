/* 
 * File:   match.hpp
 * Author: loki
 *
 * Created on October 3, 2009, 12:12 AM
 */

#ifndef _MATCH_HPP
#define	_MATCH_HPP

struct null_t {};

// для Match, по идее, вообще кроме hit/operator bool ничего не нужно,
// т.к. len теперь не используется (вместо len используются ссылки)
// засчёт ссылок получается прозрачный skip, а грозит это только тем,
// что внутри парсеров нужно следить за адекватностью состояния scan.first

// !!! нужно переписать tokenizer match с использованием Match и его ValueT

template<class ValueT>
struct Match
{
  typedef ValueT value_t;

  bool hit;
  value_t value;

  Match()
  : hit(false), value()
  {}

  Match(bool hit, value_t const& value = value_t())
  : hit(hit), value(value)
  {}

  operator bool() const
  {
    return hit;
  }
};

//typedef Match<null_t> BasicMatch;

struct BasicMatchPolicy
{
  typedef Match<null_t> match_t;

  match_t no_match() const
  {
    return match_t(false);
  }

  match_t empty_match() const
  {
    return match_t(true);
  }
  
  match_t create_match() const
  {
    return match_t(true);
  }

  void concat_match(match_t& a, match_t const& b) const
  {
    a.hit = a.hit || b.hit;    
  }

  void group_match(match_t& m, int id) const
  {
    // do nothing
  }
};

#endif	/* _MATCH_HPP */

