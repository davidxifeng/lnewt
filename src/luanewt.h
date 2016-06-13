#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <lua.h>
#include <lauxlib.h>
#include <newt.h>


#define TYPE_FORM -1
#define TYPE_UNKNOWN 0
#define TYPE_LABEL 1
#define TYPE_ENTRY 2
#define TYPE_BUTTON 3
#define TYPE_CHECKBOX 4
#define TYPE_RADIOBUTTON 5
#define TYPE_LISTBOX 6
#define TYPE_SCALE 7
#define TYPE_TEXTBOX 8


/* libnewt internals - very naughty */

struct newtComponent_struct {
    /* common data */
    int height, width;
    int top, left;
    int takesFocus;
    int isMapped;

    struct componentOps * ops;

    newtCallback callback;
    void * callbackData;

    newtCallback destroyCallback;
    void * destroyCallbackData;

    void * data;
};

/* Holds all the relevant information for this listbox */
struct listbox {
    newtComponent sb;
    int curWidth;
    int curHeight;
    int sbAdjust;
    int bdxAdjust, bdyAdjust;
    int numItems, numSelected;
    int userHasSetWidth;
    int currItem, startShowItem;
    int isActive;
    struct items *boxItems;
    int grow;
    int flags;
};


/** wrapper structs **/

struct com_t {
  newtComponent p;
  int t;
};

typedef struct com_t * component;

/** module registration **/

/* open the library - used by require() */
LUALIB_API int luaopen_newt(lua_State *L);

/** exported functions **/

/* root functions */
static int L_Init(lua_State *L);
static int L_Cls(lua_State *L);
static int L_WaitForKey(lua_State *L);
static int L_ClearKeyBuffer(lua_State *L);
static int L_DrawRootText(lua_State *L);
static int L_OpenWindow(lua_State *L);
static int L_CenteredWindow(lua_State *L);
static int L_PopWindow(lua_State *L);
static int L_PushHelpLine(lua_State *L);
static int L_PopHelpLine(lua_State *L);
static int L_Refresh(lua_State *L);
static int L_Finished(lua_State *L);
static int L_WinMessage(lua_State *L);
static int L_Suspend(lua_State *L);
static int L_Resume(lua_State *L);
static int L_SetSuspendCallback(lua_State *L);
static int L_Bell(lua_State *L);
static int L_CursorOff(lua_State *L);
static int L_CursorOn(lua_State *L);
static int L_Delay(lua_State *L);
static int L_GetScreenSize(lua_State *L);
static int L_ReflowText(lua_State *L);

/* widgets */
static int L_Button(lua_State *L);
static int L_CompactButton(lua_State *L);
static int L_Checkbox(lua_State *L);
static int L_Entry(lua_State *L);
static int L_Form(lua_State *L);
static int L_Label(lua_State *L);
static int L_Textbox(lua_State *L);
static int L_TextboxReflowed(lua_State *L);
static int L_Listbox(lua_State *L);
static int L_Radiobutton(lua_State *L);
static int L_Scale(lua_State *L);
static int L_VerticalScrollbar(lua_State *L);

/* Newt.Component Object */
static int L_AddCallback(lua_State *L);
static int L_AddComponents(lua_State *L);
static int L_AddHotKey(lua_State *L);
static int L_AppendEntry(lua_State *L);
static int L_Clear(lua_State *L);
static int L_ClearSelection(lua_State *L);
static int L_DeleteEntry(lua_State *L);
static int L_Destroy(lua_State *L);
static int L_Draw(lua_State *L);
static int L_GetCurrent(lua_State *L);
static int L_GetSelection(lua_State *L);
static int L_GetNumLines(lua_State *L);
static int L_GetValue(lua_State *L);
static int L_InsertEntry(lua_State *L);
static int L_ID(lua_State *L);
static int L_Run(lua_State *L);
static int L_SelectItem(lua_State *L);
static int L_Set(lua_State *L);
static int L_SetBackground(lua_State *L);
static int L_SetCurrent(lua_State *L);
static int L_SetCurrentByKey(lua_State *L);
static int L_SetEntry(lua_State *L);
static int L_SetHeight(lua_State *L);
static int L_SetText(lua_State *L);
static int L_SetTimer(lua_State *L);
static int L_SetType(lua_State *L);
static int L_SetValue(lua_State *L);
static int L_SetWidth(lua_State *L);
static int L_TakesFocus(lua_State *L);
static int L_Text(lua_State *L);
