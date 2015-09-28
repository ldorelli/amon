#include <util/progress_bar.hpp>

amon::ProgressBar::ProgressBar (long long totalOperations, double displayRate) {
	this->opCount = 0;
	last = 0;
	this->displayRate = displayRate;
	this->total = totalOperations;	
}

amon::ProgressBar amon::ProgressBar::operator+= (long long operations) {
	opCount += operations;
	if ((double)(opCount-last)/total >= displayRate) {
		display();
		last = opCount;
	}
	return *this;
}

void amon::ProgressBar::display() {
	double disp = (double) opCount/total;
	fprintf(stderr, "\r%.2lf%%", disp * 100.00);
}

double amon::ProgressBar::progress() {
	return (double) opCount/total;
}