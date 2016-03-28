return 
{
	effect = "ComputerGraphics/cubeEffect.effect",
	map =
	{
		{
			path = "ComputerGraphics/borgTexture.jpg",
		--	path = "ComputerGraphics/myFace.dds",
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