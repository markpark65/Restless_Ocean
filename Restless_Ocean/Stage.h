#pragma once
class Stage
{
public:
	virtual ~Stage() = default;

	virtual void start()	= 0;
	virtual void update()	= 0;
	virtual void exit()		= 0;
};

