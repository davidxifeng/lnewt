#!/usr/bin/env lua53

local n = require('newt')

n.Init()
n.Cls()

local function main()
  local msg = "Newt Test 2"
  local cols, rows = n.GetScreenSize()
  n.DrawRootText((cols - #msg) / 2, rows / 2, msg)

  n.PushHelpLine(nil)

  n.CenteredWindow(60, 20, "Test Form")
  form = n.Form()

  label = {
    n.Label(1, 1, "   Name"),
    n.Label(1, 2, "Street1"),
    n.Label(1, 3, "Street2"),
    n.Label(1, 4, "   City"), n.Label(35, 4, "State"), n.Label(44, 4, "Zip")
  }

  entry = {
    n.Entry(9, 1, "John Doe", 35),
    n.Entry(9, 2, "1234 Any Street", 50),
    n.Entry(9, 3, nil, 50),
    n.Entry(9, 4, "Any Town", 25), n.Entry(41, 4, "WA", 2), n.Entry(48, 4, "98000", 10)
  }

  radio = {}
  radio[1] = n.Radiobutton(1, 6, "Red", false)
  radio[2] = n.Radiobutton(1, 7, "Green", true, radio[1])
  radio[3] = n.Radiobutton(1, 8, "Blue", false, radio[2])

  check = {
    n.Checkbox(15, 6, "Option A"),
    n.Checkbox(15, 7, "Option B"),
    n.Checkbox(15, 8, "Option C")
  }

  button = {
    n.Button(16, 16, "[ESC] Cancel"),
    n.Button(34, 16, "[F12] Next")
  }

  form:AddComponents(label, entry, radio, check, button)

  r, v = form:Run()

  value = {
    name = entry[1]:GetValue(),
    street1 = entry[2]:GetValue(),
    street2 = entry[3]:GetValue(),
    city = entry[4]:GetValue(),
    state = entry[5]:GetValue(),
    zip = entry[6]:GetValue(),
    radio = radio[1]:GetCurrent():Text(),
    option = {
      a = check[1]:GetValue(),
      b = check[2]:GetValue(),
      c = check[3]:GetValue()
    }
  }

  if value.street2 == '' then value.street2 = nil end

  form:Destroy()

  if (r == n.EXIT_COMPONENT and v and v:Text() == '[F12] Next')
    or (r == n.EXIT_HOTKEY and v == n.KEY_F12) then

    n.PopWindow()

    n.CenteredWindow(40, 5, "Progress")
    form = n.Form()
    label = {
      n.Label(9, 1, "Processing Information"),
      n.Label(16, 2, " Step 1 ")
    }
    scale = n.Scale(1, 4, 38, 5)
    form:AddComponents(label)
    form:Draw()

    for i = 1, 5 do
      scale:Set(i)
      label[2]:SetText(string.format(" Step %d ", i))
      n.Refresh()
      os.execute('sleep 1')
    end

    form:Destroy()
    n.PopWindow()

  end

  n.Finished()
  return r, v
end

local ok, r, v = xpcall(main, debug.traceback)
if not ok then
  n.Finished()
  print(r)
else

  if r == n.EXIT_COMPONENT then
    if v:Text() == 'Next' then
      print(value.name)
      print(value.street1)
      if value.street2 then print(value.street2) end
      print(value.city .. ', ' .. value.state .. '  ' .. value.zip)
      print('Color: ' .. value.radio)
      local option = {}
      if value.option.a then table.insert(option, 'A') end
      if value.option.b then table.insert(option, 'B') end
      if value.option.c then table.insert(option, 'C') end
      print('Options: ' .. table.concat(option, ', '))
    elseif v:Text() == 'Cancel' then
      print("Canceled!")
    else
      print(v:ID(), "????")
    end
  else
    print(r, v)
  end

end
