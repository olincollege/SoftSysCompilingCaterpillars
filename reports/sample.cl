x = 1
y = 1
z = x + y
a = x - 7
b = 19.5 + 32.674
result = y / x
testing = 10 * a

if result > a
  result = result - 5
else
  result = result + 5
endif

if z < b
  b = z
endif

while testing ! 0
  testing = testing - 1
  result = testing * result
endwhile
