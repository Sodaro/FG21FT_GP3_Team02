#pragma once

#include "Widgets/Views/SListView.h"

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 *
 */
template <typename ItemType>
class TEAM02GP3_API SCustomListView : public SListView<ItemType>
{
public:
	void UpdateBarStyle(const FScrollBarStyle& inBarStyle)
	{
		WidgetBarStyle = inBarStyle;
		if (ScrollBar.IsValid())
		{
			ScrollBar->SetStyle(&WidgetBarStyle);
		}
	}

private:
	FScrollBarStyle WidgetBarStyle;
};