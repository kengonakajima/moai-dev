// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIHARNESS_H
#define	MOAIHARNESS_H

#include <sstream>
#include <string>
#include <vector>
#include <jansson.h>
#include <lua.h>

//================================================================//
// MOAIBreakpoint
//================================================================//
/**	@name	MOAIBreakpoint
	@text	Internal breakpoint definition class.
*/
struct MOAIBreakpoint {
	std::string filename;
	unsigned int line;

	inline MOAIBreakpoint(std::string f, unsigned int l)
	{
		filename = f;
		line = l;
	}
};

//================================================================//
// MOAIHarness
//================================================================//
/**	@name	MOAIHarness
	@text	Internal debugging and hooking class.
*/
class MOAIHarness {
private:

	// socket information
	static int		mSocketID;
	static struct sockaddr_in mSocketAddr;

	// breakpoint information
	static std::vector<MOAIBreakpoint> mBreakpoints;

	// pausing and waiting
	static bool     mEnginePaused;
	static void		Pause(lua_State *L);

	// callbacks
	static void		Callback(lua_State *L, lua_Debug *ar);

	// message sending
	static void     SendWait();
	static void     SendBreak(std::string func, unsigned int line, std::string file);
	static void     SendResult(json_t* result);
	static void     SendMessage(std::string data);

	// message receiving
	static void		ReceiveContinue(lua_State *L, json_t* node);
	static void		ReceivePause(lua_State *L, json_t* node);
	static void		ReceiveStop(lua_State *L, json_t* node);
	static void		ReceiveBreakSetAlways(lua_State *L, json_t* node);
	static void		ReceiveBreakSetConditional(lua_State *L, json_t* node);
	static void		ReceiveBreakClear(lua_State *L, json_t* node);
	static void		ReceiveVariableGet(lua_State *L, json_t* node);
	static void		ReceiveVariableSet(lua_State *L, json_t* node);
	static void		ReceiveEvaluate(lua_State *L, json_t* node);
	static void		ReceiveMessage(lua_State *L);

	// value encoding
	static json_t*  json_datapair(const char* name, json_t* data);
	static json_t*  ConvertStackToJSON(lua_State * L);
	static json_t*  ConvertStackPartialToJSON(lua_State * L, int start, int end);
	static json_t*  ConvertStackIndexToJSON(lua_State * L, int idx);
	static json_t*  ConvertStackIndexToJSON(lua_State * L, int idx, std::vector<const void*> * carried_references);

public:

	// hook function
	static void		HookLua(lua_State* L, const char* target, int port);

};

#endif
