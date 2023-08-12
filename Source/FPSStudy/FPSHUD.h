// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPSSTUDY_API AFPSHUD : public AHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly)
        UTexture2D* CrosshairTexture;

public:
    virtual void DrawHUD() override;
};