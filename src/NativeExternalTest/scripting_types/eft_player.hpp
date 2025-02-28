#pragma once
#include <memory>

#include "offset.hpp"
#include "memory_handler.hpp"
#include "utility.hpp"
#include "transform.hpp"
#include "eft_profile.hpp"
#include "player_physical.hpp"
#include "eft_player_body.hpp"
#include "firearm_controller.hpp"
#include "health_controller.hpp"
#include "procedural_weapon_animation.hpp"
#include "movement_context.hpp"

class player
{
	// EFT.Player
	
	uintptr_t address;
	
public:

	std::shared_ptr<player_profile> profile;

	std::shared_ptr<player_physical> physical;

	std::shared_ptr<player_body> body;

	std::shared_ptr<procedural_weapon_animation> procedural_wep_anim;

	std::shared_ptr<firearm_controller> hands_controller;

	std::shared_ptr<health_controller> health_controller;

	std::shared_ptr<movement_context> movement_context;
	
	std::string name;

	std::string faction;

	player() = default;
	
	explicit player(const uintptr_t addr) : address(addr)
	{
		profile = 
			std::make_shared<player_profile>(
				memory_handler::read<uintptr_t>(
					address + offset::player::player_profile));

		physical =
			std::make_shared<player_physical>(
				memory_handler::read<uintptr_t>(
					address + offset::player::player_physical));

		body =
			std::make_shared<player_body>(
				memory_handler::read<uintptr_t>(
					address + offset::player::player_body));

		procedural_wep_anim =
			std::make_shared<procedural_weapon_animation>(
				memory_handler::read<uintptr_t>(
					address + offset::player::procedural_weapon_anim));

		hands_controller =
			std::make_shared<firearm_controller>(
				memory_handler::read<uintptr_t>(
					address + offset::player::hands_controller));

		health_controller =
			std::make_shared<class health_controller>(
				memory_handler::read<uintptr_t>(
					address + offset::player::health_controller));

		movement_context =
			std::make_shared<class movement_context>(
				memory_handler::read<uintptr_t>(
					address + offset::player::movement_context));
		
		name = utility::wide_to_narrow(profile->get_nickname());

		faction = profile->get_side_name();
	}

	~player() = default;
	
	auto get_address() const -> uintptr_t
	{
		return address;
	}

	auto get_health() const -> float
	{
		return health_controller->get_player_health();
	}

	auto get_max_health() const -> float
	{
		return health_controller->get_player_max_health();
	}

	auto get_root_position() const -> vector3
	{
		return body->bones->root.get_position();
	}

	auto get_head_position() const -> vector3
	{
		return body->bones->head.get_position();
	}
	
	auto operator ! () const -> bool
	{
		return !this->address;
	}

	friend auto operator == (player first, player second) -> bool
	{
		return first.address == second.address;
	}
	
	auto operator == (player& other) const -> bool
	{
		return this->address == other.address;
	}

	auto operator == (player* other) const -> bool
	{
		return this->address == other->address;
	}

	auto operator == (const std::unique_ptr<player>& other) const -> bool
	{
		if(!other)
		{
			return false;
		}

		return this->address == other->address;
	}
	
	auto operator == (const std::shared_ptr<player>& other) const -> bool
	{
		if(!other)
		{
			return false;
		}
		
		return this->address == other->address;
	}

	friend auto operator != (player first, player second) -> bool
	{
		return first.address != second.address;
	}
};