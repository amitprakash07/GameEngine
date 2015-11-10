--[[
	Mesh for drawing Plane
]]
return
{
	vertices =
	{
		{
			position = {-4, -2, 4},
			color = {0.5,1.0,0.1,1.0}
		},
		
		{
			position = {4, -2, 4},
			color = {0.5,1.0,0.1,1.0}
		},
		
		{
			position = {10, -2, -10},
			color = {0.5,1.0,0.1,1.0}
		},
		
		{
			position = {-10, -2, -10},
			color = {0.5,1.0,0.1,1.0}
		}
	},
	
	indices =
	{
		winding = "right",
		nooftriangles = 2,
		{0,1,2},
		{0,2,3}
	}
}