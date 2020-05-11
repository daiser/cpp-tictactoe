#include "board.h"

bool rule::check_next(const size_t player_id) {
    if (player_id == NO_PLAYER) return false;
    if (m_winner == NO_PLAYER) {
        m_winner = player_id;
        return true;
    }
    if (m_winner != player_id) return false;
    return true;
}
