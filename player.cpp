#include "player.h"

#include <random>

player::player():m_id{ ++_next_id } {}
bool player::operator==(const player& other) {
    return m_id == other.m_id;
}


ai_random_player::ai_random_player() {}

static std::random_device rd;
static std::mt19937 gen{ rd() };

void ai_random_player::take_turn(board_base& board) const {
    board.m_moves.reset();
    const size_t* b = board.m_cells;
    for (size_t row = 0; row < board.m_size; row++) {
        for (size_t col = 0; col < board.m_size; col++) {
            if (*b == NO_PLAYER) {
                move_score* move = board.m_moves.begin();
                move->m_col = col;
                move->m_row = row;
                move->m_score = 1;
                board.m_moves.commit();
            }
            b = b + 1;
        }
    }
    std::uniform_int_distribution<> dis(0, board.m_moves.m_current - 1);
    size_t move_id = dis(gen);
    const move_score* move = board.m_moves.get(move_id);
    board.take(move->m_col, move->m_row, m_id);
}