#pragma once

class Poolable
{
public:
	Poolable();
	virtual ~Poolable();

	virtual void OnGet() = 0;
	virtual void OnRelease() = 0;
};

