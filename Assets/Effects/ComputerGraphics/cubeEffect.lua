return
{
	vertex = "ComputerGraphics/cubeVertex.glsl",
	fragment = "ComputerGraphics/cubeFragment.glsl",
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
		{
			name = "g_ScaleTransform",
			shader = "vertex",
			valType = "Matrix",
			MatrixType = "ScaleMatrix",
			count = 1,
		},
	}
}