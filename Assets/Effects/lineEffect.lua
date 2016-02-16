return
{
	vertex = "line.vshd",
	fragment = "line.fshd",
	AlphaTransparency = "False",
	DepthTesting = "False",
	DepthWriting = "False",
	FaceCulling = "False",
	uniforms =
	{
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
