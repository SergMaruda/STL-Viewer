#include "qdialogmodelproperties.h"

QDialogModelProperties::QDialogModelProperties(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//ui.tableView->horizontalHeader()->
}

QDialogModelProperties::~QDialogModelProperties()
{

}

QTableView* QDialogModelProperties::GetTableView()
{
return ui.tableView;
}
