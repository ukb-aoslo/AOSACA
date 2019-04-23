/* uVecObj.H

  object-oriented interface for OptiVec vector functions
  of type "unsigned"

  This file was written by Brian Dale, Case Western Reserve Univ.

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef UVECOBJ_H

#include <VecObj.h>

#define cvta const vector<unsigned int>&
#define cuia const ui&
#define cta  const unsigned int&
#define cmta const matrix<unsigned int>&

#define vta  vector<unsigned int>&
#define uia  ui&
#define ta   unsigned int&

#define vt   vector<unsigned int>
#define t    unsigned int
#define tVector uVector

#define tVecObj uVecObj
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
		{	if(size){	vx_vect= VU_vector(size);	ui_size= size;}
			else{	vx_vect= 0;	ui_size= 0;}}

		vector(cuia size, cta fill)
		{	if(!size) //size == 0
			{	vx_vect=0;	ui_size=0;}
			else if(!fill) //fill == 0.0
			{	vx_vect= VU_vector0(size);	ui_size= size;}
			else
			{	vx_vect= VU_vector(size);	ui_size= size;	VU_equC(vx_vect,ui_size,fill);}}

		vector(cvta init)
		{	if(init.ui_size)
			{ vx_vect= VU_vector(init.ui_size);	ui_size= init.ui_size;	VU_equV(vx_vect, init.vx_vect, ui_size);}
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
				vx_vect= VU_vector(size);
				ui_size= size;}}

		void setSize(cvta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_size != X.ui_size) //only allocate if different sizes
			{	if(vx_vect) V_free(vx_vect);
				vx_vect= VU_vector(X.ui_size);
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
			VU_equV(vx_vect, vect.vx_vect, ui_size);
			return *this;}

		vta operator=(cta scalar)
		{	enforceSize();
			VU_equC(vx_vect, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		ta operator[](const int& index){return vx_vect[index];}

		vta operator+=(cvta X)
		{	enforceSize();
			VU_accV(vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator+=(cta scalar)
		{	enforceSize();
			VU_addC(vx_vect, vx_vect, ui_size, scalar);
			return *this;}

		vta operator*=(cvta X)
		{	enforceSize();
			VU_mulV(vx_vect, vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator*=(cta scalar)
		{	enforceSize();
			VU_mulC(vx_vect,vx_vect,ui_size,scalar);
			return *this;}

		vt operator+(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VU_addV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator+(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VU_addC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator+(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VU_addC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator-(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VU_subV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator-(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VU_subC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator-(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VU_subrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator*(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VU_mulV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator*(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VU_mulC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator*(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VU_mulC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator/(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VU_divV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator/(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VU_divC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator/(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VU_divrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
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
			if(size) vx_vect= VU_vector(size);
			ui_size=size;
		}

		void vector0(ui size)
		{
			dealloc();
			if(size) vx_vect= VU_vector0(size);
			ui_size=size;
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single vector elements
//
		t* Pelement(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VU_Pelement(vx_vect,n);
		}

		t element(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VU_element(vx_vect,n);
		}

		void getElement(t *y, ui n)
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VU_getElement(y,vx_vect,n);
		}

		void setElement(ui n, cta C)
		{
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			VU_setElement(vx_vect,n, C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//
		void equ0()
		{
			enforceSize();
			VU_equ0(vx_vect,ui_size);
		}

		void equC(cta C)
		{
			enforceSize();
			VU_equC(vx_vect, ui_size, C);
		}

		void equV(cvta X)
		{
			enforceSize();
			VU_equV(vx_vect, X.vx_vect, ui_size);
		}

		#if (!defined _WIN64)
			void o_ramp(cta Start, cta Rise)
			{
				enforceSize();
				VUo_ramp(vx_vect, ui_size, Start, Rise);
			}
		#endif

		void ramp(cta Start, cta Rise)
		{
			enforceSize();
			VU_ramp(vx_vect, ui_size, Start, Rise);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VU_random(vx_vect, ui_size, seed, Min, Max);
		}

		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VU_randomLC(vx_vect, ui_size, seed, Min, Max, state);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//
		//defined by including iVecObj.h
		void o_ItoU(const iVecObj& X);
		//defined by including iVecObj.h
		void ItoU(const iVecObj& X);

		//defined by including ubVecObj.h
		void UBtoU(const ubVecObj& X);
		//defined by including usVecObj.h
		void UStoU(const usVecObj& X);

		//defined by including ulVecObj.h
		void o_ULtoU(const ulVecObj& X);
		//defined by including ulVecObj.h
		void ULtoU(const ulVecObj& X);

		#if defined _WIN64
			//defined by including uqVecObj.h
			void UQtoU(const uqVecObj& X);
		#endif


#if !defined (_WIN64) && !defined (V_HUGE)
			//uiVecObj members for Win32
   #define UItoU               equV
   #define UtoUI               equV
   #define UItoUB              UtoUB
   #define UBtoUI              UBtoU
   #define UItoUS              UtoUS
   #define UStoUI              UStoU
   #define ULtoUI              ULtoU
   #define UItoUL              UtoUL
   #define UQtoUI              UQtoU
   #define UItoUQ              UtoUQ
   #define UItoF               UtoF
   #define UItoD               UtoD
   #define UItoE               UtoE
#endif // !Win64 && !V_HUGE

/////////////////////////////////////////////////////////////////////////////////////////
//Index-oriented manipulations
//
		void reflect()
		{
			enforceSize();
			VU_reflect(vx_vect, ui_size);
		}

		void rev(cvta X)
		{
			enforceSize();
			VU_rev(vx_vect, X.vx_vect, ui_size);
		}

		void rotate( cvta X, ssize_t pos )
		{
			enforceSize();
			VU_rotate(vx_vect, X.vx_vect, ui_size, pos);
		}

		void rotate_buf( cvta X, ssize_t pos, cvta Buf )
		{
			enforceSize();
			VU_rotate_buf(vx_vect, X.vx_vect, ui_size, pos, Buf.vx_vect);
		}


		void _delete(ui pos)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VU_delete(vx_vect, ui_size, pos);
		}

		void insert(ui pos, cta C)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VU_insert(vx_vect, ui_size, pos, C);
		}

		void sort(cvta X, int dir=1)
		{
			enforceSize();
			VU_sort(vx_vect,X.vx_vect,ui_size,dir);
		}

		//sortind member of uiVecObj

#if !defined (_WIN64) && !defined (V_HUGE)
		//defined by including ubVecObj.h
		void sortind(const ubVecObj& X, int dir);

		//defined by including usVecObj.h
		void sortind(const usVecObj& X, int dir);

		//valid for both u and ui
		void sortind(const uVecObj& X, int dir);

		//defined by including ulVecObj.h
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
#endif // 32-bit

		void subvector(cvta X, ssize_t step, ui start=0)
		{
			enforceSize();
			if(vx_vect==X.vx_vect) throw OptiVec_Err();
			VU_subvector(vx_vect, ui_size, X.vx_vect+start, step);
		}

		void subvector_equC(const ui& samp, cta C)
		{
			enforceSize();
			VU_subvector_equC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_equV(const ui& samp, cvta X)
		{
			enforceSize();
			VU_subvector_equV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void indpick(const uiVecObj& Ind, cvta X)
		{
			enforceSize();
			VU_indpick(vx_vect, Ind.vx_vect, ui_size, X.vx_vect);
		}

		void indput(cvta X, const uiVecObj& Ind)
		{
			enforceSize();
			X.enforceSize();
			VU_indput(vx_vect,X.vx_vect,Ind.vx_vect,X.ui_size);
		}

		ui searchC(cta C, int mode=0) const
		{
			enforceSize();
			return VU_searchC(vx_vect, ui_size, C, mode);
		}

		//searchV is member of uiVecObj

#if !defined (_WIN64) && !defined (V_HUGE)
		//uiVecObj members
		//defined by including ubVecObj.h
		void searchV(const ubVecObj& X, const ubVecObj& Tab, int mode);

		//defined by including usVecObj.h
		void searchV(const usVecObj& X, const usVecObj& Tab, int mode);

		//valid for both u and ui
		void searchV(const uVecObj& X, const uVecObj& Tab, int mode);

		//defined by including ulVecObj.h
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
#endif //!WIN64 && !V_HUGE

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
				return VUo_sum(vx_vect, ui_size);
			}

			void o_runsum(cvta X)
			{
				enforceSize();
				VUo_runsum(vx_vect, X.vx_vect, ui_size);
			}
		#endif

		t sum() const
		{
			enforceSize();
			return VU_sum(vx_vect, ui_size);
		}

		void runsum(cvta X)
		{
			enforceSize();
			VU_runsum(vx_vect, X.vx_vect, ui_size);
		}

		//underscore needed because max defined in windef.h
		t _max() const
		{
			enforceSize();
			return VU_max(vx_vect, ui_size);
		}

		//underscore needed because min defined in windef.h
		t _min() const
		{
			enforceSize();
			return VU_min(vx_vect, ui_size);
		}

		t maxind(ui* Ind) const
		{
			enforceSize();
			return VU_maxind(Ind, vx_vect, ui_size);
		}

		t minind(ui* Ind) const
		{
			enforceSize();
			return VU_minind(Ind, vx_vect, ui_size);
		}

		double fsum() const
		{
			enforceSize();
			return VU_fsum(vx_vect,ui_size);
		}

		double mean() const
		{
			enforceSize();
			return VU_mean(vx_vect,ui_size);
		}

		void runmax(cvta X)
		{
			enforceSize();
			VU_runmax(vx_vect, X.vx_vect, ui_size);
		}

		void runmin(cvta X)
		{
			enforceSize();
			VU_runmin(vx_vect, X.vx_vect, ui_size);
		}

		int iselementC(cta C) const
		{
			enforceSize();
			return VU_iselementC(vx_vect, ui_size, C);
		}

		ui iselementV(cvta X, cvta Tab)
		{
			enforceSize();
			return VU_iselementV(vx_vect, X.vx_vect,
				ui_size, Tab.vx_vect, Tab.ui_size);
		}

		//distribution member of uiVecObj

#if !defined (_WIN64)
		//uiVecObj members
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
#endif //!WIN64


/////////////////////////////////////////////////////////////////////////////////////////
//Statistical Functions and Building Blocks
//

#if !defined (_WIN64)
		//uiVecObj members
		//defined by including fVecObj.h
		ui distribution(const fVecObj& Limits, const fVecObj& X, int mode);

		//defined by including dVecObj.h
		ui distribution(const dVecObj& Limits, const dVecObj& X, int mode);

	#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		ui distribution(const eVecObj& Limits, const eVecObj& X, int mode);
	#endif //__BORLANDC__

		//defined by including biVecObj.h
		ui distribution(const biVecObj& Limits, const biVecObj& X, int mode);

		//defined by including siVecObj.h
		ui distribution(const siVecObj& Limits, const siVecObj& X, int mode);

		//defined by including iVecObj.h
		ui distribution(const iVecObj& Limits, const iVecObj& X, int mode);

		//defined by including liVecObj.h
		ui distribution(const liVecObj& Limits, const liVecObj& X, int mode);

		//defined by including qiVecObj.h
		ui distribution(const qiVecObj& Limits, const qiVecObj& X, int mode);

		//defined by including ubVecObj.h
		ui distribution(const ubVecObj& Limits, const ubVecObj& X, int mode);

		//defined by including usVecObj.h
		ui distribution(const usVecObj& Limits, const usVecObj& X, int mode);

		//defined below
		ui distribution(const uVecObj& Limits, const uVecObj& X, int mode);

		//defined by including ulVecObj.h
		ui distribution(const ulVecObj& Limits, const ulVecObj& X, int mode);
#endif //!WIN64



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
			VU_fprint(stream,vx_vect,ui_size,nperline,linewidth);
		}

		void cprint(unsigned nperline) const
		{
			enforceSize();
			VU_cprint(vx_vect,ui_size,nperline);
		}

		void print(unsigned nperline) const
		{
			fprint(stdout,nperline,80);
		}

		void setRadix(int i) const
		{
			V_setRadix(i);
		}

		void read(FILE* stream)
		{
			enforceSize();
			VU_read(vx_vect,ui_size,stream);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			VU_write(stream,vx_vect,ui_size);
		}

//nwrite
//nread

		void setWriteFormat(char* formatString) const
		{
			VU_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VU_setWriteSeparate(sepString);
		}

//setNWriteSeparate

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_size,sizeof(ui),1,stream);
			VU_store(stream,vx_vect,ui_size);
		}

		void recall(FILE* stream)
		{
			ui sz;
			fread(&sz,sizeof(ui),1,stream);
			setSize(sz);
			VU_recall(vx_vect,ui_size,stream);
		}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//from VXmath.h
//


/////////////////////////////////////////////////////////////////////////////////////////
//Rounding
//
		//defined by including fVecObj.h
		int roundtoU(const fVecObj& X);

		//defined by including fVecObj.h
		int floortoU(const fVecObj& X);
		
		//defined by including fVecObj.h
		int ceiltoU(const fVecObj& X);
		
		//defined by including fVecObj.h
		int choptoU(const fVecObj& X);
		
		int trunctoU(const fVecObj& X)
		{
			return choptoU(X);
		}
		
		//defined by including dVecObj.h
		int roundtoU(const dVecObj& X);
		
		//defined by including dVecObj.h
		int floortoU(const dVecObj& X);

		//defined by including dVecObj.h
		int ceiltoU(const dVecObj& X);
		
		//defined by including dVecObj.h
		int choptoU(const dVecObj& X);
		
		int trunctoU(const dVecObj& X)
		{
			return choptoU(X);
		}

	#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		int roundtoU(const eVecObj& X);
		
		//defined by including eVecObj.h
		int floortoU(const eVecObj& X);
		
		//defined by including eVecObj.h
		int ceiltoU(const eVecObj& X);
		
		//defined by including eVecObj.h
		int choptoU(const eVecObj& X);
		
		int trunctoU(const eVecObj& X)
		{
			return choptoU(X);
		}
	#endif //__BORLANDC__

#if !defined (_WIN64) && !defined (V_HUGE) 
		//uiVecObj members for Win32
	#define roundtoUI roundtoU
	#define floortoUI floortoU
	#define ceiltoUI  ceiltoU
	#define choptoUI  choptoU		
	#define trunctoUI trunctoU
#endif // !WIN64 && !V_HUGE


/////////////////////////////////////////////////////////////////////////////////////////
//Comparisons
//
		ui cmp_eq0(cvta X)
		{
			enforceSize();
			return VU_cmp_eq0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_ne0(cvta X)
		{
			enforceSize();
			return VU_cmp_ne0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_gt0(cvta X)
		{
			enforceSize();
			return VU_cmp_gt0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_eqC(cvta X, cta C)
		{
			enforceSize();
			return VU_cmp_eqC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_neC(cvta X, cta C)
		{
			enforceSize();
			return VU_cmp_neC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_leC(cvta X, cta C)
		{
			enforceSize();
			return VU_cmp_leC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_ltC(cvta X, cta C)
		{
			enforceSize();
			return VU_cmp_ltC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_geC(cvta X, cta C)
		{
			enforceSize();
			return VU_cmp_geC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_gtC(cvta X, cta C)
		{
			enforceSize();
			return VU_cmp_gtC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_eqV(cvta X, cvta Y)
		{
			enforceSize();
			return VU_cmp_eqV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_neV(cvta X, cvta Y)
		{
			enforceSize();
			return VU_cmp_neV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_leV(cvta X, cvta Y)
		{
			enforceSize();
			return VU_cmp_leV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_ltV(cvta X, cvta Y)
		{
			enforceSize();
			return VU_cmp_ltV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_geV(cvta X, cvta Y)
		{
			enforceSize();
			return VU_cmp_geV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_gtV(cvta X, cvta Y)
		{
			enforceSize();
			return VU_cmp_gtV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_exclrange0C(cvta X, cta C)
		{
			enforceSize();
			return VU_cmp_exclrange0C(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_inclrangeCC(cvta X, cta CLo, cta CHi)
		{
			enforceSize();
			return VU_cmp_inclrangeCC(vx_vect,X.vx_vect,ui_size,CLo,CHi);
		}

		ui cmp_exclrangeCC(cvta X, cta CLo, cta CHi)
		{
			enforceSize();
			return VU_cmp_exclrangeCC(vx_vect,X.vx_vect,ui_size,CLo,CHi);
		}

		ui cnt_eq0()  const
		{
			enforceSize();
			return VU_cnt_eq0(vx_vect, ui_size);
		}

		ui cnt_ne0()  const
		{
			enforceSize();
			return VU_cnt_ne0(vx_vect, ui_size);
		}

		ui cnt_gt0()  const
		{
			enforceSize();
			return VU_cnt_gt0(vx_vect, ui_size);
		}

		ui cnt_eqC(cta C) const
		{
			enforceSize();
			return VU_cnt_eqC(vx_vect,ui_size,C);
		}

		ui cnt_neC(cta C) const
		{
			enforceSize();
			return VU_cnt_neC(vx_vect,ui_size,C);
		}

		ui cnt_leC(cta C) const
		{
			enforceSize();
			return VU_cnt_leC(vx_vect,ui_size,C);
		}

		ui cnt_ltC(cta C) const
		{
			enforceSize();
			return VU_cnt_ltC(vx_vect,ui_size,C);
		}

		ui cnt_geC(cta C) const
		{
			enforceSize();
			return VU_cnt_geC(vx_vect,ui_size,C);
		}

		ui cnt_gtC(cta C) const
		{
			enforceSize();
			return VU_cnt_gtC(vx_vect,ui_size,C);
		}

		ui cnt_exclrange0C(cta C) const
		{
			enforceSize();
			return VU_cnt_exclrange0C(vx_vect,ui_size,C);
		}

		ui cnt_inclrangeCC(cta CLo, cta CHi) const
		{
			enforceSize();
			return VU_cnt_inclrangeCC(vx_vect,ui_size,CLo, CHi);
		}

		ui cnt_exclrangeCC(cta CLo, cta CHi) const
		{
			enforceSize();
			return VU_cnt_exclrangeCC(vx_vect,ui_size,CLo, CHi);
		}

		ui cnt_eqV(cvta Y) const
		{
			enforceSize();
			return VU_cnt_eqV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_neV(cvta Y) const
		{
			enforceSize();
			return VU_cnt_neV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_leV(cvta Y) const
		{
			enforceSize();
			return VU_cnt_leV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_ltV(cvta Y) const
		{
			enforceSize();
			return VU_cnt_ltV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_geV(cvta Y) const
		{
			enforceSize();
			return VU_cnt_geV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_gtV(cvta Y) const
		{
			enforceSize();
			return VU_cnt_gtV(vx_vect,Y.vx_vect,ui_size);
		}

		//indexed comparisons are members of uiVecObj

#if !defined (_WIN64) 
		//uiVecObj members for Win32
		//defined by including fVecObj.h
		ui cmp_eq0ind(const fVecObj& X);
		ui cmp_ne0ind(const fVecObj& X);
		ui cmp_le0ind(const fVecObj& X);
		ui cmp_lt0ind(const fVecObj& X);
		ui cmp_ge0ind(const fVecObj& X);
		ui cmp_gt0ind(const fVecObj& X);
		ui cmp_eqCind(const fVecObj& X,const float& C);
		ui cmp_neCind(const fVecObj& X,const float& C);
		ui cmp_leCind(const fVecObj& X,const float& C);
		ui cmp_ltCind(const fVecObj& X,const float& C);
		ui cmp_geCind(const fVecObj& X,const float& C);
		ui cmp_gtCind(const fVecObj& X,const float& C);
		ui cmp_eqVind(const fVecObj& X,const fVecObj& Y);
		ui cmp_neVind(const fVecObj& X,const fVecObj& Y);
		ui cmp_leVind(const fVecObj& X,const fVecObj& Y);
		ui cmp_ltVind(const fVecObj& X,const fVecObj& Y);
		ui cmp_geVind(const fVecObj& X,const fVecObj& Y);
		ui cmp_gtVind(const fVecObj& X,const fVecObj& Y);
		ui cmp_inclrange0Cind(const fVecObj& X, const float& C);
		ui cmp_exclrange0Cind(const fVecObj& X, const float& C);
		ui cmp_inclrangeCCind(const fVecObj& X, const float& CLo, const float& CHi);
		ui cmp_exclrangeCCind(const fVecObj& X, const float& CLo, const float& CHi);

		//defined by including cfVecObj.h
		ui cmp_eq0ind(const cfVecObj& X);
		ui cmp_ne0ind(const cfVecObj& X);
		ui cmp_eqCind(const cfVecObj& X, const fComplex& C);
		ui cmp_neCind(const cfVecObj& X, const fComplex& C);
		ui cmp_eqVind(const cfVecObj& X, const cfVecObj& Y);
		ui cmp_neVind(const cfVecObj& X, const cfVecObj& Y);

		//defined by including pfVecObj.h
		ui cmp_eq0ind(const pfVecObj& X);
		ui cmp_ne0ind(const pfVecObj& X);
		ui cmp_eqCind(const pfVecObj& X, const fPolar& C);
		ui cmp_neCind(const pfVecObj& X, const fPolar& C);
		ui cmp_eqVind(const pfVecObj& X, const pfVecObj& Y);
		ui cmp_neVind(const pfVecObj& X, const pfVecObj& Y);

		//defined by including dVecObj.h
		ui cmp_eq0ind(const dVecObj& X);
		ui cmp_ne0ind(const dVecObj& X);
		ui cmp_le0ind(const dVecObj& X);
		ui cmp_lt0ind(const dVecObj& X);
		ui cmp_ge0ind(const dVecObj& X);
		ui cmp_gt0ind(const dVecObj& X);
		ui cmp_eqCind(const dVecObj& X,const double& C);
		ui cmp_neCind(const dVecObj& X,const double& C);
		ui cmp_leCind(const dVecObj& X,const double& C);
		ui cmp_ltCind(const dVecObj& X,const double& C);
		ui cmp_geCind(const dVecObj& X,const double& C);
		ui cmp_gtCind(const dVecObj& X,const double& C);
		ui cmp_eqVind(const dVecObj& X,const dVecObj& Y);
		ui cmp_neVind(const dVecObj& X,const dVecObj& Y);
		ui cmp_leVind(const dVecObj& X,const dVecObj& Y);
		ui cmp_ltVind(const dVecObj& X,const dVecObj& Y);
		ui cmp_geVind(const dVecObj& X,const dVecObj& Y);
		ui cmp_gtVind(const dVecObj& X,const dVecObj& Y);
		ui cmp_inclrange0Cind(const dVecObj& X, const double& C);
		ui cmp_exclrange0Cind(const dVecObj& X, const double& C);
		ui cmp_inclrangeCCind(const dVecObj& X, const double& CLo, const double& CHi);
		ui cmp_exclrangeCCind(const dVecObj& X, const double& CLo, const double& CHi);

		//defined by including cdVecObj.h
		ui cmp_eq0ind(const cdVecObj& X);
		ui cmp_ne0ind(const cdVecObj& X);
		ui cmp_eqCind(const cdVecObj& X, const dComplex& C);
		ui cmp_neCind(const cdVecObj& X, const dComplex& C);
		ui cmp_eqVind(const cdVecObj& X, const cdVecObj& Y);
		ui cmp_neVind(const cdVecObj& X, const cdVecObj& Y);

		//defined by including pdVecObj.h
		ui cmp_eq0ind(const pdVecObj& X);
		ui cmp_ne0ind(const pdVecObj& X);
		ui cmp_eqCind(const pdVecObj& X, const dPolar& C);
		ui cmp_neCind(const pdVecObj& X, const dPolar& C);
		ui cmp_eqVind(const pdVecObj& X, const pdVecObj& Y);
		ui cmp_neVind(const pdVecObj& X, const pdVecObj& Y);

#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		ui cmp_eq0ind(const eVecObj& X);
		ui cmp_ne0ind(const eVecObj& X);
		ui cmp_le0ind(const eVecObj& X);
		ui cmp_lt0ind(const eVecObj& X);
		ui cmp_ge0ind(const eVecObj& X);
		ui cmp_gt0ind(const eVecObj& X);
		ui cmp_eqCind(const eVecObj& X,const extended& C);
		ui cmp_neCind(const eVecObj& X,const extended& C);
		ui cmp_leCind(const eVecObj& X,const extended& C);
		ui cmp_ltCind(const eVecObj& X,const extended& C);
		ui cmp_geCind(const eVecObj& X,const extended& C);
		ui cmp_gtCind(const eVecObj& X,const extended& C);
		ui cmp_eqVind(const eVecObj& X,const eVecObj& Y);
		ui cmp_neVind(const eVecObj& X,const eVecObj& Y);
		ui cmp_leVind(const eVecObj& X,const eVecObj& Y);
		ui cmp_ltVind(const eVecObj& X,const eVecObj& Y);
		ui cmp_geVind(const eVecObj& X,const eVecObj& Y);
		ui cmp_gtVind(const eVecObj& X,const eVecObj& Y);
		ui cmp_inclrange0Cind(const eVecObj& X, const extended& C);
		ui cmp_exclrange0Cind(const eVecObj& X, const extended& C);
		ui cmp_inclrangeCCind(const eVecObj& X, const extended& CLo, const extended& CHi);
		ui cmp_exclrangeCCind(const eVecObj& X, const extended& CLo, const extended& CHi);

		//defined by including ceVecObj.h
		ui cmp_eq0ind(const ceVecObj& X);
		ui cmp_ne0ind(const ceVecObj& X);
		ui cmp_eqCind(const ceVecObj& X, const eComplex& C);
		ui cmp_neCind(const ceVecObj& X, const eComplex& C);
		ui cmp_eqVind(const ceVecObj& X, const ceVecObj& Y);
		ui cmp_neVind(const ceVecObj& X, const ceVecObj& Y);

		//defined by including peVecObj.h
		ui cmp_eq0ind(const peVecObj& X);
		ui cmp_ne0ind(const peVecObj& X);
		ui cmp_eqCind(const peVecObj& X, const ePolar& C);
		ui cmp_neCind(const peVecObj& X, const ePolar& C);
		ui cmp_eqVind(const peVecObj& X, const peVecObj& Y);
		ui cmp_neVind(const peVecObj& X, const peVecObj& Y);
#endif //__BORLANDC__

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
#endif // !WIN64


/////////////////////////////////////////////////////////////////////////////////////////
//Standard Arithmetics or Basic Arithmetics
//
		#if (!defined _WIN64)
			void o_addC(cvta X, cta C)
			{
				enforceSize();
				VUo_addC(vx_vect, X.vx_vect, ui_size, C);
			}

			void o_subC(cvta X, cta C)
			{
				enforceSize();
				VUo_subC(vx_vect, X.vx_vect, ui_size, C);
			}

			void o_subrC(cvta X, cta C)
			{
				enforceSize();
				VUo_subrC(vx_vect, X.vx_vect, ui_size, C);
			}

			void o_mulC(cvta X, cta C)
			{
				enforceSize();
				VUo_mulC(vx_vect, X.vx_vect, ui_size, C);
			}
		#endif

		void addC(cvta X, cta C)
		{
			enforceSize();
			VU_addC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subC(cvta X, cta C)
		{
			enforceSize();
			VU_subC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subrC(cvta X, cta C)
		{
			enforceSize();
			VU_subrC(vx_vect, X.vx_vect, ui_size, C);
    		}

		void mulC(cvta X, cta C)
		{
			enforceSize();
			VU_mulC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divC(cvta X, cta C)
		{
			enforceSize();
			VU_divC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divrC(cvta X, cta C)
		{
			enforceSize();
			VU_divrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void modC(cvta X, cta C)
		{
			enforceSize();
			VU_modC(vx_vect, X.vx_vect, ui_size, C);
		}

		void maxC(cvta X, cta C)
		{
			enforceSize();
			VU_maxC( vx_vect, X.vx_vect, ui_size, C);
		}

		void minC(cvta X, cta C)
		{
			enforceSize();
			VU_minC( vx_vect, X.vx_vect, ui_size, C);
		}

		#if (!defined _WIN64)
			void o_addV(cvta X, cvta Y)
			{
				enforceSize();
				VUo_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
			}

			void o_subV(cvta X, cvta Y)
			{
				enforceSize();
				VUo_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
			}

			void o_subrV(cvta X, cvta Y)
			{
				enforceSize();
				VUo_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
			}

			void o_mulV(cvta X, cvta Y)
			{
				enforceSize();
				VUo_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
			}
		#endif

		void addV(cvta X, cvta Y)
		{
			enforceSize();
			VU_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subV(cvta X, cvta Y)
		{
			enforceSize();
			VU_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subrV(cvta X, cvta Y)
		{
			enforceSize();
			VU_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void mulV(cvta X, cvta Y)
		{
			enforceSize();
			VU_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divV(cvta X, cvta Y)
		{
			enforceSize();
			VU_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divrV(cvta X, cvta Y)
		{
			enforceSize();
			VU_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void modV(cvta X, cvta Y)
		{
			enforceSize();
			VU_modV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void maxV(cvta X, cvta Y)
		{
			enforceSize();
			VU_maxV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void minV(cvta X, cvta Y)
		{
			enforceSize();
			VU_minV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Accumulation
//
		void accV(cvta X)
		{
			enforceSize();
			VU_accV(vx_vect,X.vx_vect,ui_size);
		}

		//defined by including ubVecObj.h
		void accVUB(const ubVecObj& X);

		//defined by including usVecObj.h
		void accVUS(const usVecObj& X);

#if !defined (_WIN64) && !defined (V_HUGE) 
		//uiVecObj members for Win32
	#define accVU accV		
#endif // !Win64 && !V_HUGE


/////////////////////////////////////////////////////////////////////////////////////////
//Bit-wise operations
//
		void shl(cvta X, unsigned C)
		{
			enforceSize();
			VU_shl(vx_vect,X.vx_vect,ui_size,C);
		}

		void shr(cvta X, unsigned C)
		{
			enforceSize();
			VU_shr(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "and"
			void _and(cvta X, cta C)
		#else
			void and(cvta X, cta C)
		#endif
		{
			enforceSize();
			VU_and(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "or"
			void _or(cvta X, cta C)
		#else
			void or(cvta X, cta C)
		#endif
		{
			enforceSize();
			VU_or(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "xor"
			void _xor(cvta X, cta C)
		#else
			void xor(cvta X, cta C)
		#endif
		{
			enforceSize();
			VU_xor(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "not"
			void _not(cvta X)
		#else
			void not(cvta X)
		#endif
		{
			enforceSize();
			VU_not(vx_vect,X.vx_vect,ui_size);
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
                    VU_xyAutoPlot( X.vx_vect, vx_vect, ui_size, form, color );
                }

                void xy2AutoPlot( cvta X1, unsigned form1, COLORREF color1,
                         cvta X2, cvta Y2, unsigned form2, COLORREF color2 ) const
                {
                    enforceSize();
                    enforceSize(X1.ui_size);
                    Y2.enforceSize(X2.ui_size);
                    VU_xy2AutoPlot( X1.vx_vect, vx_vect, ui_size, form1, color1,
                              X2.vx_vect, Y2.vx_vect, X2.ui_size, form2, color2 );
                }

                void yAutoPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VU_yAutoPlot( vx_vect, ui_size, form, color );
                }

                void y2AutoPlot( unsigned form1, COLORREF color1,
                        cvta Y2, unsigned form2, COLORREF color2 ) const
                {
                    enforceSize();
                    Y2.enforceSize();
                    VU_y2AutoPlot( vx_vect, ui_size, form1, color1,
                             Y2.vx_vect, Y2.ui_size, form2, color2 );
                }

                void xyDataPlot( cvta X, unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    enforceSize(X.ui_size);
                    VU_xyDataPlot( X.vx_vect, vx_vect, ui_size, form, color );
                }

                void yDataPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VU_yDataPlot( vx_vect, ui_size, form, color );
                }
            #endif   // __VGRAPH_H

/////////////////////////////////////////////////////////////////////////////////////////
// Matrix operations whose result is a vector
//

              //defined by including uMatObj.h
            void Row_extract(cmta MA, const ui iRow);
            void Col_extract(cmta MA, const ui iCol);
            void Dia_extract(cmta MA);
            void Rows_max(cmta MA);
            void Cols_max(cmta MA);
            void Rows_min(cmta MA);
            void Cols_min(cmta MA);

	};   //  end of class vector<T>


/////////////////////////////////////////////////////////////////////////////////////////
//

	inline void uiVecObj::sortind(cvta X, int dir)
	{
		enforceSize();
		VU_sortind(vx_vect,X.vx_vect,ui_size,dir);
	}

	inline void uiVecObj::searchV(cvta X, cvta Tab, int mode=0)
	{
		enforceSize();
		Tab.enforceSize();
		VU_searchV(vx_vect,X.vx_vect,ui_size,Tab.vx_vect,Tab.ui_size,mode);
	}

	inline ui uiVecObj::distribution(cvta Limits, cvta X, int mode=0)
	{
		enforceSize();
		X.enforceSize();
		return VU_distribution(vx_vect,Limits.vx_vect,ui_size,X.vx_vect,X.ui_size,mode);
	}

	inline ui uiVecObj::cmp_eq0ind(cvta X)
	{
		enforceSize();
		return VU_cmp_eq0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ne0ind(cvta X)
	{
		enforceSize();
		return VU_cmp_ne0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_gt0ind(cvta X)
	{
		enforceSize();
		return VU_cmp_gt0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_eqCind(cvta X, cta C)
	{
		enforceSize();
		return VU_cmp_eqCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_neCind(cvta X, cta C)
	{
		enforceSize();
		return VU_cmp_neCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_leCind(cvta X, cta C)
	{
		enforceSize();
		return VU_cmp_leCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_ltCind(cvta X, cta C)
	{
		enforceSize();
		return VU_cmp_ltCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_geCind(cvta X, cta C)
	{
		enforceSize();
		return VU_cmp_geCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_gtCind(cvta X, cta C)
	{
		enforceSize();
		return VU_cmp_gtCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_eqVind(cvta X, cvta Y)
	{
		enforceSize();
		return VU_cmp_eqVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_neVind(cvta X, cvta Y)
	{
		enforceSize();
		return VU_cmp_neVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_leVind(cvta X, cvta Y)
	{
		enforceSize();
		return VU_cmp_leVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ltVind(cvta X, cvta Y)
	{
		enforceSize();
		return VU_cmp_ltVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_geVind(cvta X, cvta Y)
	{
		enforceSize();
		return VU_cmp_geVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_gtVind(cvta X, cvta Y)
	{
		enforceSize();
		return VU_cmp_gtVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_exclrange0Cind(cvta X, cta C)
	{
		enforceSize();
		return VU_cmp_exclrange0Cind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_inclrangeCCind(cvta X, cta CLo, cta CHi)
	{
		enforceSize();
		return VU_cmp_inclrangeCCind(vx_vect,X.vx_vect,ui_size,CLo,CHi);
	}

	inline ui uiVecObj::cmp_exclrangeCCind(cvta X, cta CLo, cta CHi)
	{
		enforceSize();
		return VU_cmp_exclrangeCCind(vx_vect,X.vx_vect,ui_size,CLo,CHi);
	}

#ifdef UBVECOBJ_H
	inline void ubVecObj::UtoUB(const uVecObj& X)
	{
		enforceSize();
		V_UtoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void uVecObj::UBtoU(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoU(vx_vect,X.vx_vect,ui_size);
	}

	inline void uVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VU_accVUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //UBVECOBJ_H

#ifdef USVECOBJ_H
	#if (!defined _WIN64)
		inline void usVecObj::o_UtoUS(const uVecObj& X)
		{
			enforceSize();
			Vo_UtoUS(vx_vect,X.vx_vect,ui_size);
		}
	#endif

	inline void usVecObj::UtoUS(const uVecObj& X)
	{
		enforceSize();
		V_UtoUS(vx_vect,X.vx_vect,ui_size);
	}

	inline void uVecObj::UStoU(const usVecObj& X)
	{
		enforceSize();
		V_UStoU(vx_vect,X.vx_vect,ui_size);
	}

	inline void uVecObj::accVUS(const usVecObj& X)
	{
		enforceSize();
		VU_accVUS(vx_vect,X.vx_vect,ui_size);
	}
#endif //USVECOBJ

#ifdef ULVECOBJ_H
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
#endif //ULVECOBJ_H

#ifdef UQVECOBJ_H
	inline void uqVecObj::UtoUQ(const uVecObj& X)
	{
		enforceSize();
		V_UtoUQ(vx_vect,X.vx_vect,ui_size);
	}

	inline void uVecObj::UQtoU(const uqVecObj& X)
	{
		enforceSize();
		V_UQtoU(vx_vect,X.vx_vect,ui_size);
	}

	inline void uqVecObj::accVU(const uVecObj& X)
	{
		enforceSize();
		VUQ_accVU(vx_vect,X.vx_vect,ui_size);
	}
#endif //UQVECOBJ_H

#ifdef IVECOBJ_H
	#if (!defined _WIN64)
		inline void uVecObj::o_ItoU(const iVecObj& X)
		{
			enforceSize();
			Vo_ItoU(vx_vect,X.vx_vect,ui_size);
		}

		inline void iVecObj::o_UtoI(const uVecObj& X)
		{
			enforceSize();
			Vo_UtoI(vx_vect,X.vx_vect,ui_size);
		}
	#endif

	inline void uVecObj::ItoU(const iVecObj& X)
	{
		enforceSize();
		V_ItoU(vx_vect,X.vx_vect,ui_size);
	}

	inline void iVecObj::UtoI(const uVecObj& X)
	{
		enforceSize();
		V_UtoI(vx_vect,X.vx_vect,ui_size);
	}
#endif //IVECOBJ_H

#ifdef QIVECOBJ_H
	inline void qiVecObj::accVU(const uVecObj& X)
	{
		enforceSize();
		VQI_accVU(vx_vect,X.vx_vect,ui_size);
	}
#endif //QIVECOBJ_H

#ifdef FVECOBJ_H
	inline void fVecObj::accVU(const uVecObj& X)
	{
		enforceSize();
		VF_accVU(vx_vect,X.vx_vect,ui_size);
	}

	inline void fVecObj::UtoF(const uVecObj& X)
	{
		enforceSize();
		V_UtoF(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::roundtoU(const fVecObj& X)
	{
		enforceSize();
		return VF_roundtoU(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::floortoU(const fVecObj& X)
	{
		enforceSize();
		return VF_floortoU(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::ceiltoU(const fVecObj& X)
	{
		enforceSize();
		return VF_ceiltoU(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::choptoU(const fVecObj& X)
	{
		enforceSize();
		return VF_choptoU(vx_vect,X.vx_vect,ui_size);
	}
#endif //FVECOBJ_H

#ifdef DVECOBJ_H
	inline void dVecObj::accVU(const uVecObj& X)
	{
		enforceSize();
		VD_accVU(vx_vect,X.vx_vect,ui_size);
	}

	inline void dVecObj::UtoD(const uVecObj& X)
	{
		enforceSize();
		V_UtoD(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::roundtoU(const dVecObj& X)
	{
		enforceSize();
		return VD_roundtoU(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::floortoU(const dVecObj& X)
	{
		enforceSize();
		return VD_floortoU(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::ceiltoU(const dVecObj& X)
	{
		enforceSize();
		return VD_ceiltoU(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::choptoU(const dVecObj& X)
	{
		enforceSize();
		return VD_choptoU(vx_vect,X.vx_vect,ui_size);
	}
#endif //DVECOBJ_H

#ifdef EVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
	inline void eVecObj::accVU(const uVecObj& X)
	{
		enforceSize();
		VE_accVU(vx_vect,X.vx_vect,ui_size);
	}

	inline void eVecObj::UtoE(const uVecObj& X)
	{
		enforceSize();
		V_UtoE(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::roundtoU(const eVecObj& X)
	{
		enforceSize();
		return VE_roundtoU(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::floortoU(const eVecObj& X)
	{
		enforceSize();
		return VE_floortoU(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::ceiltoU(const eVecObj& X)
	{
		enforceSize();
		return VE_ceiltoU(vx_vect,X.vx_vect,ui_size);
	}

	inline int uVecObj::choptoU(const eVecObj& X)
	{
		enforceSize();
		return VE_choptoU(vx_vect,X.vx_vect,ui_size);
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

#define UVECOBJ_H
#endif //UVECOBJ_H
