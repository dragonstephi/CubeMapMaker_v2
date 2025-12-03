// Copyright Epic Games, Inc. All Rights Reserved.


#include "CubeMapMaker_v2PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "CubeMapMaker_v2CameraManager.h"
#include "Blueprint/UserWidget.h"
#include "CubeMapMaker_v2.h"
#include "Widgets/Input/SVirtualJoystick.h"

ACubeMapMaker_v2PlayerController::ACubeMapMaker_v2PlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ACubeMapMaker_v2CameraManager::StaticClass();
}

void ACubeMapMaker_v2PlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogCubeMapMaker_v2, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void ACubeMapMaker_v2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
}
