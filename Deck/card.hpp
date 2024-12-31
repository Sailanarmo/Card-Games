#pragma once

#include "cardTypes.hpp"

namespace Deck
{
  class Card
  {
    public:
      Card(const Suite suite, const Rank rank);

      auto Face() -> Suite const;
      auto Value() -> Rank const;
      auto FaceName() -> std::string_view const;
      auto RankName() -> std::string_view const;

    private:
      const Suite m_suite;
      const Rank m_rank;

  };
}