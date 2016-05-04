return 
{
	effect = "Game/standardEffectWithSpecAndNormalWithSSAO.effect",
	map =
	{
		{
			path = "ComputerGraphics/NanoSuit/leg_dif.png",
			uniformName = "g_TextureSampler",
			shader = "Fragment",
			mapType = "albedo",
		},
		{
			path = "ComputerGraphics/NanoSuit/leg_showroom_ddn.png",
			uniformName = "g_NormalTextureSampler",
			shader = "Fragment",
			mapType = "normal",
		},
		{
			path = "ComputerGraphics/NanoSuit/leg_showroom_spec.png",
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