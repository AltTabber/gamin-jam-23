// Fill out your copyright notice in the Description page of Project Settings.


#include "MeteoreEngine.h"

#include <basetyps.h>

#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMeteoreEngine::AMeteoreEngine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating our Default Components
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	StaticMeshComp->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Game/Blueprints/Sphere.Sphere'"));
	StaticMeshComp->SetStaticMesh(SphereMeshAsset.Object);
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetupAttachment(RootComponent);

	//Using Constructor Helpers to set our Static Mesh Comp with a Sphere Shape.
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Game/Content/Blueprints/Sphere.Object'"));
	//StaticMeshComp->SetStaticMesh(SphereMeshAsset.Object);
}

// Called when the game starts or when spawned
void AMeteoreEngine::BeginPlay()
{
	Super::BeginPlay();

}





