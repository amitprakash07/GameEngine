return
{
	effect = "data/transparentEffect.effect",
	uniforms =
	{
		{
			name = "g_PixelColorModifier",
			shader = "fragment",
			valtype = "Float",
			value = {0.0,1.0,0.0},
		},
		{
			name = "g_AlphaModifier",
			shader = "fragment",
			valtype = "Float",
			value = {0.8},
		}
	}

}
