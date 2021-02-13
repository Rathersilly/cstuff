const double pi = 3.14;			// pi is const; its value may not be changed
double *ptr = &pi;				// error: ptris a plain pointer
const double *cptr = &pi;		// ok: cptr may point to a double that is const
*cptr = 42;						// error: cannot assign to *cptr (because const)

double dval = 3.14;				// dval is adouble; its value can be changed
cptr = &dval; 					// ok: but can't change dval through cptrr

int errNumb = 0;
int *const curErr = &errNumb;	// curErr will always point toerr Numb
const double pi = 3.14159;
const double *const pip = &pi; 	// pip is a const pointer to a const
*pip = 2.72;					// error: pip is a pointer to const

// if the object to which curErr points (i.e.,errNumb) is nonzero
if (*curErr) {
	errorHandler();
	*curErr = 0; // ok: reset the value of the object to whichcurErris bound
}

int i = 3;
int j = 5;
const int *p = &i;
cout <<  i << " " << *p << endl;
*p += 1;					// cant: p points to const
cout <<  i << " " << *p << endl;
p = &j;						// can change address of p, but not value
cout <<  i << " " << *p << endl;
//cout << asdf << " ";
