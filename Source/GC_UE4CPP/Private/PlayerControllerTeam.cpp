// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerTeam.h"

APlayerControllerTeam::APlayerControllerTeam()
{
	TeamId = FGenericTeamId(0);
}

FGenericTeamId APlayerControllerTeam::GetGenericTeamId() const
{
	return TeamId;
}
