#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/GCGameState.h"
#include "ChooseHeroMenuWidget.generated.h"

UCLASS()
class GC_UE4CPP_API UChooseHeroMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializePrincipalMenuWidget(UWidget*);

protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void Back();

	UFUNCTION()
	void Confirm();

	UFUNCTION()
	void CheckHero(bool IsCheck);

	UFUNCTION()
	void CheckGobelinMale(bool IsCheck);

	UFUNCTION()
	void CheckGobelinFemale(bool IsCheck);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIBack;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* UIConfirm;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCheckBox* UIPersonnageHero;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCheckBox* UIPersonnageGobelinMale;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCheckBox* UIPersonnageGobelinFemale;

	UWidget* PrincipalMenuWidget;
	ESkinPlayer CurrentSkinPlayer;
	
};
