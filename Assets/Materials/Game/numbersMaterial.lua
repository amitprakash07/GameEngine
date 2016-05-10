return 
{
	effect = "Game/spriteEffect.effect",
	map =
	{
		{
			path = "Game/numbers.png",
			--path = "Game/defaultTexture.png",
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
	}		
}