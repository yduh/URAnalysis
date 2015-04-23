#ifndef CutFlowTracker_h
#define CutFlowTracker_h

#include <string>
#include <map>
#include "TFile.h"

class CutFlowTracker {
public:
	CutFlowTracker():
		cutflow_(),
		npoints_(),
		active_(true)	
	{}
	void track(std::string pointname);
	void writeTo(TFile &file);
	void activate() {active_ = true;};
	void deactivate() {active_ = false;};

private:
	std::map<std::string, std::pair<size_t, int> > cutflow_;
	size_t npoints_;
	bool active_;
};

#endif
