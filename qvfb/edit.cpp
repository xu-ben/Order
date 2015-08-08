#include "edit.h"

edit::edit(QWidget *parent):QWidget(parent)
{
	ui.setupUi(this);
	
	quantity = "1";
	changed = 1;
	ui.edit_number->setSelection(0,1);
	connect(ui.B0, SIGNAL(clicked()),this,SLOT(B0_clicked()));
	connect(ui.B1, SIGNAL(clicked()),this,SLOT(B1_clicked()));
	connect(ui.B2, SIGNAL(clicked()),this,SLOT(B2_clicked()));
	connect(ui.B3, SIGNAL(clicked()),this,SLOT(B3_clicked()));
	connect(ui.B4, SIGNAL(clicked()),this,SLOT(B4_clicked()));
	connect(ui.B5, SIGNAL(clicked()),this,SLOT(B5_clicked()));
	connect(ui.B6, SIGNAL(clicked()),this,SLOT(B6_clicked()));
	connect(ui.B7, SIGNAL(clicked()),this,SLOT(B7_clicked()));
	connect(ui.B8, SIGNAL(clicked()),this,SLOT(B8_clicked()));
	connect(ui.B9, SIGNAL(clicked()),this,SLOT(B9_clicked()));
	connect(ui.Bback, SIGNAL(clicked()),this,SLOT(Bback_clicked()));
	connect(ui.Bclear, SIGNAL(clicked()),this,SLOT(Bclear_clicked()));
	connect(ui.Benter, SIGNAL(clicked()),this,SLOT(Benter_clicked()));
}

edit::~edit()
{}

void edit::B0_clicked()
{
	if(changed)
	{
		quantity = "1";
		ui.edit_number->setSelection(0,1);
	}
	else
		quantity += ui.B0->text();
	ui.edit_number->setText(quantity);
}

void edit::B1_clicked()
{
	if(changed)
	{
		quantity = "";
		changed = 0;
	}
	quantity += ui.B1->text();
	ui.edit_number->setText(quantity);
}

void edit::B2_clicked()
{
	if(changed)
	{
		quantity = "";
		changed = 0;
	}
	quantity += ui.B2->text();
	ui.edit_number->setText(quantity);
}

void edit::B3_clicked()
{
	if(changed)
	{
		quantity = "";
		changed = 0;
	}
	quantity += ui.B3->text();
	ui.edit_number->setText(quantity);
}

void edit::B4_clicked()
{
	if(changed)
	{
		quantity = "";
		changed = 0;
	}
	quantity += ui.B4->text();
	ui.edit_number->setText(quantity);
}

void edit::B5_clicked()
{
	if(changed)
	{
		quantity = "";
		changed = 0;
	}
	quantity += ui.B5->text();
	ui.edit_number->setText(quantity);
}

void edit::B6_clicked()
{
	if(changed)
	{
		quantity = "";
		changed = 0;
	}
	quantity += ui.B6->text();
	ui.edit_number->setText(quantity);
}

void edit::B7_clicked()
{
	if(changed)
	{
		quantity = "";
		changed = 0;
	}
	quantity += ui.B7->text();
	ui.edit_number->setText(quantity);
}

void edit::B8_clicked()
{
	if(changed)
	{
		quantity = "";
		changed = 0;
	}
	quantity += ui.B8->text();
	ui.edit_number->setText(quantity);
}

void edit::B9_clicked()
{
	if(changed)
	{
		quantity = "";
		changed = 0;
	}
	quantity += ui.B9->text();
	ui.edit_number->setText(quantity);
}

void edit::Bback_clicked()
{
	if(quantity.length() >= 1)
		quantity = quantity.mid(0,quantity.length()-1);
	if(quantity.length() == 0)
	{
		quantity = "1";
		ui.edit_number->setSelection(0,1);
		changed = 1;
	}
	ui.edit_number->setText(quantity);
}

void edit::Bclear_clicked()
{
	quantity == "1";
	ui.edit_number->setText(quantity);
	ui.edit_number->setSelection(0,1);
	changed = 1;
}

void edit::Benter_clicked()
{
	this->hide();
	emit Changed(ui.edit_number->text());
	quantity == "1";
	changed = 1;
	ui.edit_number->setText("1");
	ui.edit_number->setSelection(0,1);
}
