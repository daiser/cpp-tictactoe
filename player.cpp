#include "player.h"

#include <vector>
#include <random>

#include "move.h"

player::player():m_id{ ++_next_id } {}
bool player::operator==(const player& other) {
    return m_id == other.m_id;
}


ai_random_player::ai_random_player() {}

static std::random_device rd;
static std::mt19937 gen{ rd() };

void ai_random_player::take_turn(board& board) const {
    std::vector<move> available_moves;
    for (size_t col = 0; col < board.size(); col++) {
        for (size_t row = 0; row < board.size(); row++) {
            if (board.look_at(col, row) == NO_PLAYER) available_moves.push_back(move{ col,row });
        }
    }
    std::uniform_int_distribution<> dis(0, available_moves.size()-1);
    size_t move_id = dis(gen);
    move move = available_moves[move_id];
    board.take(move.m_col, move.m_row, m_id);
}