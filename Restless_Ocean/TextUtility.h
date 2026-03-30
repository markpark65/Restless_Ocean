#pragma once
#include <string>

template<typename T>
T clamp(T val, T mn, T mx) {
	return std::min(std::max(val, mn), mx);
}

static enum class strColor
{
	Default,
	Red,
	Green,
	Blue,
	Magenta,
	Yellow,
	Cyan,
	White
};

class TextUtility {
private:
	static const char* toAnsi(strColor color)
	{
		switch (color)
		{
		case strColor::Red:		return "\x1b[31m";
		case strColor::Green:	return "\x1b[32m";
		case strColor::Yellow:	return "\x1b[33m";
		case strColor::Blue:	return "\x1b[34m";
		case strColor::Magenta: return "\x1b[35m";
		case strColor::Cyan:	return "\x1b[36m";
		case strColor::White:	return "\x1b[37m";
		default:				return "\x1b[0m";
		}
	}

public:
	/// <summary>
	/// 현재값과 최대값이 주어지면 barWidth길이의 막대로 표현하는 텍스트를 반환합니다.
	/// </summary>
	static std::string makeBar(int current, int maxValue, int barWidth, bool Colorize = false, bool reverse = false)
	{
		if (maxValue <= 0)
		{
			return "[" + std::string(barWidth, '.') + "]";
		}

		current = clamp(current, 0, maxValue);
		int filled = current * barWidth / maxValue;
		std::string result = "[" + std::string(filled, '#') + std::string(barWidth - filled, '.') + "] ";
		if (Colorize)
			return strColorizePercent(result, current, maxValue, reverse);
		else
			return "[" + std::string(filled, '#') + std::string(barWidth - filled, '.') + "] ";
	}
	/// <summary>
	/// 텍스트에 색을 입힙니다. 색상은 strColor 참고
	/// </summary>
	/// <param name="str">색을 입힐 텍스트</param>
	/// <param name="color">strColor 색상</param>
	static std::string strColorize(std::string str, strColor color) {
		return toAnsi(color) + str + toAnsi(strColor::Default);
	}

	/// <summary>
	/// <para>백분율에 따라 텍스트의 색상을 초록, 노랑, 빨강으로 변경합니다.</para>
	/// <para>100%~66% 녹색 </para>
	/// <para>66%~33% 노란색 </para>
	/// <para>33%~0% 빨간색 </para>
	/// </summary>
	/// <param name="str">색을 입힐 텍스트</param>
	/// <param name="currentVal">비율을 구할 현재값</param>
	/// <param name="maxVal">비율을 구할 최대값</param>
	/// <param name="reverse">비율을 반대로 적용할경우(pressure)에 true, 기본은 false</param>
	static std::string strColorizePercent(std::string str, int currentVal, int maxVal, bool reverse = false) {
		int percent = ((double)currentVal / maxVal) * 100;
		if (reverse)
			percent = 100 - percent;
		strColor color = strColor::Default;
		if (percent >= 66)
			color = strColor::Green;
		else if (percent >= 33)
			color = strColor::Yellow;
		else
			color = strColor::Red;
		return strColorize(str, color);
	}
};

