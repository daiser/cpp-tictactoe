#include "board.h"

class _rule {
private:
    size_t m_winner{ NO_PLAYER };
public:
    bool __fastcall check(const size_t current) {
        if (current == NO_PLAYER) return false;
        if (m_winner == NO_PLAYER) {
            m_winner = current;
        }
        if (current != m_winner) {
            m_winner = NO_PLAYER;
            return false;
        }
        return true;
    }
    size_t winner() const {
        return m_winner;
    }
};

board::board(const size_t size): m_cells{ new size_t[size * size]() }, m_size{ size }{}
board::~board() {
    delete[] m_cells;
}

size_t board::size() const {
    return m_size;
}

size_t* board::_at(const size_t col, const size_t row) {
    return &m_cells[(row % m_size) * m_size + (col % m_size)];
}

size_t board::look_at(const size_t col, const size_t row) const {
    return *const_cast<board*>(this)->_at(col, row);
}

bool board::take(const size_t col, const size_t row, const size_t player_id) {
    size_t* current = _at(col, row);
    if (*current != 0) return false;
    *current = player_id;
    return true;
}

size_t board::moves_left() const {
    size_t moves_left = 0;
    for (size_t i = 0; i < m_size * m_size; i++) {
        if (m_cells[i] == 0) moves_left++;
    }
    return moves_left;
}

void board::check_col(const size_t col) const {
    _rule rule;
    for (size_t row = 0; row < m_size; row++) {
        if (!rule.check(*const_cast<board*>(this)->_at(col, row))) return;
    }
    throw rule.winner();
}

void board::check_row(const size_t row) const {
    _rule rule;
    for (size_t col = 0; col < m_size; col++) {
        if (!rule.check(*const_cast<board*>(this)->_at(col, row))) return;
    }
    throw rule.winner();
}

void board::check_diag() const {
    _rule rule;
    for (size_t i = 0; i < m_size; i++) {
        if (!rule.check(*const_cast<board*>(this)->_at(i, i))) return;
    }
    throw rule.winner();
}

void board::check_diag2() const {
    _rule rule;
    for (size_t i = 0; i < m_size; i++) {
        if (!rule.check(*const_cast<board*>(this)->_at(i, m_size - i - 1))) return;
    }
    throw rule.winner();
}

size_t board::winner() const {
    try {
        for (size_t i = 0; i < m_size; i++) {
            check_col(i);
            check_row(i);
        }
        check_diag();
        check_diag2();
        return NO_PLAYER;
    }
    catch (const size_t& winner_id) {
        return winner_id;
    }
}

void board::print(std::ostream& to) const {
    for (size_t row = 0; row < m_size; row++) {
        for (size_t col = 0; col < m_size; col++) {
            to << look_at(col, row);
        }
        to << std::endl;
    }
}