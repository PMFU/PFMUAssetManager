#pragma once

#include "AssetInterface.h"
#include <unordered_map>
#include <vector>


using KeyType = std::string;

class AssetManager
{
public:
	template <typename assetType>
	AssetManager& addAssetType(AssetType type)
	{
		m_assetTypesList.push_back(type);
		return *this;
	}

	void build();

	template <typename assetType>
	std::optional<AssetRef<assetType>> getAsset(KeyType id)
	{
		if(m_assetmap.contains(id))
		{
			if(decltype(id) == assetType)
			{
				return std::make_optional<assetType>(m_assetmap.at(id));
			}
			else
			{
				return std::nullopt;
			}
		}
		else
		{
			return std::nullopt;
		}
	}

private:
	std::vector<AssetType>	m_assetTypesList;
	std::unordered_map<KeyType, AssetEntry> m_assetmap;
};