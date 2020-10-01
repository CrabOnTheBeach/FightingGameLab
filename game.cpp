#include "game.h"
#include <iostream>

Game::Game(std::shared_ptr<Hero> p1, std::shared_ptr<Hero> p2) {
    player[0] = p1;
    player[1] = p2;
}

int Game::choose_attack(int i) const {
    if (!player[i]->is_attack_availible(0) && !player[i]->is_attack_availible(1) && !player[i]->is_attack_availible(2))
        return -1;
    int j;
    while (std::cin >> j) {
        if (!player[i]->is_attack_availible(j - 1))
            std::cout << "Wrong choose\n" << '\n';
        else 
            break;
    }
    if (player[i]->is_attack_availible(j - 1))
        return j - 1;
    return -1;
}

void Game::play() {
    while (player[0]->hp() > 0 && player[1]->hp() > 0) {
        std::cout << "Player1 hp: " << player[0]->hp() << '\n';
        std::cout << "Player2 hp: " << player[1]->hp() << '\n';
        std::cout << "Player 1 choose attack" << '\n';
        std::cout << "Availible options:" << '\n';
        std::cout << "1. " << player[0]->upper_attack()->name() << '\n';
        std::cout << "2. " << player[0]->middle_attack()->name() << '\n';
        std::cout << "3. " << player[0]->lower_attack()->name() << '\n';
        int c1 = choose_attack(0); //0 is player number
        std::cout << "Player 2 choose attack" << '\n';
        std::cout << "Availible options:" << '\n';
        std::cout << "1. " << player[1]->upper_attack()->name() << '\n';
        std::cout << "2. " << player[1]->middle_attack()->name() << '\n';
        std::cout << "3. " << player[1]->lower_attack()->name() << '\n';
        int c2 = choose_attack(1); //1 is player number
	    //turn off dodge mechanics because it makes gameplay boring
        /*	std::cout << "Player 1 choose dodge" << '\n';
		int d1 = this->choose_attack(0); //dodge
		std::cout << "Player 2 choose dodge" << '\n';
		int d2 = this->choose_attack(1);
		player[0]->set_dodge(d1);
		player[1]->set_dodge(d2); */
        player[0]->add_effect(*	player[1], c2);
		player[1]->	add_effect(*player[0], c1);
        player[0]->act_effects();
        player[1]->act_effects();
    }
    if (player[0]->hp() < 0 && player[1]->hp() < 0)
        std::cout << "Nobody won\n";
    else if (player[0]->hp() < 0)
        std::cout << "Player 2 won\n";
    else
        std::cout << "Player 1 won\n";
}