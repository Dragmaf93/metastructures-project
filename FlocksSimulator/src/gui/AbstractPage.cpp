#include "AbstractPage.h"


AbstractPage::AbstractPage(AbstractPage::PAGE_TYPE type)
    :mType(type)
{
}

void AbstractPage::pageChanged()
{
    emit completeChanged();
}

