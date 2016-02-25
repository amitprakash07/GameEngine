return
{
	vertex = "ComputerGraphics/environmentMap.vshd",
	fragment = "ComputerGraphics/environmentMap.fshd",
	AlphaTransparency = "False",
	DepthTesting = "True",
	DepthWriting = "True",
	FaceCulling = "True",
    uniforms =
	{
		{
			name = "g_transform_localToWorld",
			shader = "vertex",
			valType = "Matrix",
			MatrixType = "LocalToWorld",
			count = 1,
		},
		{
			name = "g_transform_worldToView",
			shader = "vertex",
			valType = "Matrix",
			MatrixType = "WorldToView",
			count = 1,
		},
		{
			name = "g_transform_viewToScreen",
			shader = "vertex",
			valType = "Matrix",
			MatrixType = "ViewToScreen",
			count = 1,
		},		
	}	
}
