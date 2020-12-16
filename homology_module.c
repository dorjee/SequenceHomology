/*
 * Created on Apr 29, 2016
 * Author: Dorjee Gyaltsen
 **/

#include <Python.h>
#include <stdio.h>
#include <string.h>

// Define a new exception object for our module
static PyObject* SequenceError;

char *substring(const char *str, size_t begin, size_t len){
	if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len))
		return 0;
	return strndup(str + begin, len);
}

typedef struct Epitopes {
   int  start;
   int  end;
   char *sequence;
} Epitopes;

struct Epitopes *get_info(char *protein, int window_size) {

	int step = 1;
	int num_of_chunks = ((strlen(protein)-window_size)/step)+1;

	struct Epitopes *array;
	array = malloc(sizeof(struct Epitopes) * num_of_chunks + sizeof(char*));
	if (array == 0)
		return 0;

	int i = 0;
	while(i < (int)strlen(protein)){
		int start = i+1;
		int end = (int)window_size + i;
		if(end > (int)strlen(protein)) break;
		char *peptide = substring(protein, i, window_size);

		array[i].sequence = strdup(peptide);
		array[i].start = start;
		array[i].end = end;

		i++;
	}
	return array;
}

/* count mismatches in a string */
int count_mismatches(char* x, char* y, int max_mm) {
	int i;
	int mismatches = 0;
	for(i=0; x[i] && y[i]; ++i) {
		if(x[i] != y[i]) {
			mismatches++;
			if(mismatches > max_mm) {
				return max_mm + 1;
			}
		}
	}
	return mismatches;
}

static PyObject *get_homolog(PyObject *self, PyObject *args){
	char *epitope;
	char *protein;
	int threshold;

	// We expect at least 2 string arguments to this function
	if(!PyArg_ParseTuple(args, "ssi", &epitope, &protein, &threshold)){
		return NULL; // return error if none found
	}

	int epitope_size = (int)strlen(epitope);
	int window_size = epitope_size;

	int step = 1;
	int num_of_chunks = ((strlen(protein)-window_size)/step)+1;

	PyObject *list = PyList_New(num_of_chunks);
	if (!list)
		return NULL;

	struct Epitopes *peptide;
	peptide = get_info(protein, epitope_size);

	int i = 0;
	for (i = 0; i < num_of_chunks; i++) {

		int num_matches;
		double homology;

		int min_mismatches = epitope_size + 1; // the minimum number of mismatches of the epitope vs the protein
		int num_mismatches = count_mismatches(epitope, peptide[i].sequence, threshold);

		if(num_mismatches <= min_mismatches){
			if(num_mismatches < min_mismatches){
				min_mismatches = num_mismatches;
			}
		}

		num_matches = epitope_size - min_mismatches;
		homology = 100.0 * num_matches / epitope_size;

		// peptide-start, peptide-end, peptide-sequence, number of matches, homology
		PyList_SetItem(list, i, Py_BuildValue("(iisif)", peptide[i].start, peptide[i].end, peptide[i].sequence, num_matches, homology));
	}
	/* Stop memory leaks, again. */
	free(peptide);

	return list;
}

static char get_homolog_docs[] = "get_homolog(): get all possible sequence peptides; their star & end "
	"positions; number of matches; maximum homology values\n";

static PyMethodDef homology_methods[] = {
	// "PythonName"		C-function Name, 	argument_presentation, 	description
	{"get_homolog", 	get_homolog, 		METH_VARARGS, 			get_homolog_docs},
	{NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef homology_module = {
    PyModuleDef_HEAD_INIT,
    "homology_module",   /* name of module */
    get_homolog_docs, /* module documentation, may be NULL */
    -1, /* size of per-interpreter state of the module,
    	or -1 if the module keeps state in global variables. */
    homology_methods
};

PyMODINIT_FUNC 
PyInit_homology_module(void){
	PyObject *m;

	m = PyModule_Create(&homology_module);
	// m  = Py_InitModule("homology_module", homology_methods);
	if(m == NULL) 
		return NULL;

	SequenceError = PyErr_NewException("homology_module.error", NULL, NULL); // "Sequence.error" python error object
	Py_INCREF(SequenceError);

	PyModule_AddObject(m, "error", SequenceError); // register it to the python interpertor

	return m;
}
