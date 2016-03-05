return
{
	vertex = "ComputerGraphics/skyBoxVertex.glsl",
	fragment = "ComputerGraphics/skyBoxFragment.glsl",
	AlphaTransparency = "False",
	DepthTesting = "True",
	DepthWriting = "True",
	FaceCulling = "True",	
	uniforms =
	{
		{
			name = "g_transform_worldToView",
			shader = "vertex",
			valType = "Matrix",
			MatrixType = "WorldToView",
			count = 1,
		},				
	}
}