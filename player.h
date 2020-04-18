#pragma once

#include "board.h"
#include <random>

static size_t _next_id = 0;

class player {
protected:
    player();
    player(const player& other): m_id{ other.m_id } {}
public:
    const size_t m_id = ++_next_id;
    virtual void take_turn(board& board) const = 0;
    bool operator ==(const player& other);
};

class ai_random_player: public player {
public:
    ai_random_player();
    void take_turn(board& board) const;
};
