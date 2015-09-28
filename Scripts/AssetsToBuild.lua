return
{
	{
		BuildTool = "GenericBuilder.exe",
		{
			src = "standard.fshd",
			target = "standard.fshd",
		},

		{
			src = "standard.vshd",
			target = "standard.vshd",
		}
	},


	{
		BuildTool = "MeshBuilder.exe",
		{
			src = "SquareMesh.lua",
			target = "SquareMesh.lua",
		},
		{
			src = "TriangleMesh.lua",
			target = "TriangleMesh.lua",
		}
	}

}
