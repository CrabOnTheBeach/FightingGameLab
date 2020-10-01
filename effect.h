#ifndef EFFECT_H
#define EFFECT_H

#include "hero.h"
#include <string>

class Hero;

class Effect {
	public:
		Effect(const std::string&, int turns = 1);
		void tick(Hero&);
		virtual void act(Hero&) = 0;
		virtual void decrease();
		int turns_left();
		const std::string& name();
		virtual ~Effect();
	private:
		std::string name_;
		int turns_left_;
};

#endif //EFFECT_H