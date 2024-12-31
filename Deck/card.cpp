#include "card.hpp"

namespace Deck
{
    Card::Card(const Suite suite, const Rank rank) : m_suite(suite), m_rank(rank){}

    auto Card::Face() -> Suite const
    {
      return m_suite;
    }

    auto Card::Value() -> Rank const
    {
      return m_rank;
    }

    auto Card::FaceName() -> std::string_view const
    {
      return ToString(m_suite);
    }

    auto Card::RankName() -> std::string_view const
    {
      return ToString(m_rank);
    }
}