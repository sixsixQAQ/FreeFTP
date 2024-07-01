#pragma once

#include <QtStateMachine/QStateMachine>
#include <QtWidgets/QWidget>
#include <memory>

namespace Ui {
class FreeFTPClass;
}

class FreeFTP : public QWidget {
	Q_OBJECT

public:
	FreeFTP (QWidget *parent = nullptr);
	~FreeFTP();

private:
	void initUi ();
	std::shared_ptr<Ui::FreeFTPClass> ui = nullptr;

private Q_SLOTS:
	void slotEnterStateConnecting () const;
	void slotUpdateListView (const std::vector<std::string>& files);
signals:
	void signalConnectionFailed () const;
	void signalConnectionSucceeded (const std::vector<std::string>&files) const;
private:
	QStateMachine *m_uiStateMachine = nullptr;
	QState *m_stateUnconnected		= nullptr;
	QState *m_stateConnecting		= nullptr;
	QState *m_stateConnected		= nullptr;

	void defineUnconnectedState ();
	void defineConnectingState();
	void defineConnectedState ();
};
