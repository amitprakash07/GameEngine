return
{
	effect = "data/transparentEffect.effect",
	uniforms =
	{
		{
			name = "g_PixelColorModifier",
			shader = "fragment",
			valtype = "Float",
			value = {1.0,0.5,0.0},
		},
		{
			name = "g_AlphaModifier",
			shader = "fragment",
			valtype = "Float",
			value = {0.8},
		}
		-- {
		-- 	name = "g_transform_localToWorld",
		-- 	shader = "vertex",
		-- 	valtype = "Matrix",
		-- 	value = "None"
		-- },
		-- {
		-- 	name = "g_transform_worldToView",
		-- 	shader = "vertex",
		-- 	valtype = "Matrix",
		-- 	value = "None"
		-- },
		-- {
		-- 	name = "g_transform_viewToScreen",
		-- 	shader = "vertex",
		-- 	valtype = "Matrix",
		-- 	value = "None"
		-- }
	}

}
