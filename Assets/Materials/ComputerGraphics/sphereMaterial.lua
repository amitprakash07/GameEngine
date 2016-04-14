return 
{
	effect = "ComputerGraphics/sphereEffect.effect",
	map =
	{
		{
			path = "ComputerGraphics/nightSkySpherical.dds",		
			uniformName = "g_TextureSampler",
			shader = "Fragment",
			mapType = "albedo",
		},
        {
			path = "ComputerGraphics/nightSkySpherical_normal.dds",		
			uniformName = "g_NormalMapSampler",
			shader = "Fragment",
			mapType = "normal",
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
			value = {1.0,1.0,1.0},
		},
		{
			name = "glossiness",
			shader = "fragment",
			valtype = "Float",
			value = {1.0},
		},	
	},		
}