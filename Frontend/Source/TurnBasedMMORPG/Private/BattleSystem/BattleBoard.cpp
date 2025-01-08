#include "BattleSystem/BattleBoard.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ABattleBoard::ABattleBoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	FVector ZeroLocation{200, 600, -30};
	float MoveBy = 500;
	///////////
	Team1.Add(CreateDefaultSubobject<USceneComponent>("Team1-1"));
	Team1[0]->SetupAttachment(GetRootComponent());
	Team1[0]->SetRelativeLocation(ZeroLocation);
	Team1[0]->SetRelativeRotation({0, -90, 0});

	Team1.Add(CreateDefaultSubobject<USceneComponent>("Team1-2"));
	Team1[1]->SetupAttachment(GetRootComponent());
	Team1[1]->SetRelativeLocation(ZeroLocation + FVector{MoveBy, MoveBy / 4, 0});
	Team1[1]->SetRelativeRotation({0, -90, 0});

	Team1.Add(CreateDefaultSubobject<USceneComponent>("Team1-3"));
	Team1[2]->SetupAttachment(GetRootComponent());
	Team1[2]->SetRelativeLocation(ZeroLocation - FVector{MoveBy, -MoveBy / 4, 0});
	Team1[2]->SetRelativeRotation({0, -90, 0});

	Team1.Add(CreateDefaultSubobject<USceneComponent>("Team1-4"));
	Team1[3]->SetupAttachment(GetRootComponent());
	Team1[3]->SetRelativeLocation(ZeroLocation + FVector{MoveBy / 2, MoveBy, 0});
	Team1[3]->SetRelativeRotation({0, -90, 0});
	//////////////
	Team2.Add(CreateDefaultSubobject<USceneComponent>("Team2-1"));
	Team2[0]->SetupAttachment(GetRootComponent());
	Team2[0]->SetRelativeLocation(ZeroLocation * FVector{1, -1, 1});
	Team2[0]->SetRelativeRotation({0, 90, 0});

	Team2.Add(CreateDefaultSubobject<USceneComponent>("Team2-2"));
	Team2[1]->SetupAttachment(GetRootComponent());
	Team2[1]->SetRelativeLocation((ZeroLocation + FVector{MoveBy, MoveBy / 4, 0}) * FVector{1, -1, 1});
	Team2[1]->SetRelativeRotation({0, 90, 0});

	Team2.Add(CreateDefaultSubobject<USceneComponent>("Team2-3"));
	Team2[2]->SetupAttachment(GetRootComponent());
	Team2[2]->SetRelativeLocation((ZeroLocation - FVector{MoveBy, -MoveBy / 4, 0}) * FVector{1, -1, 1});
	Team2[2]->SetRelativeRotation({0, 90, 0});

	Team2.Add(CreateDefaultSubobject<USceneComponent>("Team2-4"));
	Team2[3]->SetupAttachment(GetRootComponent());
	Team2[3]->SetRelativeLocation((ZeroLocation + FVector{MoveBy / 2, MoveBy, 0}) * FVector{1, -1, 1});
	Team2[3]->SetRelativeRotation({0, 90, 0});
	bReplicates = true;
}

// Called when the game starts or when spawned
void ABattleBoard::BeginPlay()
{
	Super::BeginPlay();
}

const FTransform& ABattleBoard::GetSpawnPlace(ETeam Team, int PlaceId)
{
	check(Team1.Num()>PlaceId)
	check(Team2.Num()>PlaceId)

	if (Team == ETeam::Team1)
	{
		return Team1[PlaceId]->GetComponentTransform();
	}

	return Team2[PlaceId]->GetComponentTransform();
}
