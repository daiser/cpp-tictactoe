#pragma once

#include <memory>
#include "container.h"

class move {
public:
    size_t m_col;
    size_t m_row;
    move(const size_t col, const size_t row);
};

class move_score: public move {
public:
    size_t m_score;
    move_score(const size_t col, const size_t row, const size_t score);
    move_score(const move& move, const size_t score);
    move_score();
};

constexpr size_t MOVES_OVERFLOW_ERR = 1;
constexpr size_t MOVES_EMPTY_ERR = 2;

class moves {
private:
    move_score* m_moves;
    size_t m_min_score = 0;
    void reset(const size_t new_min_score);
public:
    const size_t m_max_size;
    size_t m_current = 0;
    moves(const size_t size);
    ~moves();
    inline const move_score* get(const size_t index) const {
        return &m_moves[index];
    }
    inline move_score* __fastcall begin() {
        return &m_moves[m_current];
    }
    void __fastcall commit();
    void reset();
};
