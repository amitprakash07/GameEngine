return 
{
	effect = "ComputerGraphics/planeEffect.effect",
	map =
	{
		{
			path = "ComputerGraphics/defaultTexture.png",
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
			value = {0.119,0.259,0.358},
		}
	},		
}