#include "board.h"

void rule::reset() {
    m_winner = NO_PLAYER;
}
bool rule::set_winner(const size_t new_winner) {
    m_winner = new_winner;
    return m_winner != NO_PLAYER;
}
bool rule::check_next(const size_t player_id) {
    if (player_id == NO_PLAYER) return set_winner(NO_PLAYER);
    if (m_winner == NO_PLAYER) return set_winner(player_id);
    if (m_winner != player_id) return set_winner(NO_PLAYER);
    return true;
}
//bool rule::check(const size_t* line, const size_t size) {
//    reset();
//    for (size_t i = 0; i < size; i++) {
//        if (!check_next(line[i])) return false;
//    }
//    return true;
//}
size_t rule::winner() const {
    return m_winner;
}
