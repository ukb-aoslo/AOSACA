/* cdVecObj.H

  object-oriented interface for OptiVec vector functions of type "dComplex"

  This file was written by Brian Dale, Case Western Reserve Univ.

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef CDVECOBJ_H

#include <VecObj.h>
#include <uiVecObj.h>
#include <dVecObj.h>

#define cvta const vector<dComplex>&
#define cmta const matrix<dComplex>&
#define cuia const ui&
#define cta  const dComplex&

#define vta  vector<dComplex>&
#define uia  ui&
#define ta   dComplex&

#define vt   vector<dComplex>
#define t    dComplex
#define tVector cdVector
#define tMatrix cdMatrix

#define vtbase vector<double>
#define tbase  double

#define tVecObj cdVecObj
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
		{	if(size){	vx_vect= VCD_vector(size);	ui_size= size;}
			else{	vx_vect= 0;	ui_size= 0;}}

		vector(cuia size, cta fill)
		{	if(!size) //size == 0
			{	vx_vect=0;	ui_size=0;}
			else if(!(fill.Re) && !(fill.Im)) //fill == 0.0
			{	vx_vect= VCD_vector0(size);	ui_size= size;}
			else
			{	vx_vect= VCD_vector(size);	ui_size= size;	VCD_equC(vx_vect,ui_size,fill);}}

		vector(cvta init)
		{	if(init.ui_size)
			{ vx_vect= VCD_vector(init.ui_size);	ui_size= init.ui_size;	VCD_equV(vx_vect, init.vx_vect, ui_size);}
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
				vx_vect= VCD_vector(size);
				ui_size= size;}}

		void setSize(cvta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_size != X.ui_size) //only allocate if different sizes
			{	if(vx_vect) V_free(vx_vect);
				vx_vect= VCD_vector(X.ui_size);
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
			VCD_equV(vx_vect, vect.vx_vect, ui_size);
			return *this;}

		vta operator=(cta scalar)
		{	enforceSize();
			VCD_equC(vx_vect, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		ta operator[](const int& index){return vx_vect[index];}

		vta operator+=(cvta X)
		{	enforceSize();
			VCD_accV(vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator+=(cta scalar)
		{	enforceSize();
			VCD_addC(vx_vect, vx_vect, ui_size, scalar);
			return *this;}

		vta operator*=(cvta X)
		{	enforceSize();
			VCD_mulV(vx_vect, vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator*=(cta scalar)
		{	enforceSize();
			VCD_mulC(vx_vect,vx_vect,ui_size,scalar);
			return *this;}

		vt operator+(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VCD_addV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator+(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VCD_addC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator+(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VCD_addC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator-(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VCD_subV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator-(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VCD_subC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator-(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VCD_subrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator*(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VCD_mulV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator*(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VCD_mulC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator*(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VCD_mulC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator/(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VCD_divV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator/(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VCD_divC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator/(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VCD_divrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
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
			if(size) vx_vect= VCD_vector(size);
			ui_size=size;
		}

		void vector0(ui size)
		{
			dealloc();
			if(size) vx_vect= VCD_vector0(size);
			ui_size=size;
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single vector elements
//
		t* Pelement(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VCD_Pelement(vx_vect,n);
		}

		t element(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VCD_element(vx_vect,n);
		}

		void getElement(t *y, ui n)
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VCD_getElement(y,vx_vect,n);
		}

		void setElement(ui n, cta C)
		{
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			VCD_setElement(vx_vect,n, C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//

		void equ0()
		{
			enforceSize();
			VCD_equ0(vx_vect,ui_size);
		}

		void equ1()
		{
			enforceSize();
			VCD_equ1(vx_vect,ui_size);
		}

		void equm1()
		{
			enforceSize();
			VCD_equm1(vx_vect, ui_size);
		}

		void equC(cta C)
		{
			enforceSize();
			VCD_equC(vx_vect, ui_size, C);
		}

		void equV(cvta X)
		{
			enforceSize();
			VCD_equV(vx_vect, X.vx_vect, ui_size);
		}

		void x_equV(cvta X, cta A, cta B)
		{
			enforceSize();
			VCDx_equV(vx_vect, X.vx_vect, ui_size, A, B);
		}

		void ramp(cta Start, cta Rise)
		{
			enforceSize();
			VCD_ramp(vx_vect, ui_size, Start, Rise);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VCD_random(vx_vect, ui_size, seed, Min, Max);
		}
        
		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VCD_randomLC(vx_vect, ui_size, seed, Min, Max, state);
		}

		//CtoReIm member of dVecObj

		void ReImtoC(const vtbase& Re, const vtbase& Im)
		{
			enforceSize();
			VD_ReImtoC(vx_vect, Re.vx_vect, Im.vx_vect, ui_size);
		}

		//CtoRe member of dVecObj

		void RetoC(const vtbase& Re)
		{
			enforceSize();
			VD_RetoC(vx_vect, Re.vx_vect, ui_size);
		}

		//CtoIm member of dVecObj

		void ImtoC(const vtbase& Im)
		{
			enforceSize();
			VD_ImtoC(vx_vect, Im.vx_vect, ui_size);
		}

		//CtoPolar member of dVecObj

		void PolartoC(const vtbase& Mag, const vtbase& Arg)
		{
			enforceSize();
			VD_PolartoC(vx_vect, Mag.vx_vect, Arg.vx_vect, ui_size);
		}

                void normtoC(cvta X)
		{
			enforceSize();
                        VCD_normtoC(vx_vect, X.vx_vect, ui_size);
		}

		//CtoNorm member of dVecObj
		//CtoAbs member of dVecObj
		//CtoArg member of dVecObj

		//abs member of dVecObj
		//real member of dVecObj
		//imag member of dVecObj
		//arg member of dVecObj
		//norm member of dVecObj

		void polar(const vtbase& Mag, const vtbase& Arg){ PolartoC(Mag,Arg); }

		void complex(const vtbase& Re, const vtbase& Im){ ReImtoC(Re,Im); }

		//defined by including pdVecObj.h
		void PtoC(const pdVecObj& X);


/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//
		//defined by including cfVecObj.h
		void CFtoCD(const cfVecObj& X);

		//define in ceVecObj.h
		void CEtoCD(const ceVecObj& X);

#if !(defined __BORLANDC__) || (defined _WIN64) //80-bit numbers not supported
		void CFtoCE(const cfVecObj& X)
		{
			CFtoCD(X);
		}
		void CDtoCE(const cdVecObj& X)
		{
			equV(X);
		}
#endif //__BORLANDC__



/////////////////////////////////////////////////////////////////////////////////////////
//Index-oriented manipulations
//
		void reflect()
		{
			enforceSize();
			VCD_reflect(vx_vect, ui_size);
		}

		void _delete(ui pos)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VCD_delete(vx_vect, ui_size, pos);
		}

		void insert(ui pos, cta C)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VCD_insert(vx_vect, ui_size, pos, C);
		}

		void rev(cvta X)
		{
			enforceSize();
			VCD_rev(vx_vect, X.vx_vect, ui_size);
		}

		void rotate( cvta X, ssize_t pos )
		{
			enforceSize();
			VCD_rotate(vx_vect, X.vx_vect, ui_size, pos);
		}

		void rotate_buf( cvta X, ssize_t pos, cvta Buf )
		{
			enforceSize();
			VCD_rotate_buf(vx_vect, X.vx_vect, ui_size, pos, Buf.vx_vect);
		}

		void indpick(const uiVecObj& Ind, cvta X)
		{
			enforceSize();
			VCD_indpick(vx_vect, Ind.vx_vect, ui_size, X.vx_vect);
		}

		void indput(cvta X, const uiVecObj& Ind)
		{
			enforceSize();
			X.enforceSize();
			VCD_indput(vx_vect,X.vx_vect,Ind.vx_vect,X.ui_size);
		}


		void subvector(cvta X, ssize_t step, ui start=0)
		{
			enforceSize();
			if(vx_vect==X.vx_vect) throw OptiVec_Err();
			VCD_subvector(vx_vect, ui_size, X.vx_vect+start, step);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Functions of a sub-set of elements
//
		void subvector_equC(const ui& samp, cta C)
		{
			enforceSize();
			VCD_subvector_equC(vx_vect, ((ui_size-1)/samp)+1, samp, C);
		}

		void subvector_equV(const ui& samp, cvta X)
		{
			enforceSize();
			VCD_subvector_equV(vx_vect, ((ui_size-1)/samp)+1, samp, X.vx_vect);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//One-Dimensional Vector Operations
//

		tbase absmax() const
		{
			enforceSize();
			return VCD_absmax(vx_vect, ui_size);
		}

		tbase absmin() const
		{
			enforceSize();
			return VCD_absmin(vx_vect, ui_size);
		}

		tbase absmaxind(ui* Ind) const
		{
			enforceSize();
			return VCD_absmaxind(Ind, vx_vect, ui_size);
		}

		tbase absminind(ui* Ind) const
		{
			enforceSize();
			return VCD_absminind(Ind, vx_vect, ui_size);
		}

		t maxReIm() const
		{
			enforceSize();
			return VCD_maxReIm(vx_vect, ui_size);
		}

		t minReIm() const
		{
			enforceSize();
			return VCD_minReIm(vx_vect, ui_size);
		}

		t absmaxReIm() const
		{
			enforceSize();
			return VCD_absmaxReIm(vx_vect, ui_size);
		}

		t absminReIm() const
		{
			enforceSize();
			return VCD_absminReIm(vx_vect, ui_size);
		}

		t cabsmax() const
		{
			enforceSize();
			return VCD_cabsmax(vx_vect, ui_size);
		}

		t cabsmin() const
		{
			enforceSize();
			return VCD_cabsmin(vx_vect, ui_size);
		}

		t sabsmax() const
		{
			enforceSize();
			return VCD_sabsmax(vx_vect, ui_size);
		}

		t sabsmin() const
		{
			enforceSize();
			return VCD_sabsmin(vx_vect, ui_size);
		}

		t sum() const
		{
			enforceSize();
			return VCD_sum(vx_vect, ui_size);
		}

		t prod() const
		{
			enforceSize();
			return VCD_prod(vx_vect, ui_size);
		}

		t mean() const
		{
			enforceSize();
			return VCD_mean(vx_vect, ui_size);
		}

		t meanwW(const vtbase& Wt) const
		{
			enforceSize();
			return VCD_meanwW(vx_vect, Wt.vx_vect, ui_size);
		}

		t scalprod(cvta X) const
		{
			enforceSize();
			return VCD_scalprod(vx_vect, X.vx_vect, ui_size);
		}

		void runsum(cvta X)
		{
			enforceSize();
			VCD_runsum(vx_vect, X.vx_vect, ui_size);
		}

		void runprod(cvta X)
		{
			enforceSize();
			VCD_runprod(vx_vect, X.vx_vect, ui_size);
		}

		int iselementC(cta C) const
		{
			enforceSize();
			return VCD_iselementC(vx_vect, ui_size, C);
		}

		ui iselementV(cvta X, cvta Tab)
		{
			enforceSize();
			Tab.enforceSize();
			return VCD_iselementV(vx_vect, X.vx_vect,
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
			VCDp_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		void p_FFTtoC(const vtbase& X)
		{
			enforceSize();
			VDp_FFTtoC(vx_vect,X.vx_vect,ui_size);
		}

		void p_filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VCDp_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}

		void b_FFT(cvta X, int dir, vta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			VCDb_FFT(vx_vect,X.vx_vect,ui_size,dir,Buf.vx_vect);
		}

		void b_FFTtoC(const vtbase& X, vta Buf)
		{
			enforceSize();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			VDb_FFTtoC(vx_vect,X.vx_vect,ui_size,Buf.vx_vect);
		}

		void l_FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VCDl_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		void l_FFTtoC(const vtbase& X)
		{
			enforceSize();
			VDl_FFTtoC(vx_vect,X.vx_vect,ui_size);
		}

		void l_filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VCDl_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}

		void s_FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VCDs_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		void s_FFTtoC(const vtbase& X)
		{
			enforceSize();
			VDs_FFTtoC(vx_vect,X.vx_vect,ui_size);
		}

		void s_filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VCDs_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
		}

		void FFT(cvta X, int dir=1)
		{
			enforcePow2();
			VCD_FFT(vx_vect,X.vx_vect,ui_size,dir);
		}

		void FFTtoC(const vtbase& X)
		{
			enforceSize();
			VD_FFTtoC(vx_vect,X.vx_vect,ui_size);
		}

		void filter(cvta X, cvta Flt)
		{
			enforcePow2();
			VCD_filter(vx_vect, X.vx_vect, Flt.vx_vect, ui_size);
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
			VCD_fprint(stream, vx_vect, ui_size, nperline, linewidth);
		}

		void  cprint( const unsigned& nperline ) const
		{
			enforceSize();
			VCD_cprint( vx_vect, ui_size, nperline);
		}

		void print(const unsigned& npl) const
		{
			enforceSize();
			VCD_print(vx_vect, ui_size, npl);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			VCD_write(stream, vx_vect, ui_size);
		}

		void read(FILE* stream)
		{
			enforceSize();
			VCD_read(vx_vect, ui_size, stream);
		}


//nwrite
//nread

		void setWriteFormat(char* formatString) const
		{
			VCD_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VCD_setWriteSeparate(sepString);
		}

//setNWriteSeparate

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_size,sizeof(ui),1,stream);
			VCD_store(stream,vx_vect,ui_size);
		}

		void recall(FILE* stream)
		{
			ui sz;
			fread(&sz,sizeof(ui),1,stream);
			setSize(sz);
			VCD_recall(vx_vect,ui_size,stream);
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
			return VCD_cmp_eq0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_ne0(cvta X)
		{
			enforceSize();
			return VCD_cmp_ne0(vx_vect,X.vx_vect,ui_size);
		}


		ui cmp_eqC(cvta X, cta C)
		{
			enforceSize();
			return VCD_cmp_eqC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_neC(cvta X, cta C)
		{
			enforceSize();
			return VCD_cmp_neC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_eqV(cvta X, cvta Y)
		{
			enforceSize();
			return VCD_cmp_eqV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_neV(cvta X, cvta Y)
		{
			enforceSize();
			return VCD_cmp_neV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_eq0()  const
		{
			enforceSize();
			return VCD_cnt_eq0(vx_vect, ui_size);
		}

		ui cnt_ne0()  const
		{
			enforceSize();
			return VCD_cnt_ne0(vx_vect, ui_size);
		}

		ui cnt_eqC(cta C) const
		{
			enforceSize();
			return VCD_cnt_eqC(vx_vect,ui_size,C);
		}

		ui cnt_neC(cta C) const
		{
			enforceSize();
			return VCD_cnt_neC(vx_vect,ui_size,C);
		}

		ui cnt_eqV(cvta Y) const
		{
			enforceSize();
			return VCD_cnt_eqV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_neV(cvta Y) const
		{
			enforceSize();
			return VCD_cnt_neV(vx_vect,Y.vx_vect,ui_size);
		}

		//indexed comparisons are members of uiVecObj


/////////////////////////////////////////////////////////////////////////////////////////
//Standard Arithmetics or Basic Arithmetics
//
		void limit(cvta X, cta Min, cta Max)
		{
			enforceSize();
			VCD_limit( vx_vect, X.vx_vect, ui_size, Min, Max);
		}

		void flush0(cvta X, cta AbsMin)
		{
			enforceSize();
			VCD_flush0( vx_vect, X.vx_vect, ui_size, AbsMin);
		}

		void flushInv(cvta X, cta AbsMin)
		{
			enforceSize();
			VCD_flushInv(vx_vect, X.vx_vect, ui_size, AbsMin);
		}

		void replaceNAN(cvta X, cta C)
		{
			enforceSize();
			VCD_replaceNAN( vx_vect, X.vx_vect, ui_size, C);
		}

		//x_equV defined above

		void addC(cvta X, cta C)
		{
			enforceSize();
			VCD_addC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subC(cvta X, cta C)
		{
			enforceSize();
			VCD_subC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subrC(cvta X, cta C)
		{
			enforceSize();
			VCD_subrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void mulC(cvta X, cta C)
		{
			enforceSize();
			VCD_mulC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divC(cvta X, cta C)
		{
			enforceSize();
			VCD_divC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divrC(cvta X, cta C)
		{
			enforceSize();
			VCD_divrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void x_divrC(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			VCDx_divrC(vx_vect, X.vx_vect, ui_size, A, B, C);
		}

		void addReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCD_addReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCD_subReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subrReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCD_subrReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void mulReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCD_addReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCD_addReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divrReC(cvta X, const tbase& C)
		{
			enforceSize();
			VCD_addReC(vx_vect, X.vx_vect, ui_size, C);
		}

		void addV(cvta X, cvta Y)
		{
			enforceSize();
			VCD_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subV(cvta X, cvta Y)
		{
			enforceSize();
			VCD_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subrV(cvta X, cvta Y)
		{
			enforceSize();
			VCD_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void mulV(cvta X, cvta Y)
		{
			enforceSize();
			VCD_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divV(cvta X, cvta Y)
		{
			enforceSize();
			VCD_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divrV(cvta X, cvta Y)
		{
			enforceSize();
			VCD_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void addReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCD_addReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCD_subReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subrReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCD_subrReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void mulReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCD_mulReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCD_divReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divrReV(cvta X, vtbase Y)
		{
			enforceSize();
			VCD_divrReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

                void mulVconj(cvta X, cvta Y)
		{
			enforceSize();
                        VCD_mulVconj(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void CaddV(cvta X, cvta Y, cta C)
		{
			enforceSize();
			VCD_CaddV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, C);
		}

		void x_addV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCDx_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_subV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCDx_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_subrV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCDx_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_mulV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCDx_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_divV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCDx_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_divrV(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
			VCDx_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_addReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCDx_addReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_subReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCDx_subReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_subrReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCDx_subrReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_mulReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCDx_mulReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_divReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCDx_divReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void x_divrReV(cvta X, vtbase Y, cta A, cta B)
		{
			enforceSize();
			VCDx_divrReV(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

                void x_mulVconj(cvta X, cvta Y, cta A, cta B)
		{
			enforceSize();
                        VCDx_mulVconj(vx_vect, X.vx_vect, Y.vx_vect, ui_size, A, B);
		}

		void lincomb(cvta X, cvta Y, cta CX, cta CY)
		{
			enforceSize();
			VCD_lincomb( vx_vect, X.vx_vect, Y.vx_vect, ui_size, CX, CY);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Accumulation
//
		void accV(cvta X)
		{
			enforceSize();
			VCD_accV(vx_vect,X.vx_vect,ui_size);
		}

		//defined by including cfVecObj.h
		void accVCD(const cfVecObj& X);

#if !(defined __BORLANDC__) || (defined _WIN64) //80-bit numbers not supported
		void accVCD(const cdVecObj& X){accV(X);}
#endif //__BORLANDC__


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
			VCD_subvector_addC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_subC(const ui& samp, cta C)
		{
			enforceSize();
			VCD_subvector_subC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_subrC(const ui& samp, cta C)
		{
			enforceSize();
			VCD_subvector_subrC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_mulC(const ui& samp, cta C)
		{
			enforceSize();
			VCD_subvector_mulC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_divC(const ui& samp, cta C)
		{
			enforceSize();
			VCD_subvector_divC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_divrC(const ui& samp, cta C)
		{
			enforceSize();
			VCD_subvector_divrC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_addV(const ui& samp, cvta X)
		{
			enforceSize();
			VCD_subvector_addV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_subV(const ui& samp, cvta X)
		{
			enforceSize();
			VCD_subvector_subV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_subrV(const ui& samp, cvta X)
		{
			enforceSize();
			VCD_subvector_subrV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_mulV(const ui& samp, cvta X)
		{
			enforceSize();
			VCD_subvector_mulV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_divV(const ui& samp, cvta X)
		{
			enforceSize();
			VCD_subvector_divV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void subvector_divrV(const ui& samp, cvta X)
		{
			enforceSize();
			VCD_subvector_divrV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Mathematical Functions
//
		int neg(cvta X)
		{
			enforceSize();
			return VCD_neg(vx_vect, X.vx_vect, ui_size);
		}

		int conj(cvta X)
		{
			enforceSize();
			return VCD_conj(vx_vect,X.vx_vect,ui_size);
		}

		//abs defined above

		int inv(cvta X)
		{
			enforceSize();
			return VCD_inv(vx_vect, X.vx_vect, ui_size);
		}

		int x_inv(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCDx_inv(vx_vect, X.vx_vect, ui_size, A, B);
		}

		int square(cvta X)
		{
			enforceSize();
			return VCD_square(vx_vect,X.vx_vect,ui_size);
		}

		int x_square(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCDx_square(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int cubic(cvta X)
		{
			enforceSize();
			return VCD_cubic(vx_vect,X.vx_vect,ui_size);
		}

		int x_cubic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCDx_cubic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int quartic(cvta X)
		{
			enforceSize();
			return VCD_quartic(vx_vect,X.vx_vect,ui_size);
		}

		int x_quartic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCDx_quartic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int ipow(cvta X, int pow)
		{
			enforceSize();
			return VCD_ipow(vx_vect, X.vx_vect, ui_size, pow);
		}

		int x_ipow(cvta X, int pow, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_ipow(vx_vect, X.vx_vect, ui_size, pow, A, B, C);
		}

		int u_square(cvta X)
		{
			enforceSize();
			return VCDu_square(vx_vect,X.vx_vect,ui_size);
		}

		int ux_square(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCDux_square(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int u_cubic(cvta X)
		{
			enforceSize();
			return VCDu_cubic(vx_vect,X.vx_vect,ui_size);
		}

		int ux_cubic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCDux_cubic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int u_quartic(cvta X)
		{
			enforceSize();
			return VCDu_quartic(vx_vect,X.vx_vect,ui_size);
		}

		int ux_quartic(cvta X, cta A, cta B)
		{
			enforceSize();
			return VCDux_quartic(vx_vect,X.vx_vect,ui_size,A,B);
		}

		int u_ipow(cvta X, int pow)
		{
			enforceSize();
			return VCDu_ipow(vx_vect, X.vx_vect, ui_size, pow);
		}

		int ux_ipow(cvta X, int pow, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDux_ipow(vx_vect, X.vx_vect, ui_size, pow, A, B, C);
		}

		int pow(cvta X, cta expo)
		{
			enforceSize();
			return VCD_pow(vx_vect,X.vx_vect,ui_size,expo);
		}

		int x_pow(cvta X, cta expo, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_pow(vx_vect,X.vx_vect,ui_size,expo,A,B,C);
		}

		int powReExpo(cvta X, const tbase& expo)
		{
			enforceSize();
			return VCD_powReExpo(vx_vect,X.vx_vect,ui_size,expo);
		}

		int x_powReExpo(cvta X, const tbase& expo, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_powReExpo(vx_vect,X.vx_vect,ui_size,expo,A,B,C);
		}

		int sqrt(cvta X)
		{
			enforceSize();
			return VCD_sqrt(vx_vect,X.vx_vect,ui_size);
		}

		int x_sqrt(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_sqrt(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int log(cvta X)
		{
			enforceSize();
			return VCD_log(vx_vect,X.vx_vect,ui_size);
		}

		int log2(cvta X)
		{
			enforceSize();
			return VCD_log2(vx_vect,X.vx_vect,ui_size);
		}

		int log10(cvta X)
		{
			enforceSize();
			return VCD_log10(vx_vect,X.vx_vect,ui_size);
		}

		int ln(cvta X)
		{
			return log(X);
		}

		int x_log(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_log(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int x_log2(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_log2(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int x_log10(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_log10(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int x_ln(cvta X, cta A, cta B, cta C)
		{
			return x_log(X,A,B,C);
		}

		//defined by including pdVecObj.h
		int logtoC(const pdVecObj& X);

		//defined by including pdVecObj.h
		int log2toC(const pdVecObj& X);

		//defined by including pdVecObj.h
		int log10toC(const pdVecObj& X);

		int lntoC(const pdVecObj& X){ return logtoC(X); }

		int exp(cvta X)
		{
			enforceSize();
			return VCD_exp(vx_vect,X.vx_vect,ui_size);
		}

		int x_exp(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_exp(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int expArbBase(cvta X, cta Base)
		{
			enforceSize();
			return VCD_expArbBase(vx_vect,X.vx_vect,ui_size,Base);
		}

		int x_expArbBase(cvta X, cta Base, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_expArbBase(vx_vect,X.vx_vect,ui_size,Base,A,B,C);
		}

		int sin(cvta X)
		{
			enforceSize();
			return VCD_sin(vx_vect,X.vx_vect,ui_size);
		}

		int x_sin(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_sin(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cos(cvta X)
		{
			enforceSize();
			return VCD_cos(vx_vect,X.vx_vect,ui_size);
		}

		int x_cos(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_cos(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int tan(cvta X)
		{
			enforceSize();
			return VCD_tan(vx_vect,X.vx_vect,ui_size);
		}

		int x_tan(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_tan(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int asin(cvta X)
		{
			enforceSize();
			return VCD_asin(vx_vect,X.vx_vect,ui_size);
		}

		int x_asin(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_asin(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int acos(cvta X)
		{
			enforceSize();
			return VCD_acos(vx_vect,X.vx_vect,ui_size);
		}

		int x_acos(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_acos(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int atan(cvta X)
		{
			enforceSize();
			return VCD_atan(vx_vect,X.vx_vect,ui_size);
		}

		int x_atan(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_atan(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int sinh(cvta X)
		{
			enforceSize();
			return VCD_sinh(vx_vect,X.vx_vect,ui_size);
		}

		int x_sinh(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_sinh(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int cosh(cvta X)
		{
			enforceSize();
			return VCD_cosh(vx_vect,X.vx_vect,ui_size);
		}

		int x_cosh(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_cosh(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		int tanh(cvta X)
		{
			enforceSize();
			return VCD_tanh(vx_vect,X.vx_vect,ui_size);
		}

		int x_tanh(cvta X, cta A, cta B, cta C)
		{
			enforceSize();
			return VCDx_tanh(vx_vect,X.vx_vect,ui_size,A,B,C);
		}

		//defined by including cdMatObj.h
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
                    VCD_autoPlot( vx_vect, ui_size, form, color );
                }

                void _2AutoPlot( unsigned form1, COLORREF color1,
                       cvta X2, unsigned form2, COLORREF color2 ) const
                {
                    enforceSize();
                    X2.enforceSize();
                    VCD_2AutoPlot( vx_vect,    ui_size, form1, color1,
                                X2.vx_vect, X2.ui_size, form2, color2 );
                }

                void dataPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VCD_dataPlot( vx_vect, ui_size, form, color );
                }
            #endif // __VGRAPH_H


	};


	inline ui uiVecObj::cmp_eq0ind(cvta X)
	{
		enforceSize();
		return VCD_cmp_eq0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ne0ind(cvta X)
	{
		enforceSize();
		return VCD_cmp_ne0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_eqCind(cvta X, cta C)
	{
		enforceSize();
		return VCD_cmp_eqCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_neCind(cvta X, cta C)
	{
		enforceSize();
		return VCD_cmp_neCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_eqVind(cvta X, cvta Y)
	{
		enforceSize();
		return VCD_cmp_eqVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_neVind(cvta X, cvta Y)
	{
		enforceSize();
		return VCD_cmp_neVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
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
#endif //FVECOBJ_H

#ifdef DVECOBJ_H
	inline void vtbase::CtoReIm(vtbase* Im,cvta X)
	{
		enforceSize();
		if(ui_size != Im->ui_size) throw OptiVec_SizeErr();
		VD_CtoReIm(vx_vect, Im->vx_vect, X.vx_vect, ui_size);
	}

	inline void vtbase::CtoReIm(vtbase Im,cvta X)
	{
		enforceSize();
		if(ui_size != Im.ui_size) throw OptiVec_SizeErr();
		VD_CtoReIm(vx_vect, Im.vx_vect, X.vx_vect, ui_size);
	}

	inline void vtbase::CtoRe(cvta cplx)
	{
		enforceSize();
		VD_CtoRe(vx_vect, cplx.vx_vect, ui_size);
	}

	inline void vtbase::CtoIm(cvta cplx)
	{
		enforceSize();
		VD_CtoIm(vx_vect, cplx.vx_vect, ui_size);
	}

	inline void vtbase::CtoPolar(vtbase* Arg, cvta X)
	{
		enforceSize();
		if(ui_size != Arg->ui_size) throw OptiVec_SizeErr();
		VD_CtoReIm(vx_vect, Arg->vx_vect, X.vx_vect, ui_size);
	}

	inline void vtbase::CtoPolar(vtbase Arg, cvta X)
	{
		enforceSize();
		if(ui_size != Arg.ui_size) throw OptiVec_SizeErr();
		VD_CtoReIm(vx_vect, Arg.vx_vect, X.vx_vect, ui_size);
	}

	inline void vtbase::CtoNorm(cvta cplx)
	{
		enforceSize();
		VD_CtoNorm(vx_vect, cplx.vx_vect, ui_size);
	}

	inline void vtbase::CtoAbs(cvta cplx)
	{
		enforceSize();
		VD_CtoAbs(vx_vect, cplx.vx_vect, ui_size);
	}

	inline void vtbase::CtoArg(cvta cplx)
	{
		enforceSize();
		VD_CtoArg(vx_vect, cplx.vx_vect, ui_size);
	}

	inline int vtbase::abs(cvta cplx)
	{
		enforceSize();
		return VCD_abs(vx_vect, cplx.vx_vect, ui_size);
	}
#endif //DVECOBJ_H

#ifdef EVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
#endif //__BORLANDC__
#endif //EVECOBJ_H

#ifdef CFVECOBJ_H
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
#endif //CFVECOBJ_H

#ifdef CEVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
	inline void cdVecObj::CEtoCD(const ceVecObj& X)
	{
		enforceSize();
		V_CEtoCD(vx_vect,X.vx_vect,ui_size);
	}

	inline void ceVecObj::CDtoCE(const cdVecObj& X)
	{
		enforceSize();
		V_CDtoCE(vx_vect,X.vx_vect,ui_size);
	}
#endif //__BORLANDC__
#endif //CEVECOBJ_H

#ifdef PFVECOBJ_H
#endif //PFVECOBJ_H

#ifdef PDVECOBJ_H
	inline void pdVecObj::CtoP(const cdVecObj& X)
	{
		enforceSize();
		VD_CtoP(vx_vect,X.vx_vect,ui_size);
	}

	inline void cdVecObj::PtoC(const pdVecObj& X)
	{
		enforceSize();
		VD_PtoC(vx_vect,X.vx_vect,ui_size);
	}

	inline int cdVecObj::logtoC(const pdVecObj& X)
	{
		enforceSize();
		VPD_logtoC(vx_vect,X.vx_vect,ui_size);
	}

	inline int cdVecObj::log2toC(const pdVecObj& X)
	{
		enforceSize();
		VPD_log2toC(vx_vect,X.vx_vect,ui_size);
	}

	inline int cdVecObj::log10toC(const pdVecObj& X)
	{
		enforceSize();
		VPD_log10toC(vx_vect,X.vx_vect,ui_size);
	}

	inline int pdVecObj::exptoP(const cdVecObj& X)
	{
		enforceSize();
                VCD_exptoP(vx_vect,X.vx_vect,ui_size);
	}
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

#undef vtbase
#undef tbase

#undef tVecObj
#undef tMatObj
#ifdef __BORLANDC__
#pragma warn .inl
#endif

#define CDVECOBJ_H
#endif //CDVECOBJ_H
