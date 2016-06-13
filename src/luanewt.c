#include <stdlib.h>

#include "luanewt.h"

#define MYNAME "NEWT"
#define MYVERSION MYNAME " binding for " LUA_VERSION " 2013.03.20"

#define TYPE_COMPONENT "Newt.Component"

#define lua_newncom(L) ((component)(lua_newuserdata(L, sizeof(struct com_t))))
#define lua_toncom(L, i) ((component)(lua_touserdata(L, i)))

#define bool int
#define false 0
#define true 1


/* check and return pointer */
void *luaL_checkpointer(lua_State* L, int i) {
  luaL_checktype(L, i, LUA_TLIGHTUSERDATA);
  return lua_touserdata(L, i);
}

/* check and return component object parameter */
component luaL_checkcomponent(lua_State* L, int i) {
  luaL_checkudata(L, i, TYPE_COMPONENT);
  return lua_toncom(L, i);
}

/* push a component object on the stack */
void lua_pushcomponent(lua_State *L, newtComponent com, int type) {
  if (com) {
    component p = lua_newncom(L);
    luaL_setmetatable(L, TYPE_COMPONENT);
    p->p = com;
    p->t = type;
  } else {
    lua_pushnil(L);
  }
}

/* register component tag */
void lua_regtag(lua_State *L, newtComponent com, const char *tag) {
  char id[32];
  snprintf(id, 32, "newt.%p", (void *)(com));
  lua_pushstring(L, id);
  if (tag != NULL) lua_pushstring(L, tag);
  else lua_pushnil(L);
  lua_settable(L, LUA_REGISTRYINDEX);
}

/* push component tag onto Lua stack */
void lua_pushtag(lua_State *L, newtComponent com) {
  char id[20];
  sprintf(id, "newt.%p", (void *)(com));
  lua_pushstring(L, id);
  lua_gettable(L, LUA_REGISTRYINDEX);
}


/** module registration **/

/* base functions */
static const luaL_Reg R_newt_functions[] = {

  {"Init", L_Init},
  {"Cls", L_Cls},
  {"WaitForKey", L_WaitForKey},
  {"ClearKeyBuffer", L_ClearKeyBuffer},
  {"DrawRootText", L_DrawRootText},
  {"OpenWindow", L_OpenWindow},
  {"CenteredWindow", L_CenteredWindow},
  {"PopWindow", L_PopWindow},
  {"PushHelpLine", L_PushHelpLine},
  {"PopHelpLine", L_PopHelpLine},
  {"Refresh", L_Refresh},
  {"Finished", L_Finished},
  {"WinMessage", L_WinMessage},
  {"Suspend", L_Suspend},
  {"Resume", L_Resume},
  {"SetSuspendCallback", L_SetSuspendCallback},
  {"Bell", L_Bell},
  {"CursorOff", L_CursorOff},
  {"CursorOn", L_CursorOn},
  {"Delay", L_Delay},
  {"GetScreenSize", L_GetScreenSize},
  {"ReflowText", L_ReflowText},

  {"Button", L_Button},
  {"CompactButton", L_CompactButton},
  {"Checkbox", L_Checkbox},
  {"Entry", L_Entry},
  {"Form", L_Form},
  {"Label", L_Label},
  {"Textbox", L_Textbox},
  {"TextboxReflowed", L_TextboxReflowed},
  {"Listbox", L_Listbox},
  {"Radiobutton", L_Radiobutton},
  {"Scale", L_Scale},
  {"VerticalScrollbar", L_VerticalScrollbar},


  {"ClearSelection", L_ClearSelection},
  {"DeleteEntry", L_DeleteEntry},
  {"GetSelection", L_GetSelection},
  {"GetNumLines ", L_GetNumLines },
  {"InsertEntry", L_InsertEntry},
  {"SelectItem", L_SelectItem},
  {"SetValue", L_SetValue},
  {"SetBackground", L_SetBackground},
  {"SetHeight", L_SetHeight},
  {"SetCurrent", L_SetCurrent},
  {"SetCurrentByKey", L_SetCurrentByKey},
  {"SetEntry", L_SetEntry},
  {"SetWidth", L_SetWidth},

  {NULL, NULL}
};

/* Newt.Component methods */
static const luaL_Reg R_comp_methods[] = {

  {"AddCallback", L_AddCallback},

  {"AddComponents", L_AddComponents},
  {"AddHotKey", L_AddHotKey},
  {"AppendEntry", L_AppendEntry},
  {"Clear", L_Clear},
  {"Destroy", L_Destroy},
  {"Draw", L_Draw},
  {"GetCurrent", L_GetCurrent},
  {"GetValue", L_GetValue},
  {"ID", L_ID},
  {"Run", L_Run},
  {"Set", L_Set},
  {"SetText", L_SetText},
  {"SetTimer", L_SetTimer},
  {"SetType", L_SetType},
  {"TakesFocus", L_TakesFocus},
  {"Text", L_Text},

  {NULL, NULL}
};


LUALIB_API int luaopen_newt(lua_State *L) {

  /* Newt.Component type & methods */
  luaL_newmetatable(L, TYPE_COMPONENT);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, R_comp_methods, 0);

  /* register the base functions and module flags */
  luaL_newlib(L, R_newt_functions);

  lua_pushliteral(L, MYVERSION);
  lua_setfield(L, -2, "version");     /** version */

#define luaL_push_const(name, value) \
  lua_pushinteger(L, value); \
  lua_setfield(L, -2, name)

  luaL_push_const("FLAG_RETURNEXIT", NEWT_FLAG_RETURNEXIT);
  luaL_push_const("FLAG_HIDDEN", NEWT_FLAG_HIDDEN);
  luaL_push_const("FLAG_SCROLL", NEWT_FLAG_SCROLL);
  luaL_push_const("FLAG_DISABLED", NEWT_FLAG_DISABLED);
  luaL_push_const("FLAG_BORDER", NEWT_FLAG_BORDER);
  luaL_push_const("FLAG_WRAP", NEWT_FLAG_WRAP);
  luaL_push_const("FLAG_NOF12", NEWT_FLAG_NOF12);
  luaL_push_const("FLAG_MULTIPLE", NEWT_FLAG_MULTIPLE);
  luaL_push_const("FLAG_SELECTED", NEWT_FLAG_SELECTED);
  luaL_push_const("FLAG_CHECKBOX", NEWT_FLAG_CHECKBOX);
  luaL_push_const("FLAG_PASSWORD", NEWT_FLAG_PASSWORD);
  luaL_push_const("FLAG_SHOWCURSOR", NEWT_FLAG_SHOWCURSOR);

  luaL_push_const("FLAG_CHECKBOXTREE_UNSELECTABLE", NEWT_CHECKBOXTREE_UNSELECTABLE);
  luaL_push_const("FLAG_CHECKBOXTREE_HIDE_BOX", NEWT_CHECKBOXTREE_HIDE_BOX);

  luaL_push_const("EXIT_HOTKEY", NEWT_EXIT_HOTKEY);
  luaL_push_const("EXIT_COMPONENT", NEWT_EXIT_COMPONENT);
  luaL_push_const("EXIT_FDREADY", NEWT_EXIT_FDREADY);
  luaL_push_const("EXIT_TIMER", NEWT_EXIT_TIMER);


  luaL_push_const("KEY_ESCAPE", NEWT_KEY_ESCAPE);
  luaL_push_const("KEY_RETURN", NEWT_KEY_RETURN);
  luaL_push_const("KEY_PGDN", NEWT_KEY_PGDN);
  luaL_push_const("KEY_PGUP", NEWT_KEY_PGUP);

  luaL_push_const("KEY_F1", NEWT_KEY_F1);
  luaL_push_const("KEY_F2", NEWT_KEY_F2);
  luaL_push_const("KEY_F3", NEWT_KEY_F3);
  luaL_push_const("KEY_F4", NEWT_KEY_F4);
  luaL_push_const("KEY_F5", NEWT_KEY_F5);
  luaL_push_const("KEY_F6", NEWT_KEY_F6);
  luaL_push_const("KEY_F7", NEWT_KEY_F7);
  luaL_push_const("KEY_F8", NEWT_KEY_F8);
  luaL_push_const("KEY_F9", NEWT_KEY_F9);
  luaL_push_const("KEY_F10", NEWT_KEY_F10);
  luaL_push_const("KEY_F11", NEWT_KEY_F11);
  luaL_push_const("KEY_F12", NEWT_KEY_F12);

  luaL_push_const("TYPE_UNKNOWN", TYPE_UNKNOWN);
  luaL_push_const("TYPE_FORM", TYPE_FORM);
  luaL_push_const("TYPE_LABEL", TYPE_LABEL);
  luaL_push_const("TYPE_ENTRY", TYPE_ENTRY);
  luaL_push_const("TYPE_BUTTON", TYPE_BUTTON);
  luaL_push_const("TYPE_CHECKBOX", TYPE_CHECKBOX);
  luaL_push_const("TYPE_RADIOBUTTON", TYPE_RADIOBUTTON);
  luaL_push_const("TYPE_LISTBOX", TYPE_LISTBOX);
  luaL_push_const("TYPE_SCALE", TYPE_SCALE);

  return 1;
}


/** root functions **/

/* bool Init() */
static int L_Init(lua_State *L) {
  int result;
  result = newtInit();
  lua_pushboolean(L, result);
  return 1;
}

/* Cls() */
static int L_Cls(lua_State *L) {
  newtCls();
  return 0;
}

/* WaitForKey() */
static int L_WaitForKey(lua_State *L) {
  newtWaitForKey();
  return 0;
}

/* ClearKeyBuffer() */
static int L_ClearKeyBuffer(lua_State *L) {
  newtClearKeyBuffer();
  return 0;
}

/* DrawRootText(left, top, text) */
static int L_DrawRootText(lua_State *L) {
  int left = (int)luaL_checknumber(L, 1);
  int top = (int)luaL_checknumber(L, 2);
  const char * text = luaL_checkstring(L, 3);
  newtDrawRootText(left, top, text);
  return 0;
}

/* newtOpenWindow(left, top, width, height, [title]) */
static int L_OpenWindow(lua_State *L) {
  int left = luaL_checkinteger(L, 1);
  int top = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);
  const char *title;
  if ((lua_gettop(L) < 5) || (lua_isnil(L, 5) == 1)) {
    title = NULL;
  } else {
    title = luaL_checkstring(L, 5);
  }
  int result = newtOpenWindow(left, top, width, height, title);
  lua_pushboolean(L, result);
  return 1;
}

/* bool newtCenteredWindow(width, height, [title]) */
static int L_CenteredWindow(lua_State *L) {
  int result;
  int width; int height;
  const char *title;
  width = luaL_checkinteger(L, 1);
  height = luaL_checkinteger(L, 2);

  if ((lua_gettop(L) < 3) || (lua_isnil(L, 3) == 1)) title = NULL;
  else title = luaL_checkstring(L, 3);

  result = newtCenteredWindow(width, height, title);
  lua_pushboolean(L, result);
  return 1;
}

/* PopWindow() */
static int L_PopWindow(lua_State *L) {
  newtPopWindow();
  return 0;
}

/* PushHelpLine([text]) */
static int L_PushHelpLine(lua_State *L) {
  const char *text;

  if ((lua_gettop(L) < 1) || (lua_isnil(L, 1) == 1)) text = NULL;
  else text = luaL_checkstring(L, 1);

  newtPushHelpLine(text);
  return 0;
}

/* PopHelpLine() */
static int L_PopHelpLine(lua_State *L) {
  newtPopHelpLine();
  return 0;
}

/* Refresh() */
static int L_Refresh(lua_State *L) {
  newtRefresh();
  return 0;
}

/* bool Finished() */
static int L_Finished(lua_State *L) {
  int result;
  result = newtFinished();
  lua_pushboolean(L, result);
  return 1;
}

/* Suspend() */
static int L_Suspend(lua_State *L) {
  newtSuspend();
  return 0;
}

/* Resume */
static int L_Resume(lua_State *L) {
  newtResume();
  return 0;
}

/* Bell() */
static int L_Bell(lua_State *L) {
  newtBell();
  return 0;
}

/* CursorOff() */
static int L_CursorOff(lua_State *L) {
  newtCursorOff();
  return 0;
}

/* CursorOn() */
static int L_CursorOn(lua_State *L) {
  newtCursorOn();
  return 0;
}

/* Delay() */
static int L_Delay(lua_State *L) {
  int msec;
  msec = luaL_checkinteger(L, 1);
  newtDelay(msec * 1000);
  return 0;
}

/* cols, rows = GetScreenSize() */
static int L_GetScreenSize(lua_State *L) {
  int cols; int rows;
  newtGetScreenSize(&cols, &rows);
  lua_pushinteger(L, cols);
  lua_pushinteger(L, rows);
  return 2;
}

/* widget functions */

/* com = Button(left, top, text) */
static int L_Button(lua_State *L) {
  newtComponent result;
  int left; int top;
  const char *text;

  left = luaL_checkinteger(L, 1);
  top = luaL_checkinteger(L, 2);
  text = luaL_checkstring(L, 3);

  result = newtButton(left, top, text);
  lua_regtag(L, result, text);
  lua_pushcomponent(L, result, TYPE_BUTTON);
  return 1;
}

/* com = CompactButton(left, top, text) */
static int L_CompactButton(lua_State *L) {
  int left; int top;
  const char *text;
  newtComponent result;

  left = luaL_checkinteger(L, 1);
  top = luaL_checkinteger(L, 2);
  text = luaL_checkstring(L, 3);

  result = newtCompactButton(left, top, text);
  lua_regtag(L, result, text);
  lua_pushcomponent(L, result, TYPE_BUTTON);
  return 1;
}

/* com = Checkbox(left, top, text, [checked]) */
static int L_Checkbox(lua_State *L) {
  int left; int top;
  const char *text;
  bool checked;
  newtComponent result;

  left = luaL_checkinteger(L, 1);
  top = luaL_checkinteger(L, 2);
  text = luaL_checkstring(L, 3);
  if (lua_gettop(L) < 4 || lua_isnil(L, 4) == 1) checked = false;
  else checked = lua_toboolean(L, 4);

  if (checked == false) result = newtCheckbox(left, top, text, ' ', " *", NULL);
  else result = newtCheckbox(left, top, text, '*', " *", NULL);
  lua_regtag(L, result, text);
  lua_pushcomponent(L, result, TYPE_CHECKBOX);
  return 1;
}

/* com = Entry(left, top, value, width, [flags])*/
static int L_Entry(lua_State *L) {
  int left; int top;
  const char *value;
  int width; int flags;
  newtComponent result;

  left = luaL_checkinteger(L, 1);
  top = luaL_checkinteger(L, 2);
  if (lua_isnil(L, 3) == 1) value = NULL;
  else value = luaL_checkstring(L, 3);
  width = luaL_checkinteger(L, 4);
  if (lua_gettop(L) < 5 || lua_isnil(L, 5) == 1) flags = 0;
  else flags = luaL_checkinteger(L, 5);

  result = newtEntry(left, top, value, width, NULL, flags);
  lua_pushcomponent(L, result, TYPE_ENTRY);
  return 1;
}

/* com = Form([vertBar], [help], [flags]) */
static int L_Form(lua_State *L) {
  newtComponent vertBar;
  const char *help;
  int flags;
  newtComponent result;

  if (lua_gettop(L) < 1 || lua_isnil(L, 1) == 1) vertBar = NULL;
  else vertBar = luaL_checkcomponent(L, 1)->p;
  if (lua_gettop(L) < 2 || lua_isnil(L, 2) == 1) help = NULL;
  else help = luaL_checkstring(L, 2);
  if (lua_gettop(L) < 3 || lua_isnil(L, 3) == 1) flags = 0;
  else flags = luaL_checkinteger(L, 3);

  result = newtForm(vertBar, (void *)help, flags);
  lua_pushcomponent(L, result, TYPE_FORM);
  return 1;
}

/* com = Label(left, top, text) */
static int L_Label(lua_State *L) {
  int left; int top;
  const char *text;
  newtComponent result;

  left = luaL_checkinteger(L, 1);
  top = luaL_checkinteger(L, 2);
  text = luaL_checkstring(L, 3);

  result = newtLabel(left, top, text);
  lua_pushcomponent(L, result, TYPE_LABEL);
  return 1;
}

/* textbox = Textbox(left, top, width, height, [flags]) */
static int L_Textbox(lua_State *L) {
  int left; int top;
  int width; int height;
  int flags;
  newtComponent result;

  left = luaL_checkinteger(L, 1);
  top = luaL_checkinteger(L, 2);
  width = luaL_checkinteger(L, 3);
  height = luaL_checkinteger(L, 4);
  if (lua_gettop(L) < 5 || lua_isnil(L, 5) == 1) flags = 0;
  else flags = luaL_checkinteger(L, 5);

  result = newtTextbox(left, top, width, height, flags);
  lua_pushcomponent(L, result, TYPE_TEXTBOX);
  return 1;
}


/* list = Listbox(left, top, height, flags) */
static int L_Listbox(lua_State *L) {
  int left; int top;
  int height; int flags;
  newtComponent result;

  left = luaL_checkinteger(L, 1);
  top = luaL_checkinteger(L, 2);
  height = luaL_checkinteger(L, 3);
  if (lua_gettop(L) < 4 || lua_isnil(L, 4) == 1) flags = 0;
  else flags = luaL_checkinteger(L, 4);

  result = newtListbox(left, top, height, flags);
  lua_pushcomponent(L, result, TYPE_LISTBOX);
  return 1;
}

/* com = Radiobutton(left, top, text, [selected], [prev]) */
static int L_Radiobutton(lua_State *L) {
  int left; int top;
  const char *text;
  bool selected;
  component com;
  newtComponent prev;
  newtComponent result;

  left = luaL_checkinteger(L, 1);
  top = luaL_checkinteger(L, 2);
  text = luaL_checkstring(L, 3);
  if (lua_gettop(L) < 4 || lua_isnil(L, 4) == 1) selected = false;
  else selected = lua_toboolean(L, 4);
  if (lua_gettop(L) < 5 || lua_isnil(L, 5) == 1) prev = NULL;
  else {
    com = luaL_checkcomponent(L, 5);
    if (com->t != TYPE_RADIOBUTTON) return luaL_error(L, "Previous component must be a Radiobutton");
    prev = com->p;
  }

  result = newtRadiobutton(left, top, text, selected, prev);
  lua_regtag(L, result, text);
  lua_pushcomponent(L, result, TYPE_RADIOBUTTON);
  return 1;
}

/* com = Scale(left, top, width, max) */
static int L_Scale(lua_State *L) {
  int left; int top;
  int width; lua_Integer max;
  newtComponent result;

  left = luaL_checkinteger(L, 1);
  top = luaL_checkinteger(L, 2);
  width = luaL_checkinteger(L, 3);
  max = luaL_checkinteger(L, 4);

  result = newtScale(left, top, width, max);
  lua_pushcomponent(L, result, TYPE_SCALE);
  return 1;
}

static int L_VerticalScrollbar(lua_State *L) {
  return 0;
}


/** Newt.Component object **/

/* AddComponents(com, ...) */
static int L_AddComponents(lua_State *L) {
  int argi; int argc;
  component form;
  component com;
  form = luaL_checkcomponent(L, 1);
  if (form->t != TYPE_FORM) return luaL_error(L, "Invalid Method");
  argc = lua_gettop(L);
  argi = 2;
  while ((argc > 1) && (argi <= argc)) {
    if ((lua_type(L, argi) == LUA_TUSERDATA) && (luaL_testudata(L, argi, TYPE_COMPONENT) != NULL)) {
      com = lua_toncom(L, argi);
      newtFormAddComponent(form->p, com->p);
    } else if (lua_type(L, argi) == LUA_TTABLE) {
      /* iterate through the array */
      lua_pushnil(L);  /* first key */
      while (lua_next(L, argi) != 0) {
        if ((lua_type(L, -1) == LUA_TUSERDATA) && (luaL_testudata(L, -1, TYPE_COMPONENT) != NULL)) {
          com = lua_toncom(L, -1);
          newtFormAddComponent(form->p, com->p);
        }
        /* removes 'value'; keeps 'key' for next iteration */
        lua_pop(L, 1);
      }
    }
    argi++;
  }
  return 0;
}

/* form:AddHotKey(key) */
/* form:AddHotKey({key, ...}) */
static int L_AddHotKey(lua_State *L) {
  component com;
  int key;

  com = luaL_checkcomponent(L, 1);
  if (com->t != TYPE_FORM) return luaL_error(L, "Invalid Method");
  if (lua_type(L, 2) == LUA_TTABLE) {
    /* iterate through the array */
    lua_pushnil(L);  /* first key */
    while (lua_next(L, 2) != 0) {
      key = luaL_checkinteger(L, -1);
      newtFormAddHotKey(com->p, key);
      /* removes 'value'; keeps 'key' for next iteration */
      lua_pop(L, 1);
    }
  } else {
    key = luaL_checkinteger(L, 2);
    newtFormAddHotKey(com->p, key);
  }

  return 0;
}

/* listbox:AppendEntry(text, [index]) */
/* listbox:AppendEntry({text, text}, [startindex]) */
static int L_AppendEntry(lua_State *L) {
  component com;
  const char *text;
  size_t key;

  com = luaL_checkcomponent(L, 1);
  if (com->t != TYPE_LISTBOX) return luaL_error(L, "Invalid Method");
  if (lua_gettop(L) < 3 || lua_isnil(L, 3) == 1)
    /* hack for newtListItemCount */
    key = ((struct listbox *)com->p->data)->numItems + 1;
  else key = luaL_checkinteger(L, 3);

  if (lua_type(L, 2) == LUA_TTABLE) {
    /* iterate through the array */
    lua_pushnil(L);  /* first key */
    while (lua_next(L, 2) != 0) {
      text = luaL_checkstring(L, -1);
      newtListboxAppendEntry(com->p, text, (const void *)key);
      /* removes 'value'; keeps 'key' for next iteration */
      lua_pop(L, 1);
      key++;
    }
  } else {
    text = luaL_checkstring(L, 2);
    newtListboxAppendEntry(com->p, text, (const void *)key);
  }

  return 0;
}

/* listbox:Clear() */
static int L_Clear(lua_State *L) {
  component com;
  com = luaL_checkcomponent(L, 1);
  if (com->t == TYPE_LISTBOX) return luaL_error(L, "Invalid Method");
  newtListboxClear(com->p);
  return 0;
}

static int L_Destroy(lua_State *L) {
  component form;
  form = luaL_checkcomponent(L, 1);
  if (form->t != TYPE_FORM) return luaL_error(L, "Invalid Method");
  newtFormDestroy(form->p);
  return 0;
}

/* form:Draw() */
static int L_Draw(lua_State *L) {
  component form;
  form = luaL_checkcomponent(L, 1);
  if (form->t != TYPE_FORM) return luaL_error(L, "Invalid Method");
  newtDrawForm(form->p);
  return 0;
}

/* com = radiobutton:GetCurrent() */
static int L_GetCurrent(lua_State *L) {
  component com;
  size_t iresult;
  newtComponent cresult;

  com = luaL_checkcomponent(L, 1);
  switch (com->t) {
    case TYPE_RADIOBUTTON:
      cresult = newtRadioGetCurrent(com->p);
      lua_pushcomponent(L, cresult, TYPE_RADIOBUTTON);
      break;
    case TYPE_LISTBOX:
      iresult = (size_t)newtListboxGetCurrent(com->p);
      lua_pushinteger(L, iresult);
      break;
    default:
      return luaL_error(L, "Invalid Method");
  }

  return 1;
}

/* value = entry:GetValue() */
/* value = checkbox:GetValue() */
static int L_GetValue(lua_State *L) {
  component com;
  char c;

  com = luaL_checkcomponent(L, 1);
  switch (com->t) {
    case TYPE_ENTRY:
      lua_pushstring(L, newtEntryGetValue(com->p));
      break;
    case TYPE_CHECKBOX:
      c = newtCheckboxGetValue(com->p);
      if (c == ' ') lua_pushboolean(L, false);
      else lua_pushboolean(L, true);
      break;
    default:
      return luaL_error(L, "Invalid Method");
  }
  return 1;
}

/* hex = com:ID() */
static int L_ID(lua_State *L) {
  component com;
  char result[20];

  com = luaL_checkcomponent(L, 1);
  sprintf(result, "%p", (void *)(com->p));

  lua_pushstring(L, result);
  return 1;
}

/* reason, value = form:Run() */
static int L_Run(lua_State *L) {
  component form;
  struct newtExitStruct result;
  form = luaL_checkcomponent(L, 1);
  if (form->t != TYPE_FORM) return luaL_error(L, "Invalid Method");
  newtFormRun(form->p, &result);
  lua_pushinteger(L, (int)result.reason);
  if (result.reason == NEWT_EXIT_COMPONENT) {
    lua_pushcomponent(L, result.u.co, TYPE_UNKNOWN);
  } else {
    lua_pushinteger(L, result.u.key);
  }
  return 2;
}

/* entry:Set(value, [cursoratend]) */
/* scale:Set(value) */
static int L_Set(lua_State *L) {
  component com;
  const char *svalue;
  bool cursoratend;
  lua_Integer ivalue;

  com = luaL_checkcomponent(L, 1);
  switch (com->t) {
    case TYPE_ENTRY:
      svalue = luaL_checkstring(L, 2);
      if (lua_gettop(L) < 3) cursoratend = false;
      else cursoratend = lua_toboolean(L, 3);
      newtEntrySet(com->p, svalue, cursoratend);
      break;
    case TYPE_SCALE:
      ivalue = luaL_checkinteger(L, 2);
      newtScaleSet(com->p, ivalue);
      break;
    default:
      return luaL_error(L, "Invalid Method");
  }
  return 0;
}

/* com = com:SetType(type) */
static int L_SetType(lua_State *L) {
  component com;
  int type;

  com = luaL_checkcomponent(L, 1);
  type = luaL_checkinteger(L, 2);

  lua_pushcomponent(L, com->p, type);
  return 1;
}

/* form:SetTimer(millisecs) */
static int L_SetTimer(lua_State *L) {
  component com;
  int period;

  com = luaL_checkcomponent(L, 1);
  period = luaL_checkinteger(L, 2);

  switch (com->t) {
    case TYPE_FORM:
      newtFormSetTimer(com->p, period);
      break;
    default:
      return luaL_error(L, "Invalid Method");
  }

  return 0;
}

/* label:SetText(text) */
static int L_SetText(lua_State *L) {
  component com;
  const char *text;
  com = luaL_checkcomponent(L, 1);
  text = luaL_checkstring(L, 2);
  switch (com->t) {
    case TYPE_LABEL:
      newtLabelSetText(com->p, text);
      break;
    case TYPE_TEXTBOX:
      newtTextboxSetText(com->p, text);
      break;
    default:
      return luaL_error(L, "Invalid Method");
  }
  return 0;
}

/* com:TakesFocus(bool) */
static int L_TakesFocus(lua_State *L) {
  component com;
  int val;
  com = luaL_checkcomponent(L, 1);

  if (lua_gettop(L) < 2) val = true;
  else val = lua_toboolean(L, 2);

  newtComponentTakesFocus(com->p, val);
  return 0;
}

/* tag = com:Text() */
static int L_Text(lua_State *L) {
  component com;
  com = luaL_checkcomponent(L, 1);

  lua_pushtag(L, com->p);
  return 1;
}


static int L_WinMessage(lua_State *L) {
  return 0;
}

static int L_SetSuspendCallback(lua_State *L) {
  return 0;
}

static int L_ReflowText(lua_State *L) {
  return 0;
}

static int L_TextboxReflowed(lua_State *L) {
  return 0;
}
static int L_AddCallback(lua_State *L) {
  return 0;
}

static int L_ClearSelection(lua_State *L) {
  return 0;
}

static int L_DeleteEntry(lua_State *L) {
  return 0;
}

static int L_SelectItem(lua_State *L) {
  return 0;
}

static int L_GetSelection(lua_State *L) {
  return 0;
}

static int L_GetNumLines(lua_State *L) {
  return 0;
}

static int L_InsertEntry(lua_State *L) {
  return 0;
}

static int L_SetValue(lua_State *L) {
  return 0;
}

static int L_SetBackground(lua_State *L) {
  return 0;
}

static int L_SetHeight(lua_State *L) {
  return 0;
}

static int L_SetCurrent(lua_State *L) {
  return 0;
}

static int L_SetCurrentByKey(lua_State *L) {
  return 0;
}

static int L_SetEntry(lua_State *L) {
  return 0;
}

static int L_SetWidth(lua_State *L) {
  return 0;
}
