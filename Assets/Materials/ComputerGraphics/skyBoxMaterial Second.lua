return 
{
	effect = "ComputerGraphics/skyBoxEffect.effect",
	map =
	{
		{
			path = "ComputerGraphics/LancellottiChapel.dds",
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