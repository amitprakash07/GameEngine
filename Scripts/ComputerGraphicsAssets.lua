return
{
	{
		BuildTool = "MeshBuilder.exe",
		{
			src = "ComputerGraphics/CubeForCubeMap.lua",
			target = "ComputerGraphics/CubeForCubeMap.mesh",
		},	
		{
			src = "ComputerGraphics/CheckerBoardPlane.lua",
			target = "ComputerGraphics/CheckerBoardPlane.mesh",
		},		
		{
			src = "ComputerGraphics/DefaultCube.lua",
			target = "ComputerGraphics/DefaultCube.mesh",
		},
		{
			src = "ComputerGraphics/DefaultSphere.lua",
			target = "ComputerGraphics/DefaultSphere.mesh",
		},			
	},

	{
		BuildTool = "EffectBuilder.exe",
		{
			src = "ComputerGraphics/cubeMap.lua",
			target = "ComputerGraphics/cubeMap.effect"
		},	
		{
			src = "ComputerGraphics/skyBox.lua",
			target = "ComputerGraphics/skyBox.effect"
		},		
		{
			src = "ComputerGraphics/standardEffect.lua",
			target = "ComputerGraphics/standardEffect.effect"
		},	
		{
			src = "ComputerGraphics/environmentMappingEffect.lua",
			target = "ComputerGraphics/environmentMappingEffect.effect"
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
		
		{
			src = "ComputerGraphics/skyBox.vshd",
			target = "ComputerGraphics/skyBox.vshd",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},
		
		{
			src = "ComputerGraphics/skyBox.fshd",
			target = "ComputerGraphics/skyBox.fshd",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},	

		{
			src = "ComputerGraphics/standard.vshd",
			target = "ComputerGraphics/standard.vshd",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},
		
		{
			src = "ComputerGraphics/standard.fshd",
			target = "ComputerGraphics/standard.fshd",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},

		{
			src = "ComputerGraphics/environmentMap.vshd",
			target = "ComputerGraphics/environmentMap.vshd",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},
		
		{
			src = "ComputerGraphics/environmentMap.fshd",
			target = "ComputerGraphics/environmentMap.fshd",
			optionaltype = "fragment",
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
		{
			src = "ComputerGraphics/skyBox.lua",
			target = "ComputerGraphics/skyBox.mat",
		},
		{
			src = "ComputerGraphics/checkerBoardMaterial.lua",
			target = "ComputerGraphics/checkerBoardMaterial.mat",
		},
		{
			src = "ComputerGraphics/defaultMaterial.lua",
			target = "ComputerGraphics/defaultMaterial.mat",
		},
		{
			src = "ComputerGraphics/environmentMappingMaterial.lua",
			target = "ComputerGraphics/environmentMappingMaterial.mat",
		},
	},
	
	{
		BuildTool = "TextureBuilder.exe",
		{
			src = "ComputerGraphics/environment.dds",
			target = "ComputerGraphics/environment.dds",
		},				
		{
			src = "ComputerGraphics/checkerBoard.jpg",
			target = "ComputerGraphics/checkerBoard.dds",
		},
		{
			src = "ComputerGraphics/defaultTexture.png",
			target = "ComputerGraphics/defaultTexture.png",
		},
	}
}
