#include "effect.h"

Effect::Effect(const std::string& name, int turns)
    : name_(name), turns_left_(turns) {
}

const std::string& Effect::name() {
    return name_;
} 

void Effect::tick(Hero& h) {
    act(h);
    decrease();
}

void Effect::decrease() {
    --turns_left_;
}

int Effect::turns_left() {
    return turns_left_;
}

Effect::~Effect() {
}