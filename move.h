#pragma once
class move {
public:
    const size_t m_col;
    const size_t m_row;
    move(const size_t col, const size_t row);
};

class move_score: public move {
public:
    const size_t m_score;
    move_score(const size_t col, const size_t row, const size_t score);
    move_score(const move& move, const size_t score);
};
