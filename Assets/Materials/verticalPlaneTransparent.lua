return
{
	effect = "transparentEffect.effect",
	map =
	{
		{
			path = "alpha.png",
			uniformName = "g_TextureSampler",
			shader = "Fragment",
			mapType = "albedo",
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
			name = "g_AlphaModifier",
			shader = "fragment",
			valtype = "Float",
			value = {0.5},
		},		
	}

}
