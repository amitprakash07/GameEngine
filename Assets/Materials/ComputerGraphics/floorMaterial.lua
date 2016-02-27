return 
{
	effect = "ComputerGraphics/floorEffect.effect",
	map =
	{
		{
			path = "ComputerGraphics/checkerBoard.jpg",
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