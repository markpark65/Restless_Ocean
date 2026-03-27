#pragma once
enum class EventType {
	Start,			//게임시작(플레이어생성)
	DamageDealt,	//공격(피해입힘
	DamageTaken,	//방어(피해입음
	Death,			//사망
	Kill,			//처치
	Move,			//지역 이동,actor구역에서 target구역으로 이동
	LevelUp,		//레벨업
	ObtainItem,		//actor가 아이템 획득
	UseItem,		//아이템 사용
	Return			//육지로 복귀
};
