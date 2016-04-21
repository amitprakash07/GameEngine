return 
{
	effect = "ComputerGraphics/sphereToonEffect.effect",
	map =
	{
		{
			path = "ComputerGraphics/defaultTexture.png",		
			uniformName = "g_TextureSampler",
			shader = "Fragment",
			mapType = "albedo",
		},        			
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
			name = "specularColor",
			shader = "fragment",
			valtype = "Float",
			value = {0.5,0.6,0.3},
		},
		{
			name = "glossiness",
			shader = "fragment",
			valtype = "Float",
			value = {20.0},
		},	
	},		
}