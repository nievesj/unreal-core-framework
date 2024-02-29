// Unreal Core Framework | Copyright (c) 2024 José M. Nieves - MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataCoreFrameworkTypes.h"

#include "InputCoreFrameworkTypes.generated.h"

class UTexture2D;

UENUM(BlueprintType)
enum class ECoreInputDeviceType : uint8
{
	None,
	KeyboardMouse,
	Gamepad,
	XboxGamePad,
	PS5GamePad
};

USTRUCT(BlueprintType)
struct FInputImageDefinitionRow : public FCoreTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetTransitionOptions)
	TSoftObjectPtr<UTexture2D> Icon; //Add an async image loader
};
