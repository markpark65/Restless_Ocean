#include <iostream>
#include "Monster.h"
#include "MonsterFactory.h"
#include "Player.h"
#include "Skill.h"
#include "BattleSystem.h"
#include "GameLogger.h"
#include "GameManager.h"
#include "Item.h"
#include "Inventory.h"
#include "GlobalVal.h"

void printFootballFish() {

	std::cout <<
		R"(
   ,_,...   ____             
,,,.   ,/`''   ''`-..        
'..|  ,/  (_)       '\.      
      '...            `_     
  |--.__/'     _ ''`\ `.--''`.
   \_           '_  /        |
    `\_           '`,-"`._ ,J'
      '-..._____,,-'     '''  
        )"
		<< '\n';
}

void printViperFish() {
	std::cout <<
		R"(
               __                 
           ,,/'                 
         ,','                   
    _...''/_.............._,.-,/
   \(_)                  _.  ,' 
\.__>   ,_____ _____..--''`-.,\ 
 ''''-'''      \`-.           ''
                `,'                       
)" << '\n';
}

void printGiantSquid() {
	cout << R"(
    _,..                 .+-------...
   /'  ,|              __.`--''     .
   | .''           _,-''           /|
   , |.           |'             ,'.'
    \ '"___--__.--'''`\       ,,._ / 
     '',  ,_,       . |   __,-'   '  
  ,,Y'',/'' _   , _(■)''-''          
 /' ,Y' ,,-' ,, ['' '  _,..          
|,,'',,-',_.''|  '---'''  |          
''...._--'     `,_     _,-'          
                 '''''''               
    )" << '\n';
}
int main()
{
	//콘솔 인코딩 UFT-8 with BOM으로 변경하여 깨짐 방지.
	//system("chcp 65001");
	//system("cls");
  //게임 실행
	GameManager::getInstance().run();

	return 0;
	
}
