#pragma once

#include <memory>
#include <optional>
#include <string>

namespace bs
{
	template <class T, class U>
	concept Derived = std::is_base_of<U, T>::value;

	struct Asset
	{
		virtual void load(const std::string& loaderfilename) = 0;
		virtual void unload() = 0;
	};


	struct AssetType
	{
		//Example: "tex, typeid(Texture).name"
		AssetType(const std::string& inExtension)    :   extension(inExtension)
		{
			
		}
		AssetType(std::string&& inExtension)    :   extension(inExtension)
		{
			
		}
		
		std::string extension;
	};

	template <Derived<bs::Asset> asset_type>
	struct AssetRef
	{
		std::shared_ptr<asset_type> p_Asset;

		asset_type& get()
		{
			return *p_Asset.get();
		}
	};

	struct AssetEntry
	{
		std::shared_ptr<Asset> asset;	//this is for inheritance
		std::string ID;
		size_t type; //Asset Types index
	};
}