#include "SGEntryListItem.h"
#include "SGListItem.h"
#include "Components/TextBlock.h"
#include "SGLogBook.h"
#include "Components/Button.h"

//void USGEntryListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
//{
//	//if (ListItemObject == nullptr)
//	//	return;
//
//	//ItemData = Cast<USGListItem>(ListItemObject);
//	//NameLabel->SetText(ItemData->DisplayName);
//	//ButtonWidget->OnClicked.AddDynamic(this, &USGEntryListItem::DisplayItemData);
//}

//void USGEntryListItem::AssignLogbook(USGLogBook* InLogbook)
//{
//	Logbook = InLogbook;
//}
//
//void USGEntryListItem::DisplayItemData()
//{
//	Logbook->DisplayContent(ItemData);
//}

void USGEntryListItem::NativeConstruct()
{
	ButtonWidget->OnClicked.AddDynamic(this, &USGEntryListItem::OnClick);
}

void USGEntryListItem::OnClick()
{
	OnEntryClicked.Broadcast(this);
}
