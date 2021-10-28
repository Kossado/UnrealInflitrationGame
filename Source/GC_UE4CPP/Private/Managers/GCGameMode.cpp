// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/GCGameMode.h"

#include "KnightPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/GCGameInstance.h"

AGCGameMode::AGCGameMode() : Super()
{
	// Define default classes
	GameStateClass = AGCGameState::StaticClass();
	PlayerControllerClass = AKnightPlayerController::StaticClass();
}

void AGCGameMode::InitGameState()
{
	Super::InitGameState();
	AGCGameState * GCGameState = GetGameState<AGCGameState>();
	if(GCGameState != nullptr)
	{
		GCGameState->StoredFood = 0;
		GCGameState->PickableFood = 0;
		GCGameState->StoredFoodToWin = 5;

		UGCGameInstance * GameInstance = Cast<UGCGameInstance>(GetGameInstance());
		if(GameInstance != nullptr)
		{
			GCGameState->SkinPlayer = GameInstance->GetSkinPlayer();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AGCGameMode::InitGameState - GameInstance is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AGCGameMode::InitGameState - GameState is null"));
	}
}

void AGCGameMode::StartPlay()
{
	ListSkeletalMeshWithAnimations = {
		{
			SkeletalMeshKnight, AnimClassKnight		
		},
		{
			SkeletalMeshMaleGoblin, AnimClassMaleGoblin		
		},
		{
			SkeletalMeshFemaleGoblin, AnimClassFemaleGoblin		
		}
	};
	
	TeamSkeletalMeshes={{}, {}};

	for(int i = 0; i < ListSkeletalMeshWithAnimations.Num(); i++)
	{
		if(Team1IdCharacter.Contains(i))
		{			
			TeamSkeletalMeshes[0].Add(ListSkeletalMeshWithAnimations[i]);
		}

		if(Team2IdCharacter.Contains(i))
		{			
			TeamSkeletalMeshes[1].Add(ListSkeletalMeshWithAnimations[i]);
		}
	}
	

	UGCGameInstance * GameInstance = Cast<UGCGameInstance>(GetGameInstance());

	if(GameInstance != nullptr)
	{
		ESkinPlayer SkinChoosed = GameInstance->GetSkinPlayer();

		switch (SkinChoosed)
		{
			case ESkinPlayer::EGS_KNIGHT:
				PlayerTeamId = 0;
			break;

			case ESkinPlayer::EGS_GOBELIN_MALE:
			case ESkinPlayer::EGS_GOBELIN_FEMALE:
				PlayerTeamId=1;
			break;
			
			default:
				break;
		}
	}
	
	Super::StartPlay();
	GetGameState<AGCGameState>()->CurrentGameState = EGS_PLAYING;
	InGameInterface = Cast<AInGameInterface>(GetWorld()->GetFirstPlayerController()->GetHUD());
	FoodManager->Initialize();
	EnemyManager->Initialize();
	UE_LOG(LogTemp, Error, TEXT("End Initialization"));
}

TArray<LinkSkeletalMeshAnimation> AGCGameMode::GetTeamSkeletalMeshes(int TeamId) const
{
	if(TeamId < 0 || TeamId >= TeamSkeletalMeshes.Num())
	{
		return {};
	}

	return TeamSkeletalMeshes[TeamId];
}

void AGCGameMode::RestartGame()
{
	Super::RestartGame();
}

EGameState AGCGameMode::GetCurrentGameState() const
{
	return GetGameState<AGCGameState>()->CurrentGameState;
}

int AGCGameMode::GetStoredFood() const
{
	return GetGameState<AGCGameState>()->StoredFood;
}

int AGCGameMode::GetPickableFood() const
{
	return GetGameState<AGCGameState>()->PickableFood;
}

int AGCGameMode::GetStoredFoodToWin() const
{
	return GetGameState<AGCGameState>()->StoredFoodToWin;
}

void AGCGameMode::SetCurrentGameState(EGameState CurrentGameState) const
{
	GetGameState<AGCGameState>()->CurrentGameState = CurrentGameState;
}

ESkinPlayer AGCGameMode::GetSkinPlayer() const
{
	AGCGameState * GCGameState = GetGameState<AGCGameState>();

	if(GCGameState != nullptr)
	{
		return GCGameState->SkinPlayer;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AGCGameMode::SetSkinPlayer - GameState is null"));
	}

	return ESkinPlayer::EGS_NO_SKIN;
}

USkeletalMesh * AGCGameMode::GetSkeletalMeshChoosenByPlayer() const
{
	AGCGameState * GCGameState = GetGameState<AGCGameState>();

	if(GCGameState != nullptr)
	{
		switch(GCGameState->SkinPlayer)
		{
			case ESkinPlayer::EGS_KNIGHT:
				return SkeletalMeshKnight;

			case ESkinPlayer::EGS_GOBELIN_MALE:
				return SkeletalMeshMaleGoblin;

			case ESkinPlayer::EGS_GOBELIN_FEMALE:
				return SkeletalMeshFemaleGoblin;

			default:
				UE_LOG(LogTemp, Error, TEXT("AGCGameMode::GetSkeletalMeshChoosenByPlayer - No Skin choosen"));
				return nullptr;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AGCGameMode::GetSkeletalMeshChoosenByPlayer - GameState is null"));
	}

	return nullptr;
}

TSubclassOf<UAnimInstance> AGCGameMode::GetAnimationChoosenByPlayer() const
{
	AGCGameState * GCGameState = GetGameState<AGCGameState>();

	if(GCGameState != nullptr)
	{
		switch(GCGameState->SkinPlayer)
		{
		case ESkinPlayer::EGS_KNIGHT:
			return AnimClassKnight;

		case ESkinPlayer::EGS_GOBELIN_MALE:
			return AnimClassMaleGoblin;

		case ESkinPlayer::EGS_GOBELIN_FEMALE:
			return AnimClassFemaleGoblin;

		default:
			UE_LOG(LogTemp, Error, TEXT("AGCGameMode::GetAnimationChoosenByPlayer - No Skin choosen"));
			return nullptr;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AGCGameMode::GetAnimationChoosenByPlayer - GameState is null"));
	}

	return nullptr;
}

void AGCGameMode::SetSkinPlayer(ESkinPlayer SkinPlayer) const
{
	AGCGameState * GCGameState = GetGameState<AGCGameState>();

	if(GCGameState != nullptr)
	{
		GCGameState->SkinPlayer = SkinPlayer;
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("AGCGameMode::SetSkinPlayer - GameState is null"));
	}
}

void AGCGameMode::IncrementStoredFood()
{
	GetGameState<AGCGameState>()->StoredFood++;
	if(InGameInterface)
	{
		InGameInterface->UpdateCurrentFood(GetStoredFood());
	}
	CheckGameConditions();
}

void AGCGameMode::LaunchMenuPause()
{
	if(InGameInterface)
	{
		SetCurrentGameState(EGS_PAUSE);
		InGameInterface->Pause();
	}
}

void AGCGameMode::IncrementPickableFood()
{
	GetGameState<AGCGameState>()->PickableFood++;
}

void AGCGameMode::CheckGameConditions()
{
	if(GetCurrentGameState() == EGS_DEFEAT)
	{
		return;	
	}
	
	if(GetStoredFood() >= GetStoredFoodToWin())
	{
		Victory();
	}	
}

void AGCGameMode::Victory()
{
	SetCurrentGameState(EGS_VICTORY);
	EndGame();
	if(InGameInterface)
	{
		InGameInterface->EndGame(true);
	}
}

void AGCGameMode::Defeat()
{
	if(GetCurrentGameState() == EGS_VICTORY)
	{
		return;	
	}
	
	SetCurrentGameState(EGS_DEFEAT);
	EndGame();
	if(InGameInterface)
	{
		InGameInterface->EndGame(false);
	}
}

void AGCGameMode::EndGame()
{
	DisableCharacterInput();

	if(EnemyManager!= nullptr)
	{
		EnemyManager->EndGame();
	}
}

void AGCGameMode::DisableCharacterInput()
{
	UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
}
