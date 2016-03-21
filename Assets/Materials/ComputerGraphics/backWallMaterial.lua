return 
{
	effect = "ComputerGraphics/floorEffect.effect",
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
			value = {0.249,0.278,0.123},
		}
	},		
}