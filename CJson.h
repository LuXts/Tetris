#pragma once

#include "pch.h"
#include <vector>

class CJson
{
public:
	static void load(std::vector<CString>&, std::vector<int>&);
	static void save(std::vector<CString>&, std::vector<int>&);
};
