#include "SGEntryListItem.h"
#include "SGListItem.h"
#include "Components/TextBlock.h"
#include "SGLogBook.h"
#include "Components/Button.h"

void USGEntryListItem::NativeConstruct()
{
	ButtonWidget->OnClicked.AddDynamic(this, &USGEntryListItem::OnClick);
}

void USGEntryListItem::OnClick()
{
	OnEntryClicked.Broadcast(this);
}
