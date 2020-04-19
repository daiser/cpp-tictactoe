#include "move.h"

move::move(const size_t col, const size_t row): m_col{ col }, m_row{ row } {}



move_score::move_score(const size_t col, const size_t row, const size_t score) : move(col, row), m_score{ score } {}
move_score::move_score(const move& move, const size_t score) : move(move.m_col, move.m_row), m_score{ score }{}
move_score::move_score() : move_score(0, 0, 0) {}


moves::moves(const size_t size) : m_max_size{ size }, m_moves{ new move_score[size] }{}
moves::~moves() {
    delete[] m_moves;
}
void moves::reset() {
    reset(m_max_size + 1);
}
void moves::reset(const size_t new_min_score) {
    m_current = 0;
    m_min_score = new_min_score;
}
const move_score* moves::get(const size_t index) const {
    return &m_moves[index];
}
void __fastcall moves::commit() {
    move_score* current = &m_moves[m_current];
    if (current->m_score > m_min_score) return;
    if (current->m_score < m_min_score) {
        std::memcpy(m_moves, current, sizeof(move_score));
        reset(m_moves->m_score);
    }
    m_current++;
}