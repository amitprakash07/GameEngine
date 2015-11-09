--[[
	Mesh Lua file describing four vertices and Indices order for the traingle Mesh
	]]
return
{
	-- Describing Vertices
	vertices =
	{
		{
			position = {-0.25, -0.25, 0.25},
			color = {1.0,0.0,0.0,1.0}
		},
		{
			position = {0.25, -0.25, 0.25},
			color = {0.0,1.0,0.0,1.0}
		},
		{
			position = {0.25,0.25, 0.25},
			color = {0.0,0.0,1.0,1.0}
		},
		{
			position = {-0.25,0.25, 0.25},
			color = {0.5,0.5,0.5,1.0}
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
