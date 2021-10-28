#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChooseHeroMenuWidget.generated.h"

UCLASS()
class GC_UE4CPP_API UChooseHeroMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void InitializePrincipalMenuWidget(UWidget*);

	UFUNCTION()
	void Back();

	UFUNCTION()
	void Confirm();

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
	
};
