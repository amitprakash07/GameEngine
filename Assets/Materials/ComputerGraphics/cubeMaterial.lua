return 
{
	effect = "ComputerGraphics/cubeEffect.effect",
	map =
	{
		{
			path = "ComputerGraphics/brickWall_2.dds",
		--	path = "ComputerGraphics/myFace.dds",
			uniformName = "g_TextureSampler",
			shader = "Fragment",
			mapType = "albedo",
		},	
		{
			path = "ComputerGraphics/brickWall_2_normal.dds",
		--	path = "ComputerGraphics/myFace.dds",
			uniformName = "g_NormalMapSampler",
			shader = "Fragment",
			mapType = "normal",
		},			
	},
	uniforms =
	{
		{
			name = "g_PixelColorModifier",
			shader = "fragment",
			valtype = "Float",
			value = {1.0,1.0,1.0},
		},
		{
			name = "specularColor",
			shader = "fragment",
			valtype = "Float",
			value = {1.0,1.0,1.0},
		},
		{
			name = "glossiness",
			shader = "fragment",
			valtype = "Float",
			value = {1.0},
		},	
	},		
}