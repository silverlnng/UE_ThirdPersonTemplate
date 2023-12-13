// Fill out your copyright notice in the Description page of Project Settings.


#include "ProxyPattern/MyResurceProxy.h"
#include "ProxyPattern/MyConcreteResource.h"

UMyResurceProxy::UMyResurceProxy()
{
	ActualResource = nullptr;
}

void UMyResurceProxy::LoadResource()
{
	if(!ActualResource)
	{
		ActualResource = NewObject<UMyConcreteResource>();	//角力 府家胶甫 积己
		ActualResource->LoadResource();
	}
}

UMyResurceProxy::~UMyResurceProxy()
{
	if(ActualResource)
	{
		ActualResource->ConditionalBeginDestroy();
		ActualResource =nullptr;
	}
}

void UMyResurceProxy::UseResource()
{
	if(!ActualResource)
	{
		LoadResource();
	}
	ActualResource->UseResource();
}
