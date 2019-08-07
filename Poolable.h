#pragma once

/*
All poolable objects need a move constructor?
or is it move assignment? well both really.
*/
class Poolable
{
public:
	Poolable();
	virtual ~Poolable();

	virtual void OnGet() = 0;
	virtual void OnRelease() = 0;
};

