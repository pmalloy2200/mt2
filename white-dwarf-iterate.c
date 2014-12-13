/*
 * The program solves the following system of two 
 * first order differential equations, which describe 
 * the mass, density and radius of a white dwarf star.
 *
 * This version iterates over values of central density from
 * .1 to 1,000,000 and exports mass vs radius as central 
 * density increases. 
 *
 *
 * The step-size of the integrator is automatically 
 * adjusted by the controller to maintain the 
 * requested accuracy.
 */

#include <stdio.h>
#include <math.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

int dwarf_eqs (double r, const double y[], double f[], void *params);

int main (void) 
{
  size_t neqs = 2;          /* number of equations */
  double eps_abs = 1.e-8, 
    eps_rel = 0.;           /* desired precision */
  double stepsize = 1e-6;   /* initial integration step */
  double rho_c;
  double r = 1.e-3, r1 = 50.; /* time interval */
  int status;
  
   for (rho_c = 0.1; rho_c <= 1000000; rho_c*=1.2)
  {
  /* 
   * Initial conditions 
   */
  double y[2] = {0, rho_c};
  
  /*
   * Explicit embedded Runge-Kutta-Fehlberg (4,5) method. 
   * This method is a good general-purpose integrator.
   */
  gsl_odeiv2_step    *s = gsl_odeiv2_step_alloc 
                            (gsl_odeiv2_step_rkf45, neqs);
  gsl_odeiv2_control *c = gsl_odeiv2_control_y_new (eps_abs, 
						    eps_rel);
  gsl_odeiv2_evolve  *e = gsl_odeiv2_evolve_alloc (neqs);
    
  gsl_odeiv2_system sys = {dwarf_eqs, NULL, neqs, &rho_c};
    
  /*
   * Evolution loop 
   */
   
 
      
      while ( (r < r1) && (y[1] > 0))
      {
        status = gsl_odeiv2_evolve_apply (e, c, s, &sys, &r,
                                          r1, &stepsize, y);

        if (status != GSL_SUCCESS) {
          printf ("Troubles: % .5e  % .5e  % .5e\n",r, y[0], y[1]);
          break;
        }

        // printf ("% .5e  % .5e  % .5e\n", 	      
        //        r, y[0], y[1]);
      }
        printf ("% .5e  % .5e %  5e\n", 	      
                r, y[0], rho_c);
  gsl_odeiv2_evolve_free (e);
  gsl_odeiv2_control_free (c);
  gsl_odeiv2_step_free (s);
    }
  return 0;
}
