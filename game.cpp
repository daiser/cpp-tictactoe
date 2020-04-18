#include "game.h"

#include <iostream>
#include <ctime>
#include <random>

#include "board.h"


void game::add_player(player* p) {
    m_players.push_back(p);
}

size_t game::play(const size_t board_size) const {
    if (board_size == 0) throw "invalid board size";
    size_t total_players{ m_players.size() };
    if (total_players < 2) throw "not enough players";

    size_t turn{ 0 };
    board board{ board_size };
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    while (true) {
        if (board.moves_left() == 0) {
            //std::cout << "It's a tie!" << std::endl;
            break;
        }
        //std::cout << "Turn #" << turn + 1 << std::endl;
        m_players[turn % total_players]->take_turn(board);

        //board.print(std::cout);
        //std::cout << std::endl;

        size_t winner = board.winner();
        if (winner != NO_PLAYER) {
            return winner;
        }
        turn++;
    }
    return NO_PLAYER;
}