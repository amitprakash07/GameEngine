return
{
-- =========================Generic Builder===========================
--	{
		--BuildTool = "GenericBuilder",
		--{
			--src = "Fonts/arial.ttf",
			--target = "Fonts/arial.ttf"
		--}
	--},
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
		{
			src = "ComputerGraphics/NanoSuit/arms.lua",
			target = "ComputerGraphics/NanoSuit/arms.mesh",
		},
		{
			src = "ComputerGraphics/NanoSuit/body.lua",
			target = "ComputerGraphics/NanoSuit/body.mesh",
		},
		{
			src = "ComputerGraphics/NanoSuit/hands.lua",
			target = "ComputerGraphics/NanoSuit/hands.mesh",
		},
		{
			src = "ComputerGraphics/NanoSuit/Helmet.lua",
			target = "ComputerGraphics/NanoSuit/Helmet.mesh",
		},
		{
			src = "ComputerGraphics/NanoSuit/legs.lua",
			target = "ComputerGraphics/NanoSuit/legs.mesh",
		},
		{
			src = "ComputerGraphics/NanoSuit/lights.lua",
			target = "ComputerGraphics/NanoSuit/lights.mesh",
		},
		{
			src = "ComputerGraphics/NanoSuit/Visor.lua",
			target = "ComputerGraphics/NanoSuit/Visor.mesh",
		},	
		-- proxyLightSphere
		{
			src = "ComputerGraphics/proxyLightSphere.lua",
			target = "ComputerGraphics/proxyLightSphere.mesh",
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
		{
			src = "Game/standardEffectWithSpecAndNormalWithSSAO.lua",
			target = "Game/standardEffectWithSpecAndNormalWithSSAO.effect"
		},
		--proxyLightEffect
		{
			src = "ComputerGraphics/proxyLightEffect.lua",
			target = "ComputerGraphics/proxyLightEffect.effect"
		},
		--SSAO effect
		{
			src = "Game/SSAOEffect.lua",
			target = "Game/SSAOEffect.effect"
		},
		--Text effect
		{
			src = "Game/textEffect.lua",
			target = "Game/textEffect.effect"
		}		
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
		{
			src = "ComputerGraphics/NanoSuit/armsMaterial.lua",
			target = "ComputerGraphics/NanoSuit/armsMaterial.mat",
		},
		{
			src = "ComputerGraphics/NanoSuit/bodyMaterial.lua",
			target = "ComputerGraphics/NanoSuit/bodyMaterial.mat",
		},
		{
			src = "ComputerGraphics/NanoSuit/handsMaterial.lua",
			target = "ComputerGraphics/NanoSuit/handsMaterial.mat",
		},
		{
			src = "ComputerGraphics/NanoSuit/HelmetMaterial.lua",
			target = "ComputerGraphics/NanoSuit/HelmetMaterial.mat",
		},
		{
			src = "ComputerGraphics/NanoSuit/legsMaterial.lua",
			target = "ComputerGraphics/NanoSuit/legsMaterial.mat",
		},
		{
			src = "ComputerGraphics/NanoSuit/lightsMaterial.lua",
			target = "ComputerGraphics/NanoSuit/lightsMaterial.mat",
		},
		{
			src = "ComputerGraphics/NanoSuit/VisorMaterial.lua",
			target = "ComputerGraphics/NanoSuit/VisorMaterial.mat",
		},
		-- proxyLightSphere
		{
			src = "ComputerGraphics/proxyLightSphereMaterial.lua",
			target = "ComputerGraphics/proxyLightSphereMaterial.mat",
		},
		--SSAO Material
		{
			src = "Game/SSAOMaterial.lua",
			target = "Game/SSAOMaterial.mat",
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
		{
			src = "ComputerGraphics/teapotVertex.glsl",
			target = "ComputerGraphics/teapotVertex.glsl",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},

		{
			src = "ComputerGraphics/teapotFragment.glsl",
			target = "ComputerGraphics/teapotFragment.glsl",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}

		},
	-- *******************************************************************
		{
			src = "ComputerGraphics/SSAOPassVertex.glsl",
			target = "ComputerGraphics/SSAOPassVertex.glsl",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},

		{
			src = "ComputerGraphics/SSAOPassFragment.glsl",
			target = "ComputerGraphics/SSAOPassFragment.glsl",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}

		},
	-- *******************************************************************
		{
			src = "Game/standardVertexWithSpecAndNormalWithSSAO.glsl",
			target = "Game/standardVertexWithSpecAndNormalWithSSAO.glsl",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},

		{
			src = "Game/standardFragmentWithSpecAndNormalWithSSAO.glsl",
			target = "Game/standardFragmentWithSpecAndNormalWithSSAO.glsl",
			optionaltype = "fragment",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}

		},
	-- *******************************************************************
		{
			src = "Game/textVertex.glsl",
			target = "Game/textVertex.glsl",
			optionaltype = "vertex",
			dependencies =
			{
				"ComputerGraphics/shader_common.inc"
			}
		},

		{
			src = "Game/textFragment.glsl",
			target = "Game/textFragment.glsl",
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
		{
			src = "ComputerGraphics/defaultTexture.png",
			target = "ComputerGraphics/defaultTexture.png",
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
		--NanoSuit
		{
			src = "ComputerGraphics/NanoSuit/arm_dif.png",
			target = "ComputerGraphics/NanoSuit/arm_dif.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/arm_showroom_ddn.png",
			target = "ComputerGraphics/NanoSuit/arm_showroom_ddn.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/arm_showroom_spec.png",
			target = "ComputerGraphics/NanoSuit/arm_showroom_spec.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/body_dif.png",
			target = "ComputerGraphics/NanoSuit/body_dif.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/body_showroom_ddn.png",
			target = "ComputerGraphics/NanoSuit/body_showroom_ddn.png",
		},{
			src = "ComputerGraphics/NanoSuit/body_showroom_spec.png",
			target = "ComputerGraphics/NanoSuit/body_showroom_spec.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/cell_arm_alpha.png",
			target = "ComputerGraphics/NanoSuit/cell_arm_alpha.png",
		},{
			src = "ComputerGraphics/NanoSuit/cell_body_alpha.png",
			target = "ComputerGraphics/NanoSuit/cell_body_alpha.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/cell_ddn.png",
			target = "ComputerGraphics/NanoSuit/cell_ddn.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/cell_hand_alpha.png",
			target = "ComputerGraphics/NanoSuit/cell_hand_alpha.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/cell_helmet_alpha.png",
			target = "ComputerGraphics/NanoSuit/cell_helmet_alpha.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/cell_leg_alpha.png",
			target = "ComputerGraphics/NanoSuit/cell_leg_alpha.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/glass_ddn.png",
			target = "ComputerGraphics/NanoSuit/glass_ddn.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/glass_dif.png",
			target = "ComputerGraphics/NanoSuit/glass_dif.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/hand_dif.png",
			target = "ComputerGraphics/NanoSuit/hand_dif.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/hand_showroom_ddn.png",
			target = "ComputerGraphics/NanoSuit/hand_showroom_ddn.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/hand_showroom_spec.png",
			target = "ComputerGraphics/NanoSuit/hand_showroom_spec.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/helmet_dif.png",
			target = "ComputerGraphics/NanoSuit/helmet_dif.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/helmet_showroom_ddn.png",
			target = "ComputerGraphics/NanoSuit/helmet_showroom_ddn.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/helmet_showroom_spec.png",
			target = "ComputerGraphics/NanoSuit/helmet_showroom_spec.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/leg_dif.png",
			target = "ComputerGraphics/NanoSuit/leg_dif.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/leg_showroom_ddn.png",
			target = "ComputerGraphics/NanoSuit/leg_showroom_ddn.png",
		},
		{
			src = "ComputerGraphics/NanoSuit/leg_showroom_spec.png",
			target = "ComputerGraphics/NanoSuit/leg_showroom_spec.png",
		},
	}
-- ====================================================================
}
