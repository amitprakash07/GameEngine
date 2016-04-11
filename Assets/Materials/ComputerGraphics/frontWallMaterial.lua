return 
{
	effect = "ComputerGraphics/planeEffect.effect",
	map =
	{
		{
			path = "ComputerGraphics/brickWall_3.dds",
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