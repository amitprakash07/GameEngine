return 
{
	effect = "Game/standardEffectWithSpecAndNormalWithSSAO.effect",
	map =
	{
		{
			path = "Game/Arena/metal_brace_D.png",
			uniformName = "g_TextureSampler",
			shader = "Fragment",
			mapType = "albedo",
		},
		{
			path = "Game/Arena/metal_brace_NRM.dds",
			uniformName = "g_NormalTextureSampler",
			shader = "Fragment",
			mapType = "normal",
		},
		{
			path = "Game/Arena/metal_brace_SPEC.dds",
			uniformName = "g_SpecularTextureSampler",
			shader = "Fragment",
			mapType = "specular",
		}		
	},
	uniforms =
	{
		{
			name = "g_PixelColorModifier",
			shader = "fragment",
			valtype = "Float",
			value = {1.0,1.0,1.0},
		},
		{
			name = "glossiness",
			shader = "fragment",
			valtype = "Float",
			value = {1.0},
		}
	}	
}