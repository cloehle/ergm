/*  File src/SAN.h in package ergm, part of the Statnet suite
 *  of packages for network analysis, http://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  http://statnet.org/attribution
 *
 *  Copyright 2003-2017 Statnet Commons
 */
#ifndef SAN_H
#define SAN_H

#include "ergm_edgetree.h"
#include "ergm_changestat.h"
#include "ergm_MHproposal.h"
#include "ergm_model.h"
#include "MCMC.h"

/* *** don't forget tail -> head, so this function accepts tails first, not heads  */


void SAN_wrapper (int *nedges,
		  int *tails, int *heads,
		  int *dn, int *dflag, int *bipartite, 
		  int *nterms, char **funnames,
		  char **sonames, 
		  char **MHProposaltype, char **MHProposalpackage,
		  double *inputs, double *tau, 
		  double *sample,
		  int *samplesize, int *nsteps,  
		  int *newnetworktails, 
		  int *newnetworkheads, 
		  double *invcov,
		  int *fVerbose, 
		  int *attribs, int *maxout, int *maxin, int *minout,
		  int *minin, int *condAllDegExact, int *attriblength, 
		  int *maxedges,
		  int *status);

MCMCStatus SANSample (MHProposal *MHp,
		double *invcov, double *tau, double *networkstatistics, 
		int samplesize, int nsteps, 
		int fVerbose, int nmax,
		Network *nwp, Model *m);
MCMCStatus SANMetropolisHastings (MHProposal *MHp,
			 double *invcov, double *tau, double *statistics, 
			 int nsteps, int *staken,
			 int fVerbose,
			 Network *nwp, Model *m);
#endif
