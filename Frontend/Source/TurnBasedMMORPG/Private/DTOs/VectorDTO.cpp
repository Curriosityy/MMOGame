// 


#include "DTOs/VectorDTO.h"

#include "Net/UnrealNetwork.h"


bool AVectorDTO::IsSupportedForNetworking() const
{
	return true;
}

void AVectorDTO::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, Vector)
}
