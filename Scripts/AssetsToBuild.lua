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
			target = "SquareMesh.mesh",
		},
		{
			src = "TriangleMesh.lua",
			target = "TriangleMesh.mesh",
		}
	}

}
