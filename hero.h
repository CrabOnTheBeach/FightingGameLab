#ifndef HERO_H
#define HERO_H

#include "effect.h"
#include <vector>
#include <memory>
#include <string>

typedef int attack_type_t;

class Effect;

class Hero {
  public:
		enum {UPPER, MIDDLE, LOWER, ATTACK_COUNT = 3};
		Hero(const std::string&, int hp);
		virtual std::unique_ptr<Effect> upper_attack() = 0;
		virtual std::unique_ptr<Effect> middle_attack() = 0;
		virtual std::unique_ptr<Effect> lower_attack() = 0;
		virtual void get_damage(int) = 0;
		virtual ~Hero();
		const std::string& name() const;
		void act_effects();
		void add_effect(Hero& h, attack_type_t type);
		void lock_attack(attack_type_t type);
		int hp() const;
		bool is_affected(const std::string&) const;
		bool is_attack_availible(attack_type_t type) const;
		void set_dodge(attack_type_t type); 
	private:
		int dodge_;
		std::string name_;
		std::vector<std::unique_ptr<Effect> > effects;
		bool is_attack_availible_[ATTACK_COUNT];
	protected:
		int hp_;
};

#endif //HERO_H