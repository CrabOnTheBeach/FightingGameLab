#ifndef GAME_H
#define GAME_H

#include "hero.h"

class Game {
    public:
		Game(std::shared_ptr<Hero>, std::shared_ptr<Hero>);
		void play();
    private:
		int choose_attack(int i) const;
	
		std::shared_ptr<Hero> player[2];
};
#endif //GAME_H