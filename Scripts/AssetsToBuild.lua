return
{
	{
		BuildTool = "MeshBuilder.exe",
		{
			src = "SquareMesh.lua",
			target = "SquareMesh.mesh",
		},
		
		{
			src = "Floor_Maya.lua",
			target = "Floor_Maya.mesh",	
		},
		
		{
			src = "Sphere_Maya.lua",
			target = "Sphere_Maya.mesh",	
		},

		{
			src = "TriangleMesh.lua",
			target = "TriangleMesh.mesh",
		},
		
		{
			src = "Cube_Maya.lua",
			target = "Cube_Maya.mesh",
		},
		
		{
			src = "Floor.lua",
			target = "Floor.mesh"
		},
		
		{
			src = "Helix.lua",
			target = "Helix.mesh",
		},
		
		{
			src = "Room.lua",
			target = "Room.mesh",		
		},		
		
		{
			src = "TraansSphere_Maya.lua",
			target = "TraansSphere_Maya.mesh",
		},
	},

	{
		BuildTool = "EffectBuilder.exe",
		{
			src = "standardEffect.lua",
			target = "standardEffect.effect"
		},
		{
			src = "transparentEffect.lua",
			target = "transparentEffect.effect"
		}
	},

	{
		BuildTool = "ShaderBuilder.exe",
		{
			src = "standard.fshd",
			target = "standard.fshd",
			optionaltype = "fragment",
			dependencies =
			{
				"shaders.inc"
			}

		},

		{
			src = "standard.vshd",
			target = "standard.vshd",
			optionaltype = "vertex",
			dependencies =
			{
				"shaders.inc"
			}
		},
		
		{
			src = "transparent.fshd",
			target = "transparent.fshd",
			optionaltype = "fragment",
			dependencies = 
			{
				"shaders.inc"
			}
		}
	}
}
