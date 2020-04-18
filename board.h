#pragma once

constexpr size_t NO_PLAYER = 0;

#include <ostream>

class board {
private:
    size_t* m_cells;
    const size_t m_size;
    size_t* _at(const size_t col, const size_t row);
    void check_row(const size_t row) const;
    void check_col(const size_t col) const;
    void check_diag() const;
    void check_diag2() const;
public:
    board(const size_t size);
    ~board();
    bool take(const size_t col, const size_t row, const size_t player_id);
    size_t look_at(const size_t col, const size_t row) const;
    size_t size() const;
    size_t moves_left() const;
    size_t winner() const;
    void print(std::ostream& to) const;
};

