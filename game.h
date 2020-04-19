#pragma once

#include <vector>
#include <memory>

#include "player.h"

class game {
private:
    std::vector<player*> m_players;
public:
    void add_player(player* player);
    size_t play(const bool display = false) const;
};
