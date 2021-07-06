#pragma once

#include "AssetInterface.h"
#include <unordered_map>
#include <vector>
#include <functional>

namespace bs
{
	using KeyType = std::string;

	class AssetManager
	{
	public:
		//After build this may not be called
		template <typename asset_type>
		AssetManager& addAssetType(AssetType type)
		{
			static size_t index = 0;
			m_typeslist.push_back(std::make_pair(type, std::string(typeid(asset_type).name())));

			//This is a workaround to preserve asset type
			auto load = [&, index](const std::string& filepath)
			{
				//Parse the JSON asset format
				std::shared_ptr<AssetEntry> asset;
				asset->type = index;
				asset->asset = std::shared_ptr<asset_type>(new asset_type);
				asset->asset->load(filepath);

				m_assetmap[index].emplace(asset->ID, asset);
			};

			loadTasks.push_back(load);

			++index;
			return *this;
		}

		//This may only be called once
		void build();

		//Retreive an asset from the asset manager
		template <typename asset_type>
		std::optional<AssetRef<asset_type>> getAsset(const KeyType& id)
		{
			int mapid = -1;

			for(int i = 0; i < m_typeslist.size(); ++i)
			{
				const auto& type = m_typeslist[i];
				if(std::string(typeid(asset_type).name()) == type.second)
				{
					mapid = i;
					break;
				}
			}
			if(mapid == -1)
			{
				std::cout << "Could not find an matching asset type, build a " << std::string(typeid(asset_type).name()) << " manager first to resolve this error!\n";
				return std::nullopt;
			}
			if(m_assetmap[mapid].contains(id))
			{
				return std::make_optional<AssetRef<asset_type>>(m_assetmap[mapid].at(id));
			}

			return std::nullopt;
		}

		//Add an asset to the asset manager from existing types
		template <typename asset_type>
		void addAsset(const KeyType& id, asset_type& asset)
		{
			int mapid = -1;

			for(int i = 0; i < m_typeslist.size(); ++i)
			{
				const auto& type = m_typeslist[i];
				if(std::string(typeid(asset_type).name()) == type.second)
				{
					mapid = i;
					break;
				}
			}
			if(mapid == -1)
			{
				std::cout << "Could not find an matching asset type, build a " << std::string(typeid(asset_type).name()) << " manager first to resolve this error!\n";
				return;
			}

			m_assetmap[mapid].emplace(id, asset);
		}

		//Retrieve the full asset map of an asset type, for iteration purposes
		template <typename asset_type>
		const std::optional<std::unordered_map<KeyType, AssetEntry>>& getAssetMap()
		{
			int mapid = -1;

			for(int i = 0; i < m_typeslist.size(); ++i)
			{
				const auto& type = m_typeslist[i];
				if(std::string(typeid(asset_type).name()) == type.second)
				{
					mapid = i;
					return std::make_optional<std::unordered_map<KeyType, AssetEntry>>(m_assetmap[mapid]);
				}
			}
			if(mapid == -1)
			{
				std::cout << "Could not find a map for the asset type, build a " << std::string(typeid(asset_type).name()) << " manager first to resolve this error!\n";
				return std::nullopt;
			}
		}

		//Store globally necessary pointers
		//BLANK

		
		bool				loaded = false;
		bool				loadedarray[8] = { false, false, false, false, false, false, false, false };

		~AssetManager();


		

	private:
		std::vector<std::pair<AssetType, std::string>>	m_typeslist;
		std::vector<std::function<void>(const std::string&)> loadTasks;
		std::unordered_map<KeyType, AssetEntry>* m_assetmap;
		
	};


	extern AssetManager* asset_manager;
}