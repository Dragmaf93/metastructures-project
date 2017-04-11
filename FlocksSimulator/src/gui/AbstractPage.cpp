#include "AbstractPage.h"


AbstractPage::AbstractPage(AbstractPage::PAGE_TYPE type)
    :mType(type)
{
}

void AbstractPage::initializePage()
{
    emit nextPage(mType);
}

void AbstractPage::pageChanged()
{
    emit completeChanged();
}

