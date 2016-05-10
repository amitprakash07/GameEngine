--[[
	This file contains the logic for building assets
]]

-- Static Data Initialization
--===========================

local s_AuthoredAssetDir, s_BuiltAssetDir, s_BinDir
do
	-- AuthoredAssetDir
	do
		local key = "AuthoredAssetDir"
		local errorMessage
		s_AuthoredAssetDir, errorMessage = GetVSEnvironmentVariable( key )
		if not s_AuthoredAssetDir then
			error( errorMessage )
		end
	end
	-- BuiltAssetDir
	do
		local key = "BuiltAssetDir"
		local errorMessage
		s_BuiltAssetDir, errorMessage = GetVSEnvironmentVariable( key )
		if not s_BuiltAssetDir then
			error( errorMessage )
		end
	end

	-- BinDir
	do
		local key = "BinDir"
		local errorMessage
		s_BinDir, errorMessage = GetVSEnvironmentVariable( key )
		if not s_BinDir then
			error( errorMessage )
		end
	end
end

-- Function Definitions
--=====================

--EAE6320_TODO: I have shown the simplest parameters to BuildAsset() that are possible.
--You should definitely feel free to change these
local function BuildAsset( resourceTable, dependencies_table )
	-- Get the absolute paths to the source and target
	--EAE6320_TODO: I am assuming that the relative path of the source and target is the same,
	--but if this isn't true for you (i.e. you use different extensions)
	--then you will need to update this part

	i_builderFileName = resourceTable[1]
	i_sourceRelativePath = resourceTable[2]
	i_targetRelativePath = resourceTable[3]

	local dependenciesExist = false
	if(dependencies_table) then
		if(#(dependencies_table) > 0) then
			dependenciesExist = true
		end
	end

	local subPathName,errorMessage, dependencyFolderPath
	if(i_builderFileName == "MeshBuilder.exe") then
		subPathName,errorMessage = GetVSEnvironmentVariable("MeshesDir")
	else if(i_builderFileName == "ShaderBuilder.exe") then
			subPathName,errorMessage = GetVSEnvironmentVariable("ShadersDir")
		else if(i_builderFileName == "MaterialBuilder.exe") then
				subPathName,errorMessage = GetVSEnvironmentVariable("MaterialDir")
			 else if(i_builderFileName == "EffectBuilder.exe") then
					subPathName,errorMessage = GetVSEnvironmentVariable("EffectDirName")
				  else if(i_builderFileName == "TextureBuilder.exe") then
						subPathName,errorMessage = GetVSEnvironmentVariable("TexturesDir")						
					   end
				  end
			 end
		end
	end
	
	
	if not(subPathName) then
		error(errorMessage)
	end
	
	
	local path_source = s_AuthoredAssetDir .. subPathName .. i_sourceRelativePath
	local path_target = s_BuiltAssetDir .. subPathName .. i_targetRelativePath

	-- If the source file doesn't exist then it can't be built
	do
		local doesSourceExist = DoesFileExist( path_source )
		if not doesSourceExist then
			OutputErrorMessage( "The source asset doesn't exist", path_source )
			return false
		end
	end

	-- Find the appropriate builder for this asset type
	local path_builder
	do
		if type( i_builderFileName ) == "string" then
			path_builder = s_BinDir .. i_builderFileName
			if not DoesFileExist( path_builder ) then
				error( "The specified builder (\"" .. path_builder .. "\") doesn't exist", stackLevel )
			end
		else
			error( "The specified builder file name must be a string (instead of a " ..
				type( i_builderFileName ) .. ")", stackLevel )
		end
	end

	-- Decide if the target needs to be built
	local shouldTargetBeBuilt = false
	do
		-- The simplest reason a target should be built is if it doesn't exist
		local doesTargetExist = DoesFileExist( path_target )
		if doesTargetExist then
			-- Even if the target exists it may be out-of-date.
			-- If the source has been modified more recently than the target
			-- then the target should be re-built.

			local lastWriteTime_source = GetLastWriteTime( path_source )
			local lastWriteTime_target = GetLastWriteTime( path_target )
			--We also need to check the dependency
			--if dependency is changed then we have to build
			-- let's calculate the max of all the dependency to compare to the target time
			if dependenciesExist then
			--check dependency file exists or not and calculate max time for modification among all
				local maxTimeForDependency = 0.0
				dependencyFolderPath, errorMessage = GetVSEnvironmentVariable("DependenciesFolder")
				if not dependencyFolderPath then 
					error(errorMessage)
				end
				
				for i,v in ipairs(dependencies_table) do
					local dependencyPath = s_AuthoredAssetDir .. dependencyFolderPath .. v
					print(dependencyPath)
					local fileExists = DoesFileExist(dependencyPath)
					if not fileExists then
						local errorMessage = "Dependent File " .. dependencyPath .. " does not exists"
						OutputErrorMessage(errorMessage)
					end

					local lastWriteTimeForDependencyFile = GetLastWriteTime( dependencyPath )
					--print(lastWriteTimeForDependencyFile)
					if maxTimeForDependency < lastWriteTimeForDependencyFile then
						maxTimeForDependency = lastWriteTimeForDependencyFile
					end
				end
				--print(maxTimeForDependency)
				shouldTargetBeBuilt = maxTimeForDependency > lastWriteTime_target
				--print(shouldTargetBeBuilt)
			end


			if not shouldTargetBeBuilt then
				shouldTargetBeBuilt = lastWriteTime_source > lastWriteTime_target
			end

			if not shouldTargetBeBuilt then
				-- Even if the target was built from the current source
				-- the builder may have changed which could cause different output
				local lastWriteTime_builder = GetLastWriteTime( path_builder )
				shouldTargetBeBuilt = lastWriteTime_builder > lastWriteTime_target
			end
		else
			shouldTargetBeBuilt = true;
		end
	end

	-- Build the target if necessary
	if shouldTargetBeBuilt then
		-- Create the target directory if necessary
		CreateDirectoryIfNecessary( path_target )
		-- Build
		do
			-- The command starts with the builder
			local command = "\"" .. path_builder .. "\""
			-- The source and target path must always be passed in
			local arguments = "\"" .. path_source .. "\" \"" .. path_target .. "\""

			count = #(resourceTable)
			print("count = " .. count)
			counter = 3
			if(count > 3) then
				while (counter < (count)) do
					counter = counter +1
					arguments = arguments .. " " ..resourceTable[counter]
				end
			end
			-- If you create a mechanism so that some asset types could include extra arguments
			-- you would concatenate them here, something like:
			-- arguments = arguments .. " " .. i_optionalArguments
			-- IMPORTANT NOTE:
			-- If you need to debug a builder you can put print statements here to
			-- find out what the exact command line should be.
			-- "command" should go in Debugging->Command
			-- "arguments" should go in Debugging->Command Arguments

			-- Surround the entire command line in quotes

			local commandLine = "\"" .. command .. " " .. arguments .. "\""
			print(commandLine)

			local result, terminationType, exitCode = os.execute( commandLine )
			if result then
				-- Display a message for each asset
				print( "Built " .. path_source )
				-- Return the exit code for informational purposes since we have it
				return true, exitCode
			else
				-- The builder should already output a descriptive error message if there was an error
				-- (remember that you write the builder code,
				-- and so if the build process failed it means that _your_ code has returned an error code)
				-- but it can be helpful to still return an additional vague error message here
				-- in case there is a bug in the specific builder that doesn't output an error message
				do
					local errorMessage = "The command " .. tostring( commandLine )
					if terminationType ~= "signal" then
						errorMessage = errorMessage .. " exited with code "
					else
						errorMessage = errorMessage .. " was terminated by the signal "
					end
					errorMessage = errorMessage .. tostring( exitCode )
					OutputErrorMessage( errorMessage, path_source )
				end
				-- There's a chance that the builder already created the target file,
				-- in which case it will have a new time stamp and wouldn't get built again
				-- even though the process failed
				if DoesFileExist( path_target ) then
					local result, errorMessage = os.remove( path_target )
					if not result then
						OutputErrorMessage( "Failed to delete the incorrectly-built target: " .. errorMessage, path_target )
					end
				end

				return false, exitCode
			end
		end
	else
		return true
	end
end


local function BuildAssets( i_assetsToBuild)
	local wereThereErrors = false
    local errorMessage
	if type(i_assetsToBuild) ~= 'table' then
		wereThereErrors = true
		errorMessage = "There is no table in the file"
		OutputErrorMessage(errorMessage)
	else
		for i,u in ipairs(i_assetsToBuild) do
			for j,v in ipairs(i_assetsToBuild[i]) do
				list = {}
				if (v['optionaltype']) then
					list = {i_assetsToBuild[i]["BuildTool"], v["src"], v["target"], v['optionaltype']}
				else
					list = {i_assetsToBuild[i]["BuildTool"], v["src"], v["target"]}
				end
				i_dependencies = v["dependencies"]
				isAssetBuild, anyError = BuildAsset(list, i_dependencies)
				if not isAssetBuild then
					errorMessage = errorMessage .. "Unable to build file. Returning exit code" .. anyError
					wereThereErrors = true
					return not wereThereErrors
				end
			end
		end
	end

	-- End of TODO. The following should be the final line of the function:
	return not wereThereErrors
end

-- Entry Point
--============

-- Command line arguments are represented in Lua as three dots ("...")
local commandLineArgument = ...
if commandLineArgument then
	local path_assetsToBuild = commandLineArgument
	--OutputErrorMessage(commandLineArgument)
	if DoesFileExist( path_assetsToBuild ) then
			assetsToBuild = dofile( path_assetsToBuild )
			return BuildAssets( assetsToBuild )
	else
		OutputErrorMessage( "The path to the list of assets to build that was provided to BuildAssets.lua as argument #1 (\"" ..
			path_assetsToBuild .. "\") doesn't exist" )
	end
else
	OutputErrorMessage( "BuildAssets.lua must be called with the path to the list of assets to build as an argument" )
end
