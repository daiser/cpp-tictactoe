#include "move.h"

move::move(const size_t col, const size_t row): m_col{ col }, m_row{ row } {}

move_score::move_score(const size_t col, const size_t row, const size_t score) : move(col, row), m_score{ score } {}
move_score::move_score(const move& move, const size_t score) : move(move.m_col, move.m_row), m_score{ score }{}