#pragma once

#include <string>
#include <string_view>

namespace Player
{
  class BasePlayer
  {
    public:
      BasePlayer(const std::string_view name) : m_name(name){}

      virtual auto Name() -> std::string_view const = 0;

    protected:
      const std::string m_name;

  };
}