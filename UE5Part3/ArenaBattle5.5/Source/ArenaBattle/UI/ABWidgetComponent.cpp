#include "UI/ABWidgetComponent.h"
#include "ABUserWidget.h"

void UABWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UABUserWidget* ABUserWidget = Cast<UABUserWidget>(GetWidget());
	if (ABUserWidget)
	{
		ABUserWidget->SetOwningActor(GetOwner());
	}
}
