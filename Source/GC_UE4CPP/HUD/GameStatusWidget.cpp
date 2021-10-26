#include "GameStatusWidget.h"
#include "GCGameMode.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UGameStatusWidget::UGameStatusWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UGameStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(UIPlayAgain)
	{
		UIPlayAgain->OnClicked.AddDynamic(this,&UGameStatusWidget::PlayAgain);
	}
	if(UIQuit)
	{
		UIQuit->OnClicked.AddDynamic(this,&UGameStatusWidget::Quit);
	}
	if(UIQuitDesktop)
	{
		UIQuitDesktop->OnClicked.AddDynamic(this,&UGameStatusWidget::QuitDesktop);
	}
	if(UIQuitMainMenu)
	{
		UIQuitMainMenu->OnClicked.AddDynamic(this,&UGameStatusWidget::QuitMainMenu);
	}
}

void UGameStatusWidget::PlayAgain()
{
	if(UIPlayAgain)
	{
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FInputModeGameOnly InputMode;
		Player->SetInputMode(InputMode);
		
		AGCGameMode* GameMode = Cast<AGCGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RestartGame();
	}
}

void UGameStatusWidget::Quit()
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

void UGameStatusWidget::QuitDesktop()
{
	if(UIQuitDesktop)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(),EQuitPreference::Quit,true);
	}
}

void UGameStatusWidget::QuitMainMenu()
{
	if(UIQuitMainMenu)
	{
		UGameplayStatics::OpenLevel(this, FName(FString("MenuPrincipal")), false);
	}
}