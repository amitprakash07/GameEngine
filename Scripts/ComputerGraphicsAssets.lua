return
{
	{
		BuildTool = "MeshBuilder.exe",
		{
			src = "Arena/ceilingMaterialMesh.lua",
			target = "Arena/ceilingMaterialMesh.mesh",
		},		
		{
			src = "Arena/cementMaterialMesh.lua",
			target = "Arena/cementMaterialMesh.mesh",	
		},		
		{
			src = "Arena/FloorMaterialMesh.lua",
			target = "Arena/FloorMaterialMesh.mesh",	
		},
		{
			src = "Arena/LambertTwoMaterialMesh.lua",
			target = "Arena/LambertTwoMaterialMesh.mesh",
		},
		{
			src = "Arena/MetalMaterialMesh.lua",
			target = "Arena/MetalMaterialMesh.mesh",
		},
		{
			src = "Arena/railingMaterialMesh.lua",
			target = "Arena/railingMaterialMesh.mesh",
		},
		{
			src = "Arena/wallsMaterialMesh.lua",
			target = "Arena/wallsMaterialMesh.mesh",
		},	
		{
			src = "DebugCubeForClass.lua",
			target = "DebugCubeForClass.mesh",
		},
		{
			src = "DebugCylinderForClass.lua",
			target = "DebugCylinderForClass.mesh",
		},
		{
			src = "DebugSphereForClass.lua",
			target = "DebugSphereForClass.mesh",
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
		},
		{
			src = "lineEffect.lua",
			target = "lineEffect.effect"
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
				"shader_common.inc"
			}

		},

		{
			src = "standard.vshd",
			target = "standard.vshd",
			optionaltype = "vertex",
			dependencies =
			{
				"shader_common.inc"
			}
		},
		
		{
			src = "transparent.fshd",
			target = "transparent.fshd",
			optionaltype = "fragment",
			dependencies = 
			{
				"shader_common.inc"
			}
		},
		
		{
			src = "line.vshd",
			target = "line.vshd",
			optionaltype = "vertex",
			dependencies = 
			{
				"shader_common.inc"
			}
		},
		
		{
			src = "line.fshd",
			target = "line.fshd",
			optionaltype = "fragment",
			dependencies = 
			{
				"shader_common.inc"
			}
		}
	},
	
	{
		BuildTool = "MaterialBuilder.exe",
		{
			src = "Arena/ceilingMaterial.lua",
			target = "Arena/ceilingMaterial.mat",
		},
		{
			src = "Arena/cementMaterial.lua",
			target = "Arena/cementMaterial.mat",
		},
		{
			src = "Arena/floorMaterial.lua",
			target = "Arena/floorMaterial.mat",
		},
		{
			src = "Arena/lambertTwoMaterial.lua",
			target = "Arena/lambertTwoMaterial.mat",
		},
		{
			src = "Arena/metalMaterial.lua",
			target = "Arena/metalMaterial.mat",
		},
		{
			src = "Arena/railingMaterial.lua",
			target = "Arena/railingMaterial.mat",
		},
		{
			src = "Arena/wallsMaterial.lua",
			target = "Arena/wallsMaterial.mat",
		},
		{
			src = "defaultDebugShapes.lua",
			target = "defaultDebugShapes.mat",
		},
		{
			src = "defaultMaterial.lua",
			target = "defaultMaterial.mat",
		},
		{
			src = "lineMaterial.lua",
			target = "lineMaterial.mat",
		},		
	},
	
	{
		BuildTool = "TextureBuilder.exe",
		{
			src = "Arena/cement_wall_D.png",
			target = "Arena/cement_wall_D.png",
		},
		{
			src = "Arena/floor_D.png",
			target = "Arena/floor_D.png",
		},
		{
			src = "Arena/metal_brace_D.png",
			target = "Arena/metal_brace_D.png",
		},
		{
			src = "Arena/railing_D.png",
			target = "Arena/railing_D.png",
		},
		{
			src = "Arena/wall_D.png",
			target = "Arena/wall_D.png",
		},
		{
			src = "defaultTexture.png",
			target = "defaultTexture.png",
		},		
	}
}
