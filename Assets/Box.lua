--[[
	Mesh for drawing Box
]]
return
{
	vertices =
	{
		{
			position = {-1, -1, 1},
			color = {1.0,0.0,0.0,1.0}
		},
		
		{
			position = {1, -1, 1},
			color = {0.0,1.0,0.0,1.0}
		},
		
		{
			position = {1, 1, 1},
			color = {0.0,0.0,1.0,1.0}
		},
		
		{
			position = {-1, 1, 1},
			color = {1.0,1.0,1.0,1.0}
		},
		
		{
			position = {-1, -1, -1},
			color = {1.0,1.0,1.0,1.0}
		},
		
		{
			position = {1, -1, -1},
			color = {0.0,0.0,1.0,1.0}
		},
		
		{
			position = {1, 1, -1},
			color = {0.0,1.0,0.0,1.0}
		},
		
		{
			position = {-1, 1, -1},
			color = {1.0,0.0,0.0,1.0}
		}
	},
	-- Describing Indices
	indices =
	{
		winding = "right",
		nooftriangles = 12,
		{4,6,5}, {4,7,6}, --back
		{0,1,2}, {0,2,3}, --front
		{1,5,6}, {1,6,2}, -- right side
		{0,3,7}, {0,7,4}, --left side
		{2,6,7}, {2,7,3}, --top
		{0,5,1}, {0,4,5}, --bottom
		
	}
}