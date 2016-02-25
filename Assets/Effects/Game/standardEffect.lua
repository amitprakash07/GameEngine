return
{
	vertex = "Game/standard.vshd",
	fragment = "Game/standard.fshd",
	AlphaTransparency = "False",
	DepthTesting = "True",
	DepthWriting = "True",
	FaceCulling = "False",
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