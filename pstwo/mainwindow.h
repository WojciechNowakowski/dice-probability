#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void on_ExecButton_clicked();

	private:
		Ui::MainWindow *ui;
		bool sprawdz_comb(QString badany, QString wzorzec);
		QString przetworz_string(QString number, int lenght);
};

#endif // MAINWINDOW_H
