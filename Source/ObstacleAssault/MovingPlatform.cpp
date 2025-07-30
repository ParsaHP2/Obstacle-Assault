// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay(){
	Super::BeginPlay();

	StartLoc = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
    RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime){

    if (PlatReturn()){
		FVector MoveDir = PlatformVel.GetSafeNormal();
		StartLoc = StartLoc + MoveDir * MovedDist;
		SetActorLocation(StartLoc);
		PlatformVel = -PlatformVel;
		
	} else{
		FVector CurrentLoc = GetActorLocation();
		CurrentLoc += (PlatformVel * DeltaTime);
		SetActorLocation(CurrentLoc);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime){
	AddActorLocalRotation(RotateVel * DeltaTime);
	
}

bool AMovingPlatform::PlatReturn() const{
	return GetDistMoved() > MovedDist;
}

float AMovingPlatform::GetDistMoved() const{
	return FVector::Dist(StartLoc, GetActorLocation());
}

