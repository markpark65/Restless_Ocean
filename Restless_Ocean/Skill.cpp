#include "Skill.h"
#include "Player.h"
#include "Monster.h"

Skill::Skill(std::string n) : name(n) {}
Skill::~Skill() {}

TripleDamageSkill::TripleDamageSkill() : Skill("파워 스트라이크") {}
BindSkill::BindSkill() : Skill("그물 속박") {}

void TripleDamageSkill::execute(Player* player, Monster* target) {
	if (!player || !target) return;

	int enhancedDamage = player->getAttack() * 3;
	std::cout << "[스킬] " << name << " 발동!" << std::endl;
	std::cout << "강력한 일격이 " << target->getName() << " 에게 " << enhancedDamage << "의 피해를 입힙니다!" << std::endl;
	target->takeDamage(enhancedDamage);

}
void BindSkill::execute(Player* player, Monster* target) {
	if (!player || !target) return;

	// 몬스터 속도 감소
	int currentMonsterSpeed = target->getSpeed();
	int reducedSpeed = currentMonsterSpeed / 2;

	target->setSpeed(reducedSpeed);
	std::cout << "[스킬] " << name << " 발동!!" << std::endl;
	std::cout << target->getName() << "의 움직임이 둔해졌습니다! (속도: " << currentMonsterSpeed << " -> " << reducedSpeed << ")" << std::endl;

}
