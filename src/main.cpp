

#include "AssetManager.h"

class Model	:	public Asset
{
public:
	static void load();

	void thing();
};

class Texture	:	public Asset
{
public:
	static void load();

	void thing();
};

class MapData	:	public Asset
{
public:
	static void load();

	void thing();
};

class JSON	:	public Asset
{
public:
	static void load();

	void thing();
};

int main()
{

	AssetManager asset_manager;

	asset_manager.addAssetType<Model>(AssetType("tex"))
				.addAssetType<Texture>(AssetType("tex"))
				.addAssetType<MapData>(AssetType("mpd"))
				.addAssetType<JSON>(AssetType("jsondef"))
	.build();

	auto modelAsset = asset_manager.getAsset<Model>("3D model");

	modelAsset->p_Asset->thing();


	return 0;
}