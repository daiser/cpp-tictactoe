#pragma once

#include <vector>

#include "board.h"
#include "move.h"

static size_t _next_id = 0;

class player {
protected:
    player();
    player(const player& other): m_id{ other.m_id } {}
public:
    const size_t m_id = ++_next_id;
    virtual void take_turn(board_base& board) const = 0;
    bool operator ==(const player& other);
};

class ai_random_player: public player {
private:
    mutable std::vector<move> m_available_moves;
public:
    ai_random_player();
    void take_turn(board_base& board) const;
};
