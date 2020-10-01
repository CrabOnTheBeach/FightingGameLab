#include "hero.h"
#include "effect.h"
#include "game.h"
#include <memory>
#include <iostream>
#include <vector>

//Effects and Heroes
class Corruption : public Effect {
    public:
    Corruption() : Effect("Corruption") {
        i = 0;
    }
    void act(Hero& target) override {
        target.get_damage(++i);
        std::cout << target.name() << " got " << i << " damage from corruption\n";
    }
    void decrease() {} //Corruption is infinity effect
    virtual ~Corruption() {};
    private:
    int i;
};

class ShadowBolt : public Effect {
    public:
    ShadowBolt() : Effect("Shadow bolt") {
    }
    void act(Hero& target) override {
        target.get_damage(20);
		std::cout << target.name() << " got 20 damage from shadow bolt\n";
    }
    virtual ~ShadowBolt() {};
};

class Ignite : public Effect {
    public:
    Ignite() : Effect("Ignite") {
    }
    void act(Hero& target) override {
        target.get_damage(15);
		std::cout << target.name() << " got 15 damage from ingite\n";

    }
    virtual ~Ignite() {};
};

class Warlock : public Hero {
    public:
    Warlock(): Hero("Warlock", 70) {} 
    std::unique_ptr<Effect> upper_attack() override {
        return std::make_unique<Corruption>( );
    }
    std::unique_ptr<Effect> middle_attack() override {
        return std::make_unique<ShadowBolt>();
    }
    std::unique_ptr<Effect> lower_attack() override {
        return std::make_unique<Ignite>();
    }
    void get_damage(int a) override {
        hp_ -= a;
    }
    virtual ~Warlock() {};
};

class Stun : public Effect {
    public:
    Stun() : Effect("Stun") {
    }
    void act(Hero& target) override {
        target.lock_attack(0);
        target.lock_attack(1);
        target.lock_attack(2);
		std::cout << target.name() << " got stun\n";

    }
    virtual ~Stun() {};
};

class Poison : public Effect {
    public:
    Poison() : Effect("Poison") {
    }
    void act(Hero& target) override {
       target.get_damage(3);	
	   std::cout << target.name() << " got 3 damage from poison\n";
    }
    virtual ~Poison() {};
};

class Catalyst : public Effect {
    public:
    Catalyst() : Effect("Catalyst") {
    }
    void act(Hero& target) override {
        target.get_damage(15);
        if (target.is_affected("Poison")) {	
			std::cout << target.name() << " got 45 damage from Catalyst\n";
            target.get_damage(30);
		} else  std::cout << target.name() << " got 15 damage Catalyst\n";
    }
};

class Fairy : public Hero {
    public:
    Fairy(): Hero("Fairy", 51) {}
    std::unique_ptr<Effect> upper_attack() override {
        return std::make_unique<Stun>( );
    }
    std::unique_ptr<Effect> middle_attack() override {
        return std::make_unique<Poison>();
    }
    std::unique_ptr<Effect> lower_attack() override {
        return std::make_unique<Catalyst>();
    }
    void get_damage(int a) override {
        hp_ -= a;
    }
    ~Fairy() {};
};

int main() {
    Game game(std::make_unique<Warlock>(), std::make_unique<Fairy>());
    game.play();
    return 0;
}