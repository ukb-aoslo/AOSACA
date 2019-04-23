/* eMatObj.H

  object-oriented interface for OptiVec matrix functions of type "extended"

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef EMATOBJ_H

#include <VecObj.h>
#include <eVecObj.h>
#include <uiVecObj.h>
#include <iVecObj.h>
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported

#define cmta const matrix<extended>&
#define cvta const vector<extended>&
#define cta  const extended&
#define cua  const ui&
#define cuint const ui

#define mta  matrix<extended>&
#define vta  vector<extended>&
#define ta   extended&

#define mt   matrix<extended>
#define vt   vector<extended>
#define t    extended
#define tcplx  eComplex
#define tMatrix eMatrix
#define tVector eVector

#define tMatObj eMatObj
#define tVecObj eVecObj
#ifdef __BORLANDC__
#pragma warn -inl
#endif

#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
namespace OptiVec{
#endif

	VECOBJ_NEW_TEMPLATE class matrix<t>
	{
#ifdef _MSC_VER
     public:
		tMatrix  mx_matr;
        tVector  vx_m0;
		ui       ui_ht, ui_len;
        ui       ui_size;
#else
		tMatrix  mx_matr;
        tVector  vx_m0;
		ui       ui_ht, ui_len;
        ui       ui_size;
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
		friend class matrix<ui>;
		friend class matrix<float>;
		friend class matrix<double>;
		friend class matrix<extended>;
		friend class matrix<fComplex>;
		friend class matrix<dComplex>;
		friend class matrix<eComplex>;
		friend class matrix<fPolar>;
		friend class matrix<dPolar>;
		friend class matrix<ePolar>;
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
#endif
	public:
////////////////////////////////////////////////////////////////////////////////////////////////////
//constructors and destructors
//
		matrix(){ mx_matr=0; vx_m0=0; ui_ht=0; ui_len=0; ui_size=0;}

		matrix(cua ht, cua len)
		{	if((ht > 0) && (len > 0))
			{	mx_matr=ME_matrix(ht,len); vx_m0=mx_matr[0];
				ui_ht=ht; ui_len=len; ui_size=((ui)ht)*len;
			}
			else{	mx_matr=0; vx_m0=0; ui_ht=0; ui_len=0; ui_size=0;}
		}

		matrix(cua ht, cua len, cta fill)
		{	if(!ht || !len) //size == 0
			{	mx_matr=0; vx_m0=0; ui_ht=0; ui_len=0; ui_size=0;}
			else
			{
				ui_ht=ht; ui_len=len; ui_size=((ui)ht)*len;
				if(!fill) //fill == 0.0
				{	mx_matr=ME_matrix0(ht,len); vx_m0=mx_matr[0];}
				else
				{	mx_matr=ME_matrix(ht,len);  vx_m0=mx_matr[0];
					VE_equC(vx_m0,ui_size,fill);}
			}
		}

		matrix(cmta init)
		{	if(init.ui_size)
			{	mx_matr= ME_matrix(init.ui_ht, init.ui_len); vx_m0=mx_matr[0];
				ui_ht=init.ui_ht; ui_len=init.ui_len; ui_size=init.ui_size;
				VE_equV(vx_m0, init.vx_m0, ui_size);
			} else
			{ mx_matr=0; vx_m0=0; ui_ht=0; ui_len=0; ui_size=0;}
		}

		~matrix(){ if(mx_matr) M_free(mx_matr);}


////////////////////////////////////////////////////////////////////////////////////////////////////
//management
//
		void enforceSize()const{ if(!ui_size) throw OptiVec_EmptySizeErr();}
		void enforceSize(ui ht, ui len)const{
			if(ui_len != len || ui_ht != ht || !ui_size) throw OptiVec_SizeErr();}

		void enforceLen(ui len)const{ if(ui_len != len) throw OptiVec_SizeErr();}
		void enforceHt(ui ht)const{ if(ui_ht != ht) throw OptiVec_SizeErr();}

		void enforcePow2()const{ if(!ui_isipow2(ui_len) || !ui_isipow2(ui_ht)) throw OptiVec_Pow2SizeErr();}

		void setSize(cua ht, cua len)
		{	ui size;
			size = ((ui)ht)*len;
			if(!size) dealloc(); //can set size to zero
			if(ui_len != len || ui_ht != ht) //only allocate if different sizes
			{	if(mx_matr) M_free(mx_matr);
				mx_matr= ME_matrix(ht, len); vx_m0=mx_matr[0];
				ui_len=len; ui_ht=ht; ui_size= size;
			}
		}

		void setSize(cmta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_len != X.ui_len || ui_ht != X.ui_ht) //only allocate if different sizes
			{	if(mx_matr) M_free(mx_matr);
				mx_matr= ME_matrix(X.ui_ht, X.ui_len); vx_m0=mx_matr[0];
				ui_len=X.ui_len; ui_ht=X.ui_ht; ui_size= X.ui_size;
			}
		}

		ui getHt()   const { return ui_ht; }
		ui getLen()  const { return ui_len; }
		ui getSize() const { return ui_size; }
		tMatrix getMatrix() const { return mx_matr; }
		tVector getM0()     const { return vx_m0; }

#if !defined (_CRTDBG_MAP_ALLOC) // crtdbg.h defines free as a macro
		void free()
		{	if(mx_matr) M_free(mx_matr);
			mx_matr=0; vx_m0=0; ui_ht=0; ui_len=0; ui_size=0;
		}
#endif

		void dealloc()
		{	if(mx_matr) M_free(mx_matr);
			mx_matr=0; vx_m0=0; ui_ht=0; ui_len=0; ui_size=0;
		}

		ta at(ui m, ui n) const
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return mx_matr[m][n];
		}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Overloaded operators
//
		mta operator=(cmta matr)
		{	setSize(matr.ui_ht, matr.ui_len);
			enforceSize();
			VE_equV(vx_m0, matr.vx_m0, ui_size);
			return *this;}

		mta operator=(cta scalar)
		{	enforceSize();
			VE_equC(vx_m0, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		tVector operator[](const int& index){return mx_matr[index];}

		mta operator+=(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			VE_accV(vx_m0, X.vx_m0, ui_size);
			return *this;}

		mta operator+=(cta scalar)
		{
			enforceSize();
			VE_addC(vx_m0, vx_m0, ui_size, scalar);
			return *this;}

		mta operator*=(cta scalar)
		{
			enforceSize();
			VE_mulC(vx_m0,vx_m0,ui_size,scalar);
			return *this;}

		mt operator+(cmta rhs)
		{	enforceSize(rhs.ui_ht, rhs.ui_len);
			tMatObj tmp(this->ui_ht, this->ui_len);
			VE_addV(tmp.vx_m0,this->vx_m0,rhs.vx_m0,tmp.ui_size);
			return tmp;}

		mt operator+(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VE_addC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		mt operator-(cmta rhs)
		{	enforceSize(rhs.ui_ht, rhs.ui_len);
			tMatObj tmp(this->ui_ht, this->ui_len);
			VE_subV(tmp.vx_m0,this->vx_m0,rhs.vx_m0,tmp.ui_size);
			return tmp;}

		mt operator-(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VE_subC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		mt operator*(cmta rhs)
		{	enforceLen(rhs.ui_ht);
			tMatObj tmp(this->ui_ht, rhs.ui_len);
			tmp.enforceSize();
			MEmulM(tmp.vx_m0,this->vx_m0,rhs.vx_m0,this->ui_ht, this->ui_len,rhs.ui_len);
			return tmp;}

		vt operator*(cvta rhs)
		{	enforceLen(rhs.ui_size);
			tVecObj tmp(this->ui_ht);
			tmp.enforceSize();
			MEmulV(tmp.vx_vect,this->vx_m0,rhs.vx_vect,this->ui_ht, this->ui_len);
			return tmp;}

		// operator*(cvta VX, cmta MY) is member of eVecObj, see below

		mt operator*(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VE_mulC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		mt operator/(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VE_divC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		friend mt operator+(cta C, cmta X)
		{	tMatObj tmp(X.ui_ht,X.ui_len);
			VE_addC(tmp.vx_m0,X.vx_m0,tmp.ui_size,C);
			return tmp;}

		friend mt operator-(cta C, cmta X)
		{	tMatObj tmp(X.ui_ht,X.ui_len);
			VE_subrC(tmp.vx_m0,X.vx_m0,tmp.ui_size,C);
			return tmp;}

		friend mt operator*(cta C, cmta X)
		{	tMatObj tmp(X.ui_ht,X.ui_len);
			VE_mulC(tmp.vx_m0,X.vx_m0,tmp.ui_size,C);
			return tmp;}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//OptiVec functions in member format
//from MXstd.h
//

/////////////////////////////////////////////////////////////////////////////////////////
//Generation
//
		//these are not recommended, better to use constructors
		void _matrix(cuint ht, cuint len) //underscore necessary to avoid confusing with constructor
		{
			dealloc();
			ui_size=((ui)ht)*len;
			if(ui_size){ ui_ht=ht;ui_len=len;mx_matr= ME_matrix(ht,len);vx_m0=mx_matr[0];}
		}

		void _matrix0(cuint ht, cuint len) //underscore necessary to avoid confusing with constructor
		{
			dealloc();
			ui_size=((ui)ht)*len;
			if(ui_size){ ui_ht=ht;ui_len=len;mx_matr= ME_matrix0(ht,len);vx_m0=mx_matr[0];}
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single matrix elements
//
		t* Pelement(cuint m, cuint n) const
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MEPelement(vx_m0,ui_ht,ui_len,m,n);
		}

		t element(cuint m, cuint n) const
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MEelement(vx_m0,ui_ht,ui_len,m,n);
		}

		void getElement(t *y, cuint m, cuint n)
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MEgetElement(y,vx_m0,ui_ht,ui_len,m,n);
		}

		void setElement(cuint m, cuint n, cta C)
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			MEsetElement(vx_m0,ui_ht,ui_len,m,n,C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//

		void equ0()
		{
			enforceSize();
			VE_equ0(vx_m0,ui_size);
		}

		void equ1()
		{
			enforceSize();
			MEequ1(vx_m0,ui_len);
		}

		void equm1()
		{
			enforceSize();
			MEequm1(vx_m0,ui_len);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VE_random(vx_m0, ui_size, seed, Min, Max);
		}

		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VE_randomLC(vx_m0, ui_size, seed, Min, Max, state);
		}

		void outerprod(cvta X, cvta Y)
		{
			enforceSize( X.ui_size, Y.ui_size);
			MEouterprod(vx_m0, X.vx_vect, Y.vx_vect, ui_ht, ui_len);
		}

		void Row_equ0(cuint iRow)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MERow_equ0(vx_m0, ui_ht, ui_len, iRow);
		}

		void Col_equ0(cuint iCol)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MECol_equ0(vx_m0, ui_ht, ui_len, iCol);
		}

		void Dia_equ0()
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MEDia_equ0(vx_m0, ui_len);
		}

		void Row_equC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MERow_equC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_equC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MECol_equC(vx_m0, ui_ht, ui_len, iCol, C);
		}

		void Dia_equC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MEDia_equC(vx_m0, ui_len, C);
		}

		void Row_equV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MERow_equV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_equV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MECol_equV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

		void Dia_equV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MEDia_equV(vx_m0, ui_len, X.vx_vect);
		}

		void Trd_equM(cmta MTrd)
		{
			if( MTrd.ui_ht != 3 || ui_ht != ui_len || ui_len != MTrd.ui_len )throw OptiVec_SizeErr();
			METrd_equM(vx_m0, MTrd.vx_m0, ui_len);
		}

		void Trd_extract(cmta MA)
		{
			if( ui_ht != 3 || MA.ui_ht != MA.ui_len || MA.ui_len != ui_len )throw OptiVec_SizeErr();
			METrd_extract(vx_m0, MA.vx_m0, ui_len);
		}

		void equM(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			MEequM(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void neg(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			MEneg(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void UequL()
		{
			if( !ui_len || ui_len != ui_ht )throw OptiVec_SizeErr();
			MEUequL(vx_m0, ui_len);
		}

		void LequU()
		{
			if( !ui_len || ui_len != ui_ht )throw OptiVec_SizeErr();
			MELequU(vx_m0, ui_len);
		}

		void Parzen()
		{
			enforceSize();
			MEParzen(vx_m0, ui_ht, ui_len);
		}

		void Hann()
		{
			enforceSize();
			MEHann(vx_m0, ui_ht, ui_len);
		}

		void Hanning() // erroneous name for Hann
		{
			enforceSize();
			MEHann(vx_m0, ui_ht, ui_len);
		}

		void Welch()
		{
			enforceSize();
			MEWelch(vx_m0, ui_ht, ui_len);
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//
		//defined by including dMatObj.h
		void DtoE(const dMatObj& X);

		//defined by including fMatObj.h
		void FtoE(const fMatObj& X);

		//defined by including biMatObj.h
		void BItoE(const biMatObj& X);

		//defined by including ubMatObj.h
		void UBtoE(const ubMatObj& X);

		//defined by including siMatObj.h
		void SItoE(const siMatObj& X);

		//defined by including usMatObj.h
		void UStoE(const usMatObj& X);

		//defined by including iMatObj.h
		void ItoE(const iMatObj& X);

		//defined by including uMatObj.h
		void UtoE(const uMatObj& X);

		//defined by including liMatObj.h
		void LItoE(const liMatObj& X);

		//defined by including ulMatObj.h
		void ULtoE(const ulMatObj& X);

		#if defined _WIN64
			//defined by including uqMatObj.h
			void UQtoE(const uqMatObj& X);
		#endif

		//defined by including qiMatObj.h
		void QItoE(const qiMatObj& X);


/////////////////////////////////////////////////////////////////////////////////////////
//Submatrices
//
		void submatrix(cmta MSrce, cuint firstRowInCol, cuint sampInCol, cuint firstColInRow, cuint sampInRow )
		{
			if( (MSrce.ui_ht  <= firstRowInCol+(ui_ht-1) *sampInCol) ||
                (MSrce.ui_len <= firstColInRow+(ui_len-1)*sampInRow) ) throw OptiVec_SizeErr();
			MEsubmatrix(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
                 firstRowInCol, sampInCol, firstColInRow, sampInRow );
		}

		void submatrix_equM(cuint firstRowInCol, cuint sampInCol, cuint firstColInRow, cuint sampInRow, cmta MSrce)
		{
			if( (ui_ht  <= firstRowInCol+(MSrce.ui_ht-1) *sampInCol) ||
                (ui_len <= firstColInRow+(MSrce.ui_len-1)*sampInRow) ) throw OptiVec_SizeErr();
			MEsubmatrix_equM(vx_m0, ui_ht, ui_len,
                 firstRowInCol, sampInCol, firstColInRow, sampInRow,
                 MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len );
		}

		void equMblock(cmta MSrce, cuint firstRowInCol, cuint firstColInRow )
		{
			if( (MSrce.ui_ht  < firstRowInCol+ui_ht) ||
                (MSrce.ui_len < firstColInRow+ui_len) ) throw OptiVec_SizeErr();
			MEequMblock(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
                 firstRowInCol, firstColInRow );
		}

		void equMblockT(cmta MSrce, cuint firstRowInCol, cuint firstColInRow )
		{
			if( (MSrce.ui_ht  < firstRowInCol+ui_len) ||
                (MSrce.ui_len < firstColInRow+ui_ht) ) throw OptiVec_SizeErr();
			MEequMblockT(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
                 firstRowInCol, firstColInRow );
		}

		void block_equM(cuint firstRowInCol, cuint firstColInRow, cmta MSrce )
		{
			if( (ui_ht  < firstRowInCol+MSrce.ui_ht) ||
                (ui_len < firstColInRow+MSrce.ui_len) ) throw OptiVec_SizeErr();
			MEblock_equM(vx_m0, ui_ht, ui_len, firstRowInCol, firstColInRow,
                 MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len );
		}

		void block_equMT(cuint firstRowInCol, cuint firstColInRow, cmta MSrce )
		{
			if( (ui_ht  < firstRowInCol+MSrce.ui_len) ||
                (ui_len < firstColInRow+MSrce.ui_ht) ) throw OptiVec_SizeErr();
			MEblock_equMT(vx_m0, ui_ht, ui_len, firstRowInCol, firstColInRow,
                 MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len );
		}

/////////////////////////////////////////////////////////////////////////////////////////
// Deleting or inserting a row or a column
//

		void Row_delete(cmta MA, cuint iRow)
		{
			if( MA.ui_ht <= iRow ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{	ui_size -= ui_len;  // don't reallocate, as row pointers remain intact
				MERow_delete(vx_m0, vx_m0, ui_ht--, ui_len, iRow);
			}
			else
			{	enforceSize(MA.ui_ht-1, MA.ui_len);
				MERow_delete(vx_m0, MA.vx_m0, MA.ui_ht, MA.ui_len, iRow);
			}
		}

		void Col_delete(cmta MA, cuint iCol)
		{
			if( MA.ui_len <= iCol ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = ME_matrix( ui_ht, ui_len-1 );
				MECol_delete(tmp[0], MA.vx_m0, ui_ht, ui_len--, iCol);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size -= ui_ht;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht, MA.ui_len-1);
				MECol_delete(vx_m0, MA.vx_m0, ui_ht, ui_len, iCol);
			}
		}

		void Row_insert(cmta MA, cuint iRow, cvta X)
		{
			if( ui_ht <= iRow ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = ME_matrix( ++ui_ht, ui_len );
				MERow_insert(tmp[0], MA.vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size += ui_len;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht+1, MA.ui_len);
				MERow_insert(vx_m0, MA.vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
			}
		}

		void Col_insert(cmta MA, cuint iCol, cvta X)
		{
			if( ui_len <= iCol ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = ME_matrix( ui_ht, ++ui_len );
				MECol_insert(tmp[0], MA.vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size += ui_ht;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht, MA.ui_len+1);
				MECol_insert(vx_m0, MA.vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
			}
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Basic arithmetic operations performed on one single row, or one single column
// of any matrix, or on the diagonal of a square matrix
//

		void Row_neg(cuint iRow)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MERow_neg(vx_m0, ui_ht, ui_len, iRow);
		}

		void Col_neg(cuint iCol)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MECol_neg(vx_m0, ui_ht, ui_len, iCol);
		}

		void Row_addC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MERow_addC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_addC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MECol_addC(vx_m0, ui_ht, ui_len, iCol, C);
		}

		void Dia_addC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MEDia_addC(vx_m0, ui_len, C);
		}

		void Row_addV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MERow_addV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_addV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MECol_addV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

		void Dia_addV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MEDia_addV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_subC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MERow_subC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_subC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MECol_subC(vx_m0, ui_ht, ui_len, iCol, C);
		}

		void Dia_subC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MEDia_subC(vx_m0, ui_len, C);
		}

		void Row_subV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MERow_subV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_subV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MECol_subV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

		void Dia_subV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MEDia_subV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_subrC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MERow_subrC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_subrC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MECol_subrC(vx_m0, ui_ht, ui_len, iCol, C);
		}

		void Dia_subrC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MEDia_subrC(vx_m0, ui_len, C);
		}

		void Row_subrV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MERow_subrV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_subrV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MECol_subrV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

		void Dia_subrV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MEDia_subrV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_mulC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MERow_mulC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_mulC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MECol_mulC(vx_m0, ui_ht, ui_len, iCol, C);
		}

		void Dia_mulC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MEDia_mulC(vx_m0, ui_len, C);
		}

		void Row_mulV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MERow_mulV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_mulV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MECol_mulV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

		void Dia_mulV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MEDia_mulV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_divC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MERow_divC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_divC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MECol_divC(vx_m0, ui_ht, ui_len, iCol, C);
		}

		void Dia_divC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MEDia_divC(vx_m0, ui_len, C);
		}

		void Row_divV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MERow_divV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_divV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MECol_divV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

		void Dia_divV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MEDia_divV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_divrC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MERow_divrC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_divrC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MECol_divrC(vx_m0, ui_ht, ui_len, iCol, C);
		}

		void Dia_divrC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MEDia_divrC(vx_m0, ui_len, C);
		}

		void Row_divrV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MERow_divrV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_divrV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MECol_divrV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

		void Dia_divrV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MEDia_divrV(vx_m0, ui_len, X.vx_vect);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//One-dimensional vector operations
//performed along all rows or columns, or along the diagonal of a square matrix
//(some of these functions belong to eVecObj.h)

		t Dia_max() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MEDia_max(vx_m0, ui_len);
		}

		t Dia_min() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MEDia_min(vx_m0, ui_len);
		}

		t Dia_absmax() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MEDia_absmax(vx_m0, ui_len);
		}

		t Dia_absmin() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MEDia_absmin(vx_m0, ui_len);
		}

		t Dia_sum() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MEDia_sum(vx_m0, ui_len);
		}

		t Dia_ssq() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MEDia_ssq(vx_m0, ui_len);
		}

		t Dia_prod() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MEDia_prod(vx_m0, ui_len);
		}

		void Rows_runsum()
		{
			enforceSize();
			MERows_runsum(vx_m0, ui_ht, ui_len);
		}

		void Cols_runsum()
		{
			enforceSize();
			MECols_runsum(vx_m0, ui_ht, ui_len);
		}

		void Rows_runprod()
		{
			enforceSize();
			MERows_runprod(vx_m0, ui_ht, ui_len);
		}

		void Cols_runprod()
		{
			enforceSize();
			MECols_runprod(vx_m0, ui_ht, ui_len);
		}

		void Rows_rotate(const ssize_t pos)
		{
			enforceSize();
			MERows_rotate(vx_m0, ui_ht, ui_len, pos);
		}

		void Cols_rotate(const ssize_t pos)
		{
			enforceSize();
			MECols_rotate(vx_m0, ui_ht, ui_len, pos);
		}

		void Rows_rotate_buf(const ssize_t pos, cmta MBuf)
		{
			enforceSize();
			MERows_rotate_buf(vx_m0, ui_ht, ui_len, pos, MBuf.vx_m0);
		}

		void Cols_rotate_buf(const ssize_t pos, cmta MBuf)
		{
			enforceSize();
			MECols_rotate_buf(vx_m0, ui_ht, ui_len, pos, MBuf.vx_m0);
		}

		void Rows_reflect()
		{
			enforceSize();
			MERows_reflect(vx_m0, ui_ht, ui_len);
		}

		void Cols_reflect()
		{
			enforceSize();
			MECols_reflect(vx_m0, ui_ht, ui_len);
		}

		void Rows_rev()
		{
			enforceSize();
			MERows_rev(vx_m0, ui_ht, ui_len);
		}

		void Cols_rev()
		{
			enforceSize();
			MECols_rev(vx_m0, ui_ht, ui_len);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Operations involving two rows or two colums of one matrix
//
		void Rows_exchange(cuint row1, cuint row2)
		{
			if( !ui_len || (ui_ht <= row1) || (ui_ht <= row2))throw OptiVec_SizeErr();
			MERows_exchange(vx_m0, ui_ht, ui_len, row1, row2);
		}

		void Cols_exchange(cuint col1, cuint col2)
		{
			if( !ui_len || (ui_ht <= col1) || (ui_ht <= col2))throw OptiVec_SizeErr();
			MECols_exchange(vx_m0, ui_ht, ui_len, col1, col2);
		}

		void Rows_add(cuint destRow, cuint srceRow)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MERows_add(vx_m0, ui_ht, ui_len, destRow, srceRow);
		}

		void Cols_add(cuint destCol, cuint srceCol)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol))throw OptiVec_SizeErr();
			MECols_add(vx_m0, ui_ht, ui_len, destCol, srceCol);
		}

		void Rows_sub(cuint destRow, cuint srceRow)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MERows_sub(vx_m0, ui_ht, ui_len, destRow, srceRow);
		}

		void Cols_sub(cuint destCol, cuint srceCol)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol))throw OptiVec_SizeErr();
			MECols_sub(vx_m0, ui_ht, ui_len, destCol, srceCol);
		}

		void Rows_Cadd(cuint destRow, cuint srceRow, cta C)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MERows_Cadd(vx_m0, ui_ht, ui_len, destRow, srceRow, C);
		}

		void Cols_Cadd(cuint destCol, cuint srceCol, cta C)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol))throw OptiVec_SizeErr();
			MECols_Cadd(vx_m0, ui_ht, ui_len, destCol, srceCol, C);
		}

		void Rows_lincomb(cuint destRow, cta destC, cuint srceRow, cta srceC)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MERows_lincomb(vx_m0, ui_ht, ui_len, destRow, destC, srceRow, srceC);
		}

		void Cols_lincomb(cuint destCol, cta destC, cuint srceCol, cta srceC)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol)) throw OptiVec_SizeErr();
			MECols_lincomb(vx_m0, ui_ht, ui_len, destCol, destC, srceCol, srceC);
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Center of Gravity
//

		eComplex centerOfGravityInd() const
		{
			enforceSize();
			return MEcenterOfGravityInd(vx_m0,ui_ht, ui_len);
		}

		eComplex centerOfGravityV(cvta X, cvta Y) const
		{
            if( ui_ht != Y.ui_size || ui_len != X.ui_size || !ui_size )
                throw OptiVec_SizeErr();
			return MEcenterOfGravityV(X.vx_vect,Y.vx_vect,vx_m0,ui_ht,ui_len);
		}

/////////////////////////////////////////////////////////////////////////////////////////
// Matrix transposition and rotation
//
		void transpose(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MEtranspose(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate90(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MErotate90(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate180(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MErotate180(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate270(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MErotate270(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Interpolation of Matrix Elements
//
		void polyinterpol(cvta X, cvta Y, cvta Xtab, cvta Ytab, cmta MZtab,
                          unsigned degX, unsigned degY)
		{
            if( ui_ht != Y.ui_size || ui_len != X.ui_size || !ui_size ||
                MZtab.ui_ht != Ytab.ui_size || MZtab.ui_len != Xtab.ui_size
                || !MZtab.ui_size )    throw OptiVec_SizeErr();
			if((degX>10) || (degY>10)) throw OptiVec_Err();
			if((Xtab.ui_size<degX) || (Ytab.ui_size<degY)) throw OptiVec_SmallSizeErr();
			MEpolyinterpol(vx_m0,X.vx_vect,Y.vx_vect,ui_ht,ui_len,
				Xtab.vx_vect,Ytab.vx_vect,MZtab.vx_m0,MZtab.ui_ht,MZtab.ui_len,degX,degY);
		}

		void ratinterpol(cvta X, cvta Y, cvta Xtab, cvta Ytab, cmta MZtab,
                          unsigned degX, unsigned degY)
		{
            if( ui_ht != Y.ui_size || ui_len != X.ui_size || !ui_size ||
                MZtab.ui_ht != Ytab.ui_size || MZtab.ui_len != Xtab.ui_size
                || !MZtab.ui_size )    throw OptiVec_SizeErr();
			if((degX>10) || (degY>10)) throw OptiVec_Err();
			if((Xtab.ui_size<degX) || (Ytab.ui_size<degY)) throw OptiVec_SmallSizeErr();
			MEratinterpol(vx_m0,X.vx_vect,Y.vx_vect,ui_ht,ui_len,
				Xtab.vx_vect,Ytab.vx_vect,MZtab.vx_m0,MZtab.ui_ht,MZtab.ui_len,degX,degY);
		}

		void natCubSplineInterpol(cvta X, cvta Y, cvta Xtab, cvta Ytab, cmta MZtab)
		{
            if( ui_ht != Y.ui_size || ui_len != X.ui_size || !ui_size ||
                MZtab.ui_ht != Ytab.ui_size || MZtab.ui_len != Xtab.ui_size
                || !MZtab.ui_size )    throw OptiVec_SizeErr();
			if((Xtab.ui_size<3) || (Ytab.ui_size<3)) throw OptiVec_SmallSizeErr();
			MEnatCubSplineInterpol(vx_m0,X.vx_vect,Y.vx_vect,ui_ht,ui_len,
				Xtab.vx_vect,Ytab.vx_vect,MZtab.vx_m0,MZtab.ui_ht,MZtab.ui_len);
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Matrix arithmetics
//(The following functions are more efficient than the arithmetic operators defined above)
//
		void addM(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MEaddM(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void addMT(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht,  MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MEaddMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void subM(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MEsubM(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void subMT(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht,  MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MEsubMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void subrM(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MEsubM(vx_m0, MB.vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void subrMT(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht,  MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MEsubrMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void mulC(cmta MA, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			MEmulC(vx_m0, MA.vx_m0, ui_ht, ui_len, C);
		}

		void divC(cmta MA, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			MEdivC(vx_m0, MA.vx_m0, ui_ht, ui_len, C);
		}

		void s_addM(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MEsaddM(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, C);
		}

		void s_addMT(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MEsaddMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, C);
		}

		void s_subM(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MEssubM(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, C);
		}

		void s_subMT(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MEssubMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, C);
		}

		void s_subrM(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MEssubM(vx_m0, MB.vx_m0, MA.vx_m0, ui_ht, ui_len, C);
		}

		void s_subrMT(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MEssubrMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, C);
		}

		void lincomb(cmta MA, cmta MB, cta CA, cta CB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MElincomb(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, CA, CB);
		}

		//mixed multiplications matrix * vector belong to eVecObj
        void mulM( cmta MA, cmta MB )
        {
            if( ui_ht != MA.ui_ht || ui_len != MB.ui_len || MB.ui_ht != MA.ui_len )throw OptiVec_SizeErr();
            MEmulM( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_len);
        }

        void mulMT( cmta MA, cmta MB )
        {
            if( ui_ht != MA.ui_ht || ui_len != MB.ui_ht || MB.ui_len != MA.ui_len )throw OptiVec_SizeErr();
            MEmulMT( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_ht);
        }

        void TmulM( cmta MA, cmta MB )
        {
            if( ui_ht != MA.ui_len || ui_len != MB.ui_len || MB.ui_ht != MA.ui_ht )throw OptiVec_SizeErr();
            METmulM( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_len);
        }

        void TmulMT( cmta MA, cmta MB )
        {
            if( ui_ht != MA.ui_len || ui_len != MB.ui_ht || MB.ui_len != MA.ui_ht )throw OptiVec_SizeErr();
            METmulMT( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_ht);
        }

        void dia_mulM( cvta MADia, cmta MB )
        {
            if( ui_ht != MADia.ui_size || ui_len != MB.ui_len || MB.ui_ht != MADia.ui_size )throw OptiVec_SizeErr();
            MEdiamulM( vx_m0, MADia.vx_vect, MB.vx_m0, MB.ui_ht, MB.ui_len );
        }

        void dia_mulMT( cvta MADia, cmta MB )
        {
            if( ui_ht != MADia.ui_size || ui_len != MB.ui_ht || MB.ui_len != MADia.ui_size )throw OptiVec_SizeErr();
            MEdiamulMT( vx_m0, MADia.vx_vect, MB.vx_m0, MB.ui_ht, MB.ui_len );
        }

        void mulMdia( cmta MA, cvta MBDia )
        {
            if( ui_ht != MA.ui_ht || ui_len != MBDia.ui_size || MBDia.ui_size != MA.ui_len )throw OptiVec_SizeErr();
            MEmulMdia( vx_m0, MA.vx_m0, MBDia.vx_vect, MA.ui_ht, MA.ui_len );
        }

        void TmulMdia( cmta MA, cvta MBDia )
        {
            if( ui_ht != MA.ui_len || ui_len != MBDia.ui_size || MBDia.ui_size != MA.ui_ht )throw OptiVec_SizeErr();
            METmulMdia( vx_m0, MA.vx_m0, MBDia.vx_vect, MA.ui_ht, MA.ui_len );
        }

/////////////////////////////////////////////////////////////////////////////////////////
//Linear Algebra
//
        int LUdecompose( uiVecObj Ind, cmta MA )
        {
            if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len || ui_ht != Ind.ui_size )
                throw OptiVec_SizeErr();
            return MELUdecompose( vx_m0, Ind.vx_vect, MA.vx_m0, ui_len );
        }

        int LUdecompose( uiVecObj* Ind, cmta MA )
        {
            if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len || ui_ht != Ind->ui_size )
                throw OptiVec_SizeErr();
            return MELUdecompose( vx_m0, Ind->vx_vect, MA.vx_m0, ui_len );
        }

        int  LUDresult() const
        {
            return ME_LUDresult();
        }

		void LUDsetEdit(cta Thresh) const
		{
			ME_LUDsetEdit(Thresh);
		}

		t LUDgetEdit() const
		{
			return ME_LUDgetEdit();
		}

        void LUinv( cmta MLU, const uiVecObj& Ind )
        {
            if( ui_ht != MLU.ui_ht || ui_len != MLU.ui_len || ui_ht != ui_len || ui_ht != Ind.ui_size )
                throw OptiVec_SizeErr();
            MELUinv( vx_m0, MLU.vx_m0, Ind.vx_vect, ui_len );
        }

        t LUdet( int permut ) const
        {
            if( ui_ht != ui_len ) throw OptiVec_SizeErr();
            return MELUdet( vx_m0, ui_len, permut );
        }

		int CholeskyLdecompose( cmta MA )
		{
			if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
					throw OptiVec_SizeErr();
			return MECholeskyLdecompose( vx_m0, MA.vx_m0, ui_len );
		}

		void CholeskyLinv( cmta ML )
		{
			if( ui_ht != ML.ui_ht || ui_len != ML.ui_len || ui_ht != ui_len )
					throw OptiVec_SizeErr();
			MECholeskyLinv( vx_m0, ML.vx_m0, ui_len );
		}

		int CholeskyRdecompose( cmta MA )
		{
			if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
					throw OptiVec_SizeErr();
			return MECholeskyRdecompose( vx_m0, MA.vx_m0, ui_len );
		}

		void CholeskyRinv( cmta MR )
		{
			if( ui_ht != MR.ui_ht || ui_len != MR.ui_len || ui_ht != ui_len )
					throw OptiVec_SizeErr();
			MECholeskyRinv( vx_m0, MR.vx_m0, ui_len );
		}

		t CholeskyDet() const
		{
			if( ui_ht != ui_len ) throw OptiVec_SizeErr();
			return MECholeskyDet( vx_m0, ui_len );
		}

        int SVdecompose( tMatObj *MV, tVecObj *W, cmta MA )
        {
            if( (MA.ui_ht < MA.ui_len ? (ui_ht != ui_len) : (ui_ht != MA.ui_ht))
              || ui_len != MA.ui_len || ui_len != MV->ui_len || ui_len != MV->ui_ht
              || ui_len != W->ui_size )   throw OptiVec_SizeErr();
            return MESVdecompose( vx_m0, MV->vx_m0, W->vx_vect,
                                   MA.vx_m0, MA.ui_ht, MA.ui_len );
        }

        int SVdecompose( tMatObj MV, tVecObj W, cmta MA )
        {
            if( (MA.ui_ht < MA.ui_len ? (ui_ht != ui_len) : (ui_ht != MA.ui_ht))
              || ui_len != MA.ui_len || ui_len != MV.ui_len || ui_len != MV.ui_ht
              || ui_len != W.ui_size )   throw OptiVec_SizeErr();
            return MESVdecompose( vx_m0, MV.vx_m0, W.vx_vect,
                                   MA.vx_m0, MA.ui_ht, MA.ui_len );
        }

		void SVsort( tMatObj *MVout, tVecObj *Wout, tMatObj MUraw, tMatObj MVraw, tVecObj Wraw )
		{
			if( (MUraw.ui_ht != ui_ht) || (MUraw.ui_len != ui_len) 
			  || ui_len != MVout->ui_len || ui_len != MVraw.ui_len 
			  || ui_len != MVout->ui_ht  || ui_len != MVraw.ui_ht
			  || ui_len != Wout->ui_size || ui_len != Wraw.ui_size )   throw OptiVec_SizeErr();
			MESVsort( vx_m0, MVout->vx_m0, Wout->vx_vect,
			          MUraw.vx_m0, MVraw.vx_m0, Wraw.vx_vect, ui_ht, ui_len );
		}

		void SVsort( tMatObj MVout, tVecObj Wout, tMatObj MUraw, tMatObj MVraw, tVecObj Wraw )
		{
			if( (MUraw.ui_ht != ui_ht) || (MUraw.ui_len != ui_len)
			  || ui_len != MVout.ui_len || ui_len != MVraw.ui_len
			  || ui_len != MVout.ui_ht  || ui_len != MVraw.ui_ht
			  || ui_len != Wout.ui_size || ui_len != Wraw.ui_size )   throw OptiVec_SizeErr();
			MESVsort( vx_m0, MVout.vx_m0, Wout.vx_vect,
			          MUraw.vx_m0, MVraw.vx_m0, Wraw.vx_vect, ui_ht, ui_len );
		}

		void SVDsetEdit(cta Thresh) const
		{
			ME_SVDsetEdit(Thresh);
		}

		t SVDgetEdit() const
		{
			return ME_SVDgetEdit();
		}

        int inv( cmta MA )
        {
            if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
                throw OptiVec_SizeErr();
            return MEinv( vx_m0, MA.vx_m0, ui_len );
        }

        t det() const
        {
            if( ui_ht != ui_len ) throw OptiVec_SizeErr();
            return MEdet( vx_m0, ui_len );
        }

		int sym_inv( cmta MA )
		{
			if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
				throw OptiVec_SizeErr();
			return MEsyminv( vx_m0, MA.vx_m0, ui_len );
		}

		t sym_det() const
		{
			if( ui_ht != ui_len ) throw OptiVec_SizeErr();
			return MEsymdet( vx_m0, ui_len );
		}


/////////////////////////////////////////////////////////////////////////////////////////
// Eigenvalues, Matrix Square-Root
//
// sym_eigenval is a member of tVecObj

        int sym_sqrt( cmta MA )
        {
            if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
                throw OptiVec_SizeErr();
            return MEs_sqrt( vx_m0, MA.vx_m0, ui_len );
        }


/////////////////////////////////////////////////////////////////////////////////////////
//Fourier Transforms, Convolutions, Filtering
//

		tcplx getRspEdit() const
		{
			return VE_getRspEdit();
		}

		void setRspEdit(const tcplx& trunc) const
		{
			VE_setRspEdit(trunc);
		}

		void p_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MEpFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void p_Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MEpRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void p_Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MEpCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void b_FFT(cmta X, int dir, mta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MEbFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir,Buf.vx_m0);
		}

		void b_Rows_FFT(cmta X, int dir, mta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MEbRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir,Buf.vx_m0);
		}

		void b_Cols_FFT(cmta X, int dir, mta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MEbCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir,Buf.vx_m0);
		}

		//p_FFTtoC, b_FFTtoC members of cfMatObj

		void p_filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MEpfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void p_autocorr(cmta X)
		{
			enforcePow2();
			MEpautocorr(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void p_xcorr(cmta X, cmta Y)
		{
			enforcePow2();
			MEpxcorr(vx_m0, X.vx_m0, Y.vx_m0, ui_ht, ui_len);
		}

		void p_spectrum(cmta X, cmta Win)
		{
			ui htSpec=ui_ht-1, lenSpec=ui_len-1;
			if(!ui_isipow2(htSpec) || !ui_isipow2(lenSpec)) throw OptiVec_Pow2SizeErr();
			if(X.ui_ht < 2*htSpec || X.ui_len < 2*lenSpec) throw OptiVec_BigSizeErr();
			if(Win.ui_ht != 2*htSpec || Win.ui_len != 2*lenSpec) throw OptiVec_SizeErr();
			MEpspectrum(vx_m0, htSpec, lenSpec, X.vx_m0, X.ui_ht, X.ui_len, Win.vx_m0);
		}

		void p_convolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEpconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void p_convolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEpconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void p_deconvolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEpdeconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void p_deconvolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEpdeconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void l_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MElFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void l_Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MElRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void l_Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MElCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		//l_FFTtoC member of ceMatObj

		void l_filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MElfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void l_autocorr(cmta X)
		{
			enforcePow2();
			MElautocorr(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void l_xcorr(cmta X, cmta Y)
		{
			enforcePow2();
			MElxcorr(vx_m0, X.vx_m0, Y.vx_m0, ui_ht, ui_len);
		}

		void l_spectrum(cmta X, cmta Win)
		{
			ui htSpec=ui_ht-1, lenSpec=ui_len-1;
			if(!ui_isipow2(htSpec) || !ui_isipow2(lenSpec)) throw OptiVec_Pow2SizeErr();
			if(X.ui_ht < 2*htSpec || X.ui_len < 2*lenSpec) throw OptiVec_BigSizeErr();
			if(Win.ui_ht != 2*htSpec || Win.ui_len != 2*lenSpec) throw OptiVec_SizeErr();
			MElspectrum(vx_m0, htSpec, lenSpec, X.vx_m0, X.ui_ht, X.ui_len, Win.vx_m0);
		}

		void l_convolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MElconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void l_convolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MElconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void l_deconvolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEldeconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void l_deconvolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEldeconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void s_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MEsFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void s_Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MEsRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void s_Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MEsCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		//s_FFTtoC member of ceMatObj

		void s_filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MEsfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void s_autocorr(cmta X)
		{
			enforcePow2();
			MEsautocorr(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void s_xcorr(cmta X, cmta Y)
		{
			enforcePow2();
			MEsxcorr(vx_m0, X.vx_m0, Y.vx_m0, ui_ht, ui_len);
		}

		void s_spectrum(cmta X, cmta Win)
		{
			ui htSpec=ui_ht-1, lenSpec=ui_len-1;
			if(!ui_isipow2(htSpec) || !ui_isipow2(lenSpec)) throw OptiVec_Pow2SizeErr();
			if(X.ui_ht < 2*htSpec || X.ui_len < 2*lenSpec) throw OptiVec_BigSizeErr();
			if(Win.ui_ht != 2*htSpec || Win.ui_len != 2*lenSpec) throw OptiVec_SizeErr();
			MEsspectrum(vx_m0, htSpec, lenSpec, X.vx_m0, X.ui_ht, X.ui_len, Win.vx_m0);
		}

		void s_convolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEsconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void s_convolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEsconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void s_deconvolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEsdeconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void s_deconvolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEsdeconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MEFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MERows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MECols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		//FFTtoC member of ceMatObj

		void filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MEfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void autocorr(cmta X)
		{
			enforcePow2();
			MEautocorr(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void xcorr(cmta X, cmta Y)
		{
			enforcePow2();
			MExcorr(vx_m0, X.vx_m0, Y.vx_m0, ui_ht, ui_len);
		}

		void spectrum(cmta X, cmta Win)
		{
			ui htSpec=ui_ht-1, lenSpec=ui_len-1;
			if(!ui_isipow2(htSpec) || !ui_isipow2(lenSpec)) throw OptiVec_Pow2SizeErr();
			if(X.ui_ht < 2*htSpec || X.ui_len < 2*lenSpec) throw OptiVec_BigSizeErr();
			if(Win.ui_ht != 2*htSpec || Win.ui_len != 2*lenSpec) throw OptiVec_SizeErr();
			MEspectrum(vx_m0, htSpec, lenSpec, X.vx_m0, X.ui_ht, X.ui_len, Win.vx_m0);
		}

		void convolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void convolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void deconvolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEdeconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void deconvolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MEdeconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Data fitting
// All of the fitting functions themselves belong to eVecObj (see below).
// Only a few helper functions follow here:

        void setLinfitNeglect( const t& Thresh ) const
        { VE_setLinfitNeglect( Thresh ); }

        t getLinfitNeglect() const
        {  return VE_getLinfitNeglect(); }

        t nonlinfit_getChi2( ME_NONLINFITWORKSPACE *ws ) const
        { return ME_nonlinfit_getChi2( ws );  }

        t nonlinfitwW_getChi2( ME_NONLINFITWORKSPACE *ws ) const
        { return ME_nonlinfitwW_getChi2( ws );  }

        unsigned nonlinfit_getTestRun( ME_NONLINFITWORKSPACE *ws ) const
        {   return ME_nonlinfit_getTestRun( ws ); }

        unsigned nonlinfitwW_getTestRun( ME_NONLINFITWORKSPACE *ws ) const
        {   return ME_nonlinfitwW_getTestRun( ws ); }

        unsigned nonlinfit_getTestPar( ME_NONLINFITWORKSPACE *ws ) const
        { return ME_nonlinfit_getTestPar( ws ); }

        unsigned nonlinfitwW_getTestPar( ME_NONLINFITWORKSPACE *ws ) const
        { return ME_nonlinfitwW_getTestPar( ws ); }

        int  nonlinfit_getTestDir( ME_NONLINFITWORKSPACE *ws )const
        { return ME_nonlinfit_getTestDir( ws ); }

        int  nonlinfitwW_getTestDir( ME_NONLINFITWORKSPACE *ws ) const
        { return ME_nonlinfitwW_getTestDir( ws ); }

        void  nonlinfit_stop( ME_NONLINFITWORKSPACE *ws ) const
        {  ME_nonlinfit_stop( ws ); }

        void  nonlinfitwW_stop( ME_NONLINFITWORKSPACE *ws ) const
        {  ME_nonlinfitwW_stop( ws ); }

/////////////////////////////////////////////////////////////////////////////////////////
//Input and Output
//
		void fprint(FILE* stream, unsigned linewidth) const
		{
			enforceSize();
			MEfprint(stream,vx_m0,ui_ht, ui_len,linewidth);
		}

		void cprint() const
		{
			enforceSize();
			MEcprint(vx_m0,ui_ht,ui_len);
		}

		void print() const
		{
			fprint(stdout,80);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			MEwrite(stream,vx_m0,ui_ht,ui_len);
		}

		void read(FILE* stream)
		{
			enforceSize();
			MEread(vx_m0,ui_ht,ui_len,stream);
		}

		void setWriteFormat(char* formatString) const
		{
			VE_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VE_setWriteSeparate(sepString);
		}

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_ht,sizeof(ui),1,stream);
			fwrite(&ui_len,sizeof(ui),1,stream);
			VE_store(stream,vx_m0,ui_size);
		}

		void recall(FILE* stream)
		{
			ui sz;
			fread(&ui_ht,sizeof(ui),1,stream);
			fread(&ui_len,sizeof(ui),1,stream);
			setSize(ui_ht,ui_len);
			VE_recall(vx_m0,ui_size,stream);
		}

            #ifdef __MGRAPH_H
                void xyzAutoDensityMap( cvta X, cvta Y, COLORREF mincol, COLORREF maxcol ) const
                {
                    enforceSize(X.ui_size,Y.ui_size);
                    MExyzAutoDensityMap( X.vx_vect, Y.vx_vect, vx_m0, ui_ht, ui_len,
                                          mincol, maxcol );
                }

                void xyzDataDensityMap( cvta X, cvta Y ) const
                {
                    enforceSize(X.ui_size,Y.ui_size);
                    MExyzDataDensityMap( X.vx_vect, Y.vx_vect, vx_m0, ui_ht, ui_len);
                }

                void zAutoDensityMap( COLORREF mincol, COLORREF maxcol ) const
                {
                    enforceSize();
                    MEzAutoDensityMap( vx_m0, ui_ht, ui_len, mincol, maxcol );
                }

                void zDataDensityMap() const
                {
                    enforceSize();
                    MEzDataDensityMap( vx_m0, ui_ht, ui_len);
                }

            #endif   // __MGRAPH_H
	};


	inline vt tVecObj::operator*(cmta MY)
	{
		tVecObj tmp(this->ui_size);
		tmp.enforceSize();
		VEmulM(tmp.vx_vect,vx_vect,MY.vx_m0,MY.ui_ht,MY.ui_len);
		return tmp;
	}

	inline void tVecObj::Row_extract(cmta MA, const ui iRow)
    {
        if( MA.ui_ht <= iRow || ui_size < MA.ui_len || !ui_size ) throw OptiVec_SizeErr();
        MERow_extract( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len, iRow );
    }

	inline void tVecObj::Col_extract(cmta MA, const ui iCol)
    {
        if( MA.ui_len <= iCol || ui_size < MA.ui_ht || !ui_size ) throw OptiVec_SizeErr();
        MECol_extract( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len, iCol );
    }

	inline void tVecObj::Dia_extract(cmta MA)
    {
		if( !ui_size || ui_size != MA.ui_len || (MA.ui_len != MA.ui_ht) )throw OptiVec_SizeErr();
        MEDia_extract( vx_vect, MA.vx_m0, MA.ui_len );
    }

	inline void tVecObj::Rows_max(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
        MERows_max( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Cols_max(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
        MECols_max( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Rows_min(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
        MERows_min( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Cols_min(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
        MECols_min( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Rows_absmax(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
        MERows_absmax( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Cols_absmax(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
        MECols_absmax( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Rows_absmin(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
        MERows_absmin( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Cols_absmin(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
        MECols_absmin( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Rows_sum(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
        MERows_sum( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Cols_sum(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
        MECols_sum( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Rows_ssq(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
        MERows_ssq( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Cols_ssq(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
        MECols_ssq( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Rows_prod(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
        MERows_prod( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void tVecObj::Cols_prod(cmta MA)
    {
        if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
        MECols_prod( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

	inline void uiMatObj::Rows_distribution(cvta Limits, cmta MA, int mode=0)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_ht != MA.ui_ht ) throw OptiVec_SizeErr();
		return MERows_distribution(vx_m0,Limits.vx_vect,ui_size,MA.vx_m0,MA.ui_ht,MA.ui_len,mode);
	}

	inline void uiMatObj::Cols_distribution(cvta Limits, cmta MA, int mode=0)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_len != MA.ui_len ) throw OptiVec_SizeErr();
		return MECols_distribution(vx_m0,Limits.vx_vect,ui_size,MA.vx_m0,MA.ui_ht,MA.ui_len,mode);
	}

    inline void tVecObj::MmulV( cmta MA, cvta X )
    {
        if( ui_size != MA.ui_ht || X.ui_size != MA.ui_len ) throw OptiVec_SizeErr();
        MEmulV( vx_vect, MA.vx_m0, X.vx_vect, MA.ui_ht, MA.ui_len );
    }

    inline void tVecObj::MTmulV( cmta MA, cvta X )
    {
        if( ui_size != MA.ui_len || X.ui_size != MA.ui_ht ) throw OptiVec_SizeErr();
        METmulV( vx_vect, MA.vx_m0, X.vx_vect, MA.ui_ht, MA.ui_len );
    }

    inline void tVecObj::mulM( cvta X, cmta MA )
    {
        if( ui_size != MA.ui_len || X.ui_size != MA.ui_ht ) throw OptiVec_SizeErr();
        VEmulM( vx_vect, X.vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

    inline void tVecObj::mulMT( cvta X, cmta MA )
    {
        if( ui_size != MA.ui_ht || X.ui_size != MA.ui_len ) throw OptiVec_SizeErr();
        VEmulMT( vx_vect, X.vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
    }

    inline void tVecObj::LUsolve( cmta MLU, cvta B, const uiVecObj& Ind )
    {
        if( ui_size != MLU.ui_len || ui_size != MLU.ui_ht ||
            ui_size != B.ui_size || ui_size != Ind.ui_size ) throw OptiVec_SizeErr();
        MELUsolve( vx_vect, MLU.vx_m0, B.vx_vect, Ind.vx_vect, MLU.ui_len );
    }

    inline void tVecObj::LUimprove( cvta B, cmta MA, cmta MLU,
                          const uiVecObj& Ind )
    {
        if( ui_size != MLU.ui_len || ui_size != MLU.ui_ht ||
            ui_size != MA.ui_len || ui_size != MA.ui_ht ||
            ui_size != B.ui_size || ui_size != Ind.ui_size ) throw OptiVec_SizeErr();
        MELUimprove( vx_vect, B.vx_vect, MA.vx_m0, MLU.vx_m0, Ind.vx_vect, MLU.ui_len );
    }

	inline void tVecObj::CholeskyLsolve( cmta ML, cvta B )
	{
		if( ui_size != ML.ui_len || ui_size != ML.ui_ht ||
		    ui_size != B.ui_size ) throw OptiVec_SizeErr();
		MECholeskyLsolve( vx_vect, ML.vx_m0, B.vx_vect, ML.ui_len );
	}

	inline void tVecObj::CholeskyLimprove( cvta B, cmta MA, cmta ML )
	{
		if( ui_size != ML.ui_len || ui_size != ML.ui_ht || ui_size != MA.ui_len 
		 || ui_size != MA.ui_ht || ui_size != B.ui_size ) throw OptiVec_SizeErr();
		MECholeskyLimprove( vx_vect, B.vx_vect, MA.vx_m0, ML.vx_m0, ML.ui_len );
	}

	inline void tVecObj::CholeskyRsolve( cmta MR, cvta B )
	{
		if( ui_size != MR.ui_len || ui_size != MR.ui_ht ||
		    ui_size != B.ui_size ) throw OptiVec_SizeErr();
		MECholeskyRsolve( vx_vect, MR.vx_m0, B.vx_vect, MR.ui_len );
	}

	inline void tVecObj::CholeskyRimprove( cvta B, cmta MA, cmta MR )
	{
		if( ui_size != MR.ui_len || ui_size != MR.ui_ht || ui_size != MA.ui_len 
		 || ui_size != MA.ui_ht || ui_size != B.ui_size ) throw OptiVec_SizeErr();
		MECholeskyRimprove( vx_vect, B.vx_vect, MA.vx_m0, MR.vx_m0, MR.ui_len );
	}

    inline void tVecObj::SVsolve( cmta MU, cmta MV, cvta W, cvta B )
    { // result may overwrite B only for "normal", not for over- or under-determined systems
        if( MU.ui_ht < MU.ui_len || MU.ui_len != MV.ui_len || MV.ui_len != MV.ui_ht ||
            B.ui_size != ui_size || W.ui_size != MV.ui_len || ui_size != MU.ui_ht )
            throw OptiVec_SizeErr();
        MESVsolve( vx_vect, MU.vx_m0, MV.vx_m0, W.vx_vect, B.vx_vect, B.ui_size, MU.ui_len );
    }

    inline int tVecObj::solve( cmta MA, cvta B )
    {
        if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
            ui_size != B.ui_size ) throw OptiVec_SizeErr();
        return MEsolve( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_len );
    }

    inline int tVecObj::sym_solve( cmta MA, cvta B )
    {
        if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
            ui_size != B.ui_size ) throw OptiVec_SizeErr();
        return MEsymsolve( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_len );
    }

    inline int tVecObj::solveBySVD( cmta MA, cvta B )
    {
        if(ui_size != MA.ui_len || (B.ui_size != MA.ui_ht && B.vx_vect != vx_vect)) throw OptiVec_SizeErr();
        return MEsolveBySVD( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_ht, MA.ui_len );
    }

    inline int tVecObj::safeSolve( cmta MA, cvta B )
    {
        if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
            ui_size != B.ui_size ) throw OptiVec_SizeErr();
        return MEsafeSolve( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_len );
    }

    inline int tVecObj::sym_eigenvalues( tMatObj EigM, cmta MA, int CalcEigenVec )
    {
        if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
            (CalcEigenVec && (ui_size != EigM.ui_len || ui_size != EigM.ui_ht)) )
                  throw OptiVec_SizeErr();
        return( MEs_eigenvalues( vx_vect, EigM.vx_m0, MA.vx_m0, MA.ui_len, CalcEigenVec));
    }

    inline int tVecObj::sym_eigenvalues( tMatObj* EigM, cmta MA, int CalcEigenVec )
    {
        if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
            (CalcEigenVec && (ui_size != EigM->ui_len || ui_size != EigM->ui_ht)) )
                  throw OptiVec_SizeErr();
        return( MEs_eigenvalues( vx_vect, EigM->vx_m0, MA.vx_m0, MA.ui_len, CalcEigenVec));
    }

    inline int tVecObj::polyfit( cvta X, cvta Y )
    {   unsigned deg = ui_size-1;
        if( deg >= X.ui_size || X.ui_size != Y.ui_size) throw OptiVec_SizeErr();
        return VE_polyfit( vx_vect, deg, X.vx_vect, Y.vx_vect, X.ui_size );
    }

    inline int tVecObj::polyfitwW( tMatObj Covar, cvta X, cvta Y, cvta InvVar )
    {   unsigned deg = ui_size-1;
        if( deg >= X.ui_size || X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size) throw OptiVec_SizeErr();
        return VEpolyfitwW( vx_vect, Covar.vx_m0, deg,
                     X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size );
    }

    inline int tVecObj::polyfitwW( tMatObj* Covar, cvta X, cvta Y, cvta InvVar )
    {   unsigned deg = ui_size-1;
        if( deg >= X.ui_size || X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size) throw OptiVec_SizeErr();
        return VEpolyfitwW( vx_vect, Covar->vx_m0, deg,
                     X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size );
    }

    inline int tVecObj::linfit( const iVecObj& AStatus, cvta X, cvta Y,
                     void __vf funcs(tVector BasFuncs, t x, unsigned nfuncs) )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size) throw OptiVec_SizeErr();
        return VE_linfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size, X.vx_vect, Y.vx_vect, X.ui_size, funcs );
    }

    inline int tVecObj::linfitwW( tMatObj Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf funcs(tVector BasFuncs, t x, unsigned nfuncs) )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size) throw OptiVec_SizeErr();
        return VElinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                    X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size, funcs );
    }

    inline int tVecObj::linfitwW( tMatObj* Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf funcs(tVector BasFuncs, t x, unsigned nfuncs) )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size) throw OptiVec_SizeErr();
        return VElinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                    X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size, funcs );
    }

    inline int tVecObj::linfit( const iVecObj& AStatus, cvta X, cvta Y, cmta MZ,
                     void __vf funcs(tVector BasFuncs, t x, t y, unsigned nfuncs) )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht) throw OptiVec_SizeErr();
        return MElinfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size,
                   X.vx_vect, Y.vx_vect, MZ.vx_m0, MZ.ui_ht, MZ.ui_len, funcs );
    }

    inline int tVecObj::linfitwW( tMatObj Covar, const iVecObj& AStatus,
                     cvta X, cvta Y, cmta MZ, cmta MInvVar,
                     void __vf funcs(tVector BasFuncs, t x, t y, unsigned nfuncs) )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht ||
            MZ.ui_ht != MInvVar.ui_ht || MZ.ui_len != MInvVar.ui_len ||
            Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size)
            throw OptiVec_SizeErr();
        return MElinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                   X.vx_vect, Y.vx_vect, MZ.vx_m0, MInvVar.vx_m0, MZ.ui_ht, MZ.ui_len, funcs );
    }

    inline int tVecObj::linfitwW( tMatObj* Covar, const iVecObj& AStatus,
                     cvta X, cvta Y, cmta MZ, cmta MInvVar,
                     void __vf funcs(tVector BasFuncs, t x, t y, unsigned nfuncs) )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht ||
            MZ.ui_ht != MInvVar.ui_ht || MZ.ui_len != MInvVar.ui_len ||
            Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size)
            throw OptiVec_SizeErr();
        return MElinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                   X.vx_vect, Y.vx_vect, MZ.vx_m0, MInvVar.vx_m0, MZ.ui_ht, MZ.ui_len, funcs );
    }

	inline void tVecObj::setLinfitNeglect( const t& Thresh ) const
	{ VE_setLinfitNeglect( Thresh ); }

	inline t tVecObj::getLinfitNeglect() const
	{  return VE_getLinfitNeglect(); }

	// nonlinfit functions with complete syntax:
    inline t tVecObj::nonlinfit( const iVecObj& AStatus, cvta X, cvta Y,
                         void __vf modelfunc(tVector YModel, tVector XModel, ui size),
                         void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar),
						VE_NONLINFITWORKSPACE *FitWorkSpace, VE_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size) throw OptiVec_SizeErr();
        return VE_nonlinfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size, X.vx_vect, Y.vx_vect, X.ui_size,
                      modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

    inline t tVecObj::nonlinfitwW( tMatObj Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf modelfunc(tVector YModel, tVector XModel, ui size),
                     void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar),
						VE_NONLINFITWORKSPACE *FitWorkSpace, VE_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size) throw OptiVec_SizeErr();
        return VEnonlinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                       X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size,
                       modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

    inline t tVecObj::nonlinfitwW( tMatObj* Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf modelfunc(tVector YModel, tVector XModel, ui size),
                     void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar),
						VE_NONLINFITWORKSPACE *FitWorkSpace, VE_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size) throw OptiVec_SizeErr();
        return VEnonlinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                       X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size,
                       modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

    inline t tVecObj::nonlinfit( const iVecObj& AStatus, cvta X, cvta Y, cmta MZ,
                    void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
                    void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar),
						ME_NONLINFITWORKSPACE *FitWorkSpace, VE_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht) throw OptiVec_SizeErr();
        return MEnonlinfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size,
                      X.vx_vect, Y.vx_vect, MZ.vx_m0, MZ.ui_ht, MZ.ui_len,
                      modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

    inline t tVecObj::nonlinfitwW( tMatObj Covar, const iVecObj& AStatus,
                     cvta X, cvta Y, cmta MZ, cmta MInvVar,
                     void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
                     void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar),
						ME_NONLINFITWORKSPACE *FitWorkSpace, VE_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht ||
            MZ.ui_ht != MInvVar.ui_ht || MZ.ui_len != MInvVar.ui_len ||
            Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size)
            throw OptiVec_SizeErr();
        return MEnonlinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                        X.vx_vect, Y.vx_vect, MZ.vx_m0, MInvVar.vx_m0,
                        MZ.ui_ht, MZ.ui_len, modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

    inline t tVecObj::nonlinfitwW( tMatObj* Covar, const iVecObj& AStatus,
                     cvta X, cvta Y, cmta MZ, cmta MInvVar,
                     void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
                     void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar),
						ME_NONLINFITWORKSPACE *FitWorkSpace, VE_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht ||
            MZ.ui_ht != MInvVar.ui_ht || MZ.ui_len != MInvVar.ui_len ||
            Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size)
            throw OptiVec_SizeErr();
        return MEnonlinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                        X.vx_vect, Y.vx_vect, MZ.vx_m0, MInvVar.vx_m0,
                        MZ.ui_ht, MZ.ui_len, modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

	// nonlinfit functions with simplified syntax:
    inline t tVecObj::nonlinfit( const iVecObj& AStatus, cvta X, cvta Y,
                         void __vf modelfunc(tVector YModel, tVector XModel, ui size),
                         void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar) )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size) throw OptiVec_SizeErr();
        return VE_nonlinfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size, X.vx_vect, Y.vx_vect, X.ui_size,
                      modelfunc, derivatives, NULL, NULL );
    }

    inline t tVecObj::nonlinfitwW( tMatObj Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf modelfunc(tVector YModel, tVector XModel, ui size),
                     void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar) )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size) throw OptiVec_SizeErr();
        return VEnonlinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                       X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size,
                       modelfunc, derivatives, NULL, NULL );
    }

    inline t tVecObj::nonlinfitwW( tMatObj* Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf modelfunc(tVector YModel, tVector XModel, ui size),
                     void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar) )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size) throw OptiVec_SizeErr();
        return VEnonlinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                       X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size,
                       modelfunc, derivatives, NULL, NULL );
    }

    inline t tVecObj::nonlinfit( const iVecObj& AStatus, cvta X, cvta Y, cmta MZ,
                    void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
                    void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar) )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht) throw OptiVec_SizeErr();
        return MEnonlinfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size,
                      X.vx_vect, Y.vx_vect, MZ.vx_m0, MZ.ui_ht, MZ.ui_len,
                      modelfunc, derivatives, NULL, NULL );
    }

    inline t tVecObj::nonlinfitwW( tMatObj Covar, const iVecObj& AStatus,
                     cvta X, cvta Y, cmta MZ, cmta MInvVar,
                     void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
                     void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar) )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht ||
            MZ.ui_ht != MInvVar.ui_ht || MZ.ui_len != MInvVar.ui_len ||
            Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size)
            throw OptiVec_SizeErr();
        return MEnonlinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                        X.vx_vect, Y.vx_vect, MZ.vx_m0, MInvVar.vx_m0,
                        MZ.ui_ht, MZ.ui_len, modelfunc, derivatives, NULL, NULL );
    }

    inline t tVecObj::nonlinfitwW( tMatObj* Covar, const iVecObj& AStatus,
                     cvta X, cvta Y, cmta MZ, cmta MInvVar,
                     void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
                     void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar) )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht ||
            MZ.ui_ht != MInvVar.ui_ht || MZ.ui_len != MInvVar.ui_len ||
            Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size)
            throw OptiVec_SizeErr();
        return MEnonlinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                        X.vx_vect, Y.vx_vect, MZ.vx_m0, MInvVar.vx_m0,
                        MZ.ui_ht, MZ.ui_len, modelfunc, derivatives, NULL, NULL );
    }

// all multifit functions can be called only in their normal C form,
// because ME_EXPERIMENT cannot work with VecObjects, but requires actual pointers

#ifdef FMATOBJ_H
	inline void fMatObj::EtoF(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_EtoF(vx_m0,X.vx_m0,ui_size);
	}

	inline void eMatObj::FtoE(const fMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_FtoE(vx_m0,X.vx_m0,ui_size);
	}
#endif //FMATOBJ_H

#ifdef DMATOBJ_H
	inline void eMatObj::DtoE(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_DtoE(vx_m0,X.vx_m0,ui_size);
	}

	inline void dMatObj::EtoD(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_EtoD(vx_m0,X.vx_m0,ui_size);
	}
#endif //DMATOBJ_H

#ifdef BIMATOBJ_H
	inline void eMatObj::BItoE(const biMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_BItoE(vx_m0,X.vx_m0,ui_size);
	}

	inline int biMatObj::roundtoBI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_roundtoBI(vx_m0,X.vx_m0,ui_size);
	}

	inline int biMatObj::floortoBI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_floortoBI(vx_m0,X.vx_m0,ui_size);
	}

	inline int biMatObj::ceiltoBI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_ceiltoBI(vx_m0,X.vx_m0,ui_size);
	}

	inline int biMatObj::choptoBI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_choptoBI(vx_m0,X.vx_m0,ui_size);
	}
#endif //BIMATOBJ_H

#ifdef UBMATOBJ_H
	inline void eMatObj::UBtoE(const ubMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_UBtoE(vx_m0,X.vx_m0,ui_size);
	}

	inline int ubMatObj::roundtoUB(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_roundtoUB(vx_m0,X.vx_m0,ui_size);
	}

	inline int ubMatObj::floortoUB(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_floortoUB(vx_m0,X.vx_m0,ui_size);
	}

	inline int ubMatObj::ceiltoUB(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_ceiltoUB(vx_m0,X.vx_m0,ui_size);
	}

	inline int ubMatObj::choptoUB(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_choptoUB(vx_m0,X.vx_m0,ui_size);
	}
#endif //UBMATOBJ_H


#ifdef SIMATOBJ_H
	inline void eMatObj::SItoE(const siMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_SItoE(vx_m0,X.vx_m0,ui_size);
	}

	inline int siMatObj::roundtoSI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_roundtoSI(vx_m0,X.vx_m0,ui_size);
	}

	inline int siMatObj::floortoSI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_floortoSI(vx_m0,X.vx_m0,ui_size);
	}

	inline int siMatObj::ceiltoSI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_ceiltoSI(vx_m0,X.vx_m0,ui_size);
	}

	inline int siMatObj::choptoSI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_choptoSI(vx_m0,X.vx_m0,ui_size);
	}
#endif //SIMATOBJ_H

#ifdef USMATOBJ_H
	inline void eMatObj::UStoE(const usMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_UStoE(vx_m0,X.vx_m0,ui_size);
	}

	inline int usMatObj::roundtoUS(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_roundtoUS(vx_m0,X.vx_m0,ui_size);
	}

	inline int usMatObj::floortoUS(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_floortoUS(vx_m0,X.vx_m0,ui_size);
	}

	inline int usMatObj::ceiltoUS(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_ceiltoUS(vx_m0,X.vx_m0,ui_size);
	}

	inline int usMatObj::choptoUS(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_choptoUS(vx_m0,X.vx_m0,ui_size);
	}
#endif //USMATOBJ_H

#ifdef IMATOBJ_H
	inline void eMatObj::ItoE(const iMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_ItoE(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::roundtoI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_roundtoI(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::floortoI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_floortoI(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::ceiltoI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_ceiltoI(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::choptoI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_choptoI(vx_m0,X.vx_m0,ui_size);
	}
#endif //IMATOBJ_H

#ifdef UMATOBJ_H
	inline void eMatObj::UtoE(const uMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_UtoE(vx_m0,X.vx_m0,ui_size);
	}

	inline int uMatObj::roundtoU(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_roundtoU(vx_m0,X.vx_m0,ui_size);
	}

	inline int uMatObj::floortoU(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_floortoU(vx_m0,X.vx_m0,ui_size);
	}

	inline int uMatObj::ceiltoU(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_ceiltoU(vx_m0,X.vx_m0,ui_size);
	}

	inline int uMatObj::choptoU(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_choptoU(vx_m0,X.vx_m0,ui_size);
	}
#endif //UMATOBJ_H

#ifdef LIMATOBJ_H
	inline void eMatObj::LItoE(const liMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_LItoE(vx_m0,X.vx_m0,ui_size);
	}

	inline int liMatObj::roundtoLI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_roundtoLI(vx_m0,X.vx_m0,ui_size);
	}

	inline int liMatObj::floortoLI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_floortoLI(vx_m0,X.vx_m0,ui_size);
	}

	inline int liMatObj::ceiltoLI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_ceiltoLI(vx_m0,X.vx_m0,ui_size);
	}

	inline int liMatObj::choptoLI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_choptoLI(vx_m0,X.vx_m0,ui_size);
	}
#endif //LIMATOBJ_H

#ifdef ULMATOBJ_H
	inline void eMatObj::ULtoE(const ulMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_ULtoE(vx_m0,X.vx_m0,ui_size);
	}

	inline int ulMatObj::roundtoUL(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_roundtoUL(vx_m0,X.vx_m0,ui_size);
	}

	inline int ulMatObj::floortoUL(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_floortoUL(vx_m0,X.vx_m0,ui_size);
	}

	inline int ulMatObj::ceiltoUL(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_ceiltoUL(vx_m0,X.vx_m0,ui_size);
	}

	inline int ulMatObj::choptoUL(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_choptoUL(vx_m0,X.vx_m0,ui_size);
	}
#endif //ULMATOBJ_H

#ifdef UQMATOBJ_H
	inline void eMatObj::UQtoE(const uqMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_UQtoE(vx_m0,X.vx_m0,ui_size);
	}

	inline int uqMatObj::roundtoUQ(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_roundtoUQ(vx_m0,X.vx_m0,ui_size);
	}

	inline int uqMatObj::floortoUQ(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_floortoUQ(vx_m0,X.vx_m0,ui_size);
	}

	inline int uqMatObj::ceiltoUQ(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_ceiltoUQ(vx_m0,X.vx_m0,ui_size);
	}

	inline int uqMatObj::choptoUQ(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_choptoUQ(vx_m0,X.vx_m0,ui_size);
	}
#endif //UQMATOBJ_H

#ifdef QIMATOBJ_H
	inline void eMatObj::QItoE(const qiMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_QItoE(vx_m0,X.vx_m0,ui_size);
	}

	inline int qiMatObj::roundtoQI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_roundtoQI(vx_m0,X.vx_m0,ui_size);
	}

	inline int qiMatObj::floortoQI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_floortoQI(vx_m0,X.vx_m0,ui_size);
	}

	inline int qiMatObj::ceiltoQI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_ceiltoQI(vx_m0,X.vx_m0,ui_size);
	}

	inline int qiMatObj::choptoQI(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VE_choptoQI(vx_m0,X.vx_m0,ui_size);
	}
#endif //QIMATOBJ_H


#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
}  // end of namespace OptiVec
#endif

#undef cmta
#undef cvta
#undef cua
#undef cuint
#undef cta

#undef vta
#undef mta
#undef ta

#undef vt
#undef mt
#undef t
#undef tVector
#undef tMatrix

#undef vtcplx
#undef tcplx

#undef tMatObj
#undef tVecObj

#pragma warn .inl
#endif

#define EMATOBJ_H
#endif //EMATOBJ_H
