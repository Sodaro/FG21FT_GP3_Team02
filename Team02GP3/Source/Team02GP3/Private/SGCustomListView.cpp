// Fill out your copyright notice in the Description page of Project Settings.


#include "SGCustomListView.h"
#include "SCustomListView.h"
USGCustomListView::USGCustomListView(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	WidgetBarStyle = FCoreStyle::Get().GetWidgetStyle<FScrollBarStyle>("Scrollbar");
}

TSharedRef<STableViewBase> USGCustomListView::RebuildListWidget()
{
	auto outRef = ConstructListView<SCustomListView>();
	auto customViewRef = StaticCastSharedRef<SCustomListView<UObject*>>(outRef);

	customViewRef->UpdateBarStyle(WidgetBarStyle);

	return outRef;
}