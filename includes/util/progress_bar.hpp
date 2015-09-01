#ifndef __PROGRES_HPP_
#define __PROGRES_HPP_

#include <ostream>

namespace amon {

class ProgressBar {
public:
	/**
	 * @brief      { Initializes a new progress bar. }
	 *
	 * @param[in]  totOper  { The total number of operations in the task. }
	 * @param[in]  displayRate { The percentage needed for an automatic display. }
	 */
	ProgressBar (long long totOper, double displayRate);
	
	/**
	 * @brief      { Adds a certain number of operations to the counter. }
	 *
	 * @param[in]  operations  { The number of operations that happened. }
	 *
	 * @return     { The ProgressBar object. }
	 */
	ProgressBar operator+= (long long operations);

	/**
	 * @brief      { Displays the progress bar on the stderr. }
	 *
	 */
	void display();

	/**
	 * @brief      { Returns the current progress of the task. }
	 *
	 * @return     { The percentage done. }
	 */
	double progress();

private:
	long long opCount;
	long long total;
	long long last;
	double displayRate;
};
}

#endif 