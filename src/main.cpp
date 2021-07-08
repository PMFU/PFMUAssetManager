#include "AssetManager.h"

class Model	:	public bs::Asset
{
public:
	void load(const std::string& loaderfilename) override
	{
		//Load File
	}

	void thing();
};

class Texture	:	public bs::Asset
{
public:
	void load(const std::string& loaderfilename) override
	{
		//LOAD TEXTURE
	}
	
	void thing();
};


int main()
{


	bs::asset_manager->addAssetType<Model>(bs::AssetType("tex"))
				.addAssetType<Texture>(bs::AssetType("tex"))
	.build();

	auto modelAsset = bs::asset_manager->getAsset<Model>("3D model");

	modelAsset->p_Asset->thing();


	return 0;
}