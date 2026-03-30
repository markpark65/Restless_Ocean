#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include <regex>
#include "Player.h"
#include "Monster.h"

enum class KeyInput {
	up,
	down,
	enter,
	quit,
	none
};

static int getCommand() {
	if (_kbhit()) {
		return _getch();
	}
	return -1;
}

static KeyInput getInput() {
	KeyInput keyInput = KeyInput::none;
	do {
		//입력값은 아스키 코드.
		int input = getCommand();
		if (input == 224) {
			int inputDirection = getCommand();
			if (inputDirection == 72) {
				keyInput = KeyInput::up;
			}
			else if (inputDirection == 80) {
				keyInput = KeyInput::down;
			}
		}
		else if (input == 13) {
			keyInput = KeyInput::enter;
		}
		else if (input == 81 or input == 113) {
			keyInput = KeyInput::quit;
		}
	} while (keyInput == KeyInput::none);
	return keyInput;
}

struct SceneData
{
	const Player* player = nullptr;
	std::string Title;
	std::vector<std::string> sceneImage;
	const Monster* monster = nullptr;
	std::string description;
	std::vector<std::string> options;
	int selectedIndex = 0;
};

enum class Color
{
	Default,
	Red,
	Green,
	Yellow,
	Cyan,
	White
};

struct Cell
{
	char ch = ' ';
	Color fg = Color::Default;
};



class ConsoleRenderer
{
private:
	int width;
	int height;
	std::vector<std::string> buffer;
public:
	ConsoleRenderer(int width, int height)
		: width(width), height(height),
		buffer(height, std::string(width, ' '))
	{
	}

	int OptionSelector(SceneData& scene) {
		while (true)
		{
			render(scene);
			KeyInput keyInput = getInput();
			do {
				//입력값은 아스키 코드.
				int input = getCommand();
				if (input == 224) {
					int inputDirection = getCommand();
					if (inputDirection == 72) {
						keyInput = KeyInput::up;
					}
					else if (inputDirection == 80) {
						keyInput = KeyInput::down;
					}
				}
				else if (input == 13) {
					keyInput = KeyInput::enter;
				}
				else if (input == 81 or input == 113) {
					keyInput = KeyInput::quit;
				}
			} while (keyInput == KeyInput::none);


			if (keyInput == KeyInput::up)
			{
				--scene.selectedIndex;
				if (scene.selectedIndex < 0)
				{
					scene.selectedIndex = static_cast<int>(scene.options.size()) - 1;
				}
			}
			else if (keyInput == KeyInput::down)
			{
				++scene.selectedIndex;
				if (scene.selectedIndex >= static_cast<int>(scene.options.size()))
				{
					scene.selectedIndex = 0;
				}
			}
			else if (keyInput == KeyInput::enter)
				return scene.selectedIndex;
		}
	}


	//void render(const Player* player, const SceneData& scene)
	void render(const SceneData& scene)
	{
		clear();
		drawScenePanel(0, 0, 70, 18, scene);
		drawStatusPanel(70, 0, 30, 18, scene.player);
		drawDescriptionPanel(0, 18, 70, 10, scene.description);
		drawChoicePanel(70, 18, 30, 10, scene.options, scene.selectedIndex);
		present();
	}


private:
	void clear(char fill = ' ')
	{
		for (auto& row : buffer)
		{
			row.assign(width, fill);
		}
	}

	void present() const
	{
		std::cout << "\x1b[2J";
		std::cout << "\x1b[H";

		for (const auto& row : buffer)
		{
			std::cout << row << '\n';
		}
	}

	void putChar(int x, int y, char ch)
	{
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			buffer[y][x] = ch;
		}
	}

	void drawText(int x, int y, const std::string& text)
	{
		if (y < 0 || y >= height) return;

		for (int i = 0; i < static_cast<int>(text.size()); ++i)
		{
			int px = x + i;
			if (px >= 0 && px < width)
			{
				buffer[y][px] = text[i];
			}
		}
	}

	void drawHorizontalLine(int x, int y, int length, char ch = '-')
	{
		if (y < 0 || y >= height) return;

		for (int i = 0; i < length; ++i)
		{
			int px = x + i;
			if (px >= 0 && px < width)
			{
				buffer[y][px] = ch;
			}
		}
	}

	void drawVerticalLine(int x, int y, int length, char ch = '|')
	{
		if (x < 0 || x >= width) return;

		for (int i = 0; i < length; ++i)
		{
			int py = y + i;
			if (py >= 0 && py < height)
			{
				buffer[py][x] = ch;
			}
		}
	}

	void drawBox(int x, int y, int boxWidth, int boxHeight)
	{
		if (boxWidth < 2 || boxHeight < 2) return;

		drawHorizontalLine(x, y, boxWidth, '-');
		drawHorizontalLine(x, y + boxHeight - 1, boxWidth, '-');
		drawVerticalLine(x, y, boxHeight, '|');
		drawVerticalLine(x + boxWidth - 1, y, boxHeight, '|');

		putChar(x, y, '+');
		putChar(x + boxWidth - 1, y, '+');
		putChar(x, y + boxHeight - 1, '+');
		putChar(x + boxWidth - 1, y + boxHeight - 1, '+');
	}

	void drawParagraph(int x, int y, int maxWidth, const std::string& text)
	{
		if (maxWidth <= 0) return;

		std::vector<std::string> words = splitWords(text);

		int currentY = y;
		std::string line;

		for (const auto& word : words)
		{
			if (line.empty())
			{
				line = word;
			}
			else if (static_cast<int>(line.size() + 1 + word.size()) <= maxWidth and word != "\n")
			{
				line += ' ';
				line += word;
			}
			else
			{
				drawText(x, currentY, line);
				++currentY;
				line = word;

				if (word == "\n") { line = ""; }
			}
		}

		if (!line.empty())
		{
			drawText(x, currentY, line);
		}
	}

	void drawMenu(int x, int y, const std::vector<std::string>& options, int selectedIndex)
	{
		for (int i = 0; i < static_cast<int>(options.size()); ++i)
		{
			std::string prefix = (i == selectedIndex) ? "> " : "  ";
			drawText(x, y + i, prefix + options[i]);
		}
	}

	std::string makeBar(int current, int maxValue, int barWidth) const
	{
		if (maxValue <= 0)
		{
			return "[" + std::string(barWidth, '.') + "]";
		}

		current = std::clamp(current, 0, maxValue);
		int filled = current * barWidth / maxValue;

		return "[" + std::string(filled, '#') + std::string(barWidth - filled, '.') + "]";
	}

	std::vector<std::string> splitWords(const std::string& text) const
	{
		std::vector<std::string> words;
		std::string current;

		for (char ch : text)
		{
			if (ch == ' ' || ch == '\t')
			{
				if (!current.empty())
				{
					words.push_back(current);
					current.clear();
				}
			}
			else
			{
				current += ch;
			}
		}

		if (!current.empty())
		{
			words.push_back(current);
		}

		return words;
	}

private:
	void drawScenePanel(int x, int y, int w, int h)
	{
		drawBox(x, y, w, h);
		//drawText(x + 2, y + 1, "Scene");
		//drawText(x + 3, y + 5, "asdasasdasdt설명이다");

		//drawText(x + 30, y + 2, "#####################");
		//drawText(x + 30, y + 3, "#                 # #");
		//drawText(x + 30, y + 4, "#                 # #");
		//drawText(x + 30, y + 5, "#                 # #");
		//drawText(x + 30, y + 6, "#                 # #");
		//drawText(x + 30, y + 7, "#                 # #");
		//drawText(x + 30, y + 8, "#                 # #");
		//drawText(x + 30, y + 9, "#                 # #");
		//drawText(x + 30, y + 10, "#             @   # #");
		//drawText(x + 30, y + 11, "#                 # #");
		//drawText(x + 30, y + 12, "#                 # #");
		//drawText(x + 30, y + 13, "#                 # #");
		//drawText(x + 30, y + 14, "#                 # #");
		//drawText(x + 30, y + 15, "#####################");
		//drawText(x + 30, y + 16, "                     @");
		//drawText(x + 30, y + 17, "                      @");
		//drawText(x + 30, y + 18, "                       @");

	}
	
	void drawScenePanel(int x, int y, int w, int h, const SceneData& scene)
	{
		drawBox(x, y, w, h);
		drawText(x + 2, y + 1, scene.Title);

		if (scene.monster != nullptr) {
/*
cout << "\n===============================" << '\n';
cout << "몬스터 이름: " << getName() << '\n';
cout << "출현지  :" << mapToString(getMap()) << '\n';
cout << "등급    :" << getRankName() << '\n';
cout << "HP      :" << getHealth() << '\n';
cout << "ATK     :" << getAttack() << '\n';
cout << "SPEED   :" << getSpeed() << '\n';
cout << "TYPE    :" << typeToString(getMonsterType()) << '\n';
cout << "기본 능력" << getDescription() << '\n';
cout << "===============================" << '\n';
*/
			//몬스터 정보 출력
			drawText(x + 2, y + 7,  "몬스터 이름:"+scene.monster->getName());
			drawText(x + 2, y + 8, "등급       :"+scene.monster->getRankName());
			drawText(x + 2, y + 9, "HP         :"+std::to_string(scene.monster->getHealth()));
			drawText(x + 2, y + 10, "ATK        :"+std::to_string(scene.monster->getAttack()));
			drawText(x + 2, y + 11, "SPEED      :"+std::to_string(scene.monster->getSpeed()));
			drawText(x + 2, y + 12, "TYPE       :" + scene.monster->typeToString(scene.monster->getMonsterType()));
			
			std::string skillstr = scene.monster->getDescription();
			//skillstr = skillstr.replace(	);//regex_replace(skillstr, regex("\n"), "");
			drawParagraph(x + 2, y + 13, w - 4, skillstr);
		}



		for (int i = 0; i < scene.sceneImage.size(); i++) {
			drawText(x + 30, y + i + 2, scene.sceneImage.at(i));
		}
	}

	void drawStatusPanel(int x, int y, int w, int h, const Player* player)
	{
		drawBox(x, y, w, h);
		if (player == nullptr)
			return;
		drawText(x + 2, y + 1, "플레이어 상태");
		drawText(x + 2, y + 2, "Name     :" + player->getName());

		drawText(x + 2, y + 3, "HP       :");
		drawText(x + 12, y + 3, std::to_string(player->getHp()));
		drawText(x + 15, y + 3, "/" + std::to_string(player->getMaxHp()));
		drawText(x + 2, y + 4, makeBar(player->getHp(), player->getMaxHp(), 20));

		drawText(x + 2, y + 5, "oxygen   :");
		drawText(x + 12, y + 5, std::to_string(player->getOxygen()));
		drawText(x + 15, y + 5, "/" + std::to_string(player->getMaxOxygen()));
		drawText(x + 2, y + 6, makeBar(player->getOxygen(), player->getMaxOxygen(), 20));

		drawText(x + 2, y + 7, "battery  :");
		drawText(x + 12, y + 7, std::to_string(player->getBattery()));
		drawText(x + 15, y + 7, "/100");
		drawText(x + 2, y + 8, makeBar(player->getBattery(), 100, 20));

		drawText(x + 2, y + 9, "pressure :");
		drawText(x + 12, y + 9, std::to_string(player->getPressure()));
		drawText(x + 15, y + 9, "/" + std::to_string(player->getMaxPressure()));
		drawText(x + 2, y + 10, makeBar(player->getPressure(), player->getMaxPressure(), 20));


		drawText(x + 2, y + 11, "ATK      :" + std::to_string(player->getAttack()));
		drawText(x + 2, y + 12, "SPEED    :" + std::to_string(player->getSpeed()));

		drawText(x + 2, y + 13, "EXP      :");
		drawText(x + 12, y + 13, std::to_string(player->getExp()));
		drawText(x + 15, y + 13, "/" + std::to_string(player->getMaxExp()));
		drawText(x + 2, y + 14, makeBar(player->getExp(), player->getMaxExp(), 20));

		drawText(x + 2, y + 15, "Gold     :" + std::to_string(player->getGold()));
		drawText(x + 2, y + 16, "Artifact :" + std::to_string(player->getArtifactCount()) + " / 3");
	}

	void drawDescriptionPanel(int x, int y, int w, int h, const std::string& description)
	{
		drawBox(x, y, w, h);
		drawText(x + 2, y + 1, "Description");
		drawParagraph(x + 2, y + 2, w - 4, description);
	}

	void drawChoicePanel(int x, int y, int w, int h,
		const std::vector<std::string>& options,
		int selectedIndex)
	{
		drawBox(x, y, w, h);
		drawText(x + 2, y + 1, "선택지");
		drawMenu(x + 2, y + 2, options, selectedIndex);
	}
};
