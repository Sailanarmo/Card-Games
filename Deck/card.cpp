#include "card.hpp"

namespace Deck
{
    Card::Card(const Suite suite, const Rank rank) : m_suite(suite), m_rank(rank){}

    auto Card::Face() const -> Suite
    {
      return m_suite;
    }

    auto Card::Value() const -> Rank
    {
      return m_rank;
    }

    auto Card::FaceName() const -> std::string_view
    {
      return ToString(m_suite);
    }

    auto Card::RankName() const -> std::string_view
    {
      return ToString(m_rank);
    }
}