#ifndef VISUALCONTROL_H
#define VISUALCONTROL_H

#include <QtGui/QMainWindow>

/*!
 * \brief The main window
 *
 * \author Christophe Hesters
 * \note put this in the gui namespace!
 */
class VisualControl : public QMainWindow
{
	Q_OBJECT

public:
	VisualControl(QWidget *parent = 0, Qt::WFlags flags = 0);
	~VisualControl();

};

#endif // VISUALCONTROL_H
