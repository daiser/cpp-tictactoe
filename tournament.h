#pragma once

#include <map>
#include <ostream>

#include "player.h"

typedef size_t player_key_t;
typedef player* player_val_t;
typedef std::map<player_key_t, player_val_t> player_container_t;
typedef std::pair<player_key_t, player_val_t> player_pair_t;
typedef std::map<size_t, size_t> score_container_t;
typedef std::pair<size_t, size_t> score_item_t;

constexpr size_t TOUR_NOT_ENOUGH_PLAYERS_ERR = 1;

class score {
private:
    mutable score_container_t m_score;
public:
    score();
    void add(player* player);
    void add(const player_pair_t& player);
    template<typename Iter> void add(Iter first, Iter last) {
        while (first != last) {
            add(*first);
            first++;
        }
    }
    void count_tie();
    void count_winner(const size_t player_id);
    void print(std::ostream& os) const;
    size_t get(const size_t player_id) const;
};

class tournament {
private:
    player_container_t m_players;
    const size_t m_games_number;
    const size_t m_board_size;
public:
    tournament(const size_t board_size, const size_t games_number): m_board_size{ board_size }, m_games_number{ games_number }{}
    void add_player(player* player);
    void hold();
};

