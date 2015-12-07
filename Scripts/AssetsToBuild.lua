return
{
	{
		BuildTool = "MeshBuilder.exe",
		{
			src = "cubeOpaque.lua",
			target = "cubeOpaque.mesh",
		},		
		{
			src = "CylinderOpaque.lua",
			target = "CylinderOpaque.mesh",	
		},		
		{
			src = "HelixOpaque.lua",
			target = "HelixOpaque.mesh",	
		},

		{
			src = "PlaneOpaque.lua",
			target = "PlaneOpaque.mesh",
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
	},
	
	{
		BuildTool = "MaterialBuilder.exe",
		{
			src = "BlueStandard.lua",
			target = "BlueStandard.mat",
		},
		{
			src = "GreenStandard.lua",
			target = "GreenStandard.mat",
		},
		{
			src = "RedTransparent.lua",
			target = "RedTransparent.mat",
		},
		{
			src = "YellowTransparent.lua",
			target = "YellowTransparent.mat",
		},
		{
			src = "standardMaterial.lua",
			target = "standardMaterial.mat",
		},
	},
	
	{
		BuildTool = "TextureBuilder.exe",
		{
			src = "alpha.png",
			target = "alpha.png",
		},
		
		{
			src = "bricks.png",
			target = "bricks.png",
		},
		
		{
			src = "clouds.png",
			target = "clouds.png",
		},
		
		{
			src = "eae6320.png",
			target = "eae6320.png",
		},
	}
}
