return 
{
	effect = "Game/standardEffectWithSpecAndNormalWithSSAO.effect",
	map =
	{
		{
			path = "ComputerGraphics/NanoSuit/glass_dif.png",
			uniformName = "g_TextureSampler",
			shader = "Fragment",
			mapType = "albedo",
		},
		{
			path = "ComputerGraphics/NanoSuit/glass_ddn.png",
			uniformName = "g_NormalTextureSampler",
			shader = "Fragment",
			mapType = "normal",
		},
		{
			path = "ComputerGraphics/defaultTexture.png",
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
			value = {10.0},
		}
	}	
}