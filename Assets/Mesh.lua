--[[
	Mesh Lua file describing four vertices and Indices order for the traingle Mesh
	]]
return 
{
	-- Describing Vertices
	vertices =
	{
		{
			index = 0,
			position = {0.0, 0.0},
			color = {1,0,0,1}
		},
		{
			index = 1,
			position = {1.0, 0.0},
			color = {0,1,0,1}
		},
		{
			index = 2,
			position = {1.0,1.0},
			color = {0,0,1,1}
		},
		{
			index = 3,
			position = {0.0,1.0},
			color = {0.5,0.5,0.5,1}
		}		
	},
	-- Describing Indices
	indices =
	{
		winding = "right",
		nooftriangles = 2,
		{0,1,2},
		{0,2,3}
	}
}