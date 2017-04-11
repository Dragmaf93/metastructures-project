#include "LastPage.h"

LastPage::LastPage()
    :AbstractPage(LAST_PAGE)
{
    this->setTitle("Simulations end");
    setButtonText(QWizard::FinishButton,QString("Restart"));
}
