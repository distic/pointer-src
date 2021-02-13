#pragma once

class IResizableControl {
public:
	virtual void setSize(int width, int height) = 0;
	virtual void setLocation(int x, int y) = 0;
};