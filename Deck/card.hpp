#pragma once

#include "cardTypes.hpp"

namespace Deck
{
  class Card
  {
    public:
      Card(const Suite suite, const Rank rank);

      auto Face() const -> Suite;
      auto Value() const -> Rank;
      auto FaceName() const -> std::string_view;
      auto RankName() const -> std::string_view;

    private:
      const Suite m_suite;
      const Rank m_rank;

  };
}