/* fVecObj.H

  object-oriented interface for OptiVec vector functions of type "float"

  This file was written by Brian Dale, Case Western Reserve Univ.

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef FVECOBJ_H

#include <VecObj.h>
#include <uiVecObj.h>
#include <iVecObj.h>
#ifndef __VFSTD_H
	#include <VFstd.h>
#endif
#ifndef __VFMATH_H
	#include <VFmath.h>
#endif
#ifndef __MFSTD_H
	#include <MFstd.h>
#endif

#define cvta const vector<float>&
#define cmta const matrix<float>&
#define cuia const ui&
#define cta  const float&

#define vta  vector<float>&
#define uia  ui&
#define ta   float&

#define vt   vector<float>
#define t    float
#define tVector fVector
#define tMatrix fMatrix

#define vtcplx vector<fComplex>
#define tcplx  fComplex

#define tVecObj fVecObj
#define tMatObj fMatObj
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
		{	if(size){	vx_vect= VF_vector(size);	ui_size= size;}
			else{	vx_vect= 0;	ui_size= 0;}}

		vector(cuia size, cta fill)
		{	if(!size) //size == 0
			{	vx_vect=0;	ui_size=0;}
			else if(!fill) //fill == 0.0
			{	vx_vect= VF_vector0(size);	ui_size= size;}
			else
			{	vx_vect= VF_vector(size);	ui_size= size;	VF_equC(vx_vect,ui_size,fill);}}

		vector(cvta init)
		{	if(init.ui_size)
			{ vx_vect= VF_vector(init.ui_size);	ui_size= init.ui_size;	VF_equV(vx_vect, init.vx_vect, ui_size);}
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
				vx_vect= VF_vector(size);
				ui_size= size;}}

		void setSize(cvta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_size != X.ui_size) //only allocate if different sizes
			{	if(vx_vect) V_free(vx_vect);
				vx_vect= VF_vector(X.ui_size);
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
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return vx_vect[n];
		}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Overloaded operators
//
		vta operator=(cvta vect)
		{	setSize(vect.ui_size);
			enforceSize();
			VF_equV(vx_vect, vect.vx_vect, ui_size);
			return *this;}

		vta operator=(cta scalar)
		{	enforceSize();
			VF_equC(vx_vect, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		ta operator[](const int& index){return vx_vect[index];}

		vta operator+=(cvta X)
		{	enforceSize();
			VF_accV(vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator+=(cta scalar)
		{	enforceSize();
			VF_addC(vx_vect, vx_vect, ui_size, scalar);
			return *this;}

		vta operator*=(cvta X)
		{	enforceSize();
			VF_mulV(vx_vect, vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator*=(cta scalar)
		{	enforceSize();
			VF_mulC(vx_vect,vx_vect,ui_size,scalar);
			return *this;}

		vt operator+(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VF_addV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator+(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VF_addC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator-(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VF_subV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator-(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VF_subC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator*(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VF_mulV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator*(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VF_mulC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator/(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VF_divV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator/(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VF_divC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator+(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VF_addC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator-(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VF_subrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator*(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VF_mulC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator/(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VF_divrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
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
			if(size) vx_vect= VF_vector(size);
			ui_size=size;
		}

		void vector0(ui size)
		{
			dealloc();
			if(size) vx_vect= VF_vector0(size);
			ui_size=size;
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single vector elements
//
		t* Pelement(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VF_Pelement(vx_vect,n);
		}

		t element(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VF_element(vx_vect,n);
		}

		void getElement(t *y, ui n)
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VF_getElement(y,vx_vect,n);
		}

		void setElement(ui n, cta C)
		{
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			VF_setElement(vx_vect,n, C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//

		void equ0()
		{
			enforceSize();
			VF_equ0(vx_vect,ui_size);
		}

		void equ1()
		{
			enforceSize();
			VF_equ1(vx_vect,ui_size);
		}

		void equm1()
		{
			enforceSize();
			VF_equm1(vx_vect, ui_size);
		}

		void equC(cta C)
		{
			enforceSize();
			VF_equC(vx_vect, ui_size, C);
		}

		void equV(cvta X)
		{
			enforceSize();
			VF_equV(vx_vect, X.vx_vect, ui_size);
		}

		void x_equV(cvta X, cta A, cta B)
		{
			enforceSize();
			VFx_equV(vx_vect, X.vx_vect, ui_size, A, B);
		}

		void ramp(cta Start, cta Rise)
		{
			enforceSize();
			VF_ramp(vx_vect, ui_size, Start, Rise);
		}

		void Parzen()
		{
			enforceSize();
			VF_Parzen(vx_vect, ui_size);
		}

		void Welch()
		{
			enforceSize();
			VF_Welch(vx_vect, ui_size);
		}

		void Hann()
		{
			enforceSize();
			VF_Hann(vx_vect, ui_size);
		}

		void Hanning()  // erroneous name for Hann
		{
			enforceSize();
			VF_Hann(vx_vect, ui_size);
		}

		void comb(const unsigned& spac, cta C)
		{
			enforceSize();
			if(spac>ui_size) throw OptiVec_SmallSizeErr();
			VF_comb(vx_vect, ui_size, spac, C);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VF_random(vx_vect, ui_size, seed, Min, Max);
		}

		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VF_randomLC(vx_vect, ui_size, seed, Min, Max, state);
		}

		long noise(const long& seed, cta Amp)
		{
			enforceSize();
			return VF_noise(vx_vect, ui_size, seed, Amp);
		}

		void noiseLC(const long& seed, cta Amp, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VF_noiseLC(vx_vect, ui_size, seed, Amp, state);
		}

		//defined by including cfVecObj.h
		void CtoReIm(vt* Im, const vtcplx& X);
		void CtoReIm(vt  Im, const vtcplx& X);

		//defined by including cfVecObj.h
		void CtoRe(const vtcplx& cplx);

		//defined by including cfVecObj.h
		void CtoIm(const vtcplx& cplx);

		//defined by including cfVecObj.h
		void CtoPolar(vt* Arg, const vtcplx& X);
		void CtoPolar(vt  Arg, const vtcplx& X);

		//defined by including cfVecObj.h
		void CtoNorm(const vtcplx& cplx);

		//defined by including cfVecObj.h
		void CtoAbs(const vtcplx& cplx);

		//defined by including cfVecObj.h
		void CtoArg(const vtcplx& cplx);

		//defined by including cfVecObj.h
		int abs(const vtcplx& cplx);

		void real(const vtcplx& cplx){	CtoRe(cplx);}

		void imag(const vtcplx& cplx){	CtoIm(cplx);}

		void arg(const vtcplx& cplx){	CtoArg(cplx);}

		void norm(const vtcplx& cplx){	CtoNorm(cplx);}

		//defined by including pfVecObj.h
		void PtoMagArg(vt* Arg, const pfVecObj& X);
		void PtoMagArg(vt  Arg, const pfVecObj& X);

		//defined by including pfVecObj.h
		void PtoMag(const pfVecObj& X);

		//defined by including pfVecObj.h
		void PtoArg(const pfVecObj& X);

		//defined by including pfVecObj.h
		void PtoNorm(const pfVecObj& X);

		//defined by including pfVecObj.h
		void PtoReIm(vt* Im, const pfVecObj& X);
		void PtoReIm(vt  Im, const pfVecObj& X);

		//defined by including pfVecObj.h
		void PtoRe(const pfVecObj& X);

		//defined by including pfVecObj.h
		void PtoIm(const pfVecObj& X);

		//defined by including pfVecObj.h
		int abs(const pfVecObj& X);

		void real(const pfVecObj& cplx){ PtoRe(cplx);}

		void imag(const pfVecObj& cplx){ PtoIm(cplx);}

		void arg(const pfVecObj& cplx){ PtoArg(cplx);}

		void norm(const pfVecObj& cplx){ PtoNorm(cplx);}



/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//
		//defined by including biVecObj.h
		void BItoF(const biVecObj& X);

		//defined by including siVecObj.h
		void SItoF(const siVecObj& X);

		//defined by including iVecObj.h
		void ItoF(const iVecObj& X);

		//defined by including liVecObj.h
		void LItoF(const liVecObj& X);

		//defined by including qiVecObj.h
		void QItoF(const qiVecObj& X);


		//defined by including ubVecObj.h
		void UBtoF(const ubVecObj& X);

		//defined by including usVecObj.h
		void UStoF(const usVecObj& X);

		//defined by including uVecObj.h
		void UtoF(const uVecObj& X);

		//defined by including ulVecObj.h
		void ULtoF(const ulVecObj& X);

		//defined by including dVecObj.h
		void DtoF(const dVecObj& X);

		//defined by including eVecObj.h
		void EtoF(const eVecObj& X);


/////////////////////////////////////////////////////////////////////////////////////////
//Index-oriented manipulations
//
		void reflect()
		{
			enforceSize();
			VF_reflect(vx_vect, ui_size);
		}

		void rev(cvta X)
		{
			enforceSize();
			VF_rev(vx_vect, X.vx_vect, ui_size);
		}

#ifdef V_HUGE
		void rotate( cvta X, long pos )
#else
		void rotate( cvta X, ssize_t pos )
#endif
		{
			enforceSize();
			VF_rotate(vx_vect, X.vx_vect, ui_size, pos);
		}

#ifdef V_HUGE
		void rotate_buf( cvta X, long pos, cvta Buf )
#else
		void rotate_buf( cvta X, ssize_t pos, cvta Buf )
#endif
		{
			enforceSize();
			VF_rotate_buf(vx_vect, X.vx_vect, ui_size, pos, Buf.vx_vect);
		}


		void _delete(ui pos)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VF_delete(vx_vect, ui_size, pos);
		}

		void insert(ui pos, cta C)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VF_insert(vx_vect, ui_size, pos, C);
		}

		void sort(cvta X, int dir=1)
		{
			enforceSize();
			VF_sort(vx_vect,X.vx_vect,ui_size,dir);
		}

		//sortind member of uiVecObj

		void subvector(cvta X, ssize_t step, ui start=0)
		{
			enforceSize();
			if(vx_vect==X.vx_vect) throw OptiVec_Err();
			VF_subvector(vx_vect, ui_size, X.vx_vect+start, step);
		}

		void indpick(const uiVecObj& Ind, cvta X)
		{
			enforceSize();
			VF_indpick(vx_vect, Ind.vx_vect, ui_size, X.vx_vect);
		}

		void indput(cvta X, const uiVecObj& Ind)
		{
			enforceSize();
			X.enforceSize();
			VF_indput(vx_vect,X.vx_vect,Ind.vx_vect,X.ui_size);
		}

		ui searchC(cta C, int mode=0) const
		{
			enforceSize();
			return VF_searchC(vx_vect, ui_size, C, mode);
		}

		//searchV member of uiVecObj

		void polyinterpol(cvta X, cvta Xtab, cvta Ytab, unsigned deg)
		{
			if(!ui_size || Ytab.ui_size!=Xtab.ui_size) throw OptiVec_SizeErr();
			if(deg>10) throw OptiVec_Err();
			if(Xtab.ui_size<deg) throw OptiVec_SmallSizeErr();
			VF_polyinterpol(vx_vect,X.vx_vect,ui_size,
				Xtab.vx_vect,Ytab.vx_vect,Xtab.ui_size,deg);
		}

		void ratinterpol(cvta X, cvta Xtab, cvta Ytab, unsigned deg)
		{
			if(!ui_size || Ytab.ui_size!=Xtab.ui_size) throw OptiVec_SizeErr();
			if((deg>20)||(deg<3)) throw OptiVec_Err();
			if(Xtab.ui_size<deg) throw OptiVec_SmallSizeErr();
			VF_ratinterpol(vx_vect,X.vx_vect,ui_size,
				Xtab.vx_vect,Ytab.vx_vect,Xtab.ui_size,deg);
		}

		void natCubSplineInterpol(cvta X, cvta Xtab, cvta Ytab)
		{
			if(!ui_size || Ytab.ui_size!=Xtab.ui_size) throw OptiVec_SizeErr();
			if(Xtab.ui_size<3) throw OptiVec_SmallSizeErr();
			VF_natCubSplineInterpol(vx_vect,X.vx_vect,ui_size,
				Xtab.vx_vect,Ytab.vx_vect,Xtab.ui_size);
		}

		void splinederiv2(cvta Xtab, cvta Ytab, int specify, cta Yp0, cta Ypn)
		{
			if(ui_size!=Xtab.ui_size || Ytab.ui_size!=Xtab.ui_size) throw OptiVec_SizeErr();
			if(ui_size<3) throw OptiVec_SmallSizeErr();
			VF_splinederiv2(vx_vect,Xtab.vx_vect,Ytab.vx_vect,Xtab.ui_size,
				specify,Yp0,Ypn);
		}

		void splineinterpol(cvta X, cvta Xtab, cvta Ytab, cvta Y2tab)
		{
			if(!ui_size || Ytab.ui_size!=Xtab.ui_size) throw OptiVec_SizeErr();
			if(Xtab.ui_size<3) throw OptiVec_SmallSizeErr();
			VF_splineinterpol(vx_vect,X.vx_vect,ui_size,
				Xtab.vx_vect,Ytab.vx_vect,Y2tab.vx_vect,Xtab.ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Functions of a sub-set of elements
//
		//subvector_equC defined below
		//subvector_equV defined below


/////////////////////////////////////////////////////////////////////////////////////////
//One-Dimensional Vector Operations
//
		t _max() const
		{
			enforceSize();
			return VF_max(vx_vect, ui_size);
		}

		t _min() const
		{
			enforceSize();
			return VF_min(vx_vect, ui_size);
		}


		t absmax() const
		{
			enforceSize();
			return VF_absmax(vx_vect, ui_size);
		}

		t absmin() const
		{
			enforceSize();
			return VF_absmin(vx_vect, ui_size);
		}

		int maxexp() const
		{
			enforceSize();
			return VF_maxexp(vx_vect, ui_size);
		}

		int minexp() const
		{
			enforceSize();
			return VF_minexp(vx_vect, ui_size);
		}

		t maxind(ui* Ind) const
		{
			enforceSize();
			return VF_maxind(Ind, vx_vect, ui_size);
		}

		t minind(ui* Ind) const
		{
			enforceSize();
			return VF_minind(Ind, vx_vect, ui_size);
		}

		t absmaxind(ui* Ind) const
		{
			enforceSize();
			return VF_absmaxind(Ind, vx_vect, ui_size);
		}

		t absminind(ui* Ind) const
		{
			enforceSize();
			return VF_absminind(Ind, vx_vect, ui_size);
		}

		//localmaxima member of uiVecObj
		//localminima member of uiVecObj

		void runmax(cvta X)
		{
			enforceSize();
			VF_runmax(vx_vect, X.vx_vect, ui_size);
		}

		void runmin(cvta X)
		{
			enforceSize();
			VF_runmin(vx_vect, X.vx_vect, ui_size);
		}

		t sum() const
		{
			enforceSize();
			return VF_sum(vx_vect, ui_size);
		}

		t prod() const
		{
			enforceSize();
			return VF_prod(vx_vect, ui_size);
		}

		void runsum(cvta X)
		{
			enforceSize();
			VF_runsum(vx_vect, X.vx_vect, ui_size);
		}

		void runprod(cvta X)
		{
			enforceSize();
			VF_runprod(vx_vect, X.vx_vect, ui_size);
		}

		int iselementC(cta C) const
		{
			enforceSize();
			return VF_iselementC(vx_vect, ui_size, C);
		}

		ui iselementV(cvta X, cvta Tab)
		{
			enforceSize();
			return VF_iselementV(vx_vect, X.vx_vect,
				ui_size, Tab.vx_vect, Tab.ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Statistical Functions and Building Blocks
//
		t mean() const
		{
			enforceSize();
			return VF_mean(vx_vect,ui_size);
		}

		t meanwW(cvta Wt) const
		{
			enforceSize();
			return VF_meanwW(vx_vect, Wt.vx_vect, ui_size);
		}

		t sumabs() const
		{
			enforceSize();
			return VF_sumabs(vx_vect,ui_size);
		}

		t meanabs() const
		{
			enforceSize();
			return VF_meanabs(vx_vect,ui_size);
		}

		t selected_mean(ui* nsel, cta Xmin, cta Xmax) const
		{
			enforceSize();
			return VF_selected_mean(nsel,vx_vect,ui_size,Xmin,Xmax);
		}

		t median() const
		{
			enforceSize();
			return VF_median(vx_vect,ui_size);
		}

		t sumdevC(cta C) const
		{
			enforceSize();
			return VF_sumdevC(vx_vect,ui_size,C);
		}

		t sumdevV(cvta Y) const
		{
			enforceSize();
			return VF_sumdevV(vx_vect,Y.vx_vect,ui_size);
		}

		t avdevC(cta C) const
		{
			enforceSize();
			return VF_avdevC(vx_vect,ui_size,C);
		}

		t avdevV(cvta Y) const
		{
			enforceSize();
			return VF_avdevV(vx_vect,Y.vx_vect,ui_size);
		}

		t ssq() const
		{
			enforceSize();
			return VF_ssq(vx_vect,ui_size);
		}

		t rms() const
		{
			enforceSize();
			return VF_rms(vx_vect,ui_size);
		}

		t ssqdevC(cta C) const
		{
			enforceSize();
			return VF_ssqdevC(vx_vect,ui_size,C);
		}

		t ssqdevV(cvta Y) const
		{
			enforceSize();
			return VF_ssqdevV(vx_vect,Y.vx_vect,ui_size);
		}

		t meanvar(t* Var) const
		{
			enforceSize();
			return VF_meanvar(Var,vx_vect,ui_size);
		}

		t meanvarwW(t* Var, cvta Wt) const
		{
			enforceSize();
			return VF_meanvarwW(Var,vx_vect,Wt.vx_vect,ui_size);
		}

		void min_max_mean_stddev( cvta X )
		{
			X.enforceSize();
			if(ui_size<4) throw OptiVec_SmallSizeErr();
			VF_min_max_mean_stddev(vx_vect, X.vx_vect, X.ui_size);
		}

		t varianceC(cta C) const
		{
			enforceSize();
			return VF_varianceC(vx_vect,ui_size,C);
		}

		t varianceV(cvta Y) const
		{
			enforceSize();
			return VF_varianceV(vx_vect,Y.vx_vect,ui_size);
		}

		t varianceCwW(cvta Wt,cta C) const
		{
			enforceSize();
			return VF_varianceCwW(vx_vect,Wt.vx_vect,ui_size,C);
		}

		t varianceVwW(cvta Y, cvta Wt) const
		{
			enforceSize();
			return VF_varianceVwW(vx_vect,Y.vx_vect,Wt.vx_vect,ui_size);
		}

		t chi2(cvta Y, cvta InvVar) const
		{
			enforceSize();
			return VF_chi2(vx_vect,Y.vx_vect,InvVar.vx_vect,ui_size);
		}

		t chiabs(cvta Y, cvta Wt) const
		{
			enforceSize();
			return VF_chiabs(vx_vect,Y.vx_vect,Wt.vx_vect,ui_size);
		}

		t corrcoeff(cvta Y, cta Xmean, cta Ymean) const
		{
			enforceSize();
			return VF_corrcoeff(vx_vect,Y.vx_vect,ui_size,Xmean,Ymean);
		}

		//overloaded for convenience
		t corrcoeff(cvta Y) const
		{
			enforceSize();
			return VF_corrcoeff(vx_vect,Y.vx_vect,ui_size,mean(),Y.mean());
		}

		//distribution member of uiVecObj

		void linregress(cvta X, cvta Y)
		{
			X.enforceSize();
			if(ui_size<5) throw OptiVec_SmallSizeErr();
			VF_linregress(vx_vect,X.vx_vect,Y.vx_vect,X.ui_size);
		}

		void linregresswW(cvta X, cvta Y, cvta InvVar)
		{
			X.enforceSize();
			if(ui_size<5) throw OptiVec_SmallSizeErr();
			VF_linregresswW(vx_vect,X.vx_vect,Y.vx_vect,
				InvVar.vx_vect,X.ui_size);
		}

		t centerOfGravityInd() const
		{
			enforceSize();
			return VF_centerOfGravityInd(vx_vect,ui_size);
		}

		t centerOfGravityV(cvta X) const
		{
			enforceSize();
			return VF_centerOfGravityV(X.vx_vect,vx_vect,ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Fourier Transforms, Convolutions, Filtering
//

		tcplx getRspEdit() const
		{
			return VF_getRspEdit();
		}

		void setRspEdit(const tcplx& trunc) const
		{
			VF_setRspEdit(trunc);
		}

		void p_FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VFp_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		void b_FFT(cvta X, int dir, vta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			VFb_FFT(vx_vect,X.vx_vect,ui_size,dir,Buf.vx_vect);
		}

		//p_FFTtoC, b_FFTtoC members of cfVecObj

		void p_filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VFp_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}

		void p_autocorr(cvta X)
		{
			enforcePow2();
			VFp_autocorr(vx_vect, X.vx_vect, ui_size);
		}

		void p_xcorr(cvta X, cvta Y)
		{
			enforcePow2();
			VFp_xcorr(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		t p_spectrum(cvta X, cvta Win)
		{
			enforcePow2();
			if(2*ui_size > X.ui_size) throw OptiVec_BigSizeErr();
			if(2*ui_size != Win.ui_size) throw OptiVec_SizeErr();
			return VFp_spectrum(vx_vect, ui_size,
				X.vx_vect, X.ui_size, Win.vx_vect);
		}

		void p_convolve(tVecObj* Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt->ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt->vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFp_convolve(vx_vect, Flt->vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void p_convolve(tVecObj Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt.ui_size)||(ui_size!=X.ui_size)||
				 (ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt.vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFp_convolve(vx_vect, Flt.vx_vect, X.vx_vect,	Rsp.vx_vect, ui_size);
		}

		void p_deconvolve(tVecObj* Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt->ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt->vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFp_deconvolve(vx_vect, Flt->vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void p_deconvolve(tVecObj Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt.ui_size)||(ui_size!=X.ui_size)||
				 (ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt.vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFp_deconvolve(vx_vect, Flt.vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void p_convolve(cvta Flt, cvta X, cvta Rsp, cta TruncRe, cta TruncIm)
		{
			enforceSize();
			VFp_convolve(vx_vect,Flt.vx_vect,X.vx_vect,Rsp.vx_vect,
				ui_size,TruncRe,TruncIm);
		}

		void p_deconvolve(cvta Flt, cvta X, cvta Rsp, cta TruncRe, cta TruncIm)
		{
			enforceSize();
			VFp_convolve(vx_vect,Flt.vx_vect,X.vx_vect,Rsp.vx_vect,
				ui_size,TruncRe,TruncIm);
		}

		void l_FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VFl_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		//l_FFTtoC member of cfVecObj

		void l_filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VFl_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}

		void l_autocorr(cvta X)
		{
			enforcePow2();
			VFl_autocorr(vx_vect, X.vx_vect, ui_size);
		}

		void l_xcorr(cvta X, cvta Y)
		{
			enforcePow2();
			VFl_xcorr(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		t l_spectrum(cvta X, cvta Win)
		{
			enforcePow2();
			if(2*ui_size > X.ui_size) throw OptiVec_BigSizeErr();
			if(2*ui_size != Win.ui_size) throw OptiVec_SizeErr();
			return VFl_spectrum(vx_vect, ui_size,
				X.vx_vect, X.ui_size, Win.vx_vect);
		}

		void l_convolve(tVecObj* Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt->ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt->vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFl_convolve(vx_vect, Flt->vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void l_convolve(tVecObj Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt.ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt.vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFl_convolve(vx_vect, Flt.vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void l_deconvolve(tVecObj* Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt->ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt->vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFl_deconvolve(vx_vect, Flt->vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void l_deconvolve(tVecObj Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt.ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt.vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFl_deconvolve(vx_vect, Flt.vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void l_convolve(cvta Flt, cvta X, cvta Rsp, cta TruncRe, cta TruncIm)
		{
			enforceSize();
			VFl_convolve(vx_vect,Flt.vx_vect,X.vx_vect,Rsp.vx_vect,
				ui_size,TruncRe,TruncIm);
		}

		void l_deconvolve(cvta Flt, cvta X, cvta Rsp, cta TruncRe, cta TruncIm)
		{
			enforceSize();
			VFl_convolve(vx_vect,Flt.vx_vect,X.vx_vect,Rsp.vx_vect,
				ui_size,TruncRe,TruncIm);
		}

		void s_FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VFs_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		//s_FFTtoC member of cfVecObj

		void s_filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VFs_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}

		void s_autocorr(cvta X)
		{
			enforcePow2();
			VFs_autocorr(vx_vect, X.vx_vect, ui_size);
		}

		void s_xcorr(cvta X, cvta Y)
		{
			enforcePow2();
			VFs_xcorr(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		t s_spectrum(cvta X, cvta Win)
		{
			enforcePow2();
			if(2*ui_size > X.ui_size) throw OptiVec_BigSizeErr();
			if(2*ui_size != Win.ui_size) throw OptiVec_SizeErr();
			return VFs_spectrum(vx_vect, ui_size,
				X.vx_vect, X.ui_size, Win.vx_vect);
		}

		void s_convolve(tVecObj* Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt->ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt->vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFs_convolve(vx_vect, Flt->vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void s_convolve(tVecObj Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt.ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt.vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFs_convolve(vx_vect, Flt.vx_vect, X.vx_vect,	Rsp.vx_vect, ui_size);
		}

		void s_deconvolve(tVecObj* Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt->ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt->vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFs_deconvolve(vx_vect, Flt->vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void s_deconvolve(tVecObj Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt.ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt.vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VFs_deconvolve(vx_vect, Flt.vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void s_convolve(cvta Flt, cvta X, cvta Rsp, cta TruncRe, cta TruncIm)
		{
			enforceSize();
			VFs_convolve(vx_vect,Flt.vx_vect,X.vx_vect,Rsp.vx_vect,
				ui_size,TruncRe,TruncIm);
		}

		void s_deconvolve(cvta Flt, cvta X, cvta Rsp, cta TruncRe, cta TruncIm)
		{
			enforceSize();
			VFs_convolve(vx_vect,Flt.vx_vect,X.vx_vect,Rsp.vx_vect,
				ui_size,TruncRe,TruncIm);
		}

		void FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VF_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		//FFTtoC member of cfVecObj

		void filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VF_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}

		void autocorr(cvta X)
		{
			enforcePow2();
			VF_autocorr(vx_vect, X.vx_vect, ui_size);
		}

		void xcorr(cvta X, cvta Y)
		{
			enforcePow2();
			VF_xcorr(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		t spectrum(cvta X, cvta Win)
		{
			enforcePow2();
			if(2*ui_size > X.ui_size) throw OptiVec_BigSizeErr();
			if(2*ui_size != Win.ui_size) throw OptiVec_SizeErr();
			return VF_spectrum(vx_vect, ui_size,
				X.vx_vect, X.ui_size, Win.vx_vect);
		}

		void convolve(tVecObj* Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt->ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt->vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VF_convolve(vx_vect, Flt->vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void convolve(tVecObj Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt.ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt.vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VF_convolve(vx_vect, Flt.vx_vect, X.vx_vect, Rsp.vx_vect, ui_size);
		}

		void deconvolve(tVecObj* Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt->ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt->vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VF_deconvolve(vx_vect, Flt->vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void deconvolve(tVecObj Flt, cvta X, cvta Rsp)
		{
			enforcePow2();
			if((ui_size!=Flt.ui_size)||(ui_size!=X.ui_size)||
				(ui_size!=Rsp.ui_size)) throw OptiVec_SizeErr();
			if((vx_vect==Rsp.vx_vect)||(Flt.vx_vect==X.vx_vect))
				throw OptiVec_Err();
			VF_deconvolve(vx_vect, Flt.vx_vect, X.vx_vect,
				Rsp.vx_vect, ui_size);
		}

		void convolve(cvta Flt, cvta X, cvta Rsp, cta TruncRe, cta TruncIm)
		{
			enforceSize();
			VF_convolve(vx_vect,Flt.vx_vect,X.vx_vect,Rsp.vx_vect,
				ui_size,TruncRe,TruncIm);
		}

		void deconvolve(cvta Flt, cvta X, cvta Rsp, cta TruncRe, cta TruncIm)
		{
			enforceSize();
			VF_convolve(vx_vect,Flt.vx_vect,X.vx_vect,Rsp.vx_vect,
				ui_size,TruncRe,TruncIm);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Analysis
//
		void derivC(cvta X, cta Deltat)
		{
			enforceSize();
			VF_derivC(vx_vect,X.vx_vect,ui_size,Deltat);
		}

		void derivV(cvta X, cvta Y)
		{
			enforceSize();
			VF_derivV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		t integralC(cta DeltaT) const
		{
			enforceSize();
			return VF_integralC(vx_vect,ui_size,DeltaT);
		}

		void runintegralC(cvta X, cta DeltaT)
		{
			enforceSize();
			VF_runintegralC(vx_vect,X.vx_vect,ui_size,DeltaT);
		}

		t integralV(cvta X) const
		{
			enforceSize();
			return VF_integralV(X.vx_vect,vx_vect,ui_size);
		}

		void runintegralV(cvta X, cvta Y)
		{
			enforceSize();
			VF_runintegralV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		void smooth(cvta X, const unsigned& deg)
		{
			enforceSize();
			VF_smooth(vx_vect,X.vx_vect,ui_size,deg);
		}

		void biquad(cvta X, cvta Param)
		{
			enforceSize();
			VF_biquad(vx_vect,X.vx_vect,ui_size,Param.vx_vect);
		}

		int ismonoton() const
		{
			enforceSize();
			return VF_ismonoton(vx_vect,ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Geometrical Vector Arithmetics
//
		t scalprod(cvta Y) const
		{
			enforceSize();
			return VF_scalprod(vx_vect, Y.vx_vect, ui_size);
		}

		void xprod(cvta X, cvta Y)
		{
			enforceSize(3);
			VF_xprod(vx_vect,X.vx_vect,Y.vx_vect);
		}

		t Euclid() const
		{
			enforceSize();
			return VF_Euclid(vx_vect,ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Input and Output
//
		void fprint(FILE* stream, unsigned nperline, unsigned linewidth) const
		{
			enforceSize();
			VF_fprint(stream,vx_vect,ui_size,nperline,linewidth);
		}

		void cprint(unsigned nperline) const
		{
			enforceSize();
			VF_cprint(vx_vect,ui_size,nperline);
		}

		void print(unsigned nperline) const
		{
			fprint(stdout,nperline,80);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			VF_write(stream,vx_vect,ui_size);
		}

		void read(FILE* stream)
		{
			enforceSize();
			VF_read(vx_vect,ui_size,stream);
		}

//nwrite
//nread

		void setWriteFormat(char* formatString) const
		{
			VF_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VF_setWriteSeparate(sepString);
		}

//setNWriteSeparate

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_size,sizeof(ui),1,stream);
			VF_store(stream,vx_vect,ui_size);
		}

		void recall(FILE* stream)
		{
			ui sz;
			fread(&sz,sizeof(ui),1,stream);
			setSize(sz);
			VF_recall(vx_vect,ui_size,stream);
		}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//from VXmath.h
//


/////////////////////////////////////////////////////////////////////////////////////////
//Rounding
//
		//other rounding functions are members of the appropriate 
		//class and are defined with the corresponding header file

		int round(cvta X)
		{
			enforceSize();
			return VF_round(vx_vect,X.vx_vect,ui_size);
		}

		int floor(cvta X)
		{
			enforceSize();
			return VF_floor(vx_vect,X.vx_vect,ui_size);
		}

		int ceil(cvta X)
		{
			enforceSize();
			return VF_ceil(vx_vect,X.vx_vect,ui_size);
		}

		int chop(cvta X)
		{
			enforceSize();
			return VF_chop(vx_vect,X.vx_vect,ui_size);
		}

		int trunc(cvta X)
		{
			return chop(X);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Comparisons
//
		void cmp0(cvta X)
		{
			enforceSize();
			VF_cmp0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_eq0(cvta X)
		{
			enforceSize();
			return VF_cmp_eq0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_ne0(cvta X)
		{
			enforceSize();
			return VF_cmp_ne0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_le0(cvta X)
		{
			enforceSize();
			return VF_cmp_le0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_lt0(cvta X)
		{
			enforceSize();
			return VF_cmp_lt0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_ge0(cvta X)
		{
			enforceSize();
			return VF_cmp_ge0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_gt0(cvta X)
		{
			enforceSize();
			return VF_cmp_gt0(vx_vect,X.vx_vect,ui_size);
		}

		void cmpC(cvta X, cta C)
		{
			enforceSize();
			VF_cmpC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_eqC(cvta X, cta C)
		{
			enforceSize();
			return VF_cmp_eqC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_neC(cvta X, cta C)
		{
			enforceSize();
			return VF_cmp_neC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_leC(cvta X, cta C)
		{
			enforceSize();
			return VF_cmp_leC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_ltC(cvta X, cta C)
		{
			enforceSize();
			return VF_cmp_ltC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_geC(cvta X, cta C)
		{
			enforceSize();
			return VF_cmp_geC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_gtC(cvta X, cta C)
		{
			enforceSize();
			return VF_cmp_gtC(vx_vect,X.vx_vect,ui_size,C);
		}

		void cmpV(cvta X, cvta Y)
		{
			enforceSize();
			VF_cmpV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_eqV(cvta X, cvta Y)
		{
			enforceSize();
			return VF_cmp_eqV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_neV(cvta X, cvta Y)
		{
			enforceSize();
			return VF_cmp_neV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_leV(cvta X, cvta Y)
		{
			enforceSize();
			return VF_cmp_leV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_ltV(cvta X, cvta Y)
		{
			enforceSize();
			return VF_cmp_ltV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_geV(cvta X, cvta Y)
		{
			enforceSize();
			return VF_cmp_geV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_gtV(cvta X, cvta Y)
		{
			enforceSize();
			return VF_cmp_gtV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_inclrange0C(cvta X, cta C)
		{
			enforceSize();
			return VF_cmp_inclrange0C(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_exclrange0C(cvta X, cta C)
		{
			enforceSize();
			return VF_cmp_exclrange0C(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_inclrangeCC(cvta X, cta CLo, cta CHi)
		{
			enforceSize();
			return VF_cmp_inclrangeCC(vx_vect,X.vx_vect,ui_size,CLo,CHi);
		}

		ui cmp_exclrangeCC(cvta X, cta CLo, cta CHi)
		{
			enforceSize();
			return VF_cmp_exclrangeCC(vx_vect,X.vx_vect,ui_size,CLo,CHi);
		}

		ui cnt_eq0()  const
		{
			enforceSize();
			return VF_cnt_eq0(vx_vect, ui_size);
		}

		ui cnt_ne0()  const
		{
			enforceSize();
			return VF_cnt_ne0(vx_vect, ui_size);
		}

		ui cnt_le0()  const
		{
			enforceSize();
			return VF_cnt_le0(vx_vect, ui_size);
		}

		ui cnt_lt0()  const
		{
			enforceSize();
			return VF_cnt_lt0(vx_vect, ui_size);
		}

		ui cnt_ge0()  const
		{
			enforceSize();
			return VF_cnt_ge0(vx_vect, ui_size);
		}

		ui cnt_gt0()  const
		{
			enforceSize();
			return VF_cnt_gt0(vx_vect, ui_size);
		}

		ui cnt_eqC(cta C) const
		{
			enforceSize();
			return VF_cnt_eqC(vx_vect,ui_size,C);
		}

		ui cnt_neC(cta C) const
		{
			enforceSize();
			return VF_cnt_neC(vx_vect,ui_size,C);
		}

		ui cnt_leC(cta C) const
		{
			enforceSize();
			return VF_cnt_leC(vx_vect,ui_size,C);
		}

		ui cnt_ltC(cta C) const
		{
			enforceSize();
			return VF_cnt_ltC(vx_vect,ui_size,C);
		}

		ui cnt_geC(cta C) const
		{
			enforceSize();
			return VF_cnt_geC(vx_vect,ui_size,C);
		}

		ui cnt_gtC(cta C) const
		{
			enforceSize();
			return VF_cnt_gtC(vx_vect,ui_size,C);
		}

		ui cnt_inclrange0C(cta C) const
		{
			enforceSize();
			return VF_cnt_inclrange0C(vx_vect,ui_size,C);
		}

		ui cnt_exclrange0C(cta C) const
		{
			enforceSize();
			return VF_cnt_exclrange0C(vx_vect,ui_size,C);
		}

		ui cnt_inclrangeCC(cta CLo, cta CHi) const
		{
			enforceSize();
			return VF_cnt_inclrangeCC(vx_vect,ui_size,CLo, CHi);
		}

		ui cnt_exclrangeCC(cta CLo, cta CHi) const
		{
			enforceSize();
			return VF_cnt_exclrangeCC(vx_vect,ui_size,CLo, CHi);
		}

		ui cnt_eqV(cvta Y) const
		{
			enforceSize();
			return VF_cnt_eqV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_neV(cvta Y) const
		{
			enforceSize();
			return VF_cnt_neV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_leV(cvta Y) const
		{
			enforceSize();
			return VF_cnt_leV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_ltV(cvta Y) const
		{
			enforceSize();
			return VF_cnt_ltV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_geV(cvta Y) const
		{
			enforceSize();
			return VF_cnt_geV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_gtV(cvta Y) const
		{
			enforceSize();
			return VF_cnt_gtV(vx_vect,Y.vx_vect,ui_size);
		}

		//indexed comparisons are members of uiVecObj


/////////////////////////////////////////////////////////////////////////////////////////
//Standard Arithmetics or Basic Arithmetics
//
		//equC, equV, and x_equV defined above

		void addC(cvta X, cta C)
		{
			enforceSize();
			VF_addC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subC(cvta X, cta C)
		{
			enforceSize();
			VF_subC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subrC(cvta X, cta C)
		{
			enforceSize();
			VF_subrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void mulC(cvta X, cta C)
		{
			enforceSize();
			VF_mulC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divC(cvta X, cta C)
		{
			enforceSize();
			VF_divC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divrC(cvta X, cta C)
		{
			enforceSize();
			VF_divrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void x_divrC(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			VFx_divrC(vx_vect, X.vx_vect, ui_size, A, B, C);
		}

		void addV(cvta X, cvta Y)
		{
			enforceSize();
			VF_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subV(cvta X, cvta Y)
		{
			enforceSize();
			VF_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subrV(cvta X, cvta Y)
		{
			enforceSize();
			VF_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void mulV(cvta X, cvta Y)
		{
			enforceSize();
			VF_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divV(cvta X, cvta Y)
		{
			enforceSize();
			VF_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divrV(cvta X, cvta Y)
		{
			enforceSize();
			VF_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void CaddV(cvta X, cvta Y, cta C)
		{
			enforceSize();
			VF_CaddV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, C);
		}

		void x_addV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VFx_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_subV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VFx_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_subrV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VFx_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_mulV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VFx_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_divV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VFx_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_divrV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VFx_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void s_addV(cvta X, cvta Y, cta C)
		{
			enforceSize();
			VFs_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, C);
		}

		void s_subV(cvta X, cvta Y, cta C)
		{
			enforceSize();
			VFs_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, C);
		}

		void s_subrV(cvta X, cvta Y, cta C)
		{
			enforceSize();
			VFs_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, C);
		}

		void s_mulV(cvta X, cvta Y, cta C)
		{
			enforceSize();
			VFs_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, C);
		}

		void s_divV(cvta X, cvta Y, cta C)
		{
			enforceSize();
			VFs_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, C);
		}

		void s_divrV(cvta X, cvta Y, cta C)
		{
			enforceSize();
			VFs_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, C);
		}

		void maxC(cvta X, cta C)
		{
			enforceSize();
			VF_maxC( vx_vect, X.vx_vect, ui_size, C);
		}

		void minC(cvta X, cta C)
		{
			enforceSize();
			VF_minC( vx_vect, X.vx_vect, ui_size, C);
		}

		void limit(cvta X, cta Min, cta Max)
		{
			enforceSize();
			VF_limit( vx_vect, X.vx_vect, ui_size, Min, Max);
		}

		void flush0(cvta X, cta AbsMin)
		{
			enforceSize();
			VF_flush0( vx_vect, X.vx_vect, ui_size, AbsMin);
		}

		void flushInv(cvta X, cta AbsMin)
		{
			enforceSize();
			VF_flushInv(vx_vect, X.vx_vect, ui_size, AbsMin);
		}

		void replaceNAN(cvta X, cta C)
		{
			enforceSize();
			VF_replaceNAN( vx_vect, X.vx_vect, ui_size, C);
		}

		void maxV(cvta X, cvta Y)
		{
			enforceSize();
			VF_maxV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void minV(cvta X, cvta Y)
		{
			enforceSize();
			VF_minV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void modC(cvta X, cta C)
		{
			enforceSize();
			VF_modC(vx_vect, X.vx_vect, ui_size, C);
		}

		void modV(cvta X, cvta Y)
		{
			enforceSize();
			VF_modV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void x_modV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VFx_modV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void fmodC(cvta X, cta C)
		{
			modC(X,C);
		}

		void fmodV(cvta X, cvta Y)
		{
			modV(X,Y);
		}

		void x_fmodV(cvta X, cvta Y, cta A, cta B)
		{
			x_modV(X,Y,A,B);
		}

		void redC(cvta X, cta C)
		{
			enforceSize();
			VF_redC( vx_vect, X.vx_vect, ui_size, C);
		}

		void redV(cvta X, cvta Y)
		{
			enforceSize();
			VF_redV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void x_redV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VFx_redV( vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void visC( cvta X, cta C)
		{
			enforceSize();
			VF_visC( vx_vect, X.vx_vect, ui_size, C);
		}

		void visV(cvta X, cvta Y)
		{
			enforceSize();
			VF_visV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void x_visV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VFx_visV( vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void hypC( cvta X, cta C)
		{
			enforceSize();
			VF_hypC( vx_vect, X.vx_vect, ui_size, C);
		}

		void hypV(cvta X, cvta Y)
		{
			enforceSize();
			VF_hypV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void x_hypV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VFx_hypV( vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void lincomb(cvta X, cvta Y, cta CX, cta CY)
		{
			enforceSize();
			VF_lincomb( vx_vect, X.vx_vect, Y.vx_vect, ui_size, CX, CY);
		}

		void sgn(cvta X)
		{
			cmp0(X);
		}


/////////////////////////////////////////////////////////////////////////////////////////
// Mixed-type Arithmetics, Accumulation
//
		void accV(cvta X)
		{
			enforceSize();
			VF_accV(vx_vect,X.vx_vect,ui_size);
		}

		//defined by including biVecObj.h
		void accVBI(const biVecObj& X);
        void addVBI( cvta X, const biVecObj& Y);
        void subVBI( cvta X, const biVecObj& Y);
        void subrVBI(cvta X, const biVecObj& Y);
        void mulVBI( cvta X, const biVecObj& Y);
        void divVBI( cvta X, const biVecObj& Y);
        void divrVBI(cvta X, const biVecObj& Y);

		//defined by including siVecObj.h
		void accVSI(const siVecObj& X);
        void addVSI( cvta X, const siVecObj& Y);
        void subVSI( cvta X, const siVecObj& Y);
        void subrVSI(cvta X, const siVecObj& Y);
        void mulVSI( cvta X, const siVecObj& Y);
        void divVSI( cvta X, const siVecObj& Y);
        void divrVSI(cvta X, const siVecObj& Y);

		//defined by including iVecObj.h
		void accVI( const  iVecObj& X);
        void addVI( cvta X, const iVecObj& Y);
        void subVI( cvta X, const iVecObj& Y);
        void subrVI(cvta X, const iVecObj& Y);
        void mulVI( cvta X, const iVecObj& Y);
        void divVI( cvta X, const iVecObj& Y);
        void divrVI(cvta X, const iVecObj& Y);

		//defined by including liVecObj.h
		void accVLI(const liVecObj& X);
        void addVLI( cvta X, const liVecObj& Y);
        void subVLI( cvta X, const liVecObj& Y);
        void subrVLI(cvta X, const liVecObj& Y);
        void mulVLI( cvta X, const liVecObj& Y);
        void divVLI( cvta X, const liVecObj& Y);
        void divrVLI(cvta X, const liVecObj& Y);

		//defined by including qiVecObj.h
		void accVQI(const qiVecObj& X);
        void addVQI( cvta X, const qiVecObj& Y);
        void subVQI( cvta X, const qiVecObj& Y);
        void subrVQI(cvta X, const qiVecObj& Y);
        void mulVQI( cvta X, const qiVecObj& Y);
        void divVQI( cvta X, const qiVecObj& Y);
        void divrVQI(cvta X, const qiVecObj& Y);

		//defined by including ubVecObj.h
		void accVUB(const ubVecObj& X);
        void addVUB( cvta X, const ubVecObj& Y);
        void subVUB( cvta X, const ubVecObj& Y);
        void subrVUB(cvta X, const ubVecObj& Y);
        void mulVUB( cvta X, const ubVecObj& Y);
        void divVUB( cvta X, const ubVecObj& Y);
        void divrVUB(cvta X, const ubVecObj& Y);

		//defined by including usVecObj.h
		void accVUS(const usVecObj& X);
        void addVUS( cvta X, const usVecObj& Y);
        void subVUS( cvta X, const usVecObj& Y);
        void subrVUS(cvta X, const usVecObj& Y);
        void mulVUS( cvta X, const usVecObj& Y);
        void divVUS( cvta X, const usVecObj& Y);
        void divrVUS(cvta X, const usVecObj& Y);

		//defined by including uVecObj.h
		void accVU( const  uVecObj& X);
        void addVU( cvta X, const uVecObj& Y);
        void subVU( cvta X, const uVecObj& Y);
        void subrVU(cvta X, const uVecObj& Y);
        void mulVU( cvta X, const uVecObj& Y);
        void divVU( cvta X, const uVecObj& Y);
        void divrVU(cvta X, const uVecObj& Y);

		//defined by including ulVecObj.h
		void accVUL(const ulVecObj& X);
        void addVUL( cvta X, const ulVecObj& Y);
        void subVUL( cvta X, const ulVecObj& Y);
        void subrVUL(cvta X, const ulVecObj& Y);
        void mulVUL( cvta X, const ulVecObj& Y);
        void divVUL( cvta X, const ulVecObj& Y);
        void divrVUL(cvta X, const ulVecObj& Y);

		void accVUI(const uiVecObj& X)
		{
			enforceSize();
			VF_accVUI(vx_vect,X.vx_vect,ui_size);
		}

        void addVUI( cvta X, const uiVecObj& Y)
		{
			enforceSize();
			VF_addVUI(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

        void subVUI( cvta X, const uiVecObj& Y)
		{
			enforceSize();
			VF_subVUI(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

        void subrVUI( cvta X, const uiVecObj& Y)
		{
			enforceSize();
			VF_subrVUI(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

        void mulVUI( cvta X, const uiVecObj& Y)
		{
			enforceSize();
			VF_mulVUI(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

        void divVUI( cvta X, const uiVecObj& Y)
		{
			enforceSize();
			VF_divVUI(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

        void divrVUI( cvta X, const uiVecObj& Y)
		{
			enforceSize();
			VF_divrVUI(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Bit-wise operations
//


/////////////////////////////////////////////////////////////////////////////////////////
//Functions of a sub-set of elements
//
		void subvector_equC(const ui& samp, cta C)
		{
			enforceSize();
			VF_subvector_equC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_equV(const ui& samp, cvta X)
		{
			enforceSize();
			VF_subvector_equV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_addC(const ui& samp, cta C)
		{
			enforceSize();
			VF_subvector_addC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_subC(const ui& samp, cta C)
		{
			enforceSize();
			VF_subvector_subC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_subrC(const ui& samp, cta C)
		{
			enforceSize();
			VF_subvector_subrC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_mulC(const ui& samp, cta C)
		{
			enforceSize();
			VF_subvector_mulC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_divC(const ui& samp, cta C)
		{
			enforceSize();
			VF_subvector_divC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_divrC(const ui& samp, cta C)
		{
			enforceSize();
			VF_subvector_divrC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_addV(const ui& samp, cvta X)
		{
			enforceSize();
			VF_subvector_addV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_subV(const ui& samp, cvta X)
		{
			enforceSize();
			VF_subvector_subV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_subrV(const ui& samp, cvta X)
		{
			enforceSize();
			VF_subvector_subrV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_mulV(const ui& samp, cvta X)
		{
			enforceSize();
			VF_subvector_mulV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_divV(const ui& samp, cvta X)
		{
			enforceSize();
			VF_subvector_divV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_divrV(const ui& samp, cvta X)
		{
			enforceSize();
			VF_subvector_divrV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Mathematical Functions
//

		int abs(cvta X)
		{
			enforceSize();
			return VF_abs(vx_vect, X.vx_vect, ui_size);
		}

		int neg(cvta X)
		{
			enforceSize();
			return VF_neg(vx_vect, X.vx_vect, ui_size);
		}

		int inv(cvta X)
		{
			enforceSize();
			return VF_inv(vx_vect, X.vx_vect, ui_size);
		}

		int x_inv(cvta X, cta A, cta B)
		{
			enforceSize();
			return VFx_inv(vx_vect, X.vx_vect, ui_size, A, B);
		}

		int intfrac(vt* Frac, cvta X)
		{
			enforceSize();
			enforceSize(Frac->ui_size);
			return VF_intfrac(vx_vect,Frac->vx_vect,X.vx_vect,ui_size);
		}

		int intfrac(vt Frac, cvta X)
		{
			enforceSize();
			enforceSize(Frac.ui_size);
			return VF_intfrac(vx_vect,Frac.vx_vect,X.vx_vect,ui_size);
		}

		int modf(vt* Frac, cvta X)
		{
			return intfrac(Frac,X);
		}

		int modf(vt Frac, cvta X)
		{
			return intfrac(Frac,X);
		}

		//defined by including iVecObj.h
		int mantexp(iVecObj* Exp, const fVecObj& X);
		int mantexp(iVecObj  Exp, const fVecObj& X);

		int frexp(iVecObj* Exp, cvta X){return mantexp(Exp,X);}
		int frexp(iVecObj  Exp, cvta X){return mantexp(Exp,X);}

		int hypotC(cvta X, cta C)
		{
			enforceSize();
			return VF_hypotC(vx_vect, X.vx_vect, ui_size, C);
		}

		int hypotV(cvta X, cvta Y)
		{
			enforceSize();
			return VF_hypotV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		int x_hypotV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			return VFx_hypotV(vx_vect,X.vx_vect,Y.vx_vect,ui_size,A,B);
		}

		int scale2(cvta X, int expo)
		{
			enforceSize();
			return VF_scale2(vx_vect, X.vx_vect, ui_size, expo);
		}

		int scale10(cvta X, int expo)
		{
			enforceSize();
			return VF_scale10(vx_vect, X.vx_vect, ui_size, expo);
		}

		int ldexp(cvta X, int expo)
		{
			return scale2(X,expo);
		}

		int square(cvta X)
		{
			enforceSize();
			return VF_square(vx_vect,X.vx_vect,ui_size);
		}

		int x_square(cvta X, cta A, cta B)
		{
			enforceSize();
			return VFx_square(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int cubic(cvta X)
		{
			enforceSize();
			return VF_cubic(vx_vect,X.vx_vect,ui_size);
		}

		int x_cubic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VFx_cubic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int quartic(cvta X)
		{
			enforceSize();
			return VF_quartic(vx_vect,X.vx_vect,ui_size);
		}

		int x_quartic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VFx_quartic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int poly(cvta X, cvta Coeff)
		{
			enforceSize();
			return VF_poly(vx_vect,X.vx_vect,ui_size,
				Coeff.vx_vect,(unsigned)Coeff.ui_size);
		}

		int x_poly(cvta X, cvta Coeff, cta A, cta B)
		{
			enforceSize();
			return VFx_poly(vx_vect,X.vx_vect,ui_size,
				Coeff.vx_vect,(unsigned)Coeff.ui_size,A,B);
		}

		int ipow(cvta X, int pow)
		{
			enforceSize();
			return VF_ipow(vx_vect, X.vx_vect, ui_size, pow);
		}

		int x_ipow(cvta X, int pow, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_ipow(vx_vect, X.vx_vect, ui_size, pow, A, B, C);
		}

		int u_square(cvta X)
		{
			enforceSize();
			return VFu_square(vx_vect,X.vx_vect,ui_size);
		}

		int ux_square(cvta X, cta A, cta B)
		{
			enforceSize();
			return VFux_square(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int u_cubic(cvta X)
		{
			enforceSize();
			return VFu_cubic(vx_vect,X.vx_vect,ui_size);
		}

		int ux_cubic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VFux_cubic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int u_quartic(cvta X)
		{
			enforceSize();
			return VFu_quartic(vx_vect,X.vx_vect,ui_size);
		}

		int ux_quartic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VFux_quartic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int u_poly(cvta X, cvta Coeff)
		{
			enforceSize();
			return VFu_poly(vx_vect,X.vx_vect,ui_size,
				Coeff.vx_vect,(unsigned)Coeff.ui_size);
		}

		int ux_poly(cvta X, cvta Coeff, cta A, cta B)
		{
			enforceSize();
			return VFux_poly(vx_vect,X.vx_vect,ui_size,
				Coeff.vx_vect,(unsigned)Coeff.ui_size,A,B);
		}

		int u_ipow(cvta X, int pow)
		{
			enforceSize();
			return VFu_ipow(vx_vect, X.vx_vect, ui_size, pow);
		}

		int ux_ipow(cvta X, int pow, cta A, cta B, cta C)
		{
			enforceSize();
			return VFux_ipow(vx_vect, X.vx_vect, ui_size, pow, A, B, C);
		}

		//defined by including iVecObj.h
		int ipow2(const iVecObj& X);

		//defined by including iVecObj.h
		int ipow10(const iVecObj& X);

		int pow(cvta X, cta expo)
		{
			enforceSize();
			return VF_pow(vx_vect,X.vx_vect,ui_size,expo);
		}

		int x_pow(cvta X, cta expo, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_pow(vx_vect,X.vx_vect,ui_size,expo,A,B,C);
		}

		int pow2(cvta X)
		{
			enforceSize();
			return VF_pow2(vx_vect,X.vx_vect,ui_size);
		}

		int x_pow2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_pow2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int pow10(cvta X)
		{
			enforceSize();
			return VF_pow10(vx_vect,X.vx_vect,ui_size);
		}

		int x_pow10(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_pow10(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sqrt(cvta X)
		{
			enforceSize();
			return VF_sqrt(vx_vect,X.vx_vect,ui_size);
		}

		int x_sqrt(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_sqrt(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int log(cvta X)
		{
			enforceSize();
			return VF_log(vx_vect,X.vx_vect,ui_size);
		}

		int log2(cvta X)
		{
			enforceSize();
			return VF_log2(vx_vect,X.vx_vect,ui_size);
		}

		int log10(cvta X)
		{
			enforceSize();
			return VF_log10(vx_vect,X.vx_vect,ui_size);
		}

		int ln(cvta X){return log(X);}

		int x_log(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_log(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int x_log2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_log2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int x_log10(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_log10(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int x_ln(cvta X, cta A, cta B, cta C)
		{
			return x_log(X,A,B,C);
		}

		int OD(cvta X, cvta X0)
		{
			enforceSize();
			return VF_OD(vx_vect,X.vx_vect,X0.vx_vect,ui_size);
		}

		int ODwDark(cvta X, cvta XDark, cvta X0, cvta X0Dark)
		{
			enforceSize();
			return VF_ODwDark(vx_vect,X.vx_vect,XDark.vx_vect,
				X0.vx_vect,X0Dark.vx_vect,ui_size);
		}

		void setODThresh(cta minX, cta minX0)
		{
			VF_setODThresh(minX,minX0);
		}

		int exp(cvta X)
		{
			enforceSize();
			return VF_exp(vx_vect,X.vx_vect,ui_size);
		}

		int x_exp(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_exp(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int expArbBase(cvta X, cta Base)
		{
			enforceSize();
			return VF_expArbBase(vx_vect,X.vx_vect,ui_size,Base);
		}

		int x_expArbBase(cvta X, cta Base, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_expArbBase(vx_vect,X.vx_vect,ui_size,Base,A,B,C);
		}

		int expc(cvta X)
		{
			enforceSize();
			return VF_expc(vx_vect,X.vx_vect,ui_size);
		}

		int x_expc(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_expc(vx_vect,X.vx_vect,ui_size,A,B,C);
		}


		int exp2(cvta X)
		{
			enforceSize();
			return VF_exp2(vx_vect,X.vx_vect,ui_size);
		}

		int x_exp2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_exp2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}


		int exp10(cvta X)
		{
			enforceSize();
			return VF_exp10(vx_vect,X.vx_vect,ui_size);
		}

		int x_exp10(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_exp10(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int expmx2(cvta X)
		{
			enforceSize();
			return VF_expmx2(vx_vect,X.vx_vect,ui_size);
		}

		int x_expmx2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_expmx2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int erf(cvta X)
		{
			enforceSize();
			return VF_erf(vx_vect,X.vx_vect,ui_size);
		}

		int x_erf(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_erf(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int erfc(cvta X)
		{
			enforceSize();
			return VF_erfc(vx_vect,X.vx_vect,ui_size);
		}

		int x_erfc(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_erfc(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int Gauss(cvta X, cta Wid, cta Cent, cta C)
		{
			enforceSize();
			return VF_Gauss(vx_vect,X.vx_vect,ui_size,Wid,Cent,C);
		}

		int gauss(cvta X, cta Wid, cta Cent, cta C)
		{
			return Gauss(X,Wid,Cent,C);
		}

		int Lorentz(cvta X, cta Wid, cta Cent, cta C)
		{
			enforceSize();
			return VF_Lorentz(vx_vect,X.vx_vect,ui_size,Wid,Cent,C);
		}

		int lorentz(cvta X, cta Wid, cta Cent, cta C)
		{
			return Lorentz(X,Wid,Cent,C);
		}

		int sin(cvta X)
		{
			enforceSize();
			return VF_sin(vx_vect,X.vx_vect,ui_size);
		}

		int x_sin(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_sin(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cos(cvta X)
		{
			enforceSize();
			return VF_cos(vx_vect,X.vx_vect,ui_size);
		}

		int x_cos(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_cos(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sincos(vt* Cos, cvta X)
		{
			enforceSize();
			enforceSize(Cos->ui_size);
			return VF_sincos(vx_vect,Cos->vx_vect,X.vx_vect,ui_size);
		}

		int sincos(vt Cos, cvta X)
		{
			enforceSize();
			enforceSize(Cos.ui_size);
			return VF_sincos(vx_vect,Cos.vx_vect,X.vx_vect,ui_size);
		}

		int x_sincos(vt* Cos, cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			enforceSize(Cos->ui_size);
			return VFx_sincos(vx_vect,Cos->vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int x_sincos(vt Cos, cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			enforceSize(Cos.ui_size);
			return VFx_sincos(vx_vect,Cos.vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int tan(cvta X)
		{
			enforceSize();
			return VF_tan(vx_vect,X.vx_vect,ui_size);
		}

		int x_tan(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_tan(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cot(cvta X)
		{
			enforceSize();
			return VF_cot(vx_vect,X.vx_vect,ui_size);
		}

		int x_cot(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_cot(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sec(cvta X)
		{
			enforceSize();
			return VF_sec(vx_vect,X.vx_vect,ui_size);
		}

		int x_sec(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_sec(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cosec(cvta X)
		{
			enforceSize();
			return VF_cosec(vx_vect,X.vx_vect,ui_size);
		}

		int x_cosec(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_cosec(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sin2(cvta X)
		{
			enforceSize();
			return VF_sin2(vx_vect,X.vx_vect,ui_size);
		}

		int x_sin2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_sin2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cos2(cvta X)
		{
			enforceSize();
			return VF_cos2(vx_vect,X.vx_vect,ui_size);
		}

		int x_cos2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_cos2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sincos2(vt* Cos, cvta X)
		{
			enforceSize();
			enforceSize(Cos->ui_size);
			return VF_sincos2(vx_vect,Cos->vx_vect,X.vx_vect,ui_size);
		}

		int x_sincos2(vt* Cos, cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			enforceSize(Cos->ui_size);
			return VFx_sincos2(vx_vect,Cos->vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sincos2(vt Cos, cvta X)
		{
			enforceSize();
			enforceSize(Cos.ui_size);
			return VF_sincos2(vx_vect,Cos.vx_vect,X.vx_vect,ui_size);
		}

		int x_sincos2(vt Cos, cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			enforceSize(Cos.ui_size);
			return VFx_sincos2(vx_vect,Cos.vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int tan2(cvta X)
		{
			enforceSize();
			return VF_tan2(vx_vect,X.vx_vect,ui_size);
		}

		int x_tan2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_tan2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cot2(cvta X)
		{
			enforceSize();
			return VF_cot2(vx_vect,X.vx_vect,ui_size);
		}

		int x_cot2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_cot2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sec2(cvta X)
		{
			enforceSize();
			return VF_sec2(vx_vect,X.vx_vect,ui_size);
		}

		int x_sec2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_sec2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cosec2(cvta X)
		{
			enforceSize();
			return VF_cosec2(vx_vect,X.vx_vect,ui_size);
		}

		int x_cosec2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_cosec2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int r_sin(cvta X)
		{
			enforceSize();
			return VFr_sin(vx_vect,X.vx_vect,ui_size);
		}

		int rx_sin(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFrx_sin(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int r_cos(cvta X)
		{
			enforceSize();
			return VFr_cos(vx_vect,X.vx_vect,ui_size);
		}

		int rx_cos(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFrx_cos(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int r_sincos(vt* Cos, cvta X)
		{
			enforceSize();
			enforceSize(Cos->ui_size);
			return VFr_sincos(vx_vect,Cos->vx_vect,X.vx_vect,ui_size);
		}

		int rx_sincos(vt* Cos, cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			enforceSize(Cos->ui_size);
			return VFrx_sincos(vx_vect,Cos->vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int r_sincos(vt Cos, cvta X)
		{
			enforceSize();
			enforceSize(Cos.ui_size);
			return VFr_sincos(vx_vect,Cos.vx_vect,X.vx_vect,ui_size);
		}

		int rx_sincos(vt Cos, cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			enforceSize(Cos.ui_size);
			return VFrx_sincos(vx_vect,Cos.vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int r_sin2(cvta X)
		{
			enforceSize();
			return VFr_sin2(vx_vect,X.vx_vect,ui_size);
		}

		int rx_sin2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFrx_sin2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int r_cos2(cvta X)
		{
			enforceSize();
			return VFr_cos2(vx_vect,X.vx_vect,ui_size);
		}

		int rx_cos2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFrx_cos2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int r_sincos2(vt* Cos, cvta X)
		{
			enforceSize();
			enforceSize(Cos->ui_size);
			return VFr_sincos2(vx_vect,Cos->vx_vect,X.vx_vect,ui_size);
		}

		int rx_sincos2(vt* Cos, cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			enforceSize(Cos->ui_size);
			return VFrx_sincos2(vx_vect,Cos->vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int r_sincos2(vt Cos, cvta X)
		{
			enforceSize();
			enforceSize(Cos.ui_size);
			return VFr_sincos2(vx_vect,Cos.vx_vect,X.vx_vect,ui_size);
		}

				int rx_sincos2(vt Cos, cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			enforceSize(Cos.ui_size);
			return VFrx_sincos2(vx_vect,Cos.vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		//defined by including iVecObj.h
		int sinrpi(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int cosrpi(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int sincosrpi(vt* Cos, const iVecObj& P, int q);
		int sincosrpi(vt  Cos, const iVecObj& P, int q);

		//defined by including iVecObj.h
		int tanrpi(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int cotrpi(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int secrpi(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int cosecrpi(const iVecObj& P, int q);


		//defined by including iVecObj.h
		int sinrpi2(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int cosrpi2(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int sincosrpi2(vt* Cos, const iVecObj& P, int q);
		int sincosrpi2(vt  Cos, const iVecObj& P, int q);

		//defined by including iVecObj.h
		int tanrpi2(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int cotrpi2(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int secrpi2(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int cosecrpi2(const iVecObj& P, int q);


		//defined by including iVecObj.h
		int sinrpi3(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int cosrpi3(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int sincosrpi3(vt* Cos, const iVecObj& P, int q);
		int sincosrpi3(vt  Cos, const iVecObj& P, int q);

		//defined by including iVecObj.h
		int tanrpi3(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int cotrpi3(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int secrpi3(const iVecObj& P, int q);

		//defined by including iVecObj.h
		int cosecrpi3(const iVecObj& P, int q);

		int sinc(cvta X)
		{
			enforceSize();
			return VF_sinc(vx_vect,X.vx_vect,ui_size);
		}

		int x_sinc(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_sinc(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int Kepler(cvta X, cta T, cta e)
		{
			enforceSize();
			return VF_Kepler(vx_vect,X.vx_vect,ui_size,T,e);
		}

		int x_Kepler(cvta X, cta T, cta e, cta A, cta B)
		{
			enforceSize();
			return VFx_Kepler(vx_vect,X.vx_vect,ui_size,T,e,A,B);
		}


		int kepler(cvta X, cta T, cta e)
		{
			return Kepler(X,T,e);
		}

		int x_kepler(cvta X, cta T, cta e, cta A, cta B)
		{
			return x_Kepler(X,T,e,A,B);
		}

		int asin(cvta X)
		{
			enforceSize();
			return VF_asin(vx_vect,X.vx_vect,ui_size);
		}

		int x_asin(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_asin(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int acos(cvta X)
		{
			enforceSize();
			return VF_acos(vx_vect,X.vx_vect,ui_size);
		}

		int x_acos(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_acos(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int atan(cvta X)
		{
			enforceSize();
			return VF_atan(vx_vect,X.vx_vect,ui_size);
		}

		int x_atan(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_atan(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int atan2(cvta X, cvta Y)
		{
			enforceSize();
			return VF_atan2(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		int x_atan2(cvta X, cvta Y, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_atan2(vx_vect,X.vx_vect,Y.vx_vect,ui_size,A,B,C);
		}

		int sinh(cvta X)
		{
			enforceSize();
			return VF_sinh(vx_vect,X.vx_vect,ui_size);
		}

		int x_sinh(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_sinh(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cosh(cvta X)
		{
			enforceSize();
			return VF_cosh(vx_vect,X.vx_vect,ui_size);
		}

		int x_cosh(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_cosh(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int tanh(cvta X)
		{
			enforceSize();
			return VF_tanh(vx_vect,X.vx_vect,ui_size);
		}

		int x_tanh(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_tanh(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int coth(cvta X)
		{
			enforceSize();
			return VF_coth(vx_vect,X.vx_vect,ui_size);
		}

		int x_coth(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_coth(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sech(cvta X)
		{
			enforceSize();
			return VF_sech(vx_vect,X.vx_vect,ui_size);
		}

		int x_sech(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_sech(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cosech(cvta X)
		{
			enforceSize();
			return VF_cosech(vx_vect,X.vx_vect,ui_size);
		}

		int x_cosech(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_cosech(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sech2(cvta X)
		{
			enforceSize();
			return VF_sech2(vx_vect,X.vx_vect,ui_size);
		}

		int x_sech2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VFx_sech2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		t nonlinfit_getChi2( VF_NONLINFITWORKSPACE *ws ) const
		{ return VF_nonlinfit_getChi2( ws );  }

		t nonlinfitwW_getChi2( VF_NONLINFITWORKSPACE *ws ) const
		{ return VF_nonlinfitwW_getChi2( ws );  }

		void  nonlinfit_getBestValues( VF_NONLINFITWORKSPACE *ws )
		{ VF_nonlinfit_getBestValues( vx_vect, ws ); }

		void  nonlinfitwW_getBestValues( VF_NONLINFITWORKSPACE *ws )
		{ VF_nonlinfitwW_getBestValues( vx_vect, ws ); }

		void  Mnonlinfit_getBestValues( MF_NONLINFITWORKSPACE *ws )
		{ MF_nonlinfit_getBestValues( vx_vect, ws ); }

		void  MnonlinfitwW_getBestValues( MF_NONLINFITWORKSPACE *ws )
		{ MF_nonlinfitwW_getBestValues( vx_vect, ws ); }

		unsigned nonlinfit_getTestRun( VF_NONLINFITWORKSPACE *ws ) const
		{ return VF_nonlinfit_getTestRun( ws ); }

		unsigned nonlinfitwW_getTestRun( VF_NONLINFITWORKSPACE *ws ) const
		{ return VF_nonlinfitwW_getTestRun( ws ); }

		unsigned nonlinfit_getTestPar( VF_NONLINFITWORKSPACE *ws ) const
		{ return VF_nonlinfit_getTestPar( ws ); }

		unsigned nonlinfitwW_getTestPar( VF_NONLINFITWORKSPACE *ws ) const
		{ return VF_nonlinfitwW_getTestPar( ws ); }

		int  nonlinfit_getTestDir( VF_NONLINFITWORKSPACE *ws ) const
		{ return VF_nonlinfit_getTestDir( ws ); }

		int  nonlinfitwW_getTestDir( VF_NONLINFITWORKSPACE *ws ) const
		{ return VF_nonlinfitwW_getTestDir( ws ); }

		void  nonlinfit_stop( VF_NONLINFITWORKSPACE *ws ) const
		{ VF_nonlinfit_stop( ws ); }

		void  nonlinfitwW_stop( VF_NONLINFITWORKSPACE *ws ) const
		{ VF_nonlinfitwW_stop( ws ); }


		//defined by including fMatObj.h
		vt operator*(cmta MY);
		void Row_extract(cmta MA, const ui iRow);
		void Col_extract(cmta MA, const ui iCol);
		void Dia_extract(cmta MA);
		void Rows_max(cmta MA);
		void Cols_max(cmta MA);
		void Rows_min(cmta MA);
		void Cols_min(cmta MA);
		void Rows_absmax(cmta MA);
		void Cols_absmax(cmta MA);
		void Rows_absmin(cmta MA);
		void Cols_absmin(cmta MA);
		void Rows_sum(cmta MA);
		void Cols_sum(cmta MA);
		void Rows_ssq(cmta MA);
		void Cols_ssq(cmta MA);
		void Rows_prod(cmta MA);
		void Cols_prod(cmta MA);
		void MmulV( cmta MA, cvta X );
		void MTmulV( cmta MA, cvta X );
		void mulM( cvta X, cmta MA );
		void mulMT( cvta X, cmta MA );
		void LUsolve( cmta MLU, cvta B, const uiVecObj& Ind );
		void LUimprove( cvta B, cmta MA, cmta MLU, const uiVecObj& Ind );
		void CholeskyLsolve( cmta ML, cvta B );
		void CholeskyLimprove( cvta B, cmta MA, cmta ML );
		void CholeskyRsolve( cmta MR, cvta B );
		void CholeskyRimprove( cvta B, cmta MA, cmta MR );
		void SVsolve( cmta MU, cmta MV, cvta W, cvta B );
		int solve( cmta MA, cvta B );
		int sym_solve( cmta MA, cvta B );
		int solveBySVD( cmta MA, cvta B );
		int safeSolve( cmta MA, cvta B );
		int sym_eigenvalues( tMatObj EigM, cmta MA, int CalcEigenVec );
		int sym_eigenvalues( tMatObj* EigM, cmta MA, int CalcEigenVec );
		int polyfit( cvta X, cvta Y );
		int polyfitwW( tMatObj Covar, cvta X, cvta Y, cvta InvVar );
		int polyfitwW( tMatObj* Covar, cvta X, cvta Y, cvta InvVar );
		int linfit( const iVecObj& AStatus, cvta X, cvta Y,
			void __vf funcs(tVector BasFuncs, t x, unsigned nfuncs) );
		int linfitwW( tMatObj Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
			void __vf funcs(tVector BasFuncs, t x, unsigned nfuncs) );
		int linfitwW( tMatObj* Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
			void __vf funcs(tVector BasFuncs, t x, unsigned nfuncs) );
		int linfit( const iVecObj& AStatus, cvta X, cvta Y, cmta MZ,
			void __vf funcs(tVector BasFuncs, t x, t y, unsigned nfuncs) );
		int linfitwW( tMatObj Covar, const iVecObj& AStatus,
			cvta X, cvta Y, cmta MZ, cmta MInvVar,
			void __vf funcs(tVector BasFuncs, t x, t y, unsigned nfuncs) );
		int linfitwW( tMatObj* Covar, const iVecObj& AStatus,
			cvta X, cvta Y, cmta MZ, cmta MInvVar,
			void __vf funcs(tVector BasFuncs, t x, t y, unsigned nfuncs) );
		void setLinfitNeglect( const t& Thresh ) const;
		t getLinfitNeglect() const;

		// nonlinfit functions with complete syntax:

		t nonlinfit( const iVecObj& AStatus, cvta X, cvta Y,
			void __vf modelfunc(tVector YModel, tVector XModel, ui size),
			void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar),
			VF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
		t nonlinfitwW( tMatObj Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
			void __vf modelfunc(tVector YModel, tVector XModel, ui size),
			void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar),
			VF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
		t nonlinfitwW( tMatObj* Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
			void __vf modelfunc(tVector YModel, tVector XModel, ui size),
			void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar),
			VF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
		t nonlinfit( const iVecObj& AStatus, cvta X, cvta Y, cmta MZ,
			void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
			void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar),
			MF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
		t nonlinfitwW( tMatObj Covar, const iVecObj& AStatus,
			cvta X, cvta Y, cmta MZ, cmta MInvVar,
			void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
			void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar),
			MF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
		t nonlinfitwW( tMatObj* Covar, const iVecObj& AStatus,
			cvta X, cvta Y, cmta MZ, cmta MInvVar,
			void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
			void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar),
			MF_NONLINFITWORKSPACE *FitWorkSpace, VF_NONLINFITOPTIONS *FitOpts );
		
		// simplified syntax:
		t nonlinfit( const iVecObj& AStatus, cvta X, cvta Y,
			 void __vf modelfunc(tVector YModel, tVector XModel, ui size),
			void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar) );
		t nonlinfitwW( tMatObj Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
			void __vf modelfunc(tVector YModel, tVector XModel, ui size),
			void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar) );
		t nonlinfitwW( tMatObj* Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
			void __vf modelfunc(tVector YModel, tVector XModel, ui size),
			void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar) );
		t nonlinfit( const iVecObj& AStatus, cvta X, cvta Y, cmta MZ,
			void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
			void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar) );
		t nonlinfitwW( tMatObj Covar, const iVecObj& AStatus,
			cvta X, cvta Y, cmta MZ, cmta MInvVar,
			void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
			void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar) );
		t nonlinfitwW( tMatObj* Covar, const iVecObj& AStatus,
			cvta X, cvta Y, cmta MZ, cmta MInvVar,
			void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
			void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar) );


		//defined by including cfMatObj.h
		void Rows_absmax(const matrix<fComplex>& MA);
		void Cols_absmax(const matrix<fComplex>& MA);
		void Rows_absmin(const matrix<fComplex>& MA);
		void Cols_absmin(const matrix<fComplex>& MA);

		#ifdef __VGRAPH_H
			void xyAutoPlot( cvta X, unsigned form, COLORREF color ) const
			{
				enforceSize();
				enforceSize(X.ui_size);
				VF_xyAutoPlot( X.vx_vect, vx_vect, ui_size, form, color ); }

			void xy2AutoPlot( cvta X1, unsigned form1, COLORREF color1,
			                  cvta X2, cvta Y2, unsigned form2, COLORREF color2 ) const
			{
				enforceSize();
				enforceSize(X1.ui_size);
				Y2.enforceSize(X2.ui_size);
				VF_xy2AutoPlot( X1.vx_vect, vx_vect, ui_size, form1, color1,
				                X2.vx_vect, Y2.vx_vect, X2.ui_size, form2, color2 ); }

			void yAutoPlot( unsigned form, COLORREF color ) const
			{
				enforceSize();
				VF_yAutoPlot( vx_vect, ui_size, form, color );	}

			void y2AutoPlot( unsigned form1, COLORREF color1,
			                 cvta Y2, unsigned form2, COLORREF color2 ) const
			{
				enforceSize();
				Y2.enforceSize();
				VF_y2AutoPlot( vx_vect, ui_size, form1, color1,
				               Y2.vx_vect, Y2.ui_size, form2, color2 );	}

			void xyDataPlot( cvta X, unsigned form, COLORREF color ) const
			{
				enforceSize();
				enforceSize(X.ui_size);
				VF_xyDataPlot( X.vx_vect, vx_vect, ui_size, form, color ); }

			void yDataPlot( unsigned form, COLORREF color ) const
			{
				enforceSize();
				VF_yDataPlot( vx_vect, ui_size, form, color );	}
		#endif   // __VGRAPH_H
	};  // end of class vector<T>


	inline void uiVecObj::sortind(cvta X, int dir)
	{
		enforceSize();
		VF_sortind(vx_vect,X.vx_vect,ui_size,dir);
	}

	inline void uiVecObj::searchV(cvta X, cvta Tab, int mode=0)
	{
		enforceSize();
		Tab.enforceSize();
		VF_searchV(vx_vect,X.vx_vect,ui_size,Tab.vx_vect,Tab.ui_size,mode);
	}

	inline ui uiVecObj::localmaxima(cvta X)
	{
		enforceSize();
		return VF_localmaxima(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::localminima(cvta X)
	{
		enforceSize();
		return VF_localminima(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::distribution(cvta Limits, cvta X, int mode=0)
	{
		enforceSize();
		X.enforceSize();
		return VF_distribution(vx_vect,Limits.vx_vect,ui_size,X.vx_vect,X.ui_size,mode);
	}

	inline ui uiVecObj::cmp_eq0ind(cvta X)
	{
		enforceSize();
		return VF_cmp_eq0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ne0ind(cvta X)
	{
		enforceSize();
		return VF_cmp_ne0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_le0ind(cvta X)
	{
		enforceSize();
		return VF_cmp_le0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_lt0ind(cvta X)
	{
		enforceSize();
		return VF_cmp_lt0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ge0ind(cvta X)
	{
		enforceSize();
		return VF_cmp_ge0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_gt0ind(cvta X)
	{
		enforceSize();
		return VF_cmp_gt0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_eqCind(cvta X, cta C)
	{
		enforceSize();
		return VF_cmp_eqCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_neCind(cvta X, cta C)
	{
		enforceSize();
		return VF_cmp_neCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_leCind(cvta X, cta C)
	{
		enforceSize();
		return VF_cmp_leCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_ltCind(cvta X, cta C)
	{
		enforceSize();
		return VF_cmp_ltCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_geCind(cvta X, cta C)
	{
		enforceSize();
		return VF_cmp_geCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_gtCind(cvta X, cta C)
	{
		enforceSize();
		return VF_cmp_gtCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_eqVind(cvta X, cvta Y)
	{
		enforceSize();
		return VF_cmp_eqVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_neVind(cvta X, cvta Y)
	{
		enforceSize();
		return VF_cmp_neVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_leVind(cvta X, cvta Y)
	{
		enforceSize();
		return VF_cmp_leVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ltVind(cvta X, cvta Y)
	{
		enforceSize();
		return VF_cmp_ltVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_geVind(cvta X, cvta Y)
	{
		enforceSize();
		return VF_cmp_geVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_gtVind(cvta X, cvta Y)
	{
		enforceSize();
		return VF_cmp_gtVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_inclrange0Cind(cvta X, cta C)
	{
		enforceSize();
		return VF_cmp_inclrange0Cind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_exclrange0Cind(cvta X, cta C)
	{
		enforceSize();
		return VF_cmp_exclrange0Cind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_inclrangeCCind(cvta X, cta CLo, cta CHi)
	{
		enforceSize();
		return VF_cmp_inclrangeCCind(vx_vect,X.vx_vect,ui_size,CLo,CHi);
	}

	inline ui uiVecObj::cmp_exclrangeCCind(cvta X, cta CLo, cta CHi)
	{
		enforceSize();
		return VF_cmp_exclrangeCCind(vx_vect,X.vx_vect,ui_size,CLo,CHi);
	}

#ifdef UBVECOBJ_H
	inline void fVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VF_accVUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void fVecObj::addVUB( const fVecObj& X, const ubVecObj& Y)
	{
		enforceSize();
		VF_addVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::subVUB( const fVecObj& X, const ubVecObj& Y)
	{
		enforceSize();
		VF_subVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::subrVUB( const fVecObj& X, const ubVecObj& Y)
	{
		enforceSize();
		VF_subrVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::mulVUB( const fVecObj& X, const ubVecObj& Y)
	{
		enforceSize();
		VF_mulVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::divVUB( const fVecObj& X, const ubVecObj& Y)
	{
		enforceSize();
		VF_divVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::divrVUB( const fVecObj& X, const ubVecObj& Y)
	{
		enforceSize();
		VF_divrVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::UBtoF(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoF(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::roundtoUB(const fVecObj& X)
	{
		enforceSize();
		return VF_roundtoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::floortoUB(const fVecObj& X)
	{
		enforceSize();
		return VF_floortoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::ceiltoUB(const fVecObj& X)
	{
		enforceSize();
		return VF_ceiltoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::choptoUB(const fVecObj& X)
	{
		enforceSize();
		return VF_choptoUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //UBVECOBJ_H

#ifdef USVECOBJ_H
	inline void fVecObj::accVUS(const usVecObj& X)
	{
		enforceSize();
		VF_accVUS(vx_vect,X.vx_vect,ui_size);
	}

	inline void fVecObj::addVUS( const fVecObj& X, const usVecObj& Y)
	{
		enforceSize();
		VF_addVUS(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::subVUS( const fVecObj& X, const usVecObj& Y)
	{
		enforceSize();
		VF_subVUS(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::subrVUS( const fVecObj& X, const usVecObj& Y)
	{
		enforceSize();
		VF_subrVUS(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::mulVUS( const fVecObj& X, const usVecObj& Y)
	{
		enforceSize();
		VF_mulVUS(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::divVUS( const fVecObj& X, const usVecObj& Y)
	{
		enforceSize();
		VF_divVUS(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::divrVUS( const fVecObj& X, const usVecObj& Y)
	{
		enforceSize();
		VF_divrVUS(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::UStoF(const usVecObj& X)
	{
		enforceSize();
		V_UStoF(vx_vect,X.vx_vect,ui_size);
	}

	inline int usVecObj::roundtoUS(const fVecObj& X)
	{
		enforceSize();
		return VF_roundtoUS(vx_vect,X.vx_vect,ui_size);
	}

	inline int usVecObj::floortoUS(const fVecObj& X)
	{
		enforceSize();
		return VF_floortoUS(vx_vect,X.vx_vect,ui_size);
	}

	inline int usVecObj::ceiltoUS(const fVecObj& X)
	{
		enforceSize();
		return VF_ceiltoUS(vx_vect,X.vx_vect,ui_size);
	}

	inline int usVecObj::choptoUS(const fVecObj& X)
	{
		enforceSize();
		return VF_choptoUS(vx_vect,X.vx_vect,ui_size);
	}
#endif //USVECOBJ

#ifdef UVECOBJ_H
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
#endif //UVECOBJ_H

#ifdef ULVECOBJ_H
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
#endif //ULVECOBJ_H

#ifdef BIVECOBJ_H
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
#endif //BIVECOBJ_H

#ifdef SIVECOBJ_H
	inline void fVecObj::accVSI(const siVecObj& X)
	{
		enforceSize();
		VF_accVSI(vx_vect,X.vx_vect,ui_size);
	}

	inline void fVecObj::SItoF(const siVecObj& X)
	{
		enforceSize();
		V_SItoF(vx_vect,X.vx_vect,ui_size);
	}

	inline int siVecObj::roundtoSI(const fVecObj& X)
	{
		enforceSize();
		return VF_roundtoSI(vx_vect,X.vx_vect,ui_size);
	}

	inline int siVecObj::floortoSI(const fVecObj& X)
	{
		enforceSize();
		return VF_floortoSI(vx_vect,X.vx_vect,ui_size);
	}

	inline int siVecObj::ceiltoSI(const fVecObj& X)
	{
		enforceSize();
		return VF_ceiltoSI(vx_vect,X.vx_vect,ui_size);
	}

	inline int siVecObj::choptoSI(const fVecObj& X)
	{
		enforceSize();
		return VF_choptoSI(vx_vect,X.vx_vect,ui_size);
	}
#endif //SIVECOBJ_H

#ifdef IVECOBJ_H
	inline void fVecObj::accVI(const iVecObj& X)
	{
		enforceSize();
		VF_accVI(vx_vect,X.vx_vect,ui_size);
	}

	inline void fVecObj::ItoF(const iVecObj& X)
	{
		enforceSize();
		V_ItoF(vx_vect,X.vx_vect,ui_size);
	}

	inline int iVecObj::roundtoI(const fVecObj& X)
	{
		enforceSize();
		return VF_roundtoI(vx_vect,X.vx_vect,ui_size);
	}

	inline int iVecObj::floortoI(const fVecObj& X)
	{
		enforceSize();
		return VF_floortoI(vx_vect,X.vx_vect,ui_size);
	}

	inline int iVecObj::ceiltoI(const fVecObj& X)
	{
		enforceSize();
		return VF_ceiltoI(vx_vect,X.vx_vect,ui_size);
	}

	inline int iVecObj::choptoI(const fVecObj& X)
	{
		enforceSize();
		return VF_choptoI(vx_vect,X.vx_vect,ui_size);
	}

	inline int fVecObj::mantexp(iVecObj* Exp, const fVecObj& X)
	{
		enforceSize();
		if(ui_size != Exp->ui_size) throw OptiVec_SizeErr();
		return VF_mantexp(vx_vect,Exp->vx_vect,X.vx_vect,ui_size);
	}

	inline int fVecObj::mantexp(iVecObj Exp, const fVecObj& X)
	{
		enforceSize();
		if(ui_size != Exp.ui_size) throw OptiVec_SizeErr();
		return VF_mantexp(vx_vect,Exp.vx_vect,X.vx_vect,ui_size);
	}

	inline int fVecObj::ipow2(const iVecObj& X)
	{
		enforceSize();
		return VF_ipow2(vx_vect,X.vx_vect,ui_size);
	}

	inline int fVecObj::ipow10(const iVecObj& X)
	{
		enforceSize();
		return VF_ipow10(vx_vect,X.vx_vect,ui_size);
	}

	inline int fVecObj::sinrpi(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_sinrpi(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::cosrpi(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_cosrpi(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::sincosrpi(fVecObj* Cos, const iVecObj& P, int q)
	{
		enforceSize();
		if(ui_size != Cos->ui_size) throw OptiVec_SizeErr();
		return VF_sincosrpi(vx_vect,Cos->vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::sincosrpi(fVecObj Cos, const iVecObj& P, int q)
	{
		enforceSize();
		if(ui_size != Cos.ui_size) throw OptiVec_SizeErr();
		return VF_sincosrpi(vx_vect,Cos.vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::tanrpi(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_tanrpi(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::cotrpi(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_cotrpi(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::secrpi(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_secrpi(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::cosecrpi(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_cosecrpi(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::sinrpi2(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_sinrpi2(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::cosrpi2(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_cosrpi2(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::sincosrpi2(fVecObj* Cos, const iVecObj& P, int q)
	{
		enforceSize();
		if(ui_size != Cos->ui_size) throw OptiVec_SizeErr();
		return VF_sincosrpi2(vx_vect,Cos->vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::sincosrpi2(fVecObj Cos, const iVecObj& P, int q)
	{
		enforceSize();
		if(ui_size != Cos.ui_size) throw OptiVec_SizeErr();
		return VF_sincosrpi2(vx_vect,Cos.vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::tanrpi2(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_tanrpi2(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::cotrpi2(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_cotrpi2(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::secrpi2(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_secrpi2(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::cosecrpi2(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_cosecrpi2(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::sinrpi3(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_sinrpi3(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::cosrpi3(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_cosrpi3(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::sincosrpi3(fVecObj* Cos, const iVecObj& P, int q)
	{
		enforceSize();
		if(ui_size != Cos->ui_size) throw OptiVec_SizeErr();
		return VF_sincosrpi3(vx_vect,Cos->vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::sincosrpi3(fVecObj Cos, const iVecObj& P, int q)
	{
		enforceSize();
		if(ui_size != Cos.ui_size) throw OptiVec_SizeErr();
		return VF_sincosrpi3(vx_vect,Cos.vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::tanrpi3(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_tanrpi3(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::cotrpi3(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_cotrpi3(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::secrpi3(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_secrpi3(vx_vect,P.vx_vect,ui_size,q);
	}

	inline int fVecObj::cosecrpi3(const iVecObj& P, int q)
	{
		enforceSize();
		return VF_cosecrpi3(vx_vect,P.vx_vect,ui_size,q);
	}
#endif //IVECOBJ_H

#ifdef LIVECOBJ_H
	inline void fVecObj::accVLI(const liVecObj& X)
	{
		enforceSize();
		VF_accVLI(vx_vect,X.vx_vect,ui_size);
	}

	inline void fVecObj::LItoF(const liVecObj& X)
	{
		enforceSize();
		V_LItoF(vx_vect,X.vx_vect,ui_size);
	}

	inline int liVecObj::roundtoLI(const fVecObj& X)
	{
		enforceSize();
		return VF_roundtoLI(vx_vect,X.vx_vect,ui_size);
	}

	inline int liVecObj::floortoLI(const fVecObj& X)
	{
		enforceSize();
		return VF_floortoLI(vx_vect,X.vx_vect,ui_size);
	}

	inline int liVecObj::ceiltoLI(const fVecObj& X)
	{
		enforceSize();
		return VF_ceiltoLI(vx_vect,X.vx_vect,ui_size);
	}

	inline int liVecObj::choptoLI(const fVecObj& X)
	{
		enforceSize();
		return VF_choptoLI(vx_vect,X.vx_vect,ui_size);
	}
#endif //LIVECOBJ_H

#ifdef QIVECOBJ_H
	inline void fVecObj::accVQI(const qiVecObj& X)
	{
		enforceSize();
		VF_accVQI(vx_vect,X.vx_vect,ui_size);
	}

	inline void fVecObj::QItoF(const qiVecObj& X)
	{
		enforceSize();
		V_QItoF(vx_vect,X.vx_vect,ui_size);
	}

	inline int qiVecObj::roundtoQI(const fVecObj& X)
	{
		enforceSize();
		return VF_roundtoQI(vx_vect,X.vx_vect,ui_size);
	}

	inline int qiVecObj::floortoQI(const fVecObj& X)
	{
		enforceSize();
		return VF_floortoQI(vx_vect,X.vx_vect,ui_size);
	}

	inline int qiVecObj::ceiltoQI(const fVecObj& X)
	{
		enforceSize();
		return VF_ceiltoQI(vx_vect,X.vx_vect,ui_size);
	}

	inline int qiVecObj::choptoQI(const fVecObj& X)
	{
		enforceSize();
		return VF_choptoQI(vx_vect,X.vx_vect,ui_size);
	}
#endif //QIVECOBJ_H

#ifdef DVECOBJ_H
	inline void fVecObj::DtoF(const dVecObj& X)
	{
		enforceSize();
		V_DtoF(vx_vect,X.vx_vect,ui_size);
	}

	inline void dVecObj::FtoD(const fVecObj& X)
	{
		enforceSize();
		V_FtoD(vx_vect,X.vx_vect,ui_size);
	}
#endif //DVECOBJ_H

#ifdef EVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers defined
	inline void fVecObj::EtoF(const eVecObj& X)
	{
		enforceSize();
		V_EtoF(vx_vect,X.vx_vect,ui_size);
	}

	inline void eVecObj::FtoE(const fVecObj& X)
	{
		enforceSize();
		V_FtoE(vx_vect,X.vx_vect,ui_size);
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

#ifdef PFVECOBJ_H
#endif //PFVECOBJ_H

#ifdef PDVECOBJ_H
#endif //PDVECOBJ_H

#ifdef PEVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
#endif //__BORLANDC__
#endif //PEVECOBJ_H

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
#undef tMatrix

#undef vtcplx
#undef tcplx

#undef tVecObj
#undef tMatObj
#ifdef __BORLANDC__
#pragma warn .inl
#endif

#define FVECOBJ_H
#endif //FVECOBJ_H
