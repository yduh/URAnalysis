#ifndef PDGID_h
#define PDGID_h

namespace ura{
enum PDGID {
	d = 1,
	u = 2,
	s = 3,
	c = 4,
	b = 5,
	t = 6,

	dbar = -1,
	ubar = -2,
	sbar = -3,
	cbar = -4,
	bbar = -5,
	tbar = -6,
	
	e    	 = 11,
	nu_e 	 = 12,
	mu   	 = 13,
	nu_mu  = 14,
	tau    = 15,
	nu_tau = 16,

	ebar    	= -11,
	nubar_e 	= -12,
	mubar   	= -13,
	nubar_mu  = -14,
	nubar_tau = -16,
	taubar    = -15,

	gluon = 21,
	gamma = 22,
	Z = 23,
	Wplus = 24,
	Wminus = -24,
	H = 25
};
}

#endif
