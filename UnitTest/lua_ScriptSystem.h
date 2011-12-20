/*
** Lua binding: ScriptSystem
** Generated automatically by tolua++-1.0.92 on 12/20/11 20:39:38.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_ScriptSystem_open (lua_State* tolua_S);

#include "PollMonitorObject.h"
#include "ScriptMonitorObject.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ScriptMonitorObject (lua_State* tolua_S)
{
 ScriptMonitorObject* self = (ScriptMonitorObject*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ScriptMonitorObject");
 tolua_usertype(tolua_S,"PollMonitorObject");
}

/* method: new of class  ScriptMonitorObject */
#ifndef TOLUA_DISABLE_tolua_ScriptSystem_ScriptMonitorObject_new00
static int tolua_ScriptSystem_ScriptMonitorObject_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ScriptMonitorObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ScriptMonitorObject* tolua_ret = (ScriptMonitorObject*)  Mtolua_new((ScriptMonitorObject)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScriptMonitorObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ScriptMonitorObject */
#ifndef TOLUA_DISABLE_tolua_ScriptSystem_ScriptMonitorObject_new00_local
static int tolua_ScriptSystem_ScriptMonitorObject_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ScriptMonitorObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ScriptMonitorObject* tolua_ret = (ScriptMonitorObject*)  Mtolua_new((ScriptMonitorObject)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScriptMonitorObject");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ScriptMonitorObject */
#ifndef TOLUA_DISABLE_tolua_ScriptSystem_ScriptMonitorObject_delete00
static int tolua_ScriptSystem_ScriptMonitorObject_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptMonitorObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptMonitorObject* self = (ScriptMonitorObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isAlarmed of class  ScriptMonitorObject */
#ifndef TOLUA_DISABLE_tolua_ScriptSystem_ScriptMonitorObject_isAlarmed00
static int tolua_ScriptSystem_ScriptMonitorObject_isAlarmed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptMonitorObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptMonitorObject* self = (ScriptMonitorObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isAlarmed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isAlarmed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isAlarmed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enable of class  ScriptMonitorObject */
#ifndef TOLUA_DISABLE_tolua_ScriptSystem_ScriptMonitorObject_enable00
static int tolua_ScriptSystem_ScriptMonitorObject_enable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptMonitorObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptMonitorObject* self = (ScriptMonitorObject*)  tolua_tousertype(tolua_S,1,0);
  bool val = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool bDeferredStart = ((bool)  tolua_toboolean(tolua_S,3,false));
  float deferredTime = ((float)  tolua_tonumber(tolua_S,4,1.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enable'", NULL);
#endif
  {
   self->enable(val,bDeferredStart,deferredTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCheckFunctionName of class  ScriptMonitorObject */
#ifndef TOLUA_DISABLE_tolua_ScriptSystem_ScriptMonitorObject_setCheckFunctionName00
static int tolua_ScriptSystem_ScriptMonitorObject_setCheckFunctionName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptMonitorObject",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptMonitorObject* self = (ScriptMonitorObject*)  tolua_tousertype(tolua_S,1,0);
  const std::string funName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCheckFunctionName'", NULL);
#endif
  {
   self->setCheckFunctionName(funName);
   tolua_pushcppstring(tolua_S,(const char*)funName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCheckFunctionName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ScriptSystem_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ScriptMonitorObject","ScriptMonitorObject","PollMonitorObject",tolua_collect_ScriptMonitorObject);
  #else
  tolua_cclass(tolua_S,"ScriptMonitorObject","ScriptMonitorObject","PollMonitorObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ScriptMonitorObject");
   tolua_function(tolua_S,"new",tolua_ScriptSystem_ScriptMonitorObject_new00);
   tolua_function(tolua_S,"new_local",tolua_ScriptSystem_ScriptMonitorObject_new00_local);
   tolua_function(tolua_S,".call",tolua_ScriptSystem_ScriptMonitorObject_new00_local);
   tolua_function(tolua_S,"delete",tolua_ScriptSystem_ScriptMonitorObject_delete00);
   tolua_function(tolua_S,"isAlarmed",tolua_ScriptSystem_ScriptMonitorObject_isAlarmed00);
   tolua_function(tolua_S,"enable",tolua_ScriptSystem_ScriptMonitorObject_enable00);
   tolua_function(tolua_S,"setCheckFunctionName",tolua_ScriptSystem_ScriptMonitorObject_setCheckFunctionName00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ScriptSystem (lua_State* tolua_S) {
 return tolua_ScriptSystem_open(tolua_S);
};
#endif

