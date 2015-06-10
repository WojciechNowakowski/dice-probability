#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_ExecButton_clicked()
{
	QString combination_str = ui->combEdit->text();
	int diceNo = ui->diceNoSpin->value();
	int rollNo = ui->rollNoSpin->value();
	int faceNo = ui->faceNoSpin->value();
	int ilosc_mozliwosci = pow(faceNo, diceNo);
	int zgodne = 0;
	std::vector<int> wiersz(ilosc_mozliwosci);
	std::vector<std::vector<int>> wiersze;
	diceNo = diceNo * rollNo;
	ui->ExecButton->setEnabled(false);
	ui->textEdit->clear();
	qApp->processEvents();

	for(int i = 0; i < diceNo; ++i) // stworzenie tablicy kombinacji
	{
		wiersze.push_back(wiersz);
	}

	for (int wierszNo = 1; wierszNo < diceNo + 1; ++wierszNo)
	{
		for (int i = 0; i < pow(faceNo, wierszNo); ++i)
		{
			for (int j = i * pow(faceNo, diceNo - wierszNo); j < (i + 1) * pow(faceNo, diceNo - wierszNo); ++j)
			{
				wiersze[wierszNo - 1][j] = i % faceNo + 1;
			}
		}
	}

	for (int i = 0; i < ilosc_mozliwosci; ++i)
	{
		QString badana_comb;
		for (int wierszNo = 0; wierszNo < diceNo; ++wierszNo)
		{
			badana_comb.append(QString::number(wiersze[wierszNo][i]));
		}
		if(sprawdz_comb(badana_comb, combination_str))
			zgodne++;
	}
	double procent = (double)zgodne * 100.0 / (double)ilosc_mozliwosci;
	ui->resultLCD->display(QString::number(procent));
	ui->ExecButton->setEnabled(true);
}

bool MainWindow::sprawdz_comb(QString badany, QString wzorzec)
{
	bool wynik = false;
	int dlugosc = wzorzec.length();
	int zgodne = 0;
	QString temp = badany;
	for (int i = 0; i < dlugosc; ++i)
	{
		QString znak = wzorzec.at(i);
		badany = badany.replace(badany.indexOf(znak),znak.size(), "x");
	}
	for (int i = 0; i < badany.length(); ++i)
	{
		if(badany.at(i) == "x")
			zgodne++;
	}
	if(zgodne == dlugosc)
	{
		wynik = true;
		if(ui->checkBox->checkState() == Qt::Checked)
			ui->textEdit->append(temp);
	}
	return wynik;
}
