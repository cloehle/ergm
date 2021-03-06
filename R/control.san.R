#  File R/control.san.R in package ergm, part of the Statnet suite
#  of packages for network analysis, http://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  http://statnet.org/attribution
#
#  Copyright 2003-2017 Statnet Commons
#######################################################################


#' Auxiliary for Controlling SAN
#' 
#' Auxiliary function as user interface for fine-tuning simulated annealing
#' algorithm.
#' 
#' This function is only used within a call to the \code{\link{san}} function.
#' See the \code{usage} section in \code{\link{san}} for details.
#' 
#' @param SAN.tau Tuning parameter, specifying the temperature of the
#'   process during the *penultimate* iteration. (During the last
#'   iteration, the temperature is set to 0, resulting in a greedy
#'   search, and during the previous iterations, the temperature is
#'   set to `SAN.tau*(iterations left after this one)`.
#' 
#' @param SAN.invcov Initial inverse covariance matrix used to
#'   calculate Mahalanobis distance in determining how far a proposed
#'   MCMC move is from the \code{target.stats} vector.  If `NULL`,
#'   initially set to the identity matrix, then during subsequent runs
#'   estimated empirically.
#' 
#' @param SAN.nsteps Number of MCMC proposals for each simulated annealing run.
#' @param SAN.samplesize Number of realisations' statistics to obtain for tuning purposes.
#' @param SAN.init.maxedges Maximum number of edges expected in network.
#' @param SAN.max.maxedges Hard upper bound on the number of edges in the network.
#' @param SAN.prop.weights Specifies the method to allocate probabilities of
#' being proposed to dyads. Defaults to \code{"default"}, which picks a
#' reasonable default for the specified constraint.  Other possible values are
#' \code{"TNT"}, \code{"random"}, and \code{"nonobserved"}, though not all
#' values may be used with all possible constraints.
#' @param SAN.prop.args An alternative, direct way of specifying additional
#' arguments to proposal.
#' @param SAN.packagenames Names of packages in which to look for change
#' statistic functions in addition to those autodetected. This argument should
#' not be needed outside of very strange setups.
#' @template term_options
#' @template control_MCMC_parallel
#' @template seed
#' @return A list with arguments as components.
#' @seealso \code{\link{san}}
#' @keywords models
#' @export control.san
control.san<-function(SAN.tau=1,
                      SAN.invcov=NULL,
                      SAN.nsteps=2^14,
                      SAN.samplesize=2^10,
                      SAN.init.maxedges=20000,
                      SAN.max.maxedges=2^26,
                      
                      SAN.prop.weights="default",
                      SAN.prop.args=list(),
                      SAN.packagenames=c(),
                      
                      term.options=list(),

                      seed=NULL,
                      parallel=0,
                      parallel.type=NULL,
                      parallel.version.check=TRUE){
  control<-list()
  for(arg in names(formals(sys.function())))
    control[arg]<-list(get(arg))

  set.control.class("control.san")
}
