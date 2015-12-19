return
{
	{
		BuildTool = "MeshBuilder.exe",
		{
			src = "cubeOpaque.lua",
			target = "cubeOpaque.mesh",
		},	

		{
			src = "cubeOpaque.lua",
			target = "cubeOpaque.mesh",
		},	

		{
			src = "Sphere.lua",
			target = "Sphere.mesh",
		},
		
		{
			src = "Plane.lua",
			target = "Plane.mesh",
		},
		
		{
			src = "Ground.lua",
			target = "Ground.mesh",	
		},		
		{
			src = "HelixOpaque.lua",
			target = "HelixOpaque.mesh",	
		},

		{
			src = "PlaneOpaque.lua",
			target = "PlaneOpaque.mesh",
		},
		{
			src = "RoomMeshes/AdditionalFloorFrames.lua",
			target = "RoomMeshes/AdditionalFloorFrames.mesh",
		},	
		{
			src = "RoomMeshes/Books.lua",
			target = "RoomMeshes/Books.mesh",
		},		
		{
			src = "RoomMeshes/Carpets.lua",
			target = "RoomMeshes/Carpets.mesh",	
		},		
		{
			src = "RoomMeshes/CenterBook.lua",
			target = "RoomMeshes/CenterBook.mesh",	
		},

		{
			src = "RoomMeshes/CenterTable.lua",
			target = "RoomMeshes/CenterTable.mesh",
		},
		{
			src = "RoomMeshes/Couch.lua",
			target = "RoomMeshes/Couch.mesh",
		},		
		{
			src = "RoomMeshes/Curtain.lua",
			target = "RoomMeshes/Curtain.mesh",	
		},		
		{
			src = "RoomMeshes/DoorKnob.lua",
			target = "RoomMeshes/DoorKnob.mesh",	
		},

		{
			src = "RoomMeshes/Doors.lua",
			target = "RoomMeshes/Doors.mesh",
		},
		{
			src = "RoomMeshes/FloorAndFrames.lua",
			target = "RoomMeshes/FloorAndFrames.mesh",
		},		
		{
			src = "RoomMeshes/FlowerInVase.lua",
			target = "RoomMeshes/FlowerInVase.mesh",	
		},		
		{
			src = "RoomMeshes/Lamp_1.lua",
			target = "RoomMeshes/Lamp_1.mesh",	
		},

		{
			src = "RoomMeshes/Shelves.lua",
			target = "RoomMeshes/Shelves.mesh",
		},
		{
			src = "RoomMeshes/TopLight.lua",
			target = "RoomMeshes/TopLight.mesh",
		},		
		{
			src = "RoomMeshes/Vase_Plant.lua",
			target = "RoomMeshes/Vase_Plant.mesh",	
		},		
		{
			src = "RoomMeshes/Walls.lua",
			target = "RoomMeshes/Walls.mesh",	
		},
	},

	{
		BuildTool = "EffectBuilder.exe",
		{
			src = "standardEffect.lua",
			target = "standardEffect.effect"
		},
		{
			src = "transparentEffect.lua",
			target = "transparentEffect.effect"
		}
	},

	{
		BuildTool = "ShaderBuilder.exe",
		{
			src = "standard.fshd",
			target = "standard.fshd",
			optionaltype = "fragment",
			dependencies =
			{
				"shaders.inc"
			}

		},

		{
			src = "standard.vshd",
			target = "standard.vshd",
			optionaltype = "vertex",
			dependencies =
			{
				"shaders.inc"
			}
		},
		
		{
			src = "transparent.fshd",
			target = "transparent.fshd",
			optionaltype = "fragment",
			dependencies = 
			{
				"shaders.inc"
			}
		}
	},
	
	{
		BuildTool = "MaterialBuilder.exe",
		{
			src = "BrickMaterial_opaque_Blue.lua",
			target = "BrickMaterial_opaque_Blue.mat",
		},
		{
			src = "BrickMaterial_opaque.lua",
			target = "BrickMaterial_opaque.mat",
		},
		{
			src = "BrickMaterial_transparent_blue_green.lua",
			target = "BrickMaterial_transparent_blue_green.mat",
		},
		{
			src = "BrickMaterial_transparent_red_green.lua",
			target = "BrickMaterial_transparent_red_green.mat",
		},
		{
			src = "GroundOpaque.lua",
			target = "GroundOpaque.mat",
		},
		{
			src = "verticalPlaneOpaque.lua",
			target = "verticalPlaneOpaque.mat",
		},
		{
			src = "verticalPlaneTransparent.lua",
			target = "verticalPlaneTransparent.mat",
		},
		{
			src = "Room/BackDoor.lua",
			target = "Room/BackDoor.mat",
		},
		{
			src = "Room/BackWall.lua",
			target = "Room/BackWall.mat",
		},
		{
			src = "Room/BookCenterTable.lua",
			target = "Room/BookCenterTable.mat",
		},
		{
			src = "Room/BookPile2.lua",
			target = "Room/BookPile2.mat",
		},
		{
			src = "Room/BookPile3.lua",
			target = "Room/BookPile3.mat",
		},
		{
			src = "Room/Carpet.lua",
			target = "Room/Carpet.mat",
		},
		{
			src = "Room/CarpetNearFrontDoor.lua",
			target = "Room/CarpetNearFrontDoor.mat",
		},
		{
			src = "Room/Ceiling.lua",
			target = "Room/Ceiling.mat",
		},
		{
			src = "Room/CenterTable.lua",
			target = "Room/CenterTable.mat",
		},
		{
			src = "Room/Couch.lua",
			target = "Room/Couch.mat",
		},
		{
			src = "Room/CouchSideTables.lua",
			target = "Room/CouchSideTables.mat",
		},
		{
			src = "Room/Curtain.lua",
			target = "Room/Curtain.mat",
		},
		{
			src = "Room/DoorFrames.lua",
			target = "Room/DoorFrames.mat",
		},
		{
			src = "Room/Doors.lua",
			target = "Room/Doors.mat",
		},
		{
			src = "Room/Floor.lua",
			target = "Room/Floor.mat",
		},
		{
			src = "Room/FloorCrossSection.lua",
			target = "Room/FloorCrossSection.mat",
		},
		{
			src = "Room/Shelves.lua",
			target = "Room/Shelves.mat",
		},
		{
			src = "Room/SideWall1.lua",
			target = "Room/SideWall1.mat",
		},
		{
			src = "Room/SideWall2.lua",
			target = "Room/SideWall2.mat",
		},
		{
			src = "Room/SideWall3.lua",
			target = "Room/SideWall3.mat",
		},
		{
			src = "Room/SideWall4.lua",
			target = "Room/SideWall4.mat",
		},
		{
			src = "Room/SingleCouch.lua",
			target = "Room/SingleCouch.mat",
		},
		{
			src = "Room/TV.lua",
			target = "Room/TV.mat",
		},		
	},
	
	{
		BuildTool = "TextureBuilder.exe",
		{
			src = "ground-texturep.jpg",
			target = "ground-texturep.jpg",
		},
		{
			src = "Brick_texture.jpg",
			target = "Brick_texture.jpg",
		},
		
		{
			src = "alpha.png",
			target = "alpha.png",
		},
		
		{
			src = "bricks.png",
			target = "bricks.png",
		},
		
		{
			src = "clouds.png",
			target = "clouds.png",
		},
		
		{
			src = "eae6320.png",
			target = "eae6320.png",
		},
		{
			src = "Room/book_occlusion.png",
			target = "Room/book_occlusion.png",
		},
		{
			src = "Room/stone-wall-texture.png",
			target = "Room/stone-wall-texture.png",
		},
		{
			src = "Room/T_Anisotrophic_M.png",
			target = "Room/T_Anisotrophic_M.png",
		},
		{
			src = "Room/T_Anisotrophic_N.png",
			target = "Room/T_Anisotrophic_N.png",
		},
		{
			src = "Room/T_Background_D.png",
			target = "Room/T_Background_D.png",
		},
		{
			src = "Room/T_Background_Night_D.png",
			target = "Room/T_Background_Night_D.png",
		},
		{
			src = "Room/T_Carpet_D.png",
			target = "Room/T_Carpet_D.png",
		},
		{
			src = "Room/T_Cloth_D.png",
			target = "Room/T_Cloth_D.png",
		},
		{
			src = "Room/T_Leather_D.png",
			target = "Room/T_Leather_D.png",
		},
		{
			src = "Room/T_MugLogo_D.png",
			target = "Room/T_MugLogo_D.png",
		},
		{
			src = "Room/T_Painting_D.png",
			target = "Room/T_Painting_D.png",
		},
		{
			src = "Room/T_Painting2_D.png",
			target = "Room/T_Painting2_D.png",
		},
		{
			src = "Room/T_Painting3_D.png",
			target = "Room/T_Painting3_D.png",
		},
		{
			src = "Room/T_Painting4_D.png",
			target = "Room/T_Painting4_D.png",
		},
		{
			src = "Room/T_PlantBark_D.png",
			target = "Room/T_PlantBark_D.png",
		},
		{
			src = "Room/T_PlantLeaf_D.png",
			target = "Room/T_PlantLeaf_D.png",
		},
		{
			src = "Room/T_PlantSoil_D.png",
			target = "Room/T_PlantSoil_D.png",
		},
		{
			src = "Room/T_StoneMix_D.png",
			target = "Room/T_StoneMix_D.png",
		},
		{
			src = "Room/T_Wood.png",
			target = "Room/T_Wood.png",
		},
	}
}
