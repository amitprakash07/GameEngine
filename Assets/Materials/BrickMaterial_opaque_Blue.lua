return
{
	effect = "standardEffect.effect",
	map =
	{
		{
			path = "Brick_texture.jpg",
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
			value = {0.0,0.0,1.0},
		},		
	}

}
