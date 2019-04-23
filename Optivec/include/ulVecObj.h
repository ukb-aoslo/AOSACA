/* ulVecObj.H

  object-oriented interface for OptiVec vector functions
  of type "unsigned long"

  This file was written by Brian Dale, Case Western Reserve Univ.

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef ULVECOBJ_H

#include <VecObj.h>
#include <uiVecObj.h>

#define cvta const vector<unsigned long>&
#define cmta const matrix<unsigned long>&
#define cuia const ui&
#define cta  const unsigned long&

#define vta  vector<unsigned long>&
#define uia  ui&
#define ta   unsigned long&

#define vt   vector<unsigned long>
#define t    unsigned long
#define tVector ulVector

#define tVecObj ulVecObj
#ifdef __BORLANDC__
#pragma warn -inl
#endif

#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
namespace OptiVec{
#endif

	VECOBJ_NEW_TEMPLATE class vector<t>
	{
#ifdef _MSC_VER
     public:
		tVector vx_vect;
		ui      ui_size;
#else
		tVector vx_vect;
		ui      ui_size;
		friend class vector<char>;
		friend class vector<short>;
		friend class vector<int>;
		friend class vector<long>;
		friend class vector<quad>;
		friend class vector<unsigned char>;
		friend class vector<unsigned short>;
		friend class vector<unsigned int>;
		friend class vector<unsigned long>;
		#if defined _WIN64
			friend class vector<uquad>;
		#endif
		friend class vector<ui>;
		friend class vector<float>;
		friend class vector<double>;
		friend class vector<extended>;
		friend class vector<fComplex>;
		friend class vector<dComplex>;
		friend class vector<eComplex>;
		friend class vector<fPolar>;
		friend class vector<dPolar>;
		friend class vector<ePolar>;
		friend class matrix<char>;
		friend class matrix<short>;
		friend class matrix<int>;
		friend class matrix<long>;
		friend class matrix<quad>;
		friend class matrix<unsigned char>;
		friend class matrix<unsigned short>;
		friend class matrix<unsigned int>;
		friend class matrix<unsigned long>;
		#if defined _WIN64
			friend class matrix<uquad>;
		#endif
		friend class matrix<float>;
		friend class matrix<double>;
		friend class matrix<extended>;
		friend class matrix<fComplex>;
		friend class matrix<dComplex>;
		friend class matrix<eComplex>;
#endif
	public:
////////////////////////////////////////////////////////////////////////////////////////////////////
//constructors and destructors
//
		vector(){	vx_vect=0;	ui_size=0;}

		vector(cuia size)
		{	if(size){	vx_vect= VUL_vector(size);	ui_size= size;}
			else{	vx_vect= 0;	ui_size= 0;}}

		vector(cuia size, cta fill)
		{	if(!size) //size == 0
			{	vx_vect=0;	ui_size=0;}
			else if(!fill) //fill == 0.0
			{	vx_vect= VUL_vector0(size);	ui_size= size;}
			else
			{	vx_vect= VUL_vector(size);	ui_size= size;	VUL_equC(vx_vect,ui_size,fill);}}

		vector(cvta init)
		{	if(init.ui_size)
			{ vx_vect= VUL_vector(init.ui_size);	ui_size= init.ui_size;	VUL_equV(vx_vect, init.vx_vect, ui_size);}
			else
			{	vx_vect=0;	ui_size=0;}}

		~vector(){	if(vx_vect) V_free(vx_vect);}


////////////////////////////////////////////////////////////////////////////////////////////////////
//management
//
		void enforceSize()const{ if(!ui_size) throw OptiVec_EmptySizeErr();}

		void enforceSize(ui size)const{ if(ui_size != size) throw OptiVec_SizeErr();}

		void enforcePow2()const{ if(!ui_isipow2(ui_size)) throw OptiVec_Pow2SizeErr();}

		void setSize(cuia size)
		{	if(!size) dealloc(); //can set size to zero
			if(ui_size != size) //only allocate if different sizes
			{	if(vx_vect) V_free(vx_vect);
				vx_vect= VUL_vector(size);
				ui_size= size;}}

		void setSize(cvta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_size != X.ui_size) //only allocate if different sizes
			{	if(vx_vect) V_free(vx_vect);
				vx_vect= VUL_vector(X.ui_size);
				ui_size= X.ui_size;}}

		ui       getSize() const { return ui_size; }
		tVector  getVector() const { return vx_vect; }

#if !defined (_CRTDBG_MAP_ALLOC) // crtdbg.h defines free as a macro
		void free()
		{	if(vx_vect) V_free(vx_vect);
			vx_vect=0;
			ui_size=0;}
#endif

		void dealloc()
		{	if(vx_vect) V_free(vx_vect);
			vx_vect=0;
			ui_size=0;}

		ta at(ui n)const
		{	enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return vx_vect[n];}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Overloaded operators
//
		vta operator=(cvta vect)
		{	setSize(vect.ui_size);
			enforceSize();
			VUL_equV(vx_vect, vect.vx_vect, ui_size);
			return *this;}

		vta operator=(cta scalar)
		{	enforceSize();
			VUL_equC(vx_vect, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		ta operator[](const int& index){return vx_vect[index];}

		vta operator+=(cvta X)
		{	enforceSize();
			VUL_accV(vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator+=(cta scalar)
		{	enforceSize();
			VUL_addC(vx_vect, vx_vect, ui_size, scalar);
			return *this;}

		vta operator*=(cvta X)
		{	enforceSize();
			VUL_mulV(vx_vect, vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator*=(cta scalar)
		{	enforceSize();
			VUL_mulC(vx_vect,vx_vect,ui_size,scalar);
			return *this;}

		vt operator+(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VUL_addV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator+(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VUL_addC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator+(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VUL_addC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator-(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VUL_subV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator-(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VUL_subC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator-(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VUL_subrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator*(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VUL_mulV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator*(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VUL_mulC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator*(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VUL_mulC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator/(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VUL_divV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator/(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VUL_divC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator/(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VUL_divrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//OptiVec functions in member format
//

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//from VXstd.h
//

/////////////////////////////////////////////////////////////////////////////////////////
//Generation
//
		//these are not recommended, better to use constructors
		void _vector(ui size) //underscore necessary to avoid confusing with constructor
		{
			dealloc();
			if(size) vx_vect= VUL_vector(size);
			ui_size=size;
		}

		void vector0(ui size)
		{
			dealloc();
			if(size) vx_vect= VUL_vector0(size);
			ui_size=size;
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single vector elements
//
		t* Pelement(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VUL_Pelement(vx_vect,n);
		}

		t element(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VUL_element(vx_vect,n);
		}

		void getElement(t *y, ui n)
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VUL_getElement(y,vx_vect,n);
		}

		void setElement(ui n, cta C)
		{
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			VUL_setElement(vx_vect,n, C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//

		void equ0()
		{
			enforceSize();
			VUL_equ0(vx_vect,ui_size);
		}

		void equC(cta C)
		{
			enforceSize();
			VUL_equC(vx_vect, ui_size, C);
		}

		void equV(cvta X)
		{
			enforceSize();
			VUL_equV(vx_vect, X.vx_vect, ui_size);
		}

		#if (!defined _WIN64)
			void o_ramp(cta Start, cta Rise)
			{
				enforceSize();
				VULo_ramp(vx_vect, ui_size, Start, Rise);
			}
		#endif

		void ramp(cta Start, cta Rise)
		{
			enforceSize();
			VUL_ramp(vx_vect, ui_size, Start, Rise);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VUL_random(vx_vect, ui_size, seed, Min, Max);
		}

		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VUL_randomLC(vx_vect, ui_size, seed, Min, Max, state);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//

		//defined by including liVecObj.h
		void o_LItoUL(const liVecObj& X);
		void LItoUL(const liVecObj& X);

		//defined by including ubVecObj.h
		void UBtoUL(const ubVecObj& X);

		//defined by including usVecObj.h
		void UStoUL(const usVecObj& X);

		//defined by including uVecObj.h
		void UtoUL(const uVecObj& X);

#if defined _WIN64
		//defined by including uqVecObj.h
		void UQtoUL(const uqVecObj& X);

#elif defined V_HUGE //uiVecObj members
   #define UItoU               ULtoU
   #define UtoUI               UtoUL
   #define UItoUB              ULtoUB
   #define UBtoUI              UBtoUL
   #define UItoUS              ULtoUS
   #define UStoUI              UStoUL
   #define ULtoUI              equV
   #define UItoUL              equV
   #define UItoUQ              ULtoUQ
   #define UQtoUI              UQtoUL
   #define UItoF               ULtoF
   #define UItoD               ULtoD
   #define UItoE               ULtoE
#endif // V_HUGE


/////////////////////////////////////////////////////////////////////////////////////////
//Index-oriented manipulations
//
		void reflect()
		{
			enforceSize();
			VUL_reflect(vx_vect, ui_size);
		}

		void rev(cvta X)
		{
			enforceSize();
			VUL_rev(vx_vect, X.vx_vect, ui_size);
		}

		void rotate( cvta X, ssize_t pos )
		{
			enforceSize();
			VUL_rotate(vx_vect, X.vx_vect, ui_size, pos);
		}

		void rotate_buf( cvta X, ssize_t pos, cvta Buf )
		{
			enforceSize();
			VUL_rotate_buf(vx_vect, X.vx_vect, ui_size, pos, Buf.vx_vect);
		}


		void _delete(ui pos)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VUL_delete(vx_vect, ui_size, pos);
		}

		void insert(ui pos, cta C)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VUL_insert(vx_vect, ui_size, pos, C);
		}

		void sort(cvta X, int dir=1)
		{
			enforceSize();
			VUL_sort(vx_vect,X.vx_vect,ui_size,dir);
		}

		//sortind member of uiVecObj

#ifdef V_HUGE //uiVecObj members
		//defined by including ubVecObj.h
		void sortind(const ubVecObj& X, int dir);

		//defined by including usVecObj.h
		void sortind(const usVecObj& X, int dir);

		//defined by including uVecObj.h
		void sortind(const uVecObj& X, int dir);

		//valid for both ul and ui
		void sortind(const ulVecObj& X, int dir);

		//defined by including biVecObj.h
		void sortind(const biVecObj& X, int dir);

		//defined by including siVecObj.h
		void sortind(const siVecObj& X, int dir);

		//defined by including iVecObj.h
		void sortind(const iVecObj& X, int dir);

		//defined by including liVecObj.h
		void sortind(const liVecObj& X, int dir);

		//defined by including qiVecObj.h
		void sortind(const qiVecObj& X, int dir);

		//defined by including fVecObj.h
		void sortind(const fVecObj& X, int dir);

		//defined by including dVecObj.h
		void sortind(const dVecObj& X, int dir);

#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		void sortind(const eVecObj& X, int dir);
#endif //__BORLANDC__
#endif //V_HUGE

		void subvector(cvta X, ssize_t step, ui start=0)
		{
			enforceSize();
			if(vx_vect==X.vx_vect) throw OptiVec_Err();
			VUL_subvector(vx_vect, ui_size, X.vx_vect+start, step);
		}

		void subvector_equC(const ui& samp, cta C)
		{
			enforceSize();
			VUL_subvector_equC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_equV(const ui& samp, cvta X)
		{
			enforceSize();
			VUL_subvector_equV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void indpick(const uiVecObj& Ind, cvta X)
		{
			enforceSize();
			VUL_indpick(vx_vect, Ind.vx_vect, ui_size, X.vx_vect);
		}

		void indput(cvta X, const uiVecObj& Ind)
		{
			enforceSize();
			X.enforceSize();
			VUL_indput(vx_vect,X.vx_vect,Ind.vx_vect,X.ui_size);
		}

		ui searchC(cta C, int mode=0)
		{
			enforceSize();
			return VUL_searchC(vx_vect, ui_size, C, mode);
		}

		//searchV member of uiVecObj

#ifdef V_HUGE //uiVecObj members
		//defined by including ubVecObj.h
		void searchV(const ubVecObj& X, const ubVecObj& Tab, int mode);

		//defined by including usVecObj.h
		void searchV(const usVecObj& X, const usVecObj& Tab, int mode);

		//defined by including uVecObj.h
		void searchV(const uVecObj& X, const uVecObj& Tab, int mode);

		//valid for both ul and ui
		void searchV(const ulVecObj& X, const ulVecObj& Tab, int mode);

		//defined by including biVecObj.h
		void searchV(const biVecObj& X, const biVecObj& Tab, int mode);

		//defined by including siVecObj.h
		void searchV(const siVecObj& X, const siVecObj& Tab, int mode);

		//defined by including iVecObj.h
		void searchV(const iVecObj& X, const iVecObj& Tab, int mode);

		//defined by including liVecObj.h
		void searchV(const liVecObj& X, const liVecObj& Tab, int mode);

		//defined by including qiVecObj.h
		void searchV(const qiVecObj& X, const qiVecObj& Tab, int mode);

		//defined by including fVecObj.h
		void searchV(const fVecObj& X, const fVecObj& Tab, int mode);

		//defined by including dVecObj.h
		void searchV(const dVecObj& X, const dVecObj& Tab, int mode);
		
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		void searchV(const eVecObj& X, const eVecObj& Tab, int mode);
#endif //__BORLANDC__
#endif //V_HUGE


/////////////////////////////////////////////////////////////////////////////////////////
//Functions of a sub-set of elements
//


/////////////////////////////////////////////////////////////////////////////////////////
//One-Dimensional Vector Operations
//
		#if (!defined _WIN64)
			t o_sum() const
			{
				enforceSize();
				return VULo_sum(vx_vect, ui_size);
			}

			void o_runsum(cvta X)
			{
				enforceSize();
				VULo_runsum(vx_vect, X.vx_vect, ui_size);
			}
		#endif

		t sum() const
		{
			enforceSize();
			return VUL_sum(vx_vect, ui_size);
		}

		void runsum(cvta X)
		{
			enforceSize();
			VUL_runsum(vx_vect, X.vx_vect, ui_size);
		}

		//underscore needed because max defined in windef.h
		t _max() const
		{
			enforceSize();
			return VUL_max(vx_vect, ui_size);
		}

		//underscore needed because min defined in windef.h
		t _min() const
		{
			enforceSize();
			return VUL_min(vx_vect, ui_size);
		}

		t maxind(ui* Ind) const
		{
			enforceSize();
			return VUL_maxind(Ind, vx_vect, ui_size);
		}

		t minind(ui* Ind) const
		{
			enforceSize();
			return VUL_minind(Ind, vx_vect, ui_size);
		}

		double fsum() const
		{
			enforceSize();
			return VUL_fsum(vx_vect,ui_size);
		}

		double mean() const
		{
			enforceSize();
			return VUL_mean(vx_vect,ui_size);
		}

		void runmax(cvta X)
		{
			enforceSize();
			VUL_runmax(vx_vect, X.vx_vect, ui_size);
		}

		void runmin(cvta X)
		{
			enforceSize();
			VUL_runmin(vx_vect, X.vx_vect, ui_size);
		}

		int iselementC(cta C) const
		{
			enforceSize();
			return VUL_iselementC(vx_vect, ui_size, C);
		}

		ui iselementV(cvta X, cvta Tab)
		{
			enforceSize();
			return VUL_iselementV(vx_vect, X.vx_vect,
				ui_size, Tab.vx_vect, Tab.ui_size);
		}

		//distribution member of uiVecObj

#ifdef V_HUGE //uiVecObj members
		//defined by including fVecObj.h
		ui localmaxima(const fVecObj& X);

		//defined by including dVecObj.h
		ui localmaxima(const dVecObj& X);

#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		ui localmaxima(const eVecObj& X);
#endif //__BORLANDC__

		//defined by including fVecObj.h
		ui localminima(const fVecObj& X);

		//defined by including dVecObj.h
		ui localminima(const dVecObj& X);

#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		ui localminima(const eVecObj& X);
#endif //__BORLANDC__
#endif //V_HUGE


/////////////////////////////////////////////////////////////////////////////////////////
//Statistical Functions and Building Blocks
//

#ifdef V_HUGE //uiVecObj members
		//defined by including fVecObj.h
		ui distribution(const fVecObj& Limits, const fVecObj& X, int mode);

		//defined by including dVecObj.h
		ui distribution(const dVecObj& Limits, const dVecObj& X, int mode);

#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		ui distribution(const eVecObj& Limits, const eVecObj& X, int mode);
#endif //__BORLANDC__
#endif //V_HUGE


/////////////////////////////////////////////////////////////////////////////////////////
//Fourier Transforms, Convolutions, Filtering
//


/////////////////////////////////////////////////////////////////////////////////////////
//Analysis
//


/////////////////////////////////////////////////////////////////////////////////////////
//Geometrical Vector Arithmetics
//


/////////////////////////////////////////////////////////////////////////////////////////
//Input and Output
//
		void fprint(FILE* stream, unsigned nperline, unsigned linewidth) const
		{
			enforceSize();
			VUL_fprint(stream,vx_vect,ui_size,nperline,linewidth);
		}

		void cprint(unsigned nperline) const
		{
			enforceSize();
			VUL_cprint(vx_vect,ui_size,nperline);
		}

		void print(unsigned nperline) const
		{
			fprint(stdout,nperline,80);
		}

		void setRadix(int i)
		{
			V_setRadix(i);
		}

		void read(FILE* stream)
		{
			enforceSize();
			VUL_read(vx_vect,ui_size,stream);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			VUL_write(stream,vx_vect,ui_size);
		}

//nread
//nwrite

		void setWriteFormat(char* formatString) const
		{
			VUL_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VUL_setWriteSeparate(sepString);
		}

//setNWriteSeparate

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_size,sizeof(ui),1,stream);
			VUL_store(stream,vx_vect,ui_size);
		}

		void recall(FILE* stream)
		{
			ui sz;
			fread(&sz,sizeof(ui),1,stream);
			setSize(sz);
			VUL_recall(vx_vect,ui_size,stream);
		}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//from VXmath.h
//


/////////////////////////////////////////////////////////////////////////////////////////
//Rounding
//
		//defined by including fVecObj.h
		int roundtoUL(const fVecObj& X);

		//defined by including fVecObj.h
		int floortoUL(const fVecObj& X);
		
		//defined by including fVecObj.h
		int ceiltoUL(const fVecObj& X);
		
		//defined by including fVecObj.h
		int choptoUL(const fVecObj& X);
		
		int trunctoUL(const fVecObj& X)
		{
			return choptoUL(X);
		}
		
		//defined by including dVecObj.h
		int roundtoUL(const dVecObj& X);

		//defined by including dVecObj.h
		int floortoUL(const dVecObj& X);
		
		//defined by including dVecObj.h
		int ceiltoUL(const dVecObj& X);
		
		//defined by including dVecObj.h
		int choptoUL(const dVecObj& X);
		
		int trunctoUL(const dVecObj& X)
		{
			return choptoUL(X);
		}

#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		int roundtoUL(const eVecObj& X);
		
		//defined by including eVecObj.h
		int floortoUL(const eVecObj& X);
		
		//defined by including eVecObj.h
		int ceiltoUL(const eVecObj& X);
		
		//defined by including eVecObj.h
		int choptoUL(const eVecObj& X);

		int trunctoUL(const eVecObj& X)
		{
			return choptoUL(X);
		}
#endif //__BORLANDC__

#ifdef V_HUGE //uiVecObj members
	#define roundtoUI roundtoUL
	#define floortoUI floortoUL
	#define ceiltoUI  ceiltoUL
	#define choptoUI  choptoUL		
	#define trunctoUI trunctoUL
#endif //V_HUGE


/////////////////////////////////////////////////////////////////////////////////////////
//Comparisons
//
		ui cmp_eq0(cvta X)
		{
			enforceSize();
			return VUL_cmp_eq0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_ne0(cvta X)
		{
			enforceSize();
			return VUL_cmp_ne0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_gt0(cvta X)
		{
			enforceSize();
			return VUL_cmp_gt0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_eqC(cvta X, cta C)
		{
			enforceSize();
			return VUL_cmp_eqC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_neC(cvta X, cta C)
		{
			enforceSize();
			return VUL_cmp_neC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_leC(cvta X, cta C)
		{
			enforceSize();
			return VUL_cmp_leC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_ltC(cvta X, cta C)
		{
			enforceSize();
			return VUL_cmp_ltC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_geC(cvta X, cta C)
		{
			enforceSize();
			return VUL_cmp_geC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_gtC(cvta X, cta C)
		{
			enforceSize();
			return VUL_cmp_gtC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_eqV(cvta X, cvta Y)
		{
			enforceSize();
			return VUL_cmp_eqV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_neV(cvta X, cvta Y)
		{
			enforceSize();
			return VUL_cmp_neV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_leV(cvta X, cvta Y)
		{
			enforceSize();
			return VUL_cmp_leV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_ltV(cvta X, cvta Y)
		{
			enforceSize();
			return VUL_cmp_ltV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_geV(cvta X, cvta Y)
		{
			enforceSize();
			return VUL_cmp_geV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_gtV(cvta X, cvta Y)
		{
			enforceSize();
			return VUL_cmp_gtV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_exclrange0C(cvta X, cta C)
		{
			enforceSize();
			return VUL_cmp_exclrange0C(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_inclrangeCC(cvta X, cta CLo, cta CHi)
		{
			enforceSize();
			return VUL_cmp_inclrangeCC(vx_vect,X.vx_vect,ui_size,CLo,CHi);
		}

		ui cmp_exclrangeCC(cvta X, cta CLo, cta CHi)
		{
			enforceSize();
			return VUL_cmp_exclrangeCC(vx_vect,X.vx_vect,ui_size,CLo,CHi);
		}

		ui cnt_eq0()  const
		{
			enforceSize();
			return VUL_cnt_eq0(vx_vect, ui_size);
		}

		ui cnt_ne0()  const
		{
			enforceSize();
			return VUL_cnt_ne0(vx_vect, ui_size);
		}

		ui cnt_gt0()  const
		{
			enforceSize();
			return VUL_cnt_gt0(vx_vect, ui_size);
		}

		ui cnt_eqC(cta C) const
		{
			enforceSize();
			return VUL_cnt_eqC(vx_vect,ui_size,C);
		}

		ui cnt_neC(cta C) const
		{
			enforceSize();
			return VUL_cnt_neC(vx_vect,ui_size,C);
		}

		ui cnt_leC(cta C) const
		{
			enforceSize();
			return VUL_cnt_leC(vx_vect,ui_size,C);
		}

		ui cnt_ltC(cta C) const
		{
			enforceSize();
			return VUL_cnt_ltC(vx_vect,ui_size,C);
		}

		ui cnt_geC(cta C) const
		{
			enforceSize();
			return VUL_cnt_geC(vx_vect,ui_size,C);
		}

		ui cnt_gtC(cta C) const
		{
			enforceSize();
			return VUL_cnt_gtC(vx_vect,ui_size,C);
		}

		ui cnt_exclrange0C(cta C) const
		{
			enforceSize();
			return VUL_cnt_exclrange0C(vx_vect,ui_size,C);
		}

		ui cnt_inclrangeCC(cta CLo, cta CHi) const
		{
			enforceSize();
			return VUL_cnt_inclrangeCC(vx_vect,ui_size,CLo, CHi);
		}

		ui cnt_exclrangeCC(cta CLo, cta CHi) const
		{
			enforceSize();
			return VUL_cnt_exclrangeCC(vx_vect,ui_size,CLo, CHi);
		}

		ui cnt_eqV(cvta Y) const
		{
			enforceSize();
			return VUL_cnt_eqV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_neV(cvta Y) const
		{
			enforceSize();
			return VUL_cnt_neV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_leV(cvta Y) const
		{
			enforceSize();
			return VUL_cnt_leV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_ltV(cvta Y) const
		{
			enforceSize();
			return VUL_cnt_ltV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_geV(cvta Y) const
		{
			enforceSize();
			return VUL_cnt_geV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_gtV(cvta Y) const
		{
			enforceSize();
			return VUL_cnt_gtV(vx_vect,Y.vx_vect,ui_size);
		}

		//indexed comparisons are members of uiVecObj

		//defined by including biVecObj.h
		ui cmp_eq0ind(const biVecObj& X);
		ui cmp_ne0ind(const biVecObj& X);
		ui cmp_le0ind(const biVecObj& X);
		ui cmp_lt0ind(const biVecObj& X);
		ui cmp_ge0ind(const biVecObj& X);
		ui cmp_gt0ind(const biVecObj& X);
		ui cmp_eqCind(const biVecObj& X,const char& C);
		ui cmp_neCind(const biVecObj& X,const char& C);
		ui cmp_leCind(const biVecObj& X,const char& C);
		ui cmp_ltCind(const biVecObj& X,const char& C);
		ui cmp_geCind(const biVecObj& X,const char& C);
		ui cmp_gtCind(const biVecObj& X,const char& C);
		ui cmp_eqVind(const biVecObj& X,const biVecObj& Y);
		ui cmp_neVind(const biVecObj& X,const biVecObj& Y);
		ui cmp_leVind(const biVecObj& X,const biVecObj& Y);
		ui cmp_ltVind(const biVecObj& X,const biVecObj& Y);
		ui cmp_geVind(const biVecObj& X,const biVecObj& Y);
		ui cmp_gtVind(const biVecObj& X,const biVecObj& Y);
		ui cmp_inclrange0Cind(const biVecObj& X, const char& C);
		ui cmp_exclrange0Cind(const biVecObj& X, const char& C);
		ui cmp_inclrangeCCind(const biVecObj& X, const char& CLo, const char& CHi);
		ui cmp_exclrangeCCind(const biVecObj& X, const char& CLo, const char& CHi);

		//defined by including siVecObj.h
		ui cmp_eq0ind(const siVecObj& X);
		ui cmp_ne0ind(const siVecObj& X);
		ui cmp_le0ind(const siVecObj& X);
		ui cmp_lt0ind(const siVecObj& X);
		ui cmp_ge0ind(const siVecObj& X);
		ui cmp_gt0ind(const siVecObj& X);
		ui cmp_eqCind(const siVecObj& X,const short& C);
		ui cmp_neCind(const siVecObj& X,const short& C);
		ui cmp_leCind(const siVecObj& X,const short& C);
		ui cmp_ltCind(const siVecObj& X,const short& C);
		ui cmp_geCind(const siVecObj& X,const short& C);
		ui cmp_gtCind(const siVecObj& X,const short& C);
		ui cmp_eqVind(const siVecObj& X,const siVecObj& Y);
		ui cmp_neVind(const siVecObj& X,const siVecObj& Y);
		ui cmp_leVind(const siVecObj& X,const siVecObj& Y);
		ui cmp_ltVind(const siVecObj& X,const siVecObj& Y);
		ui cmp_geVind(const siVecObj& X,const siVecObj& Y);
		ui cmp_gtVind(const siVecObj& X,const siVecObj& Y);
		ui cmp_inclrange0Cind(const siVecObj& X, const short& C);
		ui cmp_exclrange0Cind(const siVecObj& X, const short& C);
		ui cmp_inclrangeCCind(const siVecObj& X, const short& CLo, const short& CHi);
		ui cmp_exclrangeCCind(const siVecObj& X, const short& CLo, const short& CHi);

		//defined by including iVecObj.h
		ui cmp_eq0ind(const iVecObj& X);
		ui cmp_ne0ind(const iVecObj& X);
		ui cmp_le0ind(const iVecObj& X);
		ui cmp_lt0ind(const iVecObj& X);
		ui cmp_ge0ind(const iVecObj& X);
		ui cmp_gt0ind(const iVecObj& X);
		ui cmp_eqCind(const iVecObj& X,const int& C);
		ui cmp_neCind(const iVecObj& X,const int& C);
		ui cmp_leCind(const iVecObj& X,const int& C);
		ui cmp_ltCind(const iVecObj& X,const int& C);
		ui cmp_geCind(const iVecObj& X,const int& C);
		ui cmp_gtCind(const iVecObj& X,const int& C);
		ui cmp_eqVind(const iVecObj& X,const iVecObj& Y);
		ui cmp_neVind(const iVecObj& X,const iVecObj& Y);
		ui cmp_leVind(const iVecObj& X,const iVecObj& Y);
		ui cmp_ltVind(const iVecObj& X,const iVecObj& Y);
		ui cmp_geVind(const iVecObj& X,const iVecObj& Y);
		ui cmp_gtVind(const iVecObj& X,const iVecObj& Y);
		ui cmp_inclrange0Cind(const iVecObj& X, const int& C);
		ui cmp_exclrange0Cind(const iVecObj& X, const int& C);
		ui cmp_inclrangeCCind(const iVecObj& X, const int& CLo, const int& CHi);
		ui cmp_exclrangeCCind(const iVecObj& X, const int& CLo, const int& CHi);

		//defined by including liVecObj.h
		ui cmp_eq0ind(const liVecObj& X);
		ui cmp_ne0ind(const liVecObj& X);
		ui cmp_le0ind(const liVecObj& X);
		ui cmp_lt0ind(const liVecObj& X);
		ui cmp_ge0ind(const liVecObj& X);
		ui cmp_gt0ind(const liVecObj& X);
		ui cmp_eqCind(const liVecObj& X,const long& C);
		ui cmp_neCind(const liVecObj& X,const long& C);
		ui cmp_leCind(const liVecObj& X,const long& C);
		ui cmp_ltCind(const liVecObj& X,const long& C);
		ui cmp_geCind(const liVecObj& X,const long& C);
		ui cmp_gtCind(const liVecObj& X,const long& C);
		ui cmp_eqVind(const liVecObj& X,const liVecObj& Y);
		ui cmp_neVind(const liVecObj& X,const liVecObj& Y);
		ui cmp_leVind(const liVecObj& X,const liVecObj& Y);
		ui cmp_ltVind(const liVecObj& X,const liVecObj& Y);
		ui cmp_geVind(const liVecObj& X,const liVecObj& Y);
		ui cmp_gtVind(const liVecObj& X,const liVecObj& Y);
		ui cmp_inclrange0Cind(const liVecObj& X, const long& C);
		ui cmp_exclrange0Cind(const liVecObj& X, const long& C);
		ui cmp_inclrangeCCind(const liVecObj& X, const long& CLo, const long& CHi);
		ui cmp_exclrangeCCind(const liVecObj& X, const long& CLo, const long& CHi);

		//defined by including qiVecObj.h
		ui cmp_eq0ind(const qiVecObj& X);
		ui cmp_ne0ind(const qiVecObj& X);
		ui cmp_le0ind(const qiVecObj& X);
		ui cmp_lt0ind(const qiVecObj& X);
		ui cmp_ge0ind(const qiVecObj& X);
		ui cmp_gt0ind(const qiVecObj& X);
		ui cmp_eqCind(const qiVecObj& X,const quad& C);
		ui cmp_neCind(const qiVecObj& X,const quad& C);
		ui cmp_leCind(const qiVecObj& X,const quad& C);
		ui cmp_ltCind(const qiVecObj& X,const quad& C);
		ui cmp_geCind(const qiVecObj& X,const quad& C);
		ui cmp_gtCind(const qiVecObj& X,const quad& C);
		ui cmp_eqVind(const qiVecObj& X,const qiVecObj& Y);
		ui cmp_neVind(const qiVecObj& X,const qiVecObj& Y);
		ui cmp_leVind(const qiVecObj& X,const qiVecObj& Y);
		ui cmp_ltVind(const qiVecObj& X,const qiVecObj& Y);
		ui cmp_geVind(const qiVecObj& X,const qiVecObj& Y);
		ui cmp_gtVind(const qiVecObj& X,const qiVecObj& Y);
		ui cmp_inclrange0Cind(const qiVecObj& X, const quad& C);
		ui cmp_exclrange0Cind(const qiVecObj& X, const quad& C);
		ui cmp_inclrangeCCind(const qiVecObj& X, const quad& CLo, const quad& CHi);
		ui cmp_exclrangeCCind(const qiVecObj& X, const quad& CLo, const quad& CHi);

		//defined by including ubVecObj.h
		ui cmp_eq0ind(const ubVecObj& X);
		ui cmp_ne0ind(const ubVecObj& X);
		ui cmp_gt0ind(const ubVecObj& X);
		ui cmp_eqCind(const ubVecObj& X,const unsigned char& C);
		ui cmp_neCind(const ubVecObj& X,const unsigned char& C);
		ui cmp_leCind(const ubVecObj& X,const unsigned char& C);
		ui cmp_ltCind(const ubVecObj& X,const unsigned char& C);
		ui cmp_geCind(const ubVecObj& X,const unsigned char& C);
		ui cmp_gtCind(const ubVecObj& X,const unsigned char& C);
		ui cmp_eqVind(const ubVecObj& X,const ubVecObj& Y);
		ui cmp_neVind(const ubVecObj& X,const ubVecObj& Y);
		ui cmp_leVind(const ubVecObj& X,const ubVecObj& Y);
		ui cmp_ltVind(const ubVecObj& X,const ubVecObj& Y);
		ui cmp_geVind(const ubVecObj& X,const ubVecObj& Y);
		ui cmp_gtVind(const ubVecObj& X,const ubVecObj& Y);
		ui cmp_exclrange0Cind(const ubVecObj& X, const unsigned char& C);
		ui cmp_inclrangeCCind(const ubVecObj& X, const unsigned char& CLo, const unsigned char& CHi);
		ui cmp_exclrangeCCind(const ubVecObj& X, const unsigned char& CLo, const unsigned char& CHi);

		//defined by including usVecObj.h
		ui cmp_eq0ind(const usVecObj& X);
		ui cmp_ne0ind(const usVecObj& X);
		ui cmp_gt0ind(const usVecObj& X);
		ui cmp_eqCind(const usVecObj& X,const unsigned short& C);
		ui cmp_neCind(const usVecObj& X,const unsigned short& C);
		ui cmp_leCind(const usVecObj& X,const unsigned short& C);
		ui cmp_ltCind(const usVecObj& X,const unsigned short& C);
		ui cmp_geCind(const usVecObj& X,const unsigned short& C);
		ui cmp_gtCind(const usVecObj& X,const unsigned short& C);
		ui cmp_eqVind(const usVecObj& X,const usVecObj& Y);
		ui cmp_neVind(const usVecObj& X,const usVecObj& Y);
		ui cmp_leVind(const usVecObj& X,const usVecObj& Y);
		ui cmp_ltVind(const usVecObj& X,const usVecObj& Y);
		ui cmp_geVind(const usVecObj& X,const usVecObj& Y);
		ui cmp_gtVind(const usVecObj& X,const usVecObj& Y);
		ui cmp_exclrange0Cind(const usVecObj& X, const unsigned short& C);
		ui cmp_inclrangeCCind(const usVecObj& X, const unsigned short& CLo, const unsigned short& CHi);
		ui cmp_exclrangeCCind(const usVecObj& X, const unsigned short& CLo, const unsigned short& CHi);

		//defined by including uVecObj.h
		ui cmp_eq0ind(const uVecObj& X);
		ui cmp_ne0ind(const uVecObj& X);
		ui cmp_gt0ind(const uVecObj& X);
		ui cmp_eqCind(const uVecObj& X,const unsigned int& C);
		ui cmp_neCind(const uVecObj& X,const unsigned int& C);
		ui cmp_leCind(const uVecObj& X,const unsigned int& C);
		ui cmp_ltCind(const uVecObj& X,const unsigned int& C);
		ui cmp_geCind(const uVecObj& X,const unsigned int& C);
		ui cmp_gtCind(const uVecObj& X,const unsigned int& C);
		ui cmp_eqVind(const uVecObj& X,const uVecObj& Y);
		ui cmp_neVind(const uVecObj& X,const uVecObj& Y);
		ui cmp_leVind(const uVecObj& X,const uVecObj& Y);
		ui cmp_ltVind(const uVecObj& X,const uVecObj& Y);
		ui cmp_geVind(const uVecObj& X,const uVecObj& Y);
		ui cmp_gtVind(const uVecObj& X,const uVecObj& Y);
		ui cmp_exclrange0Cind(const uVecObj& X, const unsigned int& C);
		ui cmp_inclrangeCCind(const uVecObj& X, const unsigned int& CLo, const unsigned int& CHi);
		ui cmp_exclrangeCCind(const uVecObj& X, const unsigned int& CLo, const unsigned int& CHi);

	//defined by including ulVecObj.h
	ui cmp_eq0ind(const ulVecObj& X);
	ui cmp_ne0ind(const ulVecObj& X);
	ui cmp_gt0ind(const ulVecObj& X);
	ui cmp_eqCind(const ulVecObj& X,const unsigned long& C);
	ui cmp_neCind(const ulVecObj& X,const unsigned long& C);
	ui cmp_leCind(const ulVecObj& X,const unsigned long& C);
	ui cmp_ltCind(const ulVecObj& X,const unsigned long& C);
	ui cmp_geCind(const ulVecObj& X,const unsigned long& C);
	ui cmp_gtCind(const ulVecObj& X,const unsigned long& C);
	ui cmp_eqVind(const ulVecObj& X,const ulVecObj& Y);
	ui cmp_neVind(const ulVecObj& X,const ulVecObj& Y);
	ui cmp_leVind(const ulVecObj& X,const ulVecObj& Y);
	ui cmp_ltVind(const ulVecObj& X,const ulVecObj& Y);
	ui cmp_geVind(const ulVecObj& X,const ulVecObj& Y);
	ui cmp_gtVind(const ulVecObj& X,const ulVecObj& Y);
	ui cmp_exclrange0Cind(const ulVecObj& X, const unsigned long& C);
	ui cmp_inclrangeCCind(const ulVecObj& X, const unsigned long& CLo, const unsigned long& CHi);
	ui cmp_exclrangeCCind(const ulVecObj& X, const unsigned long& CLo, const unsigned long& CHi);


/////////////////////////////////////////////////////////////////////////////////////////
//Standard Arithmetics or Basic Arithmetics
//

		#if (!defined _WIN64)
			void o_addC(cvta X, cta C)
			{
				enforceSize();
				VULo_addC(vx_vect, X.vx_vect, ui_size, C);
			}

			void o_subC(cvta X, cta C)
			{
				enforceSize();
				VULo_subC(vx_vect, X.vx_vect, ui_size, C);
			}

			void o_subrC(cvta X, cta C)
			{
				enforceSize();
				VULo_subrC(vx_vect, X.vx_vect, ui_size, C);
			}

			void o_mulC(cvta X, cta C)
			{
				enforceSize();
				VULo_mulC(vx_vect, X.vx_vect, ui_size, C);
			}
		#endif

		void addC(cvta X, cta C)
		{
			enforceSize();
			VUL_addC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subC(cvta X, cta C)
		{
			enforceSize();
			VUL_subC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subrC(cvta X, cta C)
		{
			enforceSize();
			VUL_subrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void mulC(cvta X, cta C)
		{
			enforceSize();
			VUL_mulC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divC(cvta X, cta C)
		{
			enforceSize();
			VUL_divC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divrC(cvta X, cta C)
		{
			enforceSize();
			VUL_divrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void modC(cvta X, cta C)
		{
			enforceSize();
			VUL_modC(vx_vect, X.vx_vect, ui_size, C);
		}

		void maxC(cvta X, cta C)
		{
			enforceSize();
			VUL_maxC( vx_vect, X.vx_vect, ui_size, C);
		}

		void minC(cvta X, cta C)
		{
			enforceSize();
			VUL_minC( vx_vect, X.vx_vect, ui_size, C);
		}

		#if (!defined _WIN64)
			void o_addV(cvta X, cvta Y)
			{
				enforceSize();
				VULo_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
			}

			void o_subV(cvta X, cvta Y)
			{
				enforceSize();
				VULo_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
			}

			void o_subrV(cvta X, cvta Y)
			{
				enforceSize();
				VULo_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
			}

			void o_mulV(cvta X, cvta Y)
			{
				enforceSize();
				VULo_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
			}
		#endif

		void addV(cvta X, cvta Y)
		{
			enforceSize();
			VUL_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subV(cvta X, cvta Y)
		{
			enforceSize();
			VUL_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subrV(cvta X, cvta Y)
		{
			enforceSize();
			VUL_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void mulV(cvta X, cvta Y)
		{
			enforceSize();
			VUL_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divV(cvta X, cvta Y)
		{
			enforceSize();
			VUL_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divrV(cvta X, cvta Y)
		{
			enforceSize();
			VUL_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void modV(cvta X, cvta Y)
		{
			enforceSize();
			VUL_modV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void maxV(cvta X, cvta Y)
		{
			enforceSize();
			VUL_maxV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void minV(cvta X, cvta Y)
		{
			enforceSize();
			VUL_minV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Accumulation
//
		void accV(cvta X)
		{
			enforceSize();
			VUL_accV(vx_vect,X.vx_vect,ui_size);
		}

		//defined by including ubVecObj.h
		void accVUB(const ubVecObj& X);

		//defined by including usVecObj.h
		void accVUS(const usVecObj& X);

		//defined by including uVecObj.h
		void accVU(const uVecObj& X);


/////////////////////////////////////////////////////////////////////////////////////////
//Bit-wise operations
//
		void shl(cvta X, unsigned C)
		{
			enforceSize();
			VUL_shl(vx_vect,X.vx_vect,ui_size,C);
		}

		void shr(cvta X, unsigned C)
		{
			enforceSize();
			VUL_shr(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "and"
			void _and(cvta X, cta C)
		#else
			void and(cvta X, cta C)
		#endif
		{
			enforceSize();
			VUL_and(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "or"
			void _or(cvta X, cta C)
		#else
			void or(cvta X, cta C)
		#endif
		{
			enforceSize();
			VUL_or(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "xor"
			void _xor(cvta X, cta C)
		#else
			void xor(cvta X, cta C)
		#endif
		{
			enforceSize();
			VUL_xor(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "not"
			void _not(cvta X)
		#else
			void not(cvta X)
		#endif
		{
			enforceSize();
			VUL_not(vx_vect,X.vx_vect,ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Functions of a sub-set of elements
//


/////////////////////////////////////////////////////////////////////////////////////////
//Mathematical Functions
//


/////////////////////////////////////////////////////////////////////////////////////////
//Optical Density Y = log10( X0 / X )
//
//Optical Density functions members of fVecObj, dVecObj, and eVecObj


/////////////////////////////////////////////////////////////////////////////////////////
// Graphics
//

            #ifdef __VGRAPH_H
                void xyAutoPlot( cvta X, unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    enforceSize(X.ui_size);
                    VUL_xyAutoPlot( X.vx_vect, vx_vect, ui_size, form, color );
                }

                void xy2AutoPlot( cvta X1, unsigned form1, COLORREF color1,
                         cvta X2, cvta Y2, unsigned form2, COLORREF color2 ) const
                {
                    enforceSize();
                    enforceSize(X1.ui_size);
                    Y2.enforceSize(X2.ui_size);
                    VUL_xy2AutoPlot( X1.vx_vect, vx_vect, ui_size, form1, color1,
                              X2.vx_vect, Y2.vx_vect, X2.ui_size, form2, color2 );
                }

                void yAutoPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VUL_yAutoPlot( vx_vect, ui_size, form, color );
                }

                void y2AutoPlot( unsigned form1, COLORREF color1,
                        cvta Y2, unsigned form2, COLORREF color2 ) const
                {
                    enforceSize();
                    Y2.enforceSize();
                    VUL_y2AutoPlot( vx_vect, ui_size, form1, color1,
                             Y2.vx_vect, Y2.ui_size, form2, color2 );
                }

                void xyDataPlot( cvta X, unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    enforceSize(X.ui_size);
                    VUL_xyDataPlot( X.vx_vect, vx_vect, ui_size, form, color );
                }

                void yDataPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VUL_yDataPlot( vx_vect, ui_size, form, color );
                }
            #endif   // __VGRAPH_H

/////////////////////////////////////////////////////////////////////////////////////////
// Matrix operations whose result is a vector
//

              //defined by including ulMatObj.h
            void Row_extract(cmta MA, const ui iRow);
            void Col_extract(cmta MA, const ui iCol);
            void Dia_extract(cmta MA);
            void Rows_max(cmta MA);
            void Cols_max(cmta MA);
            void Rows_min(cmta MA);
            void Cols_min(cmta MA);

	};   /* end of class vector<t>  */

/////////////////////////////////////////////////////////////////////////////////////////
//

	inline void uiVecObj::sortind(const ulVecObj& X, int dir)
	{
		enforceSize();
		VUL_sortind(vx_vect,X.vx_vect,ui_size,dir);
	}

	inline void uiVecObj::searchV(const ulVecObj& X, const ulVecObj& Tab, int mode=0)
	{
		enforceSize();
		Tab.enforceSize();
		VUL_searchV(vx_vect,X.vx_vect,ui_size,Tab.vx_vect,Tab.ui_size,mode);
	}

	inline ui uiVecObj::distribution(cvta Limits, cvta X, int mode=0)
	{
		enforceSize();
		X.enforceSize();
		return VUL_distribution(vx_vect,Limits.vx_vect,ui_size,X.vx_vect,X.ui_size,mode);
	}

	inline ui uiVecObj::cmp_eq0ind(cvta X)
	{
		enforceSize();
		return VUL_cmp_eq0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ne0ind(cvta X)
	{
		enforceSize();
		return VUL_cmp_ne0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_gt0ind(cvta X)
	{
		enforceSize();
		return VUL_cmp_gt0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_eqCind(cvta X, cta C)
	{
		enforceSize();
		return VUL_cmp_eqCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_neCind(cvta X, cta C)
	{
		enforceSize();
		return VUL_cmp_neCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_leCind(cvta X, cta C)
	{
		enforceSize();
		return VUL_cmp_leCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_ltCind(cvta X, cta C)
	{
		enforceSize();
		return VUL_cmp_ltCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_geCind(cvta X, cta C)
	{
		enforceSize();
		return VUL_cmp_geCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_gtCind(cvta X, cta C)
	{
		enforceSize();
		return VUL_cmp_gtCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_eqVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUL_cmp_eqVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_neVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUL_cmp_neVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_leVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUL_cmp_leVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ltVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUL_cmp_ltVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_geVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUL_cmp_geVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_gtVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUL_cmp_gtVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_exclrange0Cind(cvta X, cta C)
	{
		enforceSize();
		return VUL_cmp_exclrange0Cind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_inclrangeCCind(cvta X, cta CLo, cta CHi)
	{
		enforceSize();
		return VUL_cmp_inclrangeCCind(vx_vect,X.vx_vect,ui_size,CLo,CHi);
	}

	inline ui uiVecObj::cmp_exclrangeCCind(cvta X, cta CLo, cta CHi)
	{
		enforceSize();
		return VUL_cmp_exclrangeCCind(vx_vect,X.vx_vect,ui_size,CLo,CHi);
	}

#ifdef UBVECOBJ_H
	inline void ubVecObj::ULtoUB(const ulVecObj& X)
	{
		enforceSize();
		V_ULtoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void ulVecObj::UBtoUL(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline void ulVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VUL_accVUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //UBVECOBJ_H

#ifdef USVECOBJ_H
	#if (!defined _WIN64)
		inline void usVecObj::o_ULtoUS(const ulVecObj& X)
		{
			enforceSize();
			Vo_ULtoUS(vx_vect,X.vx_vect,ui_size);
		}
	#endif

	inline void usVecObj::ULtoUS(const ulVecObj& X)
	{
		enforceSize();
		V_ULtoUS(vx_vect,X.vx_vect,ui_size);
	}

	inline void ulVecObj::UStoUL(const usVecObj& X)
	{
		enforceSize();
		V_UStoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline void ulVecObj::accVUS(const usVecObj& X)
	{
		enforceSize();
		VUL_accVUS(vx_vect,X.vx_vect,ui_size);
	}
#endif //USVECOBJ

#ifdef UVECOBJ_H
	#if (!defined _WIN64)
		inline void uVecObj::o_ULtoU(const ulVecObj& X)
		{
			enforceSize();
			Vo_ULtoU(vx_vect,X.vx_vect,ui_size);
		}
	#endif

	inline void uVecObj::ULtoU(const ulVecObj& X)
	{
		enforceSize();
		V_ULtoU(vx_vect,X.vx_vect,ui_size);
	}

	inline void ulVecObj::UtoUL(const uVecObj& X)
	{
		enforceSize();
		V_UtoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline void ulVecObj::accVU(const uVecObj& X)
	{
		enforceSize();
		VUL_accVU(vx_vect,X.vx_vect,ui_size);
	}
#endif //UVECOBJ_H

#ifdef UQVECOBJ_H
	inline void uqVecObj::ULtoUQ(const ulVecObj& X)
	{
		enforceSize();
		V_ULtoUQ(vx_vect,X.vx_vect,ui_size);
	}

	inline void ulVecObj::UQtoUL(const uqVecObj& X)
	{
		enforceSize();
		V_UQtoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline void uqVecObj::accVUL(const ulVecObj& X)
	{
		enforceSize();
		VUQ_accVUL(vx_vect,X.vx_vect,ui_size);
	}
#endif //UQVECOBJ_H

#ifdef LIVECOBJ_H
	#if (!defined _WIN64)
		inline void ulVecObj::o_LItoUL(const liVecObj& X)
		{
			enforceSize();
			Vo_LItoUL(vx_vect,X.vx_vect,ui_size);
		}

		inline void liVecObj::o_ULtoLI(const ulVecObj& X)
		{
			enforceSize();
			Vo_ULtoLI(vx_vect,X.vx_vect,ui_size);
		}
	#endif

	inline void ulVecObj::LItoUL(const liVecObj& X)
	{
		enforceSize();
		V_LItoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline void liVecObj::ULtoLI(const ulVecObj& X)
	{
		enforceSize();
		V_ULtoLI(vx_vect,X.vx_vect,ui_size);
	}
#endif //LIVECOBJ_H

#ifdef QIVECOBJ_H
	inline void qiVecObj::accVUL(const ulVecObj& X)
	{
		enforceSize();
		VQI_accVUL(vx_vect,X.vx_vect,ui_size);
	}
#endif //QIVECOBJ_H

#ifdef FVECOBJ_H
	inline void fVecObj::accVUL(const ulVecObj& X)
	{
		enforceSize();
		VF_accVUL(vx_vect,X.vx_vect,ui_size);
	}

	inline void fVecObj::ULtoF(const ulVecObj& X)
	{
		enforceSize();
		V_ULtoF(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::roundtoUL(const fVecObj& X)
	{
		enforceSize();
		return VF_roundtoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::floortoUL(const fVecObj& X)
	{
		enforceSize();
		return VF_floortoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::ceiltoUL(const fVecObj& X)
	{
		enforceSize();
		return VF_ceiltoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::choptoUL(const fVecObj& X)
	{
		enforceSize();
		return VF_choptoUL(vx_vect,X.vx_vect,ui_size);
	}
#endif //FVECOBJ_H

#ifdef DVECOBJ_H
	inline void dVecObj::accVUL(const ulVecObj& X)
	{
		enforceSize();
		VD_accVUL(vx_vect,X.vx_vect,ui_size);
	}

	inline void dVecObj::ULtoD(const ulVecObj& X)
	{
		enforceSize();
		V_ULtoD(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::roundtoUL(const dVecObj& X)
	{
		enforceSize();
		return VD_roundtoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::floortoUL(const dVecObj& X)
	{
		enforceSize();
		return VD_floortoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::ceiltoUL(const dVecObj& X)
	{
		enforceSize();
		return VD_ceiltoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::choptoUL(const dVecObj& X)
	{
		enforceSize();
		return VD_choptoUL(vx_vect,X.vx_vect,ui_size);
	}
#endif //DVECOBJ_H

#ifdef EVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
	inline void eVecObj::accVUL(const ulVecObj& X)
	{
		enforceSize();
		VE_accVUL(vx_vect,X.vx_vect,ui_size);
	}

	inline void eVecObj::ULtoE(const ulVecObj& X)
	{
		enforceSize();
		V_ULtoE(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::roundtoUL(const eVecObj& X)
	{
		enforceSize();
		return VE_roundtoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::floortoUL(const eVecObj& X)
	{
		enforceSize();
		return VE_floortoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::ceiltoUL(const eVecObj& X)
	{
		enforceSize();
		return VE_ceiltoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline int ulVecObj::choptoUL(const eVecObj& X)
	{
		enforceSize();
		return VE_choptoUL(vx_vect,X.vx_vect,ui_size);
	}
#endif //__BORLANDC__
#endif //EVECOBJ_H

#ifdef CFVECOBJ_H
#endif //CFVECOBJ_H

#ifdef CDVECOBJ_H
#endif //CDVECOBJ_H

#ifdef CEVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
#endif //__BORLANDC__
#endif //CEVECOBJ_H

#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
}  // end of namespace OptiVec
#endif

#undef cvta
#undef cmta
#undef cuia
#undef cta

#undef vta
#undef uia
#undef ta

#undef vt
#undef t
#undef tVector

#undef vtcplx
#undef tcplx

#undef tVecObj
#ifdef __BORLANDC__
#pragma warn .inl
#endif

#define ULVECOBJ_H
#endif //ULVECOBJ_H
