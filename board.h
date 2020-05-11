#pragma once

constexpr size_t NO_PLAYER = 0;

#include <ostream>
#include <algorithm>
#include <iostream>

#include "container.h"
#include "move.h"

class rule {
private:
    size_t m_winner{ NO_PLAYER };
public:
    bool __fastcall check_next(const size_t player_id);
    //bool __fastcall check(const size_t* line, const size_t size);
    template<typename TLineIt> bool __fastcall check(TLineIt first, TLineIt last) {
        reset();
        while (first != last) {
            if (!check_next(*first)) return false;
            first++;
        }
        return true;
    }
    void reset() {
        m_winner = NO_PLAYER; // setting to NO_PLAYER=0;
    }
    inline size_t winner() const {
        return m_winner;
    }
};

class board_base {
    friend class ai_random_player;
protected:
    size_t* m_cells;
    board_base(const size_t size): m_size{ size }, m_moves{ size * size }, m_cells{ new size_t[size * size]() } {}
    ~board_base() {
        delete[] m_cells;
    }
    inline size_t* __fastcall at(const size_t col, const size_t row) {
        return &m_cells[row * m_size + col];
    }
public:
    const size_t m_size;
    mutable moves m_moves;
    virtual bool take(const size_t col, const size_t row, const size_t player_id) = 0;
    inline const size_t* __fastcall at(const size_t col, const size_t row) const {
        return &m_cells[row * m_size + col];
    }
};

template <size_t SIZE>
class board: public board_base {
private:
    mutable rule m_rule;
    const size_t* m_last_cell = &m_cells[SIZE * SIZE];
    void check_row(const size_t row) const {
        m_rule.reset();
        for (size_t* cell = const_cast<board*>(this)->at(0, row); cell < cell + SIZE; cell++) {
            if (!m_rule.check_next(*cell)) return;
        }
        throw m_rule.winner();
    }
    void check_col(const size_t col) const {
        m_rule.reset();
        const size_t* last_cell = at(col, SIZE);
        for (size_t* cell = const_cast<board*>(this)->at(col, 0); cell < last_cell; cell += SIZE) {
            if (!m_rule.check_next(*cell)) return;
        }
        throw m_rule.winner();
    }
    void check_diag() const {
        m_rule.reset();
        for (size_t* cell = m_cells; cell < m_last_cell; cell += (SIZE + 1)) {
            if (!m_rule.check_next(*cell)) return;
        }
        throw m_rule.winner();
    }
    void check_inv_diag() const {
        m_rule.reset();
        for (size_t* cell = m_cells + (SIZE - 1); cell < m_last_cell; cell += (SIZE - 1)) {
            if (!m_rule.check_next(*cell)) return;
        }
        throw m_rule.winner();
    }
    size_t m_moves_made = 0;
public:
    board():board_base(SIZE) {}
    bool take(const size_t col, const size_t row, const size_t player_id) override {
        size_t* cell = at(col, row);
        if (*cell != NO_PLAYER) return false;
        *cell = player_id;
        m_moves_made++;

        check_col(col);
        check_row(row);
        if (col == row) {
            check_diag();
            check_inv_diag();
        }
        return true;
    }
    size_t moves_left() const {
        return m_moves.m_max_size-m_moves_made;
    }
    void print(std::ostream& to) const {
        size_t* cell = m_cells;
        for (size_t row = 0; row < SIZE; row++) {
            for (size_t col = 0; col < SIZE; col++) {
                to << *(cell++);
            }
            to << std::endl;
        }
    }
};

