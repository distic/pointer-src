#pragma once

#include <map>
#include <functional>
#include "misc/framework.h"

class IContainer {
public:
	void bindWmId(DWORD resId, std::function<void()> fn)
	{
		m_collection[resId] = fn;
	}

	void bindTabSel(std::function<void()> fn)
	{
		m_tabSelFn = fn;
	}

protected:
	std::map<DWORD, std::function<void()>> m_collection;
	std::function<void()> m_tabSelFn;
};