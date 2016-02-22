return
{
	{
		BuildTool = "MeshBuilder.exe",
		{
			src = "ComputerGraphics/CubeForCubeMap.lua",
			target = "ComputerGraphics/CubeForCubeMap.mesh",
		},				
	},

	{
		BuildTool = "EffectBuilder.exe",
		{
			src = "ComputerGraphics/cubeMap.lua",
			target = "ComputerGraphics/cubeMap.effect"
		},				
	},

	{
		BuildTool = "ShaderBuilder.exe",
		{
			src = "ComputerGraphics/cubeMap.fshd",
			target = "ComputerGraphics/cubeMap.fshd",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}

		},

		{
			src = "ComputerGraphics/cubeMap.vshd",
			target = "ComputerGraphics/cubeMap.vshd",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},		
	},
	
	{
		BuildTool = "MaterialBuilder.exe",
		{
			src = "ComputerGraphics/cubeMap.lua",
			target = "ComputerGraphics/cubeMap.mat",
		},				
	},
	
	{
		BuildTool = "TextureBuilder.exe",
		{
			src = "ComputerGraphics/environment.dds",
			target = "ComputerGraphics/environment.dds",
		},				
	}
}
