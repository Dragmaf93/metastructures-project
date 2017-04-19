#include "LastPage.h"

LastPage::LastPage()
    :AbstractPage(LAST_PAGE)
{
    this->setTitle("Simulations end");
    this->setFinalPage(true);
//    setButtonText(QWizard::FinishButton,QString("Restart"));
}
