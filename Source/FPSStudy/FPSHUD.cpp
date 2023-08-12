#include "FPSHUD.h"

void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();

    UE_LOG(LogTemp, Log, TEXT("Aim"));

    if (CrosshairTexture)
    {
        // ĵ���� �߽��� ã���ϴ�.
        FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

        // �ؽ�ó �߽��� ĵ���� �߽ɿ� �µ��� �ؽ�ó�� ũ�� ���� ��ŭ �������� �ݴϴ�.
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // �߽����� ���ؼ��� �׸��ϴ�.
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
}\