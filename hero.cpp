#include "hero.h"
#include <iostream>

Hero::Hero(const std::string& name, int hp)
    :name_(name), hp_(hp) {
	dodge_ = -1;
    is_attack_availible_[0] = is_attack_availible_[1] = is_attack_availible_[2] = 1;
}
	
const std::string& Hero::name() const {
    return name_;
} 

void Hero::act_effects() {
    is_attack_availible_[0] = is_attack_availible_[1] = is_attack_availible_[2] = 1;
    for (unsigned i = 0; i < effects.size(); i++) {
        effects.at(i)->tick(*this);
        if (effects.at(i)->turns_left() < 1) {
            effects.erase(effects.begin() + i);
            i--;
        }
    }
	dodge_ = -1;
}

void Hero::add_effect(Hero& source, attack_type_t type) {
	//this = target
	if (type == dodge_) {
		std::cout << "Hero " << name_ << " dodged attack!'\n";
		return;
	}
    switch (type) {
        case UPPER:
		    effects.push_back((source.upper_attack()));
            break;
        case MIDDLE:
		    effects.push_back(std::move(source.middle_attack()));
            break;
        case LOWER:
		    effects.push_back(std::move(source.lower_attack()));
            break;
    }
}

void Hero::lock_attack(attack_type_t type) {
    is_attack_availible_[type] = 0;
}

int Hero::hp() const {
    return hp_;
}

bool Hero::is_affected(const std::string& name) const {
    for (unsigned i = 0; i < effects.size(); i++) {
        if (effects.at(i)->name() == name)
            return 1;
    }
    return 0;
}

bool Hero::is_attack_availible(attack_type_t type) const {
    if (type != UPPER && type != MIDDLE && type != LOWER)
        return 0;
    return is_attack_availible_[type];
}

void Hero::set_dodge(attack_type_t type) {
	dodge_ = type;
}

Hero::~Hero() {
}