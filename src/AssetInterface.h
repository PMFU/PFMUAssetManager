#pragma once

#include <memory>
#include <optional>
#include <string>


struct Asset
{
	
};


struct AssetType
{
	//Example: "tex, typeid(Texture).name"
	AssetType(std::string inExtension)    :   extension(inExtension)
	{
		
	}
	
	std::string extension;
};

template <typename assetType>
struct AssetRef
{
	std::shared_ptr<assetType> p_Asset;
};

struct AssetEntry
{
	std::weak_ptr<Asset> asset;	//this is for inheritance
	std::string ID;
	size_t type; //Asset Types index
};