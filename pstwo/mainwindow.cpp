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

void MainWindow::on_ExecButton_clicked()
{
	QString combination_str = ui->combEdit->text();
	int diceNo = ui->diceNoSpin->value();
	int rollNo = ui->rollNoSpin->value();
	int faceNo = ui->faceNoSpin->value();
	int zgodne = 0;
	diceNo = diceNo * rollNo;
	int ilosc_mozliwosci = pow(faceNo, diceNo);
	std::vector<int> wiersz;

	ui->ExecButton->setEnabled(false);
	ui->textEdit->clear();
	qApp->processEvents();

	for (int i = 0; i < ilosc_mozliwosci; ++i)
	{
		QString liczba = QString::number(i, faceNo);
		liczba = przetworz_string(liczba, diceNo);
		//std::cout << liczba.toStdString() << std::endl;
		if(sprawdz_comb(liczba, combination_str))
			zgodne++;
	}
	std::cout << zgodne << " / " << ilosc_mozliwosci << std::endl;
	double procent = (double)zgodne * 100.0 / (double)ilosc_mozliwosci;
	ui->resultLCD->display(QString::number(procent));
	ui->ExecButton->setEnabled(true);
}

QString MainWindow::przetworz_string(QString number, int lenght)
{
	QString result = "";
	for (int i = 0; i < lenght - number.length(); ++i)
	{
		result.append("0");
	}
	result.append(number);
	for(int j = 0; j < result.length(); ++j)
	{
		QChar znak = result.at(j);
		if (znak == '0')
			znak = '1';
		else if (znak == '1')
			znak = '2';
		else if (znak == '2')
			znak = '3';
		else if (znak == '3')
			znak = '4';
		else if (znak == '4')
			znak = '5';
		else if (znak == '5')
			znak = '6';

		result.replace(j, 1, znak);
	}
	return result;
}
