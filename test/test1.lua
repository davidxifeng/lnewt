#!/usr/bin/env lua53

local newt = require('newt')

newt.Init()
newt.Cls()


local function main()
  local msg = "Hello World!"
  local cols, rows = newt.GetScreenSize()
  newt.DrawRootText((cols - #msg) / 2, rows / 2, msg)

  newt.PushHelpLine(nil)
  newt.Refresh()
  newt.WaitForKey()

  newt.PushHelpLine("Testing 1,2,3...")
  newt.Refresh()
  newt.WaitForKey()

  newt.PopHelpLine()
  newt.CenteredWindow(20, 4, "Window 1")
  newt.WaitForKey()

  newt.PopWindow()
  newt.OpenWindow(5, 5, 20, 4, "Window 2")
  newt.Refresh()
  newt.WaitForKey()

  newt.Finished()
end

local ok, r = xpcall(main, debug.traceback)
if not ok then
  newt.Finished()

  print(r)
end
