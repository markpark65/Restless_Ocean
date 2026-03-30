#include "Skill.h"
#include "Player.h"
#include "Monster.h"

Skill::Skill(std::string n, int cost) : name(n), batteryCost(cost) {}
Skill::~Skill() {}

TripleDamageSkill::TripleDamageSkill() : Skill("파워 스트라이크", 20) {}
BindSkill::BindSkill() : Skill("그물 속박", 20) {}
CounterSkill::CounterSkill() :Skill("크로스 카운터", 20) {}

void TripleDamageSkill::execute(Player* player, Monster* target) {
	if (!player || !target) return;

	int enhancedDamage = player->getAttack() * 3;
	std::cout << "[스킬] " << name << " 발동! (배터리 20% 소모)" << std::endl;
	std::cout << "강력한 일격이 " << target->getName() << " 에게 " << enhancedDamage << "의 피해를 입힙니다!" << std::endl;
	target->takeDamage(enhancedDamage);

}
void BindSkill::execute(Player* player, Monster* target) {
	if (!player || !target) return;

	// 몬스터 속도 감소
	int currentMonsterSpeed = target->getSpeed();
	int reducedSpeed = currentMonsterSpeed / 2;

	target->setSpeed(reducedSpeed);
	std::cout << "[스킬] " << name << " 발동!! (배터리 20% 소모)" << std::endl;
	std::cout << target->getName() << "의 움직임이 둔해졌습니다! (속도: " << currentMonsterSpeed << " -> " << reducedSpeed << ")" << std::endl;

}
void CounterSkill::execute(Player* player, Monster* target) {
	if (!player || !target) return;

	if (player->getSpeed() > target->getSpeed()) {
		int counterDamage = target->getAttack() + player->getAttack();

		std::cout << "[스킬] " << name << " 발동! (배터리 20% 소모)" << std::endl;
		std::cout << "적의 공격을 읽고 카운터를 날립니다!" << std::endl;
		std::cout << "데미지 계산: [적 ATK " << target->getAttack()
			<< "] + [내 ATK " << player->getAttack() << "]" << std::endl;

		target->takeDamage(counterDamage);
	}
	else {
		std::cout << "적의 속도가 너무 빠릅니다! 카운터에 실패했습니다..... 역습이 허용됐습니다" << std::endl;
		//실패 시 체력을 깍음
		player->takeDamage(20);
	}
}
