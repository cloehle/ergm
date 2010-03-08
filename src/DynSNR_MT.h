#ifndef DYNSNR_MT_H
#define DYNSNR_MT_H

#include "MCMCDyn.h"
#include "MHproposals.h"
#include "DynSPSA_MT.h"


void MCMCDynSNR_MT_wrapper(// Observed network.
		    int *heads, int *tails, int *n_edges,
		    int *maxpossibleedges,
		    int *n_nodes, int *dflag, int *bipartite, 
		    // Ordering of formation and dissolution.
		    int *order_code, 
		    // Formation terms and proposals.
		    int *F_nterms, char **F_funnames, char **F_sonames, 
		    char **F_MHproposaltype, char **F_MHproposalpackage,
		    double *F_inputs, double *F_theta0, 
		    double *init_dev,
		    // SNR settings.
		    double *a,
		    double *alpha,
		    double *A,
		    double *c,
		    double *gamma,
		    int *iterations,
		    // Dissolution terms and proposals.
		    int *D_nterms, char **D_funnames, char **D_sonames, 
		    char **D_MHproposaltype, char **D_MHproposalpackage,
		    double *D_inputs, double *D_theta0,
		    // Degree bounds.
		    int *attribs, int *maxout, int *maxin, int *minout,
		    int *minin, int *condAllDegExact, int *attriblength,
		    // MCMC settings.
		    int *burnin, int *interval, int *dyninterval,
		    // Space for output.
		    int *maxedges,
		    // Verbosity.
		    int *fVerbose);

void MCMCDynSNR_MT(MCMCSampleDynObjective_args *t1args,
		    MCMCSampleDynObjective_args *t2args,
		    double *F_theta, 
		    double a, double alpha, double A, double c, double gamma, unsigned int iterations,
		    unsigned int burnin, unsigned int interval,
		    int fVerbose);


#endif