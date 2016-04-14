return 
{
	effect = "ComputerGraphics/planeMeshEffect.effect",
	map =
	{
		{
			path = "ComputerGraphics/ceiling.dds",		
			uniformName = "g_TextureSampler",
			shader = "Fragment",
			mapType = "albedo",
		},
        {
			path = "ComputerGraphics/ceiling_normal.dds",		
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