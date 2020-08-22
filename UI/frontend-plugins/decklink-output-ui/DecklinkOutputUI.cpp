#include "DecklinkOutputUI.h"
#include <obs-module.h>
#include <util/platform.h>
#include <util/util.hpp>
#include "decklink-ui-main.h"

DecklinkOutputUI::DecklinkOutputUI(QWidget *parent)
	: QDialog(parent), ui(new Ui_Output)
{
}

void DecklinkOutputUI::ShowHideDialog()
{
}

void DecklinkOutputUI::SetupPropertiesView()
{
}

void DecklinkOutputUI::SaveSettings()
{
}

void DecklinkOutputUI::SetupPreviewPropertiesView()
{
}

void DecklinkOutputUI::SavePreviewSettings()
{
}

void DecklinkOutputUI::on_outputButton_clicked()
{
}

void DecklinkOutputUI::PropertiesChanged()
{
}

void DecklinkOutputUI::OutputStateChanged(bool active)
{
}

void DecklinkOutputUI::on_previewOutputButton_clicked()
{
}

void DecklinkOutputUI::PreviewPropertiesChanged()
{
}

void DecklinkOutputUI::PreviewOutputStateChanged(bool active)
{
}
