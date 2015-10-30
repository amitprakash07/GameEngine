return
{
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
	},


	{
		BuildTool = "EffectBuilder.exe",
		{
			src = "standardEffect.lua",
			target = "standardEffect.effect",
		}
	},

	{
		BuildTool = "ShaderBuilder.exe",
		{
			src = "standard.fshd",
			target = "standard.fshd",
			type = "fragment"
		},

		{
			src = "standard.vshd",
			target = "standard.vshd",
			type = "vertex"
		}
	}

}
