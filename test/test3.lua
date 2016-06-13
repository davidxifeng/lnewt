#!/usr/bin/env lua53

local n = require('newt')

n.Init()
n.Cls()

local menu = {
  "Item 1",
  "Item 2",
  "Item 3",
  "Item 4",
  "Item 5",
  "Item 6",
  "Item 7",
  "Item 8",
  "Item 9",
  "Item 10",
  "Item 11",
  "Item 12",
}

local function main()
  local menuitem = {}
  local width = 0
  local hotkey = {}

  for i, v in ipairs(menu) do
    if i <= 12 then
      v = string.format("[F%d] %s", i, v)
      table.insert(hotkey, n['KEY_F' .. i])
    end
    if width < #v then width = #v end
    menuitem[i] = v
  end

  local msg = "Newt Test 3"
  local cols, rows = n.GetScreenSize()
  local height = #menuitem
  if #menuitem > (rows - 12) then height = rows - 12 end

  n.DrawRootText(0, 0, msg)
  n.DrawRootText((cols - #msg) / 2, rows / 2, msg)

  n.PushHelpLine(nil)

  n.CenteredWindow(width + 4, height + 2, "Menu")
  form = n.Form()

  flags = n.FLAG_RETURNEXIT
  if height < #menuitem then flags = flags + n.FLAG_SCROLL end

  list = n.Listbox(1, 1, height, flags)
  list:AppendEntry(menuitem)

  form:AddComponents(list)
  form:AddHotKey(hotkey)

  local r, v = form:Run()
  local sel
  if r == n.EXIT_COMPONENT and v and v:ID() == list:ID() then
    sel = list:GetCurrent()
  elseif r == n.EXIT_HOTKEY then
    sel = v - n.KEY_F1 + 1
  end

  n.Finished()
  return sel
end

local ok, sel = xpcall(main, debug.traceback)
if not ok then
  n.Finished()
  print(sel)
else
  print(menu[sel])
end

