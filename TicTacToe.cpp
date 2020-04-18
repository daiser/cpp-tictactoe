// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <random>

#include "tournament.h"
#include "player.h"
#include "stopwatch.h"

int main() {
    tournament tour{ 10, 10000 };

    ai_random_player p1;
    ai_random_player p2;
    ai_random_player p3;
    //ai_random_player p3{ 2 };

    tour.add_player(&p1);
    tour.add_player(&p2);
    tour.add_player(&p3);

    stopwatch sw{ "Main" };
    sw.reset();
    tour.hold();
    sw.print(std::cout);
}