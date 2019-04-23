/* cfVecObj.H

  object-oriented interface for OptiVec vector functions of type "fComplex"

  This file was written by Brian Dale, Case Western Reserve Univ.

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef CFVECOBJ_H

#include <VecObj.h>
#include <uiVecObj.h>
#include <fVecObj.h>

#define cvta const vector<fComplex>&
#define cmta const matrix<fComplex>&
#define cuia const ui&
#define cta  const fComplex&

#define vta  vector<fComplex>&
#define mta  matrix<fComplex>&
#define uia  ui&
#define ta   fComplex&

#define vt   vector<fComplex>
#define t    fComplex
#define tVector cfVector
#define tMatrix cfMatrix

#define vtbase vector<float>
#define tbase  float

#define tVecObj cfVecObj
#define tMatObj cfMatObj
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
		{	if(size){	vx_vect= VCF_vector(size);	ui_size= size;}
			else{	vx_vect= 0;	ui_size= 0;}}

		vector(cuia size, cta fill)
		{	if(!size) //size == 0
			{	vx_vect=0;	ui_size=0;}
			else if(!(fill.Re) && !(fill.Im)) //fill == 0.0
			{	vx_vect= VCF_vector0(size);	ui_size= size;}
			else
			{	vx_vect= VCF_vector(size);	ui_size= size;	VCF_equC(vx_vect,ui_size,fill);}}

		vector(cvta init)
		{	if(init.ui_size)
			{ vx_vect= VCF_vector(init.ui_size);	ui_size= init.ui_size;	VCF_equV(vx_vect, init.vx_vect, ui_size);}
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
				vx_vect= VCF_vector(size);
				ui_size= size;}}

		void setSize(cvta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_size != X.ui_size) //only allocate if different sizes
			{	if(vx_vect) V_free(vx_vect);
				vx_vect= VCF_vector(X.ui_size);
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
			VCF_equV(vx_vect, vect.vx_vect, ui_size);
			return *this;}

		vta operator=(cta scalar)
		{	enforceSize();
			VCF_equC(vx_vect, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		ta operator[](const int& index){return vx_vect[index];}

		vta operator+=(cvta X)
		{	enforceSize();
			VCF_accV(vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator+=(cta scalar)
		{	enforceSize();
			VCF_addC(vx_vect, vx_vect, ui_size, scalar);
			return *this;}

		vta operator*=(cvta X)
		{	enforceSize();
			VCF_mulV(vx_vect, vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator*=(cta scalar)
		{	enforceSize();
			VCF_mulC(vx_vect,vx_vect,ui_size,scalar);
			return *this;}

		vt operator+(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VCF_addV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator+(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VCF_addC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator+(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VCF_addC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator-(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VCF_subV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator-(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VCF_subC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator-(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VCF_subrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator*(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VCF_mulV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator*(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VCF_mulC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator*(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VCF_mulC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator/(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VCF_divV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator/(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VCF_divC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator/(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VCF_divrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
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
			if(size) vx_vect= VCF_vector(size);
			ui_size=size;
		}

		void vector0(ui size)
		{
			dealloc();
			if(size) vx_vect= VCF_vector0(size);
			ui_size=size;
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single vector elements
//
		t* Pelement(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VCF_Pelement(vx_vect,n);
		}

		t element(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VCF_element(vx_vect,n);
		}

		void getElement(t *y, ui n)
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VCF_getElement(y,vx_vect,n);
		}

		void setElement(ui n, cta C)
		{
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			VCF_setElement(vx_vect,n, C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//
		void equ0()
		{
			enforceSize();
			VCF_equ0(vx_vect,ui_size);
		}

		void equ1()
		{
			enforceSize();
			VCF_equ1(vx_vect,ui_size);
		}

		void equm1()
		{
			enforceSize();
			VCF_equm1(vx_vect, ui_size);
		}

		void equC(cta C)
		{
			enforceSize();
			VCF_equC(vx_vect, ui_size, C);
		}

		void equV(cvta X)
		{
			enforceSize();
			VCF_equV(vx_vect, X.vx_vect, ui_size);
		}

		void x_equV(cvta X, cta A, cta B)
		{
			enforceSize();
			VCFx_equV(vx_vect, X.vx_vect, ui_size, A, B);
		}

		void ramp(cta Start, cta Rise)
		{
			enforceSize();
			VCF_ramp(vx_vect, ui_size, Start, Rise);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VCF_random(vx_vect, ui_size, seed, Min, Max);
		}

		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VCF_randomLC(vx_vect, ui_size, seed, Min, Max, state);
		}

		//CtoReIm member of fVecObj

		void ReImtoC(const vtbase& Re, const vtbase& Im)
		{
			enforceSize();
			VF_ReImtoC(vx_vect, Re.vx_vect, Im.vx_vect, ui_size);
		}

		//CtoRe member of fVecObj

		void RetoC(const vtbase& Re)
		{
			enforceSize();
			VF_RetoC(vx_vect, Re.vx_vect, ui_size);
		}

		//CtoIm member of fVecObj

		void ImtoC(const vtbase& Im)
		{
			enforceSize();
			VF_ImtoC(vx_vect, Im.vx_vect, ui_size);
		}

		//CtoPolar member of fVecObj

		void PolartoC(const vtbase& Mag, const vtbase& Arg)
		{
			enforceSize();
			VF_PolartoC(vx_vect, Mag.vx_vect, Arg.vx_vect, ui_size);
		}

		void normtoC(cvta X)
		{
			enforceSize();
			VCF_normtoC(vx_vect, X.vx_vect, ui_size);
		}

		//CtoNorm member of fVecObj
		//CtoAbs member of fVecObj
		//CtoArg member of fVecObj

		//abs member of fVecObj
		//real member of fVecObj
		//imag member of fVecObj
		//arg member of fVecObj
		//norm member of fVecObj

		void polar(const vtbase& Mag, const vtbase& Arg){ PolartoC(Mag,Arg); }

		void complex(const vtbase& Re, const vtbase& Im){ ReImtoC(Re,Im); }

		//defined by including pfVecObj.h
		void PtoC(const pfVecObj& X);


/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//
		//defined by including cdVecObj.h
		void CDtoCF(const cdVecObj& X);

		//defined by including ceVecObj.h
		void CEtoCF(const ceVecObj& X);



/////////////////////////////////////////////////////////////////////////////////////////
//Index-oriented manipulations
//
		void reflect()
		{
			enforceSize();
			VCF_reflect(vx_vect, ui_size);
		}

		void _delete(ui pos)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VCF_delete(vx_vect, ui_size, pos);
		}

		void insert(ui pos, cta C)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VCF_insert(vx_vect, ui_size, pos, C);
		}

		void rev(cvta X)
		{
			enforceSize();
			VCF_rev(vx_vect, X.vx_vect, ui_size);
		}

		void rotate( cvta X, ssize_t pos )
		{
			enforceSize();
			VCF_rotate(vx_vect, X.vx_vect, ui_size, pos);
		}

		void rotate_buf( cvta X, ssize_t pos, cvta Buf )
		{
			enforceSize();
			VCF_rotate_buf(vx_vect, X.vx_vect, ui_size, pos, Buf.vx_vect);
		}

		void indpick(const uiVecObj& Ind, cvta X)
		{
			enforceSize();
			VCF_indpick(vx_vect, Ind.vx_vect, ui_size, X.vx_vect);
		}

		void indput(cvta X, const uiVecObj& Ind)
		{
			enforceSize();
			X.enforceSize();
			VCF_indput(vx_vect,X.vx_vect,Ind.vx_vect,X.ui_size);
		}

		void subvector(cvta X, ssize_t step, ui start=0)
		{
			enforceSize();
			if(vx_vect==X.vx_vect) throw OptiVec_Err();
			VCF_subvector(vx_vect, ui_size, X.vx_vect+start, step);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Functions of a sub-set of elements
//
		void subvector_equC(const ui& samp, cta C)
		{
			enforceSize();
			VCF_subvector_equC(vx_vect, ((ui_size-1)/samp)+1, samp, C);
		}

		void subvector_equV(const ui& samp, cvta X)
		{
			enforceSize();
			VCF_subvector_equV(vx_vect, ((ui_size-1)/samp)+1, samp, X.vx_vect);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//One-Dimensional Vector Operations
//

		tbase absmax() const
		{
			enforceSize();
			return VCF_absmax(vx_vect, ui_size);
		}

		tbase absmin() const
		{
			enforceSize();
			return VCF_absmin(vx_vect, ui_size);
		}

		tbase absmaxind(ui* Ind) const
		{
			enforceSize();
			return VCF_absmaxind(Ind, vx_vect, ui_size);
		}

		tbase absminind(ui* Ind) const
		{
			enforceSize();
			return VCF_absminind(Ind, vx_vect, ui_size);
		}

		t maxReIm() const
		{
			enforceSize();
			return VCF_maxReIm(vx_vect, ui_size);
		}

		t minReIm() const
		{
			enforceSize();
			return VCF_minReIm(vx_vect, ui_size);
		}

		t absmaxReIm() const
		{
			enforceSize();
			return VCF_absmaxReIm(vx_vect, ui_size);
		}

		t absminReIm() const
		{
			enforceSize();
			return VCF_absminReIm(vx_vect, ui_size);
		}

		t cabsmax() const
		{
			enforceSize();
			return VCF_cabsmax(vx_vect, ui_size);
		}

		t cabsmin() const
		{
			enforceSize();
			return VCF_cabsmin(vx_vect, ui_size);
		}

		t sabsmax() const
		{
			enforceSize();
			return VCF_sabsmax(vx_vect, ui_size);
		}

		t sabsmin() const
		{
			enforceSize();
			return VCF_sabsmin(vx_vect, ui_size);
		}

		t sum() const
		{
			enforceSize();
			return VCF_sum(vx_vect, ui_size);
		}

		t prod() const
		{
			enforceSize();
			return VCF_prod(vx_vect, ui_size);
		}

		t mean() const
		{
			enforceSize();
			return VCF_mean(vx_vect, ui_size);
		}

		t meanwW(const vtbase& Wt) const
		{
			enforceSize();
			return VCF_meanwW(vx_vect, Wt.vx_vect, ui_size);
		}

		t scalprod(cvta X) const
		{
			enforceSize();
			return VCF_scalprod(vx_vect, X.vx_vect, ui_size);
		}

		void runsum(cvta X)
		{
			enforceSize();
			VCF_runsum(vx_vect, X.vx_vect, ui_size);
		}

		void runprod(cvta X)
		{
			enforceSize();
			VCF_runprod(vx_vect, X.vx_vect, ui_size);
		}

		int iselementC(cta C) const
		{
			enforceSize();
			return VCF_iselementC(vx_vect, ui_size, C);
		}

		ui iselementV(cvta X, cvta Tab)
		{
			enforceSize();
			Tab.enforceSize();
			return VCF_iselementV(vx_vect, X.vx_vect,
				ui_size, Tab.vx_vect, Tab.ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Statistical Functions and Building Blocks
//


/////////////////////////////////////////////////////////////////////////////////////////
//Fourier Transforms, Convolutions, Filtering
//
		void p_FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VCFp_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		void p_FFTtoC(const vtbase& X)
		{
			enforceSize();
			VFp_FFTtoC(vx_vect,X.vx_vect,ui_size);
		}

		void p_filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VCFp_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}

		void b_FFT(cvta X, int dir, vta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			VCFb_FFT(vx_vect,X.vx_vect,ui_size,dir,Buf.vx_vect);
		}

		void b_FFTtoC(const vtbase& X, vta Buf)
		{
			enforceSize();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			VFb_FFTtoC(vx_vect,X.vx_vect,ui_size,Buf.vx_vect);
		}

		void l_FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VCFl_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		void l_FFTtoC(const vtbase& X)
		{
			enforceSize();
			VFl_FFTtoC(vx_vect,X.vx_vect,ui_size);
		}

		void l_filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VCFl_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}

		void s_FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VCFs_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		void s_FFTtoC(const vtbase& X)
		{
			enforceSize();
			VFs_FFTtoC(vx_vect,X.vx_vect,ui_size);
		}

		void s_filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VCFs_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}

		void FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VCF_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		void FFTtoC(const vtbase& X)
		{
			enforceSize();
			VF_FFTtoC(vx_vect,X.vx_vect,ui_size);
		}

		void filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VCF_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Analysis
//


/////////////////////////////////////////////////////////////////////////////////////////
//Geometrical Vector Arithmetics
//


/////////////////////////////////////////////////////////////////////////////////////////
//Input and Output
//
		void fprint(FILE* stream, const unsigned& nperline, const unsigned& linewidth) const
		{
			enforceSize();
			VCF_fprint(stream, vx_vect, ui_size, nperline, linewidth);
		}

		void  cprint( const unsigned& nperline ) const
		{
			enforceSize();
			VCF_cprint( vx_vect, ui_size, nperline);
		}

		void print(const unsigned& npl) const
		{
			enforceSize();
			VCF_print(vx_vect, ui_size, npl);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			VCF_write(stream, vx_vect, ui_size);
		}

		void read(FILE* stream)
		{
			enforceSize();
			VCF_read(vx_vect, ui_size, stream);
		}


//nwrite
//nread

		void setWriteFormat(char* formatString) const
		{
			VCF_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VCF_setWriteSeparate(sepString);
		}

//setNWriteSeparate

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_size,sizeof(ui),1,stream);
			VCF_store(stream,vx_vect,ui_size);
		}

		void recall(FILE* stream)
		{
			ui sz;
			fread(&sz,sizeof(ui),1,stream);
			setSize(sz);
			VCF_recall(vx_vect,ui_size,stream);
		}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//from VXmath.h
//


/////////////////////////////////////////////////////////////////////////////////////////
//Rounding
//


/////////////////////////////////////////////////////////////////////////////////////////
//Comparisons
//

		ui cmp_eq0(cvta X)
		{
			enforceSize();
			return VCF_cmp_eq0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_ne0(cvta X)
		{
			enforceSize();
			return VCF_cmp_ne0(vx_vect,X.vx_vect,ui_size);
		}


		ui cmp_eqC(cvta X, cta C)
		{
			enforceSize();
			return VCF_cmp_eqC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_neC(cvta X, cta C)
		{
			enforceSize();
			return VCF_cmp_neC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_eqV(cvta X, cvta Y)
		{
			enforceSize();
			return VCF_cmp_eqV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_neV(cvta X, cvta Y)
		{
			enforceSize();
			return VCF_cmp_neV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_eq0()  const
		{
			enforceSize();
			return VCF_cnt_eq0(vx_vect, ui_size);
		}

		ui cnt_ne0()  const
		{
			enforceSize();
			return VCF_cnt_ne0(vx_vect, ui_size);
		}

		ui cnt_eqC(cta C) const
		{
			enforceSize();
			return VCF_cnt_eqC(vx_vect,ui_size,C);
		}

		ui cnt_neC(cta C) const
		{
			enforceSize();
			return VCF_cnt_neC(vx_vect,ui_size,C);
		}

		ui cnt_eqV(cvta Y) const
		{
			enforceSize();
			return VCF_cnt_eqV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_neV(cvta Y) const
		{
			enforceSize();
			return VCF_cnt_neV(vx_vect,Y.vx_vect,ui_size);
		}

		//indexed comparisons are members of uiVecObj


/////////////////////////////////////////////////////////////////////////////////////////
//Standard Arithmetics or Basic Arithmetics
//
		void limit(cvta X, cta Min, cta Max)
		{
			enforceSize();
			VCF_limit( vx_vect, X.vx_vect, ui_size, Min, Max);
		}

		void flush0(cvta X, cta AbsMin)
		{
			enforceSize();
			VCF_flush0( vx_vect, X.vx_vect, ui_size, AbsMin);
		}

		void flushInv(cvta X, cta AbsMin)
		{
			enforceSize();
			VCF_flushInv(vx_vect, X.vx_vect, ui_size, AbsMin);
		}

		void replaceNAN(cvta X, cta C)
		{
			enforceSize();
			VCF_replaceNAN( vx_vect, X.vx_vect, ui_size, C);
		}

		//x_equV defined above
		 
		void addC(cvta X, cta C)
		{
			enforceSize();
			VCF_addC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subC(cvta X, cta C)
		{
			enforceSize();
			VCF_subC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subrC(cvta X, cta C)
		{
			enforceSize();
			VCF_subrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void mulC(cvta X, cta C)
		{
			enforceSize();
			VCF_mulC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divC(cvta X, cta C)
		{
			enforceSize();
			VCF_divC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divrC(cvta X, cta C)
		{
			enforceSize();
			VCF_divrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void x_divrC(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			VCFx_divrC(vx_vect, X.vx_vect, ui_size, A, B, C);
		}

		void addReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCF_addReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCF_subReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subrReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCF_subrReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void mulReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCF_addReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCF_addReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divrReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCF_addReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void addV(cvta X, cvta Y)
		{
			enforceSize();
			VCF_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subV(cvta X, cvta Y)
		{
			enforceSize();
			VCF_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subrV(cvta X, cvta Y)
		{
			enforceSize();
			VCF_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void mulV(cvta X, cvta Y)
		{
			enforceSize();
			VCF_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divV(cvta X, cvta Y)
		{
			enforceSize();
			VCF_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divrV(cvta X, cvta Y)
		{
			enforceSize();
			VCF_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void addReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCF_addReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCF_subReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subrReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCF_subrReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void mulReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCF_mulReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCF_divReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divrReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCF_divrReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

                void mulVconj(cvta X, cvta Y)
		{
			enforceSize();
                        VCF_mulVconj(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void CaddV(cvta X, cvta Y, cta C)
		{
			enforceSize();
			VCF_CaddV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, C);
		}

		void x_addV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCFx_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_subV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCFx_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_subrV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCFx_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_mulV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCFx_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_divV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCFx_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_divrV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCFx_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_addReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCFx_addReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_subReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCFx_subReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_subrReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCFx_subrReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_mulReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCFx_mulReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_divReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCFx_divReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_divrReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCFx_divrReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

                void x_mulVconj(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
                        VCFx_mulVconj(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void lincomb(cvta X, cvta Y, cta CX, cta CY)
		{
			enforceSize();
			VCF_lincomb( vx_vect, X.vx_vect, Y.vx_vect, ui_size, CX, CY);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Accumulation
//
		void accV(cvta X)
		{
			enforceSize();
			VCF_accV(vx_vect,X.vx_vect,ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Bit-wise operations
//


/////////////////////////////////////////////////////////////////////////////////////////
//Functions of a sub-set of elements
//
		//subvector_equC, subvector_equV defined above

		void subvector_addC(const ui& samp, cta C)
		{
			enforceSize();
			VCF_subvector_addC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_subC(const ui& samp, cta C)
		{
			enforceSize();
			VCF_subvector_subC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_subrC(const ui& samp, cta C)
		{
			enforceSize();
			VCF_subvector_subrC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_mulC(const ui& samp, cta C)
		{
			enforceSize();
			VCF_subvector_mulC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_divC(const ui& samp, cta C)
		{
			enforceSize();
			VCF_subvector_divC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_divrC(const ui& samp, cta C)
		{
			enforceSize();
			VCF_subvector_divrC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_addV(const ui& samp, cvta X)
		{
			enforceSize();
			VCF_subvector_addV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_subV(const ui& samp, cvta X)
		{
			enforceSize();
			VCF_subvector_subV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_subrV(const ui& samp, cvta X)
		{
			enforceSize();
			VCF_subvector_subrV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_mulV(const ui& samp, cvta X)
		{
			enforceSize();
			VCF_subvector_mulV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_divV(const ui& samp, cvta X)
		{
			enforceSize();
			VCF_subvector_divV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_divrV(const ui& samp, cvta X)
		{
			enforceSize();
			VCF_subvector_divrV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}



/////////////////////////////////////////////////////////////////////////////////////////
//Mathematical Functions
//
		int neg(cvta X)
		{
			enforceSize();
			return VCF_neg(vx_vect, X.vx_vect, ui_size);
		}

		int conj(cvta X)
		{
			enforceSize();
			return VCF_conj(vx_vect,X.vx_vect,ui_size);
		}

		//abs defined above

		int inv(cvta X)
		{
			enforceSize();
			return VCF_inv(vx_vect, X.vx_vect, ui_size);
		}

		int x_inv(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCFx_inv(vx_vect, X.vx_vect, ui_size, A, B);
		}

		int square(cvta X)
		{
			enforceSize();
			return VCF_square(vx_vect,X.vx_vect,ui_size);
		}

		int x_square(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCFx_square(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int cubic(cvta X)
		{
			enforceSize();
			return VCF_cubic(vx_vect,X.vx_vect,ui_size);
		}

		int x_cubic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCFx_cubic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int quartic(cvta X)
		{
			enforceSize();
			return VCF_quartic(vx_vect,X.vx_vect,ui_size);
		}

		int x_quartic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCFx_quartic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int ipow(cvta X, int pow)
		{
			enforceSize();
			return VCF_ipow(vx_vect, X.vx_vect, ui_size, pow);
		}

		int x_ipow(cvta X, int pow, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_ipow(vx_vect, X.vx_vect, ui_size, pow, A, B, C);
		}

		int u_square(cvta X)
		{
			enforceSize();
			return VCFu_square(vx_vect,X.vx_vect,ui_size);
		}

		int ux_square(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCFux_square(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int u_cubic(cvta X)
		{
			enforceSize();
			return VCFu_cubic(vx_vect,X.vx_vect,ui_size);
		}

		int ux_cubic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCFux_cubic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int u_quartic(cvta X)
		{
			enforceSize();
			return VCFu_quartic(vx_vect,X.vx_vect,ui_size);
		}

		int ux_quartic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCFux_quartic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int u_ipow(cvta X, int pow)
		{
			enforceSize();
			return VCFu_ipow(vx_vect, X.vx_vect, ui_size, pow);
		}

		int ux_ipow(cvta X, int pow, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFux_ipow(vx_vect, X.vx_vect, ui_size, pow, A, B, C);
		}

		int pow(cvta X, cta expo)
		{
			enforceSize();
			return VCF_pow(vx_vect,X.vx_vect,ui_size,expo);
		}

		int x_pow(cvta X, cta expo, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_pow(vx_vect,X.vx_vect,ui_size,expo,A,B,C);
		}

		int powReExpo(cvta X, const tbase& expo)
		{
			enforceSize();
			return VCF_powReExpo(vx_vect,X.vx_vect,ui_size,expo);
		}

		int x_powReExpo(cvta X, const tbase& expo, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_powReExpo(vx_vect,X.vx_vect,ui_size,expo,A,B,C);
		}

		int sqrt(cvta X)
		{
			enforceSize();
			return VCF_sqrt(vx_vect,X.vx_vect,ui_size);
		}

		int x_sqrt(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_sqrt(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int log(cvta X)
		{
			enforceSize();
			return VCF_log(vx_vect,X.vx_vect,ui_size);
		}

		int log2(cvta X)
		{
			enforceSize();
			return VCF_log2(vx_vect,X.vx_vect,ui_size);
		}

		int log10(cvta X)
		{
			enforceSize();
			return VCF_log10(vx_vect,X.vx_vect,ui_size);
		}

		int ln(cvta X)
		{
			return log(X);
		}

		int x_log(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_log(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int x_log2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_log2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int x_log10(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_log10(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int x_ln(cvta X, cta A, cta B, cta C)
		{
			return x_log(X,A,B,C);
		}

		//defined by including pfVecObj.h
		int logtoC(const pfVecObj& X);

		//defined by including pfVecObj.h
		int log2toC(const pfVecObj& X);

		//defined by including pfVecObj.h
		int log10toC(const pfVecObj& X);

		int lntoC(const pfVecObj& X){ return logtoC(X); }

		int exp(cvta X)
		{
			enforceSize();
			return VCF_exp(vx_vect,X.vx_vect,ui_size);
		}

		int x_exp(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_exp(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int expArbBase(cvta X, cta Base)
		{
			enforceSize();
			return VCF_expArbBase(vx_vect,X.vx_vect,ui_size,Base);
		}

		int x_expArbBase(cvta X, cta Base, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_expArbBase(vx_vect,X.vx_vect,ui_size,Base,A,B,C);
		}

		int sin(cvta X)
		{
			enforceSize();
			return VCF_sin(vx_vect,X.vx_vect,ui_size);
		}

		int x_sin(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_sin(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cos(cvta X)
		{
			enforceSize();
			return VCF_cos(vx_vect,X.vx_vect,ui_size);
		}

		int x_cos(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_cos(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int tan(cvta X)
		{
			enforceSize();
			return VCF_tan(vx_vect,X.vx_vect,ui_size);
		}

		int x_tan(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_tan(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int asin(cvta X)
		{
			enforceSize();
			return VCF_asin(vx_vect,X.vx_vect,ui_size);
		}

		int x_asin(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_asin(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int acos(cvta X)
		{
			enforceSize();
			return VCF_acos(vx_vect,X.vx_vect,ui_size);
		}

		int x_acos(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_acos(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int atan(cvta X)
		{
			enforceSize();
			return VCF_atan(vx_vect,X.vx_vect,ui_size);
		}

		int x_atan(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_atan(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sinh(cvta X)
		{
			enforceSize();
			return VCF_sinh(vx_vect,X.vx_vect,ui_size);
		}

		int x_sinh(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_sinh(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cosh(cvta X)
		{
			enforceSize();
			return VCF_cosh(vx_vect,X.vx_vect,ui_size);
		}

		int x_cosh(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_cosh(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int tanh(cvta X)
		{
			enforceSize();
			return VCF_tanh(vx_vect,X.vx_vect,ui_size);
		}

		int x_tanh(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCFx_tanh(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		//defined by including cfMatObj.h
		vt operator*(cmta MY);
		void Row_extract(cmta MA, const ui iRow);
		void Col_extract(cmta MA, const ui iCol);
		void Dia_extract(cmta MA);
		void Rows_maxReIm(cmta MA);
		void Cols_maxReIm(cmta MA);
		void Rows_minReIm(cmta MA);
		void Cols_minReIm(cmta MA);
		void Rows_absmaxReIm(cmta MA);
		void Cols_absmaxReIm(cmta MA);
		void Rows_absminReIm(cmta MA);
		void Cols_absminReIm(cmta MA);
		void Rows_sabsmax(cmta MA);
		void Cols_sabsmax(cmta MA);
		void Rows_sabsmin(cmta MA);
		void Cols_sabsmin(cmta MA);
		void Rows_cabsmax(cmta MA);
		void Cols_cabsmax(cmta MA);
		void Rows_cabsmin(cmta MA);
		void Cols_cabsmin(cmta MA);
		void Rows_sum(cmta MA);
		void Cols_sum(cmta MA);
		void Rows_prod(cmta MA);
		void Cols_prod(cmta MA);
		void MmulV( cmta MA, cvta X );
		void MTmulV( cmta MA, cvta X );
		void mulM( cvta X, cmta MA );
		void mulMT( cvta X, cmta MA );
		void LUsolve( cmta MLU, cvta B, const uiVecObj& Ind );
		void LUimprove( cvta B, cmta MA, cmta MLU, const uiVecObj& Ind );
		int solve( cmta MA, cvta B );

            #ifdef __VGRAPH_H
                void autoPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VCF_autoPlot( vx_vect, ui_size, form, color );
                }

                void _2AutoPlot( unsigned form1, COLORREF color1,
                       cvta X2, unsigned form2, COLORREF color2 ) const
                {
                    enforceSize();
                    X2.enforceSize();
                    VCF_2AutoPlot( vx_vect,    ui_size, form1, color1,
                                X2.vx_vect, X2.ui_size, form2, color2 );
                }

                void dataPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VCF_dataPlot( vx_vect, ui_size, form, color );
                }
            #endif // __VGRAPH_H
	};


	inline ui uiVecObj::cmp_eq0ind(cvta X)
	{
		enforceSize();
		return VCF_cmp_eq0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ne0ind(cvta X)
	{
		enforceSize();
		return VCF_cmp_ne0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_eqCind(cvta X, cta C)
	{
		enforceSize();
		return VCF_cmp_eqCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_neCind(cvta X, cta C)
	{
		enforceSize();
		return VCF_cmp_neCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_eqVind(cvta X, cvta Y)
	{
		enforceSize();
		return VCF_cmp_eqVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_neVind(cvta X, cvta Y)
	{
		enforceSize();
		return VCF_cmp_neVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

#ifdef UBVECOBJ_H
#endif //UBVECOBJ_H

#ifdef USVECOBJ_H
#endif //USVECOBJ

#ifdef UVECOBJ_H
#endif //UVECOBJ_H

#ifdef ULVECOBJ_H
#endif //ULVECOBJ_H

#ifdef BIVECOBJ_H
#endif //BIVECOBJ_H

#ifdef SIVECOBJ_H
#endif //SIVECOBJ_H

#ifdef IVECOBJ_H
#endif //IVECOBJ_H

#ifdef LIVECOBJ_H
#endif //LIVECOBJ_H

#ifdef QIVECOBJ_H
#endif //QIVECOBJ_H

#ifdef FVECOBJ_H
	inline void vtbase::CtoReIm(vtbase* Im,cvta X)
	{
		enforceSize();
		if(ui_size != Im->ui_size) throw OptiVec_SizeErr();
		VF_CtoReIm(vx_vect, Im->vx_vect, X.vx_vect, ui_size);
	}

	inline void vtbase::CtoReIm(vtbase Im,cvta X)
	{
		enforceSize();
		if(ui_size != Im.ui_size) throw OptiVec_SizeErr();
		VF_CtoReIm(vx_vect, Im.vx_vect, X.vx_vect, ui_size);
	}

	inline void vtbase::CtoRe(cvta cplx)
	{
		enforceSize();
		VF_CtoRe(vx_vect, cplx.vx_vect, ui_size);
	}

	inline void vtbase::CtoIm(cvta cplx)
	{
		enforceSize();
		VF_CtoIm(vx_vect, cplx.vx_vect, ui_size);
	}

	inline void vtbase::CtoPolar(vtbase* Arg, cvta X)
	{
		enforceSize();
		if(ui_size != Arg->ui_size) throw OptiVec_SizeErr();
		VF_CtoReIm(vx_vect, Arg->vx_vect, X.vx_vect, ui_size);
	}

	inline void vtbase::CtoPolar(vtbase Arg, cvta X)
	{
		enforceSize();
		if(ui_size != Arg.ui_size) throw OptiVec_SizeErr();
		VF_CtoReIm(vx_vect, Arg.vx_vect, X.vx_vect, ui_size);
	}

	inline void vtbase::CtoNorm(cvta cplx)
	{
		enforceSize();
		VF_CtoNorm(vx_vect, cplx.vx_vect, ui_size);
	}

	inline void vtbase::CtoAbs(cvta cplx)
	{
		enforceSize();
		VF_CtoAbs(vx_vect, cplx.vx_vect, ui_size);
	}

	inline void vtbase::CtoArg(cvta cplx)
	{
		enforceSize();
		VF_CtoArg(vx_vect, cplx.vx_vect, ui_size);
	}

	inline int vtbase::abs(cvta cplx)
	{
		enforceSize();
		return VCF_abs(vx_vect, cplx.vx_vect, ui_size);
	}
#endif //FVECOBJ_H

#ifdef DVECOBJ_H
#endif //DVECOBJ_H

#ifdef EVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
#endif //__BORLANDC__
#endif //EVECOBJ_H

#ifdef CDVECOBJ_H
	inline void cfVecObj::CDtoCF(const cdVecObj& X)
	{
		enforceSize();
		V_CDtoCF(vx_vect,X.vx_vect,ui_size);
	}

	inline void cdVecObj::CFtoCD(const cfVecObj& X)
	{
		enforceSize();
		V_CFtoCD(vx_vect,X.vx_vect,ui_size);
	}
#endif //CDVECOBJ_H

#ifdef CEVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
	inline void cfVecObj::CEtoCF(const ceVecObj& X)
	{
		enforceSize();
		V_CEtoCF(vx_vect,X.vx_vect,ui_size);
	}

	inline void ceVecObj::CFtoCE(const cfVecObj& X)
	{
		enforceSize();
		V_CFtoCE(vx_vect,X.vx_vect,ui_size);
	}
#endif //__BORLANDC__
#endif //CEVECOBJ_H

#ifdef PFVECOBJ_H
	inline void pfVecObj::CtoP(const cfVecObj& X)
	{
		enforceSize();
		VF_CtoP(vx_vect,X.vx_vect,ui_size);
	}

	inline void cfVecObj::PtoC(const pfVecObj& X)
	{
		enforceSize();
		VF_PtoC(vx_vect,X.vx_vect,ui_size);
	}

	inline int cfVecObj::logtoC(const pfVecObj& X)
	{
		enforceSize();
		VPF_logtoC(vx_vect,X.vx_vect,ui_size);
	}

	inline int cfVecObj::log2toC(const pfVecObj& X)
	{
		enforceSize();
		VPF_log2toC(vx_vect,X.vx_vect,ui_size);
	}

	inline int cfVecObj::log10toC(const pfVecObj& X)
	{
		enforceSize();
		VPF_log10toC(vx_vect,X.vx_vect,ui_size);
	}

	inline int pfVecObj::exptoP(const cfVecObj& X)
	{
		enforceSize();
		VCF_exptoP(vx_vect,X.vx_vect,ui_size);
	}
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
#undef mta
#undef uia
#undef ta

#undef vt
#undef t
#undef tVector
#undef tMatrix

#undef vtbase
#undef tbase

#undef tVecObj
#undef tMatObj
#ifdef __BORLANDC__
#pragma warn .inl
#endif

#define CFVECOBJ_H
#endif //CFVECOBJ_H
