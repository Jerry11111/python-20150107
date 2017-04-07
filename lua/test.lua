print("Hello World!")
-- table
function test_table()
	a = {}
	x = "y"
	a[x] = 10 -- put 10 in field "y"
	a[1] = "a"
	a["c"] = "a"
	print(a[x]) --> 10 -- value of field "y"
	print(a.x) --> nil -- value of field "x" (undefined)
	print(a.y) --> 10 -- value of field "y"
	print(type(a))
	for k, v in pairs(a) do print(k, v) end -- print table
	print(os.date())
end
--test_table()
function test_common()
	print("abc")
	print(1, 2, "abc")
	a, b, c = 1, 2, 3
	print(a, b, c)
	-- local 表示局部变量, 只能在代码块中有效, 默认为全局变量
	counter = 0
	while counter <= 3 do
		local loc1 = 2
		glo1 = 2
		print(counter)
		counter = counter + 1
	end
	print(loc1, glo1)-- loc1 invisiable, glo1 visible
end
test_common()
