require 'torch'
require 'dok'
require 'image'
require 'xlua'

local help_desc = [[
      Drawing primitives
]]

draw = {}

-- load C lib
require 'libdraw'

function draw.line(im, x1, y1, x2, y2, r, g, b)
   r = r or 0
   g = g or 0
   b = b or 0
   im.libdraw.drawLine(im, x1, y1, x2, y2, r, g, b)
end

function draw.point(im, x, y, radius, r, g, b)
   local radius2 = (radius-1)*(radius-1)
   for dx = -radius+1,radius-1 do
      if (x+dx >= 1) and (x+dx <= im:size(3)) then
	 for dy = -radius+1,radius-1 do
	    if (y+dy >= 1) and (y+dy <= im:size(2)) then
	       if dx*dx+dy*dy <= radius2 then
		  im[1][y+dy][x+dx] = r
		  im[2][y+dy][x+dx] = g
		  im[3][y+dy][x+dx] = b
	       end
	    end
	 end
      end
   end
end

function draw.circle(im, x, y, radius, r, g, b, thickness)
   thickness = thickness or 1
   local n = 20
   local delta = 2*math.pi/n
   local alpha = 0
   for i = 1,n do
      draw.line(im, x+radius*math.cos(alpha),
		y+radius*math.sin(alpha),
		x+radius*math.cos(alpha+delta),
		y+radius*math.sin(alpha+delta),
		r, g, b)
      alpha = alpha + delta
   end
end

function draw.testme()
   require 'image'
   local lena = image.lena()
   draw.line(lena, 100, 200, 400, 230, 1, 1, 1)
   image.display(lena)
end