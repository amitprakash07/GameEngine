return
{

-- ===============================MeshBuilder=========================
	{
		BuildTool = "MeshBuilder.exe",
		{
			src = "ComputerGraphics/Cube.lua",
			target = "ComputerGraphics/Cube.mesh",
		},	
		{
			src = "ComputerGraphics/floor.lua",
			target = "ComputerGraphics/floor.mesh",
		},		
		{
			src = "ComputerGraphics/reflectiveSphere.lua",
			target = "ComputerGraphics/reflectiveSphere.mesh",
		},
		{
			src = "ComputerGraphics/Torus.lua",
			target = "ComputerGraphics/Torus.mesh",
		},	
		{
			src = "ComputerGraphics/environmentMappingSphere.lua",
			target = "ComputerGraphics/environmentMappingSphere.mesh",
		},				
	},
-- =====================================================================

-- ===============================EffectBuilder=========================
	{
		BuildTool = "EffectBuilder.exe",
		{
			src = "ComputerGraphics/cubeEffect.lua",
			target = "ComputerGraphics/cubeEffect.effect"
		},	
		{
			src = "ComputerGraphics/floorEffect.lua",
			target = "ComputerGraphics/floorEffect.effect"
		},		
		{
			src = "ComputerGraphics/reflectiveSphereEffect.lua",
			target = "ComputerGraphics/reflectiveSphereEffect.effect"
		},	
		{
			src = "ComputerGraphics/skyBoxEffect.lua",
			target = "ComputerGraphics/skyBoxEffect.effect"
		},
		{
			src = "ComputerGraphics/environmentMappingSphereEffect.lua",
			target = "ComputerGraphics/environmentMappingSphereEffect.effect"
		},
	},

-- =======================================================================


-- ===============================MaterialBuilder=========================
	{
		BuildTool = "MaterialBuilder.exe",
		{
			src = "ComputerGraphics/cubeMaterial.lua",
			target = "ComputerGraphics/cubeMaterial.mat",
		},				
		{
			src = "ComputerGraphics/floorMaterial.lua",
			target = "ComputerGraphics/floorMaterial.mat",
		},
		{
			src = "ComputerGraphics/reflectiveSphereMaterial.lua",
			target = "ComputerGraphics/reflectiveSphereMaterial.mat",
		},
		{
			src = "ComputerGraphics/skyBoxMaterial.lua",
			target = "ComputerGraphics/skyBoxMaterial.mat",
		},		
		{
			src = "ComputerGraphics/environmentMappingSphereMaterial.lua",
			target = "ComputerGraphics/environmentMappingSphereMaterial.mat",
		},
	},

-- ======================================================================


-- ===============================ShaderBuilder=========================
	{
		BuildTool = "ShaderBuilder.exe",
		
		{
			src = "ComputerGraphics/cubeVertex.glsl",
			target = "ComputerGraphics/cubeVertex.glsl",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},

		{
			src = "ComputerGraphics/cubeFragment.glsl",
			target = "ComputerGraphics/cubeFragment.glsl",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}

		},
		-- *******************************************************************
		{
			src = "ComputerGraphics/floorVertex.glsl",
			target = "ComputerGraphics/floorVertex.glsl",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},

		{
			src = "ComputerGraphics/floorFragment.glsl",
			target = "ComputerGraphics/floorFragment.glsl",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}

		},
	-- *******************************************************************
		{
			src = "ComputerGraphics/reflectiveSphereVertex.glsl",
			target = "ComputerGraphics/reflectiveSphereVertex.glsl",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},

		{
			src = "ComputerGraphics/reflectiveSphereFragment.glsl",
			target = "ComputerGraphics/reflectiveSphereFragment.glsl",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}

		},
	-- *******************************************************************
		{
			src = "ComputerGraphics/skyBoxVertex.glsl",
			target = "ComputerGraphics/skyBoxVertex.glsl",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},

		{
			src = "ComputerGraphics/skyBoxFragment.glsl",
			target = "ComputerGraphics/skyBoxFragment.glsl",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}

		},
	-- *******************************************************************		
		{
			src = "ComputerGraphics/environmentMappingSphereVertex.glsl",
			target = "ComputerGraphics/environmentMappingSphereVertex.glsl",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},

		{
			src = "ComputerGraphics/environmentMappingSphereFragment.glsl",
			target = "ComputerGraphics/environmentMappingSphereFragment.glsl",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}

		},
	-- *******************************************************************	
	
	},

-- ====================================================================


-- ===============================TextureBuilder=========================
	
	{
		BuildTool = "TextureBuilder.exe",
		{
			src = "ComputerGraphics/myFace.dds",
			target = "ComputerGraphics/myFace.dds",
		},				
		{
			src = "ComputerGraphics/checkerBoard.jpg",
			target = "ComputerGraphics/checkerBoard.jpg",
		},
		{
			src = "ComputerGraphics/defaultTexture.png",
			target = "ComputerGraphics/defaultTexture.png",
		},
		{
			src = "ComputerGraphics/Yokohama3.dds",
			target = "ComputerGraphics/Yokohama3.dds",
		},
		{
			src = "ComputerGraphics/LancellottiChapel.dds",
			target = "ComputerGraphics/LancellottiChapel.dds",
		},
	}
-- ====================================================================

}
