#pragma once
enum class EventType {
	Start,			//게임시작(플레이어생성)
	DamageDealt,	//A가 B에게 value만큼 공격
	DamageTaken,	//A가 B에게 value만큼 피해받음
	Death,			//사망 A가 B에게 사망
	Kill,			//처치 A가 B를 처치
	Move,			//지역 이동, A구역에서 B구역으로 이동
	LevelUp,		//A가 n로 레벨업
	ObtainItem,		//A가 X아이템 획득
	UseItem,		//A가 X아이템 사용
	ObtainGold,		//A가 X아이템 획득
	UseGold,		//A가 X아이템 사용
	Return			//육지로 복귀
};
