#pragma once
#include "Console.hpp"
#include "Game.hpp"
#include "D3D11Window.hpp"

class Hooking
{
public:

	explicit Hooking();
	~Hooking() noexcept;
	Hooking(Hooking const&) = delete;
	Hooking(Hooking&&) = delete;
	Hooking& operator=(Hooking const&) = delete;
	Hooking& operator=(Hooking&&) = delete;

	void Hook();
	void Unhook();
};
inline std::unique_ptr<Hooking> g_Hooking;