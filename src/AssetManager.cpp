#include "AssetManager.h"

#include <filesystem>
#include <fstream>

// include nlohmann json

std::string getExtension(const std::string& filename)
{
	int extensionIndex = 0;
	for(int i = 0; i < filename.size(); ++i)
	{
		if(filename[i] == '.')
		{
			extensionIndex = i;
			break;
		}
	}
	return filename.substr(extensionIndex);
}

namespace bs
{
	AssetManager* asset_manager;

	void AssetManager::build()
	{
		m_assetmap = new std::unordered_map<KeyType, AssetEntry>[m_typeslist.size()];

		//LOAD MOST ASSETS:

		for(int i = 0; i < m_typeslist.size(); ++i)
		{	//THIS IS LIKE ONE OF THE MOST RETARDED WAYS TO DO THIS, FIX THIS
			const auto& type = m_typeslist[i];
			const auto& extensionStr = type.first.extension;

			for(const auto& file : std::filesystem::recursive_directory_iterator("res"))
			{	// file is each file
				auto ext = getExtension(file.path().filename().string());
				if(ext == extensionStr)
				{
					//Load
					loadTasks[i](file.path().filename().string());

					/*
					std::ifstream f(file.path().filename().string());
					nlohmann::json j;

					f >> j;

					

					//Parse the JSON asset format
					std::shared_ptr<AssetEntry> asset;
					asset->type = i;
					asset->asset->load(file.path().filename().string());

					m_assetmap[i].emplace(j["name"].get<std::string>(), asset);

					// @TODO: finish
					*/
				}
			}
		}
	}

	AssetManager::~AssetManager()
	{
		//UNLOAD ALL ASSETS:
		/*for(int i = 0; i < m_typeslist.size(); ++i)
		{
			auto& assetmap = m_assetmap[i];
			for(auto& [ID, Asset] : assetmap)
			{
				Asset.asset->unload();
			}
		}*/

		delete[] m_assetmap;

	}
}