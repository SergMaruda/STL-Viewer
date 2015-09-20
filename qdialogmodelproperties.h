#ifndef QDIALOGMODELPROPERTIES_H
#define QDIALOGMODELPROPERTIES_H

#include <QDialog>
#include "ui_qdialogmodelproperties.h"

class QDialogModelProperties : public QDialog
{
	Q_OBJECT

public:
	QDialogModelProperties(QWidget *parent = 0);
	~QDialogModelProperties();

private:
	Ui::QDialogModelProperties ui;
};

#endif // QDIALOGMODELPROPERTIES_H
