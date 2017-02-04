#include "stdafx.h"
#include "ScriptSystem.h"

namespace Magma
{
	ScriptSystem* ScriptSystem::ourInstance = nullptr;

	ScriptSystem* ScriptSystem::GetInstance()
	{
		if (!ourInstance)
			ourInstance = new ScriptSystem();

		return ourInstance;
	}

	void ScriptSystem::Destroy()
	{
		SAFE_DELETE(ourInstance);
	}

	void ScriptSystem::SetRegisterFunction(std::function<void(ScriptSystem&, lua_State*)> aFunction)
	{
		myCppRegisterFunction = aFunction;
	}

	ScriptSystem::ScriptSystem()
	{
	}


	ScriptSystem::~ScriptSystem()
	{
	}

	lua_State* ScriptSystem::CreateState(const CU::String& aFilePath)
	{
		lua_State* state = luaL_newstate();
		SetCurrentState(state);

		luaL_openlibs(state);

		myCppRegisterFunction(*this, myCurrentState);

		luaL_dofile(myCurrentState, aFilePath.c_str());

		return state;
	}

	void ScriptSystem::SetCurrentState(lua_State* aState)
	{
		myCurrentState = aState;
	}

	void ScriptSystem::RegisterFunction(const CU::String& aNameInLua, lua_CFunction aFunction)
	{
		lua_register(myCurrentState, aNameInLua.c_str(), aFunction);
	}

	void ScriptSystem::CallFunction(const CU::String& aName)
	{
		lua_getglobal(myCurrentState, aName.c_str());
		if (lua_isnil(myCurrentState, -1))
		{
			int apa = 5;
		}

		lua_pcall(myCurrentState, 0, 0, 0);
	}

	void ScriptSystem::GetArgFromLua(int aIndex, char* aString)
	{
		//aString = lua_tostring(myCurrentState, aIndex);
	}

	void ScriptSystem::GetArgFromLua(int aIndex, int& aInt)
	{
		aInt = static_cast<int>(lua_tointeger(myCurrentState, aIndex));
	}

	void ScriptSystem::GetArgFromLua(int aIndex, float& aFloat)
	{
		aFloat = static_cast<float>(lua_tonumber(myCurrentState, aIndex));
	}

	void ScriptSystem::GetArgFromLua(int aIndex, bool& aBool)
	{
		aBool = static_cast<bool>(lua_toboolean(myCurrentState, aIndex));
	}

	void ScriptSystem::CheckError(int aErrorCode)
	{
		if (aErrorCode != 0)
		{
			printf("%s", lua_tostring(myCurrentState, -1));
			lua_pop(myCurrentState, 1);
		}
	}

}