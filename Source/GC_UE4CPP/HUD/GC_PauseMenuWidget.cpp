#include "GC_PauseMenuWidget.h"
#include "MainGameMode.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UGC_PauseMenuWidget::UGC_PauseMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UGC_PauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(UIResume)
	{
		UIResume->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::Resume);
	}
	if(UIRestart)
	{
		UIRestart->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::Restart);
	}
	if(UIQuit)
	{
		UIQuit->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::Quit);
	}
	if(UIQuitDesktop)
	{
		UIQuitDesktop->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::QuitDesktop);
	}
	if(UIQuitMainMenu)
	{
		UIQuitMainMenu->OnClicked.AddDynamic(this,&UGC_PauseMenuWidget::QuitMainMenu);
	}
}

void UGC_PauseMenuWidget::Resume()
{
	if(UIResume)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		UGameplayStatics::SetGamePaused(GetWorld(),false);
		
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeGameOnly InputMode;
		Player->SetInputMode(InputMode);
		Player->bShowMouseCursor = false;

		if (this->UIQuitDesktop->IsVisible())
		{
			this->UIQuitDesktop->SetVisibility(ESlateVisibility::Hidden);
			this->UIQuitMainMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UGC_PauseMenuWidget::Restart()
{
	if(UIRestart)
	{
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeGameOnly InputMode;
		Player->SetInputMode(InputMode);
		
		AMainGameMode* GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RestartGame();
	}
}

void UGC_PauseMenuWidget::Quit()
{
	if(UIQuit && UIQuitDesktop && UIQuitMainMenu)
	{
		if (this->UIQuitDesktop->IsVisible())
		{
			this->UIQuitDesktop->SetVisibility(ESlateVisibility::Hidden);
			this->UIQuitMainMenu->SetVisibility(ESlateVisibility::Hidden);
		} else {
			this->UIQuitDesktop->SetVisibility(ESlateVisibility::Visible);
			this->UIQuitMainMenu->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UGC_PauseMenuWidget::QuitDesktop()
{
	if(UIQuitDesktop)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	}
}

void UGC_PauseMenuWidget::QuitMainMenu()
{
	if(UIQuitMainMenu)
	{
		UGameplayStatics::OpenLevel(this, FName(FString("MenuPrincipal")), false);
	}
}