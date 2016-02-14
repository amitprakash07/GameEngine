return 
{
	effect = "standardEffect.effect",
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
			value = {0.8,0.5,0.6},
		}
	}	
}