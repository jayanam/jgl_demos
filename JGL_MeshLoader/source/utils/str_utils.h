#pragma once

#include "pch.h"

namespace nutils
{
  std::vector<uint32_t> tokenize(const std::string& line, const char token)
  {
    std::vector<uint32_t> result;
    
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, token))
      if (!item.empty())
        result.push_back(std::stoi(item));

    return result;
  }
}
