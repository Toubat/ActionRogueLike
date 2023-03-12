// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// check distance between AI pawn and target actor
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		const AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(("TargetActor")));
		if (TargetActor)
		{
			const AAIController* AIController = OwnerComp.GetAIOwner();
			if (ensure(AIController))
			{
				const APawn* AIPawn = AIController->GetPawn();
				if (ensure(AIPawn))
				{
					const float Distance = FVector::Distance(AIPawn->GetActorLocation(), TargetActor->GetActorLocation());
					const bool bWithinRange = Distance <= 1000.0f;
					const bool bHasLOS = bWithinRange && AIController->LineOfSightTo(TargetActor);

					BlackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, bHasLOS);
				}
			}
		}
	}
}