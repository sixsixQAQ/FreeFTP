#include "FreeFTP.h"

#include "FTPUtil.h"
#include "ui_FreeFTP.h"

#include <QFile>

void
FreeFTP::initUi()
{
	ui->setupUi (this);
	ui->gridLayout->removeWidget (ui->btnConnect);
	ui->gridLayout->removeWidget (ui->btnDisconnect);
	ui->gridLayout->addWidget (ui->btnConnect, 0, 2, ui->gridLayout->rowCount(), 1);
	ui->gridLayout->addWidget (ui->btnDisconnect, 0, 3, ui->gridLayout->rowCount(), 1);
	ui->gridLayout->addWidget (ui->btnConnecting, 0, 4, ui->gridLayout->rowCount(), 1);
	ui->btnConnect->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Expanding);
	ui->btnDisconnect->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Expanding);
	ui->btnConnecting->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Expanding);

	ui->btnConnecting->setDisabled (true);
	ui->lineEditPassword->setEchoMode (QLineEdit::EchoMode::Password);
}

FreeFTP::FreeFTP (QWidget *parent) : QWidget (parent), ui(std::make_shared<Ui::FreeFTPClass>())
{
	initUi();

	m_uiStateMachine   = new QStateMachine (this);
	m_stateConnecting  = new QState (m_uiStateMachine);
	m_stateConnected   = new QState (m_uiStateMachine);
	m_stateUnconnected = new QState (m_uiStateMachine);
	m_uiStateMachine->setInitialState (m_stateUnconnected);

	defineUnconnectedState();
	defineConnectingState();
	defineConnectedState();

	connect (m_stateConnecting, &QState::entered, this, &FreeFTP::slotEnterStateConnecting);

	m_uiStateMachine->start();
}

void
FreeFTP::slotEnterStateConnecting() const
{
	FTPUtil::connectToServer (
		ui->lineEditHost->text().toStdString(),
		ui->lineEditUser->text().toStdString(),
		ui->lineEditPassword->text().toStdString(),
		[=] (bool succeeded) {
			if (succeeded)
				emit signalConnectionSucceeded();
			else
				emit signalConnectionFailed();
		}
	);
}

void
FreeFTP::defineUnconnectedState()
{
	auto state = m_stateUnconnected;
	state->assignProperty (ui->btnConnect, "visible", true);
	state->assignProperty (ui->btnDisconnect, "visible", false);
	state->assignProperty (ui->btnConnecting, "visible", false);
	state->addTransition (ui->btnConnect, &QPushButton::clicked, m_stateConnecting);
}

void
FreeFTP::defineConnectingState()
{
	auto state = m_stateConnecting;
	state->assignProperty (ui->btnConnecting, "visible", true);
	state->assignProperty (ui->btnConnect, "visible", false);
	state->assignProperty (ui->btnDisconnect, "visible", false);
	state->addTransition (this, &FreeFTP::signalConnectionSucceeded, m_stateConnected);
	state->addTransition (this, &FreeFTP::signalConnectionFailed, m_stateUnconnected);
}

void
FreeFTP::defineConnectedState()
{
	auto state = m_stateConnected;
	state->assignProperty (ui->btnDisconnect, "visible", true);
	state->assignProperty (ui->btnConnect, "visible", false);
	state->assignProperty (ui->btnConnecting, "visible", false);
}

FreeFTP::~FreeFTP()
{
}
