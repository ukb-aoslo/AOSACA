/* biVecObj.H

  object-oriented interface for OptiVec vector functions of type "byte"

  This file was written by Brian Dale, Case Western Reserve Univ.

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef BIVECOBJ_H

#include <VecObj.h>
#include <uiVecObj.h>
#include <ubVecObj.h>

#define cvta const vector<char>&
#define cmta const matrix<char>&
#define cuia const ui&
#define cta  const char&

#define vta  vector<char>&
#define uia  ui&
#define ta   char&

#define vt   vector<char>
#define t    char
#define tVector biVector

#define tVecObj biVecObj
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
		{	if(size){	vx_vect= VBI_vector(size);	ui_size= size;}
			else{	vx_vect= 0;	ui_size= 0;}}

		vector(cuia size, cta fill)
		{	if(!size) //size == 0
			{	vx_vect=0;	ui_size=0;}
			else if(!fill) //fill == 0.0
			{	vx_vect= VBI_vector0(size);	ui_size= size;}
			else
			{	vx_vect= VBI_vector(size);	ui_size= size;	VBI_equC(vx_vect,ui_size,fill);}}

		vector(cvta init)
		{	if(init.ui_size)
			{ vx_vect= VBI_vector(init.ui_size);	ui_size= init.ui_size;	VBI_equV(vx_vect, init.vx_vect, ui_size);}
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
				vx_vect= VBI_vector(size);
				ui_size= size;}}

		void setSize(cvta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_size != X.ui_size) //only allocate if different sizes
			{	if(vx_vect) V_free(vx_vect);
				vx_vect= VBI_vector(X.ui_size);
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
			VBI_equV(vx_vect, vect.vx_vect, ui_size);
			return *this;}

		vta operator=(cta scalar)
		{	enforceSize();
			VBI_equC(vx_vect, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		ta operator[](const int& index){return vx_vect[index];}

		vta operator+=(cvta X)
		{	enforceSize();
			VBI_accV(vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator+=(cta scalar)
		{	enforceSize();
			VBI_addC(vx_vect, vx_vect, ui_size, scalar);
			return *this;}

		vta operator*=(cvta X)
		{	enforceSize();
			VBI_mulV(vx_vect, vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator*=(cta scalar)
		{	enforceSize();
			VBI_mulC(vx_vect,vx_vect,ui_size,scalar);
			return *this;}

		vt operator+(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VBI_addV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator+(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VBI_addC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator+(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VBI_addC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator-(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VBI_subV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator-(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VBI_subC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator-(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VBI_subrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator*(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VBI_mulV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator*(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VBI_mulC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator*(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VBI_mulC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator/(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VBI_divV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator/(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VBI_divC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator/(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VBI_divrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
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
			if(size) vx_vect= VBI_vector(size);
			ui_size=size;
		}

		void vector0(ui size)
		{
			dealloc();
			if(size) vx_vect= VBI_vector0(size);
			ui_size=size;
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single vector elements
//
		t* Pelement(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VBI_Pelement(vx_vect,n);
		}

		t element(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VBI_element(vx_vect,n);
		}

		void getElement(t *y, ui n)
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VBI_getElement(y,vx_vect,n);
		}

		void setElement(ui n, cta C)
		{
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			VBI_setElement(vx_vect,n, C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//
		void equ0()
		{
			enforceSize();
			VBI_equ0(vx_vect,ui_size);
		}

		void equC(cta C)
		{
			enforceSize();
			VBI_equC(vx_vect, ui_size, C);
		}

		void equV(cvta X)
		{
			enforceSize();
			VBI_equV(vx_vect, X.vx_vect, ui_size);
		}

		void ramp(cta Start, cta Rise)
		{
			enforceSize();
			VBI_ramp(vx_vect, ui_size, Start, Rise);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VBI_random(vx_vect, ui_size, seed, Min, Max);
		}

		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VBI_randomLC(vx_vect, ui_size, seed, Min, Max, state);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//
		//defined by including ubVecObj.h
		void UBtoBI(const ubVecObj& X);

		//defined by including siVecObj.h
		void SItoBI(const siVecObj& X);

		//defined by including biVecObj.h
		void  ItoBI(const  iVecObj& X);

		//defined by including liVecObj.h
		void LItoBI(const liVecObj& X);

		//defined by including qiVecObj.h
		void QItoBI(const qiVecObj& X);


/////////////////////////////////////////////////////////////////////////////////////////
//Index-oriented manipulations
//
		void reflect()
		{
			enforceSize();
			VBI_reflect(vx_vect, ui_size);
		}

		void rev(cvta X)
		{
			enforceSize();
			VBI_rev(vx_vect, X.vx_vect, ui_size);
		}

		void rotate( cvta X, ssize_t pos )
		{
			enforceSize();
			VBI_rotate(vx_vect, X.vx_vect, ui_size, pos);
		}

		void rotate_buf( cvta X, ssize_t pos, cvta Buf )
		{
			enforceSize();
			VBI_rotate_buf(vx_vect, X.vx_vect, ui_size, pos, Buf.vx_vect);
		}


		void _delete(ui pos)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VBI_delete(vx_vect, ui_size, pos);
		}

		void insert(ui pos, cta C)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VBI_insert(vx_vect, ui_size, pos, C);
		}

		void sort(cvta X, int dir=1)
		{
			enforceSize();
			VBI_sort(vx_vect,X.vx_vect,ui_size,dir);
		}

		//sortind member of uiVecObj

		void subvector(cvta X, ssize_t step, ui start=0)
		{
			enforceSize();
			if(vx_vect==X.vx_vect) throw OptiVec_Err();
			VBI_subvector(vx_vect, ui_size, X.vx_vect+start, step);
		}

		void subvector_equC(const ui& samp, cta C)
		{
			enforceSize();
			VBI_subvector_equC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_equV(const ui& samp, cvta X)
		{
			enforceSize();
			VBI_subvector_equV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void indpick(const uiVecObj& Ind, cvta X)
		{
			enforceSize();
			VBI_indpick(vx_vect, Ind.vx_vect, ui_size, X.vx_vect);
		}

		void indput(cvta X, const uiVecObj& Ind)
		{
			enforceSize();
			X.enforceSize();
			VBI_indput(vx_vect,X.vx_vect,Ind.vx_vect,X.ui_size);
		}

		ui searchC(cta C, int mode=0) const
		{
			enforceSize();
			return VBI_searchC(vx_vect, ui_size, C, mode);
		}

		//searchV member of uiVecObj


/////////////////////////////////////////////////////////////////////////////////////////
//Functions of a sub-set of elements
//


/////////////////////////////////////////////////////////////////////////////////////////
//One-Dimensional Vector Operations
//
		t sum() const
		{
			enforceSize();
			return VBI_sum(vx_vect, ui_size);
		}

		void runsum(cvta X)
		{
			enforceSize();
			VBI_runsum(vx_vect, X.vx_vect, ui_size);
		}

		t _max() const
		{
			enforceSize();
			return VBI_max(vx_vect, ui_size);
		}

		t _min() const
		{
			enforceSize();
			return VBI_min(vx_vect, ui_size);
		}

		t maxind(ui* Ind) const
		{
			enforceSize();
			return VBI_maxind(Ind, vx_vect, ui_size);
		}

		t minind(ui* Ind) const
		{
			enforceSize();
			return VBI_minind(Ind, vx_vect, ui_size);
		}

		void runmax(cvta X)
		{
			enforceSize();
			VBI_runmax(vx_vect, X.vx_vect, ui_size);
		}

		void runmin(cvta X)
		{
			enforceSize();
			VBI_runmin(vx_vect, X.vx_vect, ui_size);
		}

		double fsum() const
		{
			enforceSize();
			return VBI_fsum(vx_vect,ui_size);
		}

		double mean() const
		{
			enforceSize();
			return VBI_mean(vx_vect,ui_size);
		}

		int iselementC(cta C) const
		{
			enforceSize();
			return VBI_iselementC(vx_vect, ui_size, C);
		}

		ui iselementV(cvta X, cvta Tab)
		{
			enforceSize();
			return VBI_iselementV(vx_vect, X.vx_vect,
				ui_size, Tab.vx_vect, Tab.ui_size);
		}

		//distribution member of uiVecObj


/////////////////////////////////////////////////////////////////////////////////////////
//Statistical Functions and Building Blocks
//




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
			VBI_fprint(stream,vx_vect,ui_size,nperline,linewidth);
		}

		void cprint(unsigned nperline) const
		{
			enforceSize();
			VBI_cprint(vx_vect,ui_size,nperline);
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
			VBI_read(vx_vect,ui_size,stream);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			VBI_write(stream,vx_vect,ui_size);
		}

//nread
//nwrite

		void setWriteFormat(char* formatString) const
		{
			VBI_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VBI_setWriteSeparate(sepString);
		}

//setNWriteSeparate

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_size,sizeof(ui),1,stream);
			VBI_store(stream,vx_vect,ui_size);
		}

		void recall(FILE* stream)
		{
			ui sz;
			fread(&sz,sizeof(ui),1,stream);
			setSize(sz);
			VBI_recall(vx_vect,ui_size,stream);
		}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//from VXmath.h
//


/////////////////////////////////////////////////////////////////////////////////////////
//Rounding
//
		//defined by including fVecObj.h
		int roundtoBI(const fVecObj& X);

		//defined by including fVecObj.h
		int floortoBI(const fVecObj& X);

		//defined by including fVecObj.h
		int ceiltoBI(const fVecObj& X);

		//defined by including fVecObj.h
		int choptoBI(const fVecObj& X);

		int trunctoBI(const fVecObj& X)
		{
			return choptoBI(X);
		}

		//defined by including dVecObj.h
		int roundtoBI(const dVecObj& X);

		//defined by including dVecObj.h
		int floortoBI(const dVecObj& X);

		//defined by including dVecObj.h
		int ceiltoBI(const dVecObj& X);

		//defined by including dVecObj.h
		int choptoBI(const dVecObj& X);

		int trunctoBI(const dVecObj& X)
		{
			return choptoBI(X);
		}

#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		int roundtoBI(const eVecObj& X);

		//defined by including eVecObj.h
		int floortoBI(const eVecObj& X);

		//defined by including eVecObj.h
		int ceiltoBI(const eVecObj& X);

		//defined by including eVecObj.h
		int choptoBI(const eVecObj& X);

		int trunctoBI(const eVecObj& X)
		{
			return choptoBI(X);
		}
#endif //__BORLANDC__


/////////////////////////////////////////////////////////////////////////////////////////
//Comparisons
//
		void cmp0(cvta X)
		{
			enforceSize();
			VBI_cmp0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_eq0(cvta X)
		{
			enforceSize();
			return VBI_cmp_eq0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_ne0(cvta X)
		{
			enforceSize();
			return VBI_cmp_ne0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_le0(cvta X)
		{
			enforceSize();
			return VBI_cmp_le0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_lt0(cvta X)
		{
			enforceSize();
			return VBI_cmp_lt0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_ge0(cvta X)
		{
			enforceSize();
			return VBI_cmp_ge0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_gt0(cvta X)
		{
			enforceSize();
			return VBI_cmp_gt0(vx_vect,X.vx_vect,ui_size);
		}

		void cmpC(cvta X, cta C)
		{
			enforceSize();
			VBI_cmpC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_eqC(cvta X, cta C)
		{
			enforceSize();
			return VBI_cmp_eqC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_neC(cvta X, cta C)
		{
			enforceSize();
			return VBI_cmp_neC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_leC(cvta X, cta C)
		{
			enforceSize();
			return VBI_cmp_leC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_ltC(cvta X, cta C)
		{
			enforceSize();
			return VBI_cmp_ltC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_geC(cvta X, cta C)
		{
			enforceSize();
			return VBI_cmp_geC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_gtC(cvta X, cta C)
		{
			enforceSize();
			return VBI_cmp_gtC(vx_vect,X.vx_vect,ui_size,C);
		}

		void cmpV(cvta X, cvta Y)
		{
			enforceSize();
			VBI_cmpV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_eqV(cvta X, cvta Y)
		{
			enforceSize();
			return VBI_cmp_eqV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_neV(cvta X, cvta Y)
		{
			enforceSize();
			return VBI_cmp_neV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_leV(cvta X, cvta Y)
		{
			enforceSize();
			return VBI_cmp_leV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_ltV(cvta X, cvta Y)
		{
			enforceSize();
			return VBI_cmp_ltV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_geV(cvta X, cvta Y)
		{
			enforceSize();
			return VBI_cmp_geV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_gtV(cvta X, cvta Y)
		{
			enforceSize();
			return VBI_cmp_gtV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_inclrange0C(cvta X, cta C)
		{
			enforceSize();
			return VBI_cmp_inclrange0C(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_exclrange0C(cvta X, cta C)
		{
			enforceSize();
			return VBI_cmp_exclrange0C(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_inclrangeCC(cvta X, cta CLo, cta CHi)
		{
			enforceSize();
			return VBI_cmp_inclrangeCC(vx_vect,X.vx_vect,ui_size,CLo,CHi);
		}

		ui cmp_exclrangeCC(cvta X, cta CLo, cta CHi)
		{
			enforceSize();
			return VBI_cmp_exclrangeCC(vx_vect,X.vx_vect,ui_size,CLo,CHi);
		}

		ui cnt_eq0()  const
		{
			enforceSize();
			return VBI_cnt_eq0(vx_vect, ui_size);
		}

		ui cnt_ne0()  const
		{
			enforceSize();
			return VBI_cnt_ne0(vx_vect, ui_size);
		}

		ui cnt_le0()  const
		{
			enforceSize();
			return VBI_cnt_le0(vx_vect, ui_size);
		}

		ui cnt_lt0()  const
		{
			enforceSize();
			return VBI_cnt_lt0(vx_vect, ui_size);
		}

		ui cnt_ge0()  const
		{
			enforceSize();
			return VBI_cnt_ge0(vx_vect, ui_size);
		}

		ui cnt_gt0()  const
		{
			enforceSize();
			return VBI_cnt_gt0(vx_vect, ui_size);
		}

		ui cnt_eqC(cta C) const
		{
			enforceSize();
			return VBI_cnt_eqC(vx_vect,ui_size,C);
		}

		ui cnt_neC(cta C) const
		{
			enforceSize();
			return VBI_cnt_neC(vx_vect,ui_size,C);
		}

		ui cnt_leC(cta C) const
		{
			enforceSize();
			return VBI_cnt_leC(vx_vect,ui_size,C);
		}

		ui cnt_ltC(cta C) const
		{
			enforceSize();
			return VBI_cnt_ltC(vx_vect,ui_size,C);
		}

		ui cnt_geC(cta C) const
		{
			enforceSize();
			return VBI_cnt_geC(vx_vect,ui_size,C);
		}

		ui cnt_gtC(cta C) const
		{
			enforceSize();
			return VBI_cnt_gtC(vx_vect,ui_size,C);
		}

		ui cnt_inclrange0C(cta C) const
		{
			enforceSize();
			return VBI_cnt_inclrange0C(vx_vect,ui_size,C);
		}

		ui cnt_exclrange0C(cta C) const
		{
			enforceSize();
			return VBI_cnt_exclrange0C(vx_vect,ui_size,C);
		}

		ui cnt_inclrangeCC(cta CLo, cta CHi) const
		{
			enforceSize();
			return VBI_cnt_inclrangeCC(vx_vect,ui_size,CLo, CHi);
		}

		ui cnt_exclrangeCC(cta CLo, cta CHi) const
		{
			enforceSize();
			return VBI_cnt_exclrangeCC(vx_vect,ui_size,CLo, CHi);
		}

		ui cnt_eqV(cvta Y) const
		{
			enforceSize();
			return VBI_cnt_eqV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_neV(cvta Y) const
		{
			enforceSize();
			return VBI_cnt_neV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_leV(cvta Y) const
		{
			enforceSize();
			return VBI_cnt_leV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_ltV(cvta Y) const
		{
			enforceSize();
			return VBI_cnt_ltV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_geV(cvta Y) const
		{
			enforceSize();
			return VBI_cnt_geV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_gtV(cvta Y) const
		{
			enforceSize();
			return VBI_cnt_gtV(vx_vect,Y.vx_vect,ui_size);
		}

		// signum function of unsigned input vectors: output is signed
		void cmpC(const ubVecObj& X, unsigned char C)
		{
			enforceSize();
			VUB_cmpC(vx_vect,X.vx_vect,ui_size,C);
		}

		void cmpV(const ubVecObj& X, const ubVecObj& Y)
		{
			enforceSize();
			VUB_cmpV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		//indexed comparisons are members of uiVecObj


/////////////////////////////////////////////////////////////////////////////////////////
//Standard Arithmetics or Basic Arithmetics
//
		void neg(cvta X)
		{
			enforceSize();
			VBI_neg(vx_vect, X.vx_vect, ui_size);
		}

		void abs(cvta X)
		{
			enforceSize();
			VBI_abs(vx_vect, X.vx_vect, ui_size);
		}

		void addC(cvta X, cta C)
		{
			enforceSize();
			VBI_addC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subC(cvta X, cta C)
		{
			enforceSize();
			VBI_subC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subrC(cvta X, cta C)
		{
			enforceSize();
			VBI_subrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void mulC(cvta X, cta C)
		{
			enforceSize();
			VBI_mulC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divC(cvta X, cta C)
		{
			enforceSize();
			VBI_divC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divrC(cvta X, cta C)
		{
			enforceSize();
			VBI_divrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void modC(cvta X, cta C)
		{
			enforceSize();
			VBI_modC(vx_vect, X.vx_vect, ui_size, C);
		}

		void maxC(cvta X, cta C)
		{
			enforceSize();
			VBI_maxC( vx_vect, X.vx_vect, ui_size, C);
		}

		void minC(cvta X, cta C)
		{
			enforceSize();
			VBI_minC( vx_vect, X.vx_vect, ui_size, C);
		}

		void addV(cvta X, cvta Y)
		{
			enforceSize();
			VBI_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subV(cvta X, cvta Y)
		{
			enforceSize();
			VBI_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subrV(cvta X, cvta Y)
		{
			enforceSize();
			VBI_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void mulV(cvta X, cvta Y)
		{
			enforceSize();
			VBI_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divV(cvta X, cvta Y)
		{
			enforceSize();
			VBI_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divrV(cvta X, cvta Y)
		{
			enforceSize();
			VBI_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void modV(cvta X, cvta Y)
		{
			enforceSize();
			VBI_modV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void maxV(cvta X, cvta Y)
		{
			enforceSize();
			VBI_maxV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void minV(cvta X, cvta Y)
		{
			enforceSize();
			VBI_minV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Accumulation
//
		void accV(cvta X)
		{
			enforceSize();
			VBI_accV(vx_vect,X.vx_vect,ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Bit-wise operations
//
		void shl(cvta X, unsigned C)
		{
			enforceSize();
			VBI_shl(vx_vect,X.vx_vect,ui_size,C);
		}

		void shr(cvta X, unsigned C)
		{
			enforceSize();
			VBI_shr(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "and"
			void _and(cvta X, cta C)
		#else
			void and(cvta X, cta C)
		#endif
		{
			enforceSize();
			VBI_and(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "or"
			void _or(cvta X, cta C)
		#else
			void or(cvta X, cta C)
		#endif
		{
			enforceSize();
			VBI_or(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "xor"
			void _xor(cvta X, cta C)
		#else
			void xor(cvta X, cta C)
		#endif
		{
			enforceSize();
			VBI_xor(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "not"
			void _not(cvta X)
		#else
			void not(cvta X)
		#endif
		{
			enforceSize();
			VBI_not(vx_vect,X.vx_vect,ui_size);
		}

/////////////////////////////////////////////////////////////////////////////////////////
// Graphics
//

            #ifdef __VGRAPH_H
                void xyAutoPlot( cvta X, unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    enforceSize(X.ui_size);
                    VBI_xyAutoPlot( X.vx_vect, vx_vect, ui_size, form, color );
                }

                void xy2AutoPlot( cvta X1, unsigned form1, COLORREF color1,
                         cvta X2, cvta Y2, unsigned form2, COLORREF color2 ) const
                {
                    enforceSize();
                    enforceSize(X1.ui_size);
                    Y2.enforceSize(X2.ui_size);
                    VBI_xy2AutoPlot( X1.vx_vect, vx_vect, ui_size, form1, color1,
                              X2.vx_vect, Y2.vx_vect, X2.ui_size, form2, color2 );
                }

                void yAutoPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VBI_yAutoPlot( vx_vect, ui_size, form, color );
                }

                void y2AutoPlot( unsigned form1, COLORREF color1,
                        cvta Y2, unsigned form2, COLORREF color2 ) const
                {
                    enforceSize();
                    Y2.enforceSize();
                    VBI_y2AutoPlot( vx_vect, ui_size, form1, color1,
                             Y2.vx_vect, Y2.ui_size, form2, color2 );
                }

                void xyDataPlot( cvta X, unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    enforceSize(X.ui_size);
                    VBI_xyDataPlot( X.vx_vect, vx_vect, ui_size, form, color );
                }

                void yDataPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VBI_yDataPlot( vx_vect, ui_size, form, color );
                }
            #endif   // __VGRAPH_H

/////////////////////////////////////////////////////////////////////////////////////////
// Matrix operations whose result is a vector
//

              //defined by including biMatObj.h
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
		VBI_sortind(vx_vect,X.vx_vect,ui_size,dir);
	}

	inline void uiVecObj::searchV(cvta X, cvta Tab, int mode=0)
	{
		enforceSize();
		Tab.enforceSize();
		VBI_searchV(vx_vect,X.vx_vect,ui_size,Tab.vx_vect,Tab.ui_size,mode);
	}

	inline ui uiVecObj::distribution(cvta Limits, cvta X, int mode=0)
	{
		enforceSize();
		X.enforceSize();
		return VBI_distribution(vx_vect,Limits.vx_vect,ui_size,X.vx_vect,X.ui_size,mode);
	}

	inline ui uiVecObj::cmp_eq0ind(cvta X)
	{
		enforceSize();
		return VBI_cmp_eq0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ne0ind(cvta X)
	{
		enforceSize();
		return VBI_cmp_ne0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_le0ind(cvta X)
	{
		enforceSize();
		return VBI_cmp_le0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_lt0ind(cvta X)
	{
		enforceSize();
		return VBI_cmp_lt0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ge0ind(cvta X)
	{
		enforceSize();
		return VBI_cmp_ge0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_gt0ind(cvta X)
	{
		enforceSize();
		return VBI_cmp_gt0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_eqCind(cvta X, cta C)
	{
		enforceSize();
		return VBI_cmp_eqCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_neCind(cvta X, cta C)
	{
		enforceSize();
		return VBI_cmp_neCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_leCind(cvta X, cta C)
	{
		enforceSize();
		return VBI_cmp_leCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_ltCind(cvta X, cta C)
	{
		enforceSize();
		return VBI_cmp_ltCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_geCind(cvta X, cta C)
	{
		enforceSize();
		return VBI_cmp_geCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_gtCind(cvta X, cta C)
	{
		enforceSize();
		return VBI_cmp_gtCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_eqVind(cvta X, cvta Y)
	{
		enforceSize();
		return VBI_cmp_eqVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_neVind(cvta X, cvta Y)
	{
		enforceSize();
		return VBI_cmp_neVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_leVind(cvta X, cvta Y)
	{
		enforceSize();
		return VBI_cmp_leVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ltVind(cvta X, cvta Y)
	{
		enforceSize();
		return VBI_cmp_ltVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_geVind(cvta X, cvta Y)
	{
		enforceSize();
		return VBI_cmp_geVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_gtVind(cvta X, cvta Y)
	{
		enforceSize();
		return VBI_cmp_gtVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_inclrange0Cind(cvta X, cta C)
	{
		enforceSize();
		return VBI_cmp_inclrange0Cind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_exclrange0Cind(cvta X, cta C)
	{
		enforceSize();
		return VBI_cmp_exclrange0Cind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_inclrangeCCind(cvta X, cta CLo, cta CHi)
	{
		enforceSize();
		return VBI_cmp_inclrangeCCind(vx_vect,X.vx_vect,ui_size,CLo,CHi);
	}

	inline ui uiVecObj::cmp_exclrangeCCind(cvta X, cta CLo, cta CHi)
	{
		enforceSize();
		return VBI_cmp_exclrangeCCind(vx_vect,X.vx_vect,ui_size,CLo,CHi);
	}

#ifdef UBVECOBJ_H
	inline void ubVecObj::BItoUB(const biVecObj& X)
	{
		enforceSize();
		V_BItoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void biVecObj::UBtoBI(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoBI(vx_vect,X.vx_vect,ui_size);
	}
#endif //UBVECOBJ_H

#ifdef SIVECOBJ_H
	inline void siVecObj::BItoSI(const biVecObj& X)
	{
		enforceSize();
		V_BItoSI(vx_vect,X.vx_vect,ui_size);
	}

	inline void biVecObj::SItoBI(const siVecObj& X)
	{
		enforceSize();
		V_SItoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline void siVecObj::accVBI(const biVecObj& X)
	{
		enforceSize();
		VSI_accVBI(vx_vect,X.vx_vect,ui_size);
	}
#endif //SIVECOBJ_H

#ifdef IVECOBJ_H
	inline void biVecObj::ItoBI(const iVecObj& X)
	{
		enforceSize();
		V_ItoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline void iVecObj::BItoI(const biVecObj& X)
	{
		enforceSize();
		V_BItoI(vx_vect,X.vx_vect,ui_size);
	}

	inline void iVecObj::accVBI(const biVecObj& X)
	{
		enforceSize();
		VI_accVBI(vx_vect,X.vx_vect,ui_size);
	}
#endif //IVECOBJ_H

#ifdef LIVECOBJ_H
	inline void biVecObj::LItoBI(const liVecObj& X)
	{
		enforceSize();
		V_LItoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline void liVecObj::BItoLI(const biVecObj& X)
	{
		enforceSize();
		V_BItoLI(vx_vect,X.vx_vect,ui_size);
	}

	inline void liVecObj::accVBI(const biVecObj& X)
	{
		enforceSize();
		VLI_accVBI(vx_vect,X.vx_vect,ui_size);
	}
#endif //LIVECOBJ_H

#ifdef QIVECOBJ_H
	inline void biVecObj::QItoBI(const qiVecObj& X)
	{
		enforceSize();
		V_QItoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline void qiVecObj::BItoQI(const biVecObj& X)
	{
		enforceSize();
		V_BItoQI(vx_vect,X.vx_vect,ui_size);
	}

	inline void qiVecObj::accVBI(const biVecObj& X)
	{
		enforceSize();
		VQI_accVBI(vx_vect,X.vx_vect,ui_size);
	}
#endif //QIVECOBJ_H

#ifdef FVECOBJ_H
	inline void fVecObj::accVBI(const biVecObj& X)
	{
		enforceSize();
		VF_accVBI(vx_vect,X.vx_vect,ui_size);
	}

	inline void fVecObj::BItoF(const biVecObj& X)
	{
		enforceSize();
		V_BItoF(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::roundtoBI(const fVecObj& X)
	{
		enforceSize();
		return VF_roundtoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::floortoBI(const fVecObj& X)
	{
		enforceSize();
		return VF_floortoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::ceiltoBI(const fVecObj& X)
	{
		enforceSize();
		return VF_ceiltoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::choptoBI(const fVecObj& X)
	{
		enforceSize();
		return VF_choptoBI(vx_vect,X.vx_vect,ui_size);
	}
#endif //FVECOBJ_H

#ifdef DVECOBJ_H
	inline void dVecObj::accVBI(const biVecObj& X)
	{
		enforceSize();
		VD_accVBI(vx_vect,X.vx_vect,ui_size);
	}

	inline void dVecObj::BItoD(const biVecObj& X)
	{
		enforceSize();
		V_BItoD(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::roundtoBI(const dVecObj& X)
	{
		enforceSize();
		return VD_roundtoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::floortoBI(const dVecObj& X)
	{
		enforceSize();
		return VD_floortoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::ceiltoBI(const dVecObj& X)
	{
		enforceSize();
		return VD_ceiltoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::choptoBI(const dVecObj& X)
	{
		enforceSize();
		return VD_choptoBI(vx_vect,X.vx_vect,ui_size);
	}
#endif //DVECOBJ_H

#ifdef EVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
	inline void eVecObj::accVBI(const biVecObj& X)
	{
		enforceSize();
		VE_accVBI(vx_vect,X.vx_vect,ui_size);
	}

	inline void eVecObj::BItoE(const biVecObj& X)
	{
		enforceSize();
		V_BItoE(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::roundtoBI(const eVecObj& X)
	{
		enforceSize();
		return VE_roundtoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::floortoBI(const eVecObj& X)
	{
		enforceSize();
		return VE_floortoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::ceiltoBI(const eVecObj& X)
	{
		enforceSize();
		return VE_ceiltoBI(vx_vect,X.vx_vect,ui_size);
	}

	inline int biVecObj::choptoBI(const eVecObj& X)
	{
		enforceSize();
		return VE_choptoBI(vx_vect,X.vx_vect,ui_size);
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

#define BIVECOBJ_H
#endif //BIVECOBJ_H
