return
{
-- ===============================MeshBuilder=========================
	{
		BuildTool = "MeshBuilder.exe",
		{
			src = "Game/Arena/ceilingMaterialMesh.lua",
			target = "Game/Arena/ceilingMaterialMesh.mesh",
		},		
		{
			src = "Game/Arena/cementMaterialMesh.lua",
			target = "Game/Arena/cementMaterialMesh.mesh",	
		},		
		{
			src = "Game/Arena/FloorMaterialMesh.lua",
			target = "Game/Arena/FloorMaterialMesh.mesh",	
		},
		{
			src = "Game/Arena/LambertTwoMaterialMesh.lua",
			target = "Game/Arena/LambertTwoMaterialMesh.mesh",
		},
		{
			src = "Game/Arena/MetalMaterialMesh.lua",
			target = "Game/Arena/MetalMaterialMesh.mesh",
		},
		{
			src = "Game/Arena/railingMaterialMesh.lua",
			target = "Game/Arena/railingMaterialMesh.mesh",
		},
		{
			src = "Game/Arena/wallsMaterialMesh.lua",
			target = "Game/Arena/wallsMaterialMesh.mesh",
		},	
		{
			src = "Game/DebugCubeForClass.lua",
			target = "Game/DebugCubeForClass.mesh",
		},
		{
			src = "Game/DebugCylinderForClass.lua",
			target = "Game/DebugCylinderForClass.mesh",
		},
		{
			src = "Game/DebugSphereForClass.lua",
			target = "Game/DebugSphereForClass.mesh",
		},		
	},

-- =====================================================================

-- ===============================EffectBuilder=========================

	{
		BuildTool = "EffectBuilder.exe",
		{
			src = "Game/standardEffect.lua",
			target = "Game/standardEffect.effect"
		},
		{
			src = "Game/transparentEffect.lua",
			target = "Game/transparentEffect.effect"
		},
		{
			src = "Game/lineEffect.lua",
			target = "Game/lineEffect.effect"
		},
		{
			src = "Game/spriteEffect.lua",
			target = "Game/spriteEffect.effect"
		},
		{
			src = "Game/standardEffectWithSpecAndNormal.lua",
			target = "Game/standardEffectWithSpecAndNormal.effect"
		},

	},

-- =======================================================================


-- ===============================MaterialBuilder=========================
	{
		BuildTool = "MaterialBuilder.exe",
		{
			src = "Game/Arena/ceilingMaterial.lua",
			target = "Game/Arena/ceilingMaterial.mat",
		},
		{
			src = "Game/Arena/cementMaterial.lua",
			target = "Game/Arena/cementMaterial.mat",
		},
		{
			src = "Game/Arena/floorMaterial.lua",
			target = "Game/Arena/floorMaterial.mat",
		},
		{
			src = "Game/Arena/lambertTwoMaterial.lua",
			target = "Game/Arena/lambertTwoMaterial.mat",
		},
		{
			src = "Game/Arena/metalMaterial.lua",
			target = "Game/Arena/metalMaterial.mat",
		},
		{
			src = "Game/Arena/railingMaterial.lua",
			target = "Game/Arena/railingMaterial.mat",
		},
		{
			src = "Game/Arena/wallsMaterial.lua",
			target = "Game/Arena/wallsMaterial.mat",
		},
		{
			src = "Game/defaultDebugShapes.lua",
			target = "Game/defaultDebugShapes.mat",
		},
		{
			src = "Game/defaultMaterial.lua",
			target = "Game/defaultMaterial.mat",
		},
		{
			src = "Game/lineMaterial.lua",
			target = "Game/lineMaterial.mat",
		},	
		{
			src = "Game/spriteMaterial.lua",
			target = "Game/spriteMaterial.mat",
		},	
		{
			src = "Game/numbersMaterial.lua",
			target = "Game/numbersMaterial.mat",
		},
	},

-- ======================================================================


-- ===============================ShaderBuilder=========================

	{
		BuildTool = "ShaderBuilder.exe",
		{
			src = "Game/standard.fshd",
			target = "Game/standard.fshd",
			optionaltype = "fragment",
			dependencies =
			{
				"Game/shader_common.inc"
			}

		},

		{
			src = "Game/standard.vshd",
			target = "Game/standard.vshd",
			optionaltype = "vertex",
			dependencies =
			{
				"Game/shader_common.inc"
			}
		},

-- *******************************************************************

		{
			src = "Game/transparent.fshd",
			target = "Game/transparent.fshd",
			optionaltype = "fragment",
			dependencies = 
			{
				"Game/shader_common.inc"
			}
		},

-- *******************************************************************
		{
			src = "Game/line.vshd",			
			target = "Game/line.vshd",
			optionaltype = "vertex",
			dependencies = 
			{
				"Game/shader_common.inc"
			}
		},
		
		{
			src = "Game/line.fshd",
			target = "Game/line.fshd",
			optionaltype = "fragment",
			dependencies = 
			{
				"Game/shader_common.inc"
			}
		},

-- *******************************************************************
		{
			src = "Game/spriteVertex.glsl",			
			target = "Game/spriteVertex.glsl",
			optionaltype = "vertex",
			dependencies = 
			{
				"Game/shader_common.inc"
			}
		},
		
		{
			src = "Game/spriteFragment.glsl",
			target = "Game/spriteFragment.glsl",
			optionaltype = "fragment",
			dependencies = 
			{
				"Game/shader_common.inc"
			}
		},
-- *******************************************************************
		{
			src = "Game/standardVertexWithSpecAndNormal.glsl",			
			target = "Game/standardVertexWithSpecAndNormal.glsl",
			optionaltype = "vertex",
			dependencies = 
			{
				"Game/shader_common.inc"
			}
		},
		
		{
			src = "Game/standardFragmentWithSpecAndNormal.glsl",
			target = "Game/standardFragmentWithSpecAndNormal.glsl",
			optionaltype = "fragment",
			dependencies = 
			{
				"Game/shader_common.inc"
			}
		},
-- *******************************************************************
	},

-- ====================================================================


-- ===============================TextureBuilder=========================	
	{
		BuildTool = "TextureBuilder.exe",
		--cement wall_D
		{
			src = "Game/Arena/cement_wall_COLOR.dds",
			target = "Game/Arena/cement_wall_COLOR.dds",
		},
		{
			src = "Game/Arena/cement_wall_D.png",
			target = "Game/Arena/cement_wall_D.png",
		},
		{
			src = "Game/Arena/cement_wall_NRM.dds",
			target = "Game/Arena/cement_wall_NRM.dds",
		},
		{
			src = "Game/Arena/cement_wall_SPEC.dds",
			target = "Game/Arena/cement_wall_SPEC.dds",
		},
		-- floor_D
		{
			src = "Game/Arena/floor_COLOR.dds",
			target = "Game/Arena/floor_COLOR.dds",
		},
		{
			src = "Game/Arena/floor_D.png",
			target = "Game/Arena/floor_D.png",
		},
		{
			src = "Game/Arena/floor_NRM.dds",
			target = "Game/Arena/floor_NRM.dds",
		},
		{
			src = "Game/Arena/floor_SPEC.dds",
			target = "Game/Arena/floor_SPEC.dds",
		},
		-- metal_brace_D
		{
			src = "Game/Arena/metal_brace_COLOR.dds",
			target = "Game/Arena/metal_brace_COLOR.dds",
		},
		{
			src = "Game/Arena/metal_brace_D.png",
			target = "Game/Arena/metal_brace_D.png",
		},
		{
			src = "Game/Arena/metal_brace_NRM.dds",
			target = "Game/Arena/metal_brace_NRM.dds",
		},
		{
			src = "Game/Arena/metal_brace_SPEC.dds",
			target = "Game/Arena/metal_brace_SPEC.dds",
		},
		--railing_D
		{
			src = "Game/Arena/railing_COLOR.dds",
			target = "Game/Arena/railing_COLOR.dds",
		},
		{
			src = "Game/Arena/railing_D.png",
			target = "Game/Arena/railing_D.png",
		},
		{
			src = "Game/Arena/railing_NRM.dds",
			target = "Game/Arena/railing_NRM.dds",
		},
		{
			src = "Game/Arena/railing_SPEC.dds",
			target = "Game/Arena/railing_SPEC.dds",
		},
		--wall_D
		{
			src = "Game/Arena/wall_COLOR.dds",
			target = "Game/Arena/wall_COLOR.dds",
		},
		{
			src = "Game/Arena/wall_D.png",
			target = "Game/Arena/wall_D.png",
		},
		{
			src = "Game/Arena/wall_NRM.dds",
			target = "Game/Arena/wall_NRM.dds",
		},
		{
			src = "Game/Arena/wall_SPEC.dds",
			target = "Game/Arena/wall_SPEC.dds",
		},
		--Default Texture
		{
			src = "Game/defaultTexture.png",
			target = "Game/defaultTexture.png",
		},	
		-- Game Logo
		{
			src = "Game/logo.png",
			target = "Game/logo.png",
		},
		--Sprite
		{
			src = "Game/numbers.png",
			target = "Game/numbers.png",
		},	
	}
-- ====================================================================
}
