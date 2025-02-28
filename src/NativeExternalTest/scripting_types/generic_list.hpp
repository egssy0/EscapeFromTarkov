#pragma once
#include <cstdint>
#include <vector>

#include "memory_handler.hpp"
#include "offset.hpp"

#ifndef LIST_T_HPP
#define LIST_T_HPP

template<typename T>
class generic_list
{
	// System.Collections.Geenric.List<T>
	
public:

	uintptr_t address;

	uint32_t count;

	std::vector<T> data;
	
	explicit generic_list(const uintptr_t addr) : address(addr)
	{
		count = 
			memory_handler::read<uint32_t>(addr + offset::generic_list::count);

		auto base = 
			memory_handler::read<uintptr_t>(addr + offset::generic_list::base) + offset::array::base;
		
		for(unsigned index = 0; index < count; index++)
		{
			auto temp_address = memory_handler::read<uintptr_t>(base + index * 8);

			data.push_back( T(temp_address) );
		}
	}
};

#endif