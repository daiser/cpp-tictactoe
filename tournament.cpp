#include "tournament.h"

#include <iostream>

#include "game.h"

void tournament::add_player(player* player) {
    m_players.insert(player_pair_t{ player->m_id, player });
}

void tournament::hold() {
    if (m_players.size() < 2) throw TOUR_NOT_ENOUGH_PLAYERS_ERR;
    score score;
    score.add(m_players.begin(), m_players.end());

    for (size_t game_no = 0; game_no < m_games_number; game_no++) {
        game game{};

        for (auto& p : m_players) {
            game.add_player(p.second);
        }

        size_t winner = game.play(m_board_size);
        score.count_winner(winner);
    }
    score.print(std::cout);
}


score::score() {
    m_score.insert(std::pair<size_t, size_t>{NO_PLAYER, 0});
}
void score::add(const player_pair_t& player) {
    m_score.insert(score_item_t{ player.first, 0 });
}
void score::add(player* player) {
    score_item_t pair{ player->m_id, 0 };
    m_score.insert(pair);
}
void score::count_winner(const size_t player_id) {
    m_score[player_id] += 1;
}
void score::count_tie() {
    count_winner(NO_PLAYER);
}
void score::print(std::ostream& os) const {
    os << "== SCOREBOARD ==" << std::endl;
    for (const score_item_t& item : m_score) {
        if (item.first == NO_PLAYER) {
            os << "TIE: ";
        }
        else {
            os << "Player #" << item.first << ": ";
        }
        os << item.second << std::endl;
    }
}
size_t score::get(const size_t player_id) const {
    return m_score[player_id];
}
