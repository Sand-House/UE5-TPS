// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletObjectPool.h"

// Sets default values
ABulletObjectPool::ABulletObjectPool()
{
	UE_LOG(LogTemp, Log, TEXT("Create Bullet Object Pool"));

	static ConstructorHelpers::FObjectFinder<UBlueprint> blueprint_finder(TEXT("/Script/Engine.Blueprint'/Game/Objects/BulletModel.BulletModel'")); // 미리 만들어놓은 bullet 블루프린트 클래스를 FObjectFinder함수를 이용해 탐색
	if (blueprint_finder.Succeeded())
		bulletBluePrint = (UClass*)blueprint_finder.Object->GeneratedClass; //탐색 후 bulletBulePrint 변수에 할당
}

// Called when the game starts or when spawned
void ABulletObjectPool::BeginPlay()
{
	Super::BeginPlay();

	bulletPool.Empty(); //오브젝트 풀 비우기

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this; // 생성될 bullet의 소유자를 현재 액터로 설정, 
	for (int32 i = 0; i < poolSize; i++) //bullet 블루 프린트 클래스를 통해 poolSize만큼 bullet 오브젝트 미리 생성
	{
		AActor* bullet = GetWorld()->SpawnActor<AActor>(bulletBluePrint, SpawnParams);
		if (bullet)
		{
			//bullet 액터를 비활성화하기 위해 아래 세 가지 함수를 실행 (랜더링 x, 충돌 x, Tick함수 x)
			bullet->SetActorEnableCollision(false);
			bullet->SetActorTickEnabled(false);
			bullet->SetActorHiddenInGame(true);
			bulletPool.Add(bullet); //생성된 bullet을 bulletPool Array에 추가
			UE_LOG(LogTemp, Log, TEXT("Object Pool : Create Bullet %d"), i);
		}
	}
}

AActor* ABulletObjectPool::GetBullet() //Bullet 오브젝트 가져오기
{	
	for (AActor* bullet : bulletPool)
	{
		bullet->SetActorHiddenInGame(false);
		bullet->SetActorTickEnabled(true);
		bullet->SetActorEnableCollision(true);
		if (bullet->GetActorLocation() == FVector(0, 0, 0)) // 안쓰는 탄
		{
			UE_LOG(LogTemp, Log, TEXT("Get Bullet"));
			return bullet;
		}
	}

	return nullptr;
}

void ABulletObjectPool::ReturnBullet(AActor* bullet) //사용한 Bullet 오브젝트 반환
{
	if (bullet)
	{
		bullet->SetActorTickEnabled(false);
		bullet->SetActorEnableCollision(false);
		bullet->SetActorHiddenInGame(true);
		bullet->SetActorLocation(FVector(0, 0, 0));
		UE_LOG(LogTemp, Log, TEXT("Return Bullet"))
	}
}


