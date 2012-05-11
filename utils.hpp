/* 
 * File:   utils.hpp
 * Author: loki
 *
 * Created on November 20, 2009, 11:54 AM
 */

#ifndef _UTILS_HPP
#define	_UTILS_HPP

#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>

std::string readEntireFile(std::string const& file) {
  std::ifstream f(file.c_str(), std::ios::in | std::ios::binary);
  if(!f.is_open()) {
    throw std::runtime_error("can't open file");
  }

  f.seekg(0, std::ios::end);
  std::size_t fileSize = f.tellg();
  f.seekg(0, std::ios::beg);

  std::vector<char> buff;
  buff.reserve(fileSize);
  f.read(&buff[0], fileSize);  

  return std::string(&buff[0], &buff[fileSize]);
}

#endif	/* _UTILS_HPP */

