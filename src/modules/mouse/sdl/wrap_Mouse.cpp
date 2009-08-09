/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
**/

#include "wrap_Mouse.h"

namespace love
{
namespace mouse
{
namespace sdl
{
	static Mouse * instance = 0;

	int w_getX(lua_State * L)
	{
		lua_pushnumber(L, instance->getX());
		return 1;
	}

	int w_getY(lua_State * L)
	{
		lua_pushnumber(L, instance->getY());
		return 1;
	}

	int w_getPosition(lua_State * L)
	{
		int x, y;
		instance->getPosition(&x, &y);
		lua_pushinteger(L, x);
		lua_pushinteger(L, y);
		return 2;
	}

	int w_setPosition(lua_State * L)
	{
		int x = luaL_checkint(L, 1);
		int y = luaL_checkint(L, 2);
		instance->setPosition(x, y);
		return 0;
	}

	int w_isDown(lua_State * L)
	{
		int b = luaL_checkint(L, 1);
		luax_pushboolean(L, instance->isDown(b));
		return 1;
	}

	int w_setVisible(lua_State * L)
	{
		bool b = luax_toboolean(L, 1);
		instance->setVisible(b);
		return 0;
	}

	int w_isVisible(lua_State * L)
	{
		luax_pushboolean(L, instance->isVisible());
		return 1;
	}

	int w_setGrap(lua_State * L)
	{
		bool b = luax_toboolean(L, 1);
		instance->setGrab(b);
		return 0;
	}

	int w_isGrabbed(lua_State * L)
	{
		luax_pushboolean(L, instance->isGrabbed());
		return 1;
	}
	

	int w_Mouse_open(lua_State * L)
	{
		// List of functions to wrap.
		static const luaL_Reg functions[] = {
			{ "getX", w_getX },
			{ "getY", w_getY },
			{ "setPosition", w_setPosition },
			{ "isDown", w_isDown },
			{ "setVisible", w_setVisible },
			{ "isVisible", w_isVisible },
			{ "getPosition", w_getPosition },
			{ "setGrab", w_setGrap },
			{ "isGrabbed", w_isGrabbed },
			{ 0, 0 }
		};

		// List of constants.
		static const LuaConstant constants[] = {
			{ "mouse_left", Mouse::MOUSE_LEFT },
			{ "mouse_middle", Mouse::MOUSE_MIDDLE },
			{ "mouse_right", Mouse::MOUSE_RIGHT },
			{ "mouse_wheelup", Mouse::MOUSE_WHEELUP },
			{ "mouse_wheeldown", Mouse::MOUSE_WHEELDOWN },
			{ 0, 0 }
		};

		if(instance == 0)
		{
			try 
			{
				instance = new Mouse();
			} 
			catch(Exception & e)
			{
				return luaL_error(L, e.what());
			}
		}

		luax_register_gc(L, instance);

		return luax_register_module(L, functions, 0, constants, "mouse");
	}

} // sdl
} // mouse
} // love

int luaopen_love_mouse(lua_State * L)
{
	return love::mouse::sdl::w_Mouse_open(L);
}
