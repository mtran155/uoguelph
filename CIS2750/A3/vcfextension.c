/*
* vcfextension.c -- Wrapper functions to use with Python
* 
* Author: Michael Tran #0524704
* Date Created: March 7, 2014
* Contact: mtran04@uoguelph.ca 
*/

#include <Python.h>
#include "vcutil.h"
#include "vcftool.h"
#include <string.h>

VcFile filep;

/*
 * Function returns the Vcard property name in a string
 * 
 * Arguments:
 * VcProp - an integer that represents a VcPname 
 * 
 * Return value:
 * the string corresponding to the VcPname
 */
static char * propertyName( int VcProp ){
    char * name;

    if(VcProp == VCP_VERSION){
        name = "VERSION";
        return name;
    }
    else if(VcProp == VCP_N){
        name = "N";
        return name;
    }
    else if(VcProp == VCP_FN){
        name = "FN";
        return name;
    }
    else if(VcProp == VCP_NICKNAME){
        name = "NICKNAME";
        return name;
    }
    else if(VcProp == VCP_PHOTO){
        name = "PHOTO";
        return name;
    }
    else if(VcProp == VCP_BDAY){
        name = "BDAY";
        return name;
    }
    else if(VcProp == VCP_ADR){
        name = "ADR";
        return name;
    }
    else if(VcProp == VCP_LABEL){
        name = "LABEL";
        return name;
    }
    else if(VcProp == VCP_TEL){
        name = "TEL";
        return name;
    }
    else if(VcProp == VCP_EMAIL){
        name = "EMAIL";
        return name;
    }
    else if(VcProp == VCP_GEO){
        name = "GEO";
        return name;
    }else if(VcProp == VCP_TITLE){
        name = "TITLE";
        return name;
    }
    else if(VcProp == VCP_ORG){
        name = "ORG";
        return name;
    }
    else if(VcProp == VCP_NOTE){
        name = "NOTE";
        return name;
    }
    else if(VcProp == VCP_UID){
        name = "UID";
        return name;
    }
    else if(VcProp == VCP_URL){
        name = "URL";
        return name;
    }
    else{
        name = "";
        return name;
    }
}

PyObject *Vcf_freeFile( PyObject *self, PyObject *args );
PyObject *Vcf_writeFile( PyObject *self, PyObject *args );

static PyObject *Vcf_readFile( PyObject *self, PyObject *args ){
	char * filename;
	char string[100];
	int fileSize;
	int numCards = 0;
	VcStatus status;
	FILE * infile = NULL;
	FILE * outfile = NULL;

	if(!PyArg_ParseTuple(args, "s", &filename)){
		return NULL;
	}

	infile = fopen(filename, "r");
	status = readVcFile(infile, &filep);
	numCards = filep.ncards;
	fclose(infile);
	getUnfolded(NULL,NULL);

	if(status.code != OK){
		char lineError[100];
		if(status.code == IOERR)
			strcpy(string, "IOERR Error ");
		else if(status.code == SYNTAX)
			strcpy(string, "SYNTAX Error ");
		else if(status.code == PAROVER)
			strcpy(string, "PAROVER Error ");
		else if(status.code == BEGEND)
			strcpy(string, "BEGEND Error ");
		else if(status.code == BADVER)
			strcpy(string, "BADVER Error ");
		else if(status.code == NOPVER)
			strcpy(string, "NOPVER Error ");
		else if(status.code == NOPNFN)
			strcpy(string, "NOPNFN Error ");

		sprintf(lineError, "Line from = %d  Line to = %d\n", status.linefrom, status.lineto);
		strcat(string, lineError);

		return Py_BuildValue("s", &string);
	}
	else{
		strcpy(string, "OK");
	}

	outfile = fopen("output.txt", "w");

	vcfInfo(outfile, &filep);
	fclose(outfile);

	outfile = fopen("output.txt", "r");

	fseek(outfile, 0, SEEK_END);
	fileSize = ftell(outfile);
	rewind(outfile);
	char fileContent[fileSize];
	fread(fileContent, sizeof(char), fileSize, outfile);
	fclose(outfile);
	fileContent[fileSize] = '\0';

	return Py_BuildValue("ssi", &string, &fileContent, numCards);
}

static PyObject *Vcf_getCard( PyObject *self, PyObject *args ){
	PyObject * card = PyList_New(0);
	PyObject * temp;
	int i;
	static int counter = 0;

	for(i = 0; i < filep.cardp[counter]->nprops; i++){
		if(filep.cardp[counter] != NULL){
			temp = Py_BuildValue("ssss", propertyName(filep.cardp[counter]->prop[i].name), filep.cardp[counter]->prop[i].partype, 
				filep.cardp[counter]->prop[i].parval, filep.cardp[counter]->prop[i].value);
			PyList_Append(card, temp);
		}
	}
	counter++;

	if(counter == filep.ncards){
		counter = 0;
	}

	return card;
}

PyObject *Vcf_freeFile( PyObject *self, PyObject *args ){}
PyObject *Vcf_writeFile( PyObject *self, PyObject *args ){}


//Module Method Definition
static PyMethodDef vcfMethods[] = {
	{"readFile", Vcf_readFile, METH_VARARGS},
	{"getCard", Vcf_getCard, METH_VARARGS},
	{"freeFile", Vcf_freeFile, METH_NOARGS},
	{"writeFile", Vcf_writeFile, METH_VARARGS},
	{NULL, NULL, 0, NULL} 
};

//Module Header Definition
static struct PyModuleDef vcfModuleDef = {
	PyModuleDef_HEAD_INIT,
	"Vcf",     //enable "import Vcf"
	NULL,      //omit module documentation
	-1,        //module keeps state in global variables
	vcfMethods //link module name "Vcf" to methods table 
};

PyMODINIT_FUNC 

PyInit_Vcf(void){ 
	PyModule_Create( &vcfModuleDef ); 
}