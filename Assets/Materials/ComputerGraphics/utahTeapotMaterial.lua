return 
{
	effect = "ComputerGraphics/utahTeapotEffect.effect",
	map =
	{
		{
			path = "ComputerGraphics/marbleTexture.jpg",
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
		}
	},		
}