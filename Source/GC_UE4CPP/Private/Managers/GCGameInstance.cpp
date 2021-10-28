#include "Managers/GCGameInstance.h"

UGCGameInstance::UGCGameInstance() : Super()
{
	SkinPlayer = EGS_NO_SKIN;
}

void UGCGameInstance::SetSkinPlayer(ESkinPlayer skinPlayer)
{
	SkinPlayer = skinPlayer;
}

ESkinPlayer UGCGameInstance::GetSkinPlayer() const
{
	return SkinPlayer;
}
