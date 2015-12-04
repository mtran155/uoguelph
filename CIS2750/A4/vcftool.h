/********
vcftool.h -- header file for vcftool.c in Asmt 2
Last updated:  January 28, 2014 10:05:00 PM       

Author: Michael Tran #0524704
Date Created: January 28, 2014
Contact: mtran04@uoguelph.ca
********/
#ifndef VCFTOOL_H_
#define VCFTOOL_H_ A2

#include "vcutil.h"

int vcfInfo( FILE *const outfile, const VcFile *filep );
int vcfCanon( VcFile *const filep );
int vcfSelect( VcFile *const filep, const char *which );
int vcfSort( VcFile *const filep );

int vcfCanProp( VcProp *const propp );

#endif