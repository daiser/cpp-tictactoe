#include "game.h"

#include <iostream>
#include <ctime>
#include <random>

#include "board.h"

#ifdef _DEBUG
#define BOARD_SIZE 5
#else
#define BOARD_SIZE 10
#endif

void game::add_player(player* p) {
    m_players.push_back(p);
}

size_t game::play(const bool display) const {
    size_t total_players{ m_players.size() };
    if (total_players < 2) throw "not enough players";

    size_t turn{ 0 };
    board<BOARD_SIZE> board;

    while (true) {
        if (board.moves_left() == 0) {
            //std::cout << "It's a tie!" << std::endl;
            break;
        }
        //std::cout << "Turn #" << turn + 1 << std::endl;
        try {
            m_players[turn % total_players]->take_turn(board);
        }
        catch (const size_t& winner) {
            return winner;
        }

        if (display) {
            board.print(std::cout);
            std::cout << std::endl;
        }

        turn++;
    }
    return NO_PLAYER;
}