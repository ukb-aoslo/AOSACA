/* dMatObj.H

  object-oriented interface for OptiVec matrix functions of type "double"

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef DMATOBJ_H

#include <VecObj.h>
#include <dVecObj.h>
#include <uiVecObj.h>
#include <iVecObj.h>

#define cmta const matrix<double>&
#define cvta const vector<double>&
#define cta  const double&
#define cua  const ui&
#define cuint const ui

#define mta  matrix<double>&
#define vta  vector<double>&
#define ta   double&

#define mt   matrix<double>
#define vt   vector<double>
#define t    double
#define tcplx  dComplex
#define tMatrix dMatrix
#define tVector dVector

#define tMatObj dMatObj
#define tVecObj dVecObj
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
			{	mx_matr=MD_matrix(ht,len); vx_m0=mx_matr[0];
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
                {	mx_matr=MD_matrix0(ht,len); vx_m0=mx_matr[0];}
				else
				{	mx_matr=MD_matrix(ht,len);  vx_m0=mx_matr[0];
					VD_equC(vx_m0,ui_size,fill);}
            }
		}

		matrix(cmta init)
		{	if(init.ui_size)
			{	mx_matr= MD_matrix(init.ui_ht, init.ui_len); vx_m0=mx_matr[0];
				ui_ht=init.ui_ht; ui_len=init.ui_len; ui_size=init.ui_size;
				VD_equV(vx_m0, init.vx_m0, ui_size);
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
				mx_matr= MD_matrix(ht, len); vx_m0=mx_matr[0];
				ui_len=len; ui_ht=ht; ui_size= size;
			}
		}

		void setSize(cmta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_len != X.ui_len || ui_ht != X.ui_ht) //only allocate if different sizes
			{	if(mx_matr) M_free(mx_matr);
				mx_matr= MD_matrix(X.ui_ht, X.ui_len); vx_m0=mx_matr[0];
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
			VD_equV(vx_m0, matr.vx_m0, ui_size);
			return *this;}

		mta operator=(cta scalar)
		{	enforceSize();
			VD_equC(vx_m0, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		tVector operator[](const int& index){return mx_matr[index];}

		mta operator+=(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			VD_accV(vx_m0, X.vx_m0, ui_size);
			return *this;}

		mta operator+=(cta scalar)
		{
			enforceSize();
			VD_addC(vx_m0, vx_m0, ui_size, scalar);
			return *this;}

		mta operator*=(cta scalar)
		{
			enforceSize();
			VD_mulC(vx_m0,vx_m0,ui_size,scalar);
			return *this;}

		mt operator+(cmta rhs)
		{	enforceSize(rhs.ui_ht, rhs.ui_len);
			tMatObj tmp(this->ui_ht, this->ui_len);
			VD_addV(tmp.vx_m0,this->vx_m0,rhs.vx_m0,tmp.ui_size);
			return tmp;}

		mt operator+(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VD_addC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		mt operator-(cmta rhs)
		{	enforceSize(rhs.ui_ht, rhs.ui_len);
			tMatObj tmp(this->ui_ht, this->ui_len);
			VD_subV(tmp.vx_m0,this->vx_m0,rhs.vx_m0,tmp.ui_size);
			return tmp;}

		mt operator-(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VD_subC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		mt operator*(cmta rhs)
		{	enforceLen(rhs.ui_ht);
			tMatObj tmp(this->ui_ht, rhs.ui_len);
			tmp.enforceSize();
			MDmulM(tmp.vx_m0,this->vx_m0,rhs.vx_m0,this->ui_ht, this->ui_len,rhs.ui_len);
			return tmp;}

		vt operator*(cvta rhs)
		{	enforceLen(rhs.ui_size);
			tVecObj tmp(this->ui_ht);
			tmp.enforceSize();
			MDmulV(tmp.vx_vect,this->vx_m0,rhs.vx_vect,this->ui_ht, this->ui_len);
			return tmp;}

		// operator*(cvta VX, cmta MY) is member of dVecObj, see below

		mt operator*(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VD_mulC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		mt operator/(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VD_divC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		friend mt operator+(cta C, cmta X)
		{	tMatObj tmp(X.ui_ht,X.ui_len);
			VD_addC(tmp.vx_m0,X.vx_m0,tmp.ui_size,C);
			return tmp;}

		friend mt operator-(cta C, cmta X)
		{	tMatObj tmp(X.ui_ht,X.ui_len);
			VD_subrC(tmp.vx_m0,X.vx_m0,tmp.ui_size,C);
			return tmp;}

		friend mt operator*(cta C, cmta X)
		{	tMatObj tmp(X.ui_ht,X.ui_len);
			VD_mulC(tmp.vx_m0,X.vx_m0,tmp.ui_size,C);
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
			if(ui_size){ ui_ht=ht;ui_len=len;mx_matr= MD_matrix(ht,len);vx_m0=mx_matr[0];}
		}

		void _matrix0(cuint ht, cuint len) //underscore necessary to avoid confusing with constructor
		{
			dealloc();
			ui_size=((ui)ht)*len;
			if(ui_size){ ui_ht=ht;ui_len=len;mx_matr= MD_matrix0(ht,len);vx_m0=mx_matr[0];}
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single matrix elements
//
		t* Pelement(cuint m, cuint n) const
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MDPelement(vx_m0,ui_ht,ui_len,m,n);
		}

		t element(cuint m, cuint n) const
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MDelement(vx_m0,ui_ht,ui_len,m,n);
		}

		void getElement(t *y, cuint m, cuint n)
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MDgetElement(y,vx_m0,ui_ht,ui_len,m,n);
		}

		void setElement(cuint m, cuint n, cta C)
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			MDsetElement(vx_m0,ui_ht,ui_len,m,n,C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//

		void equ0()
		{
			enforceSize();
			VD_equ0(vx_m0,ui_size);
		}

		void equ1()
		{
			enforceSize();
			MDequ1(vx_m0,ui_len);
		}

		void equm1()
		{
			enforceSize();
			MDequm1(vx_m0,ui_len);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VD_random(vx_m0, ui_size, seed, Min, Max);
		}

		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VD_randomLC(vx_m0, ui_size, seed, Min, Max, state);
		}

		void outerprod(cvta X, cvta Y)
		{
			enforceSize( X.ui_size, Y.ui_size);
			MDouterprod(vx_m0, X.vx_vect, Y.vx_vect, ui_ht, ui_len);
		}

		void Row_equ0(cuint iRow)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MDRow_equ0(vx_m0, ui_ht, ui_len, iRow);
		}

		void Col_equ0(cuint iCol)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MDCol_equ0(vx_m0, ui_ht, ui_len, iCol);
		}

		void Dia_equ0()
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MDDia_equ0(vx_m0, ui_len);
		}

		void Row_equC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MDRow_equC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_equC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MDCol_equC(vx_m0, ui_ht, ui_len, iCol, C);
		}

		void Dia_equC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MDDia_equC(vx_m0, ui_len, C);
		}

		void Row_equV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MDRow_equV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_equV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MDCol_equV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

		void Dia_equV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MDDia_equV(vx_m0, ui_len, X.vx_vect);
		}

		void Trd_equM(cmta MTrd)
		{
			if( MTrd.ui_ht != 3 || ui_ht != ui_len || ui_len != MTrd.ui_len )throw OptiVec_SizeErr();
			MDTrd_equM(vx_m0, MTrd.vx_m0, ui_len);
		}

		void Trd_extract(cmta MA)
		{
			if( ui_ht != 3 || MA.ui_ht != MA.ui_len || MA.ui_len != ui_len )throw OptiVec_SizeErr();
			MDTrd_extract(vx_m0, MA.vx_m0, ui_len);
		}

		void equM(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			MDequM(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void neg(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			MDneg(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void UequL()
		{
			if( !ui_len || ui_len != ui_ht )throw OptiVec_SizeErr();
			MDUequL(vx_m0, ui_len);
		}

		void LequU()
		{
			if( !ui_len || ui_len != ui_ht )throw OptiVec_SizeErr();
			MDLequU(vx_m0, ui_len);
		}

		void Parzen()
		{
			enforceSize();
			MDParzen(vx_m0, ui_ht, ui_len);
		}

		void Hann()
		{
			enforceSize();
			MDHann(vx_m0, ui_ht, ui_len);
		}

		void Hanning()  // erroneous name for Hann
		{
			enforceSize();
			MDHann(vx_m0, ui_ht, ui_len);
		}

		void Welch()
		{
			enforceSize();
			MDWelch(vx_m0, ui_ht, ui_len);
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//
		//defined by including fMatObj.h
		void FtoD(const fMatObj& X);

		//defined by including eMatObj.h
		void EtoD(const eMatObj& X);

		//defined by including biMatObj.h
		void BItoD(const biMatObj& X);

		//defined by including ubMatObj.h
		void UBtoD(const ubMatObj& X);

		//defined by including siMatObj.h
		void SItoD(const siMatObj& X);

		//defined by including usMatObj.h
		void UStoD(const usMatObj& X);

		//defined by including iMatObj.h
		void ItoD(const iMatObj& X);

		//defined by including uMatObj.h
		void UtoD(const uMatObj& X);

		//defined by including liMatObj.h
		void LItoD(const liMatObj& X);

		//defined by including ulMatObj.h
		void ULtoD(const ulMatObj& X);

		#if defined _WIN64
			//defined by including uqMatObj.h
			void UQtoD(const uqMatObj& X);
		#endif

		//defined by including qiMatObj.h
		void QItoD(const qiMatObj& X);



/////////////////////////////////////////////////////////////////////////////////////////
//Submatrices
//
		void submatrix(cmta MSrce, cuint firstRowInCol, cuint sampInCol, cuint firstColInRow, cuint sampInRow )
		{
			if( (MSrce.ui_ht  <= firstRowInCol+(ui_ht-1) *sampInCol) ||
                (MSrce.ui_len <= firstColInRow+(ui_len-1)*sampInRow) ) throw OptiVec_SizeErr();
			MDsubmatrix(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
                 firstRowInCol, sampInCol, firstColInRow, sampInRow );
		}

		void submatrix_equM(cuint firstRowInCol, cuint sampInCol, cuint firstColInRow, cuint sampInRow, cmta MSrce)
		{
			if( (ui_ht  <= firstRowInCol+(MSrce.ui_ht-1) *sampInCol) ||
                (ui_len <= firstColInRow+(MSrce.ui_len-1)*sampInRow) ) throw OptiVec_SizeErr();
			MDsubmatrix_equM(vx_m0, ui_ht, ui_len,
                 firstRowInCol, sampInCol, firstColInRow, sampInRow,
                 MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len );
		}

		void equMblock(cmta MSrce, cuint firstRowInCol, cuint firstColInRow )
		{
			if( (MSrce.ui_ht  < firstRowInCol+ui_ht) ||
                (MSrce.ui_len < firstColInRow+ui_len) ) throw OptiVec_SizeErr();
			MDequMblock(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
                 firstRowInCol, firstColInRow );
		}

		void equMblockT(cmta MSrce, cuint firstRowInCol, cuint firstColInRow )
		{
			if( (MSrce.ui_ht  < firstRowInCol+ui_len) ||
                (MSrce.ui_len < firstColInRow+ui_ht) ) throw OptiVec_SizeErr();
			MDequMblockT(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
                 firstRowInCol, firstColInRow );
		}

		void block_equM(cuint firstRowInCol, cuint firstColInRow, cmta MSrce )
		{
			if( (ui_ht  < firstRowInCol+MSrce.ui_ht) ||
                (ui_len < firstColInRow+MSrce.ui_len) ) throw OptiVec_SizeErr();
			MDblock_equM(vx_m0, ui_ht, ui_len, firstRowInCol, firstColInRow,
                 MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len );
		}

		void block_equMT(cuint firstRowInCol, cuint firstColInRow, cmta MSrce )
		{
			if( (ui_ht  < firstRowInCol+MSrce.ui_len) ||
                (ui_len < firstColInRow+MSrce.ui_ht) ) throw OptiVec_SizeErr();
			MDblock_equMT(vx_m0, ui_ht, ui_len, firstRowInCol, firstColInRow,
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
				MDRow_delete(vx_m0, vx_m0, ui_ht--, ui_len, iRow);
			}
			else
			{	enforceSize(MA.ui_ht-1, MA.ui_len);
				MDRow_delete(vx_m0, MA.vx_m0, MA.ui_ht, MA.ui_len, iRow);
			}
		}

		void Col_delete(cmta MA, cuint iCol)
		{
			if( MA.ui_len <= iCol ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = MD_matrix( ui_ht, ui_len-1 );
				MDCol_delete(tmp[0], MA.vx_m0, ui_ht, ui_len--, iCol);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size -= ui_ht;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht, MA.ui_len-1);
				MDCol_delete(vx_m0, MA.vx_m0, ui_ht, ui_len, iCol);
			}
		}

		void Row_insert(cmta MA, cuint iRow, cvta X)
		{
			if( ui_ht <= iRow ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = MD_matrix( ++ui_ht, ui_len );
				MDRow_insert(tmp[0], MA.vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size += ui_len;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht+1, MA.ui_len);
				MDRow_insert(vx_m0, MA.vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
			}
		}

		void Col_insert(cmta MA, cuint iCol, cvta X)
		{
			if( ui_len <= iCol ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = MD_matrix( ui_ht, ++ui_len );
				MDCol_insert(tmp[0], MA.vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size += ui_ht;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht, MA.ui_len+1);
				MDCol_insert(vx_m0, MA.vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
			}
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Basic arithmetic operations performed on one single row, or one single column
// of any matrix, or on the diagonal of a square matrix
//

		void Row_neg(cuint iRow)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MDRow_neg(vx_m0, ui_ht, ui_len, iRow);
		}

		void Col_neg(cuint iCol)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MDCol_neg(vx_m0, ui_ht, ui_len, iCol);
		}

		void Row_addC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MDRow_addC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_addC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MDCol_addC(vx_m0, ui_ht, ui_len, iCol, C);
		}

                void Dia_addC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MDDia_addC(vx_m0, ui_len, C);
		}

		void Row_addV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MDRow_addV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_addV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MDCol_addV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

                void Dia_addV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MDDia_addV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_subC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MDRow_subC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_subC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MDCol_subC(vx_m0, ui_ht, ui_len, iCol, C);
		}

                void Dia_subC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MDDia_subC(vx_m0, ui_len, C);
		}

		void Row_subV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MDRow_subV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_subV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MDCol_subV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

                void Dia_subV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MDDia_subV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_subrC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MDRow_subrC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_subrC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MDCol_subrC(vx_m0, ui_ht, ui_len, iCol, C);
		}

                void Dia_subrC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MDDia_subrC(vx_m0, ui_len, C);
		}

		void Row_subrV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MDRow_subrV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_subrV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MDCol_subrV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

                void Dia_subrV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MDDia_subrV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_mulC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MDRow_mulC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_mulC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MDCol_mulC(vx_m0, ui_ht, ui_len, iCol, C);
		}

                void Dia_mulC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MDDia_mulC(vx_m0, ui_len, C);
		}

		void Row_mulV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MDRow_mulV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_mulV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MDCol_mulV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

                void Dia_mulV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MDDia_mulV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_divC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MDRow_divC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_divC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MDCol_divC(vx_m0, ui_ht, ui_len, iCol, C);
		}

                void Dia_divC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MDDia_divC(vx_m0, ui_len, C);
		}

		void Row_divV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MDRow_divV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_divV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MDCol_divV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

                void Dia_divV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MDDia_divV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_divrC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MDRow_divrC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_divrC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MDCol_divrC(vx_m0, ui_ht, ui_len, iCol, C);
		}

                void Dia_divrC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MDDia_divrC(vx_m0, ui_len, C);
		}

		void Row_divrV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MDRow_divrV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_divrV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MDCol_divrV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

                void Dia_divrV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MDDia_divrV(vx_m0, ui_len, X.vx_vect);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//One-dimensional vector operations
//performed along all rows or columns, or along the diagonal of a square matrix
//(some of these functions belong to dVecObj.h)

		t Dia_max() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MDDia_max(vx_m0, ui_len);
		}

		t Dia_min() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MDDia_min(vx_m0, ui_len);
		}

		t Dia_absmax() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MDDia_absmax(vx_m0, ui_len);
		}

		t Dia_absmin() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MDDia_absmin(vx_m0, ui_len);
		}

		t Dia_sum() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MDDia_sum(vx_m0, ui_len);
		}

		t Dia_ssq() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MDDia_ssq(vx_m0, ui_len);
		}

		t Dia_prod() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MDDia_prod(vx_m0, ui_len);
		}

		void Rows_runsum()
		{
			enforceSize();
			MDRows_runsum(vx_m0, ui_ht, ui_len);
		}

		void Cols_runsum()
		{
			enforceSize();
			MDCols_runsum(vx_m0, ui_ht, ui_len);
		}

		void Rows_runprod()
		{
			enforceSize();
			MDRows_runprod(vx_m0, ui_ht, ui_len);
		}

		void Cols_runprod()
		{
			enforceSize();
			MDCols_runprod(vx_m0, ui_ht, ui_len);
		}

		void Rows_rotate(const ssize_t pos)
		{
			enforceSize();
			MDRows_rotate(vx_m0, ui_ht, ui_len, pos);
		}

		void Cols_rotate(const ssize_t pos)
		{
			enforceSize();
			MDCols_rotate(vx_m0, ui_ht, ui_len, pos);
		}

		void Rows_rotate_buf(const ssize_t pos, cmta MBuf)
		{
			enforceSize();
			MDRows_rotate_buf(vx_m0, ui_ht, ui_len, pos, MBuf.vx_m0);
		}

		void Cols_rotate_buf(const ssize_t pos, cmta MBuf)
		{
			enforceSize();
			MDCols_rotate_buf(vx_m0, ui_ht, ui_len, pos, MBuf.vx_m0);
		}

		void Rows_reflect()
		{
			enforceSize();
			MDRows_reflect(vx_m0, ui_ht, ui_len);
		}

		void Cols_reflect()
		{
			enforceSize();
			MDCols_reflect(vx_m0, ui_ht, ui_len);
		}

		void Rows_rev()
		{
			enforceSize();
			MDRows_rev(vx_m0, ui_ht, ui_len);
		}

		void Cols_rev()
		{
			enforceSize();
			MDCols_rev(vx_m0, ui_ht, ui_len);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Operations involving two rows or two colums of one matrix
//
		void Rows_exchange(cuint row1, cuint row2)
		{
			if( !ui_len || (ui_ht <= row1) || (ui_ht <= row2))throw OptiVec_SizeErr();
			MDRows_exchange(vx_m0, ui_ht, ui_len, row1, row2);
		}

		void Cols_exchange(cuint col1, cuint col2)
		{
			if( !ui_len || (ui_ht <= col1) || (ui_ht <= col2))throw OptiVec_SizeErr();
			MDCols_exchange(vx_m0, ui_ht, ui_len, col1, col2);
		}

		void Rows_add(cuint destRow, cuint srceRow)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MDRows_add(vx_m0, ui_ht, ui_len, destRow, srceRow);
		}

		void Cols_add(cuint destCol, cuint srceCol)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol))throw OptiVec_SizeErr();
			MDCols_add(vx_m0, ui_ht, ui_len, destCol, srceCol);
		}

		void Rows_sub(cuint destRow, cuint srceRow)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MDRows_sub(vx_m0, ui_ht, ui_len, destRow, srceRow);
		}

		void Cols_sub(cuint destCol, cuint srceCol)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol))throw OptiVec_SizeErr();
			MDCols_sub(vx_m0, ui_ht, ui_len, destCol, srceCol);
		}

		void Rows_Cadd(cuint destRow, cuint srceRow, cta C)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MDRows_Cadd(vx_m0, ui_ht, ui_len, destRow, srceRow, C);
		}

		void Cols_Cadd(cuint destCol, cuint srceCol, cta C)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol))throw OptiVec_SizeErr();
			MDCols_Cadd(vx_m0, ui_ht, ui_len, destCol, srceCol, C);
		}

		void Rows_lincomb(cuint destRow, cta destC, cuint srceRow, cta srceC)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MDRows_lincomb(vx_m0, ui_ht, ui_len, destRow, destC, srceRow, srceC);
		}

		void Cols_lincomb(cuint destCol, cta destC, cuint srceCol, cta srceC)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol)) throw OptiVec_SizeErr();
			MDCols_lincomb(vx_m0, ui_ht, ui_len, destCol, destC, srceCol, srceC);
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Center of Gravity
//

		dComplex centerOfGravityInd() const
		{
			enforceSize();
			return MDcenterOfGravityInd(vx_m0,ui_ht, ui_len);
		}

		dComplex centerOfGravityV(cvta X, cvta Y) const
		{
            if( ui_ht != Y.ui_size || ui_len != X.ui_size || !ui_size )
                throw OptiVec_SizeErr();
			return MDcenterOfGravityV(X.vx_vect,Y.vx_vect,vx_m0,ui_ht,ui_len);
		}

/////////////////////////////////////////////////////////////////////////////////////////
// Matrix transposition and rotation
//
		void transpose(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MDtranspose(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate90(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MDrotate90(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate180(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MDrotate180(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate270(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MDrotate270(vx_m0, MA.vx_m0, ui_ht, ui_len);
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
			MDpolyinterpol(vx_m0,X.vx_vect,Y.vx_vect,ui_ht,ui_len,
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
			MDratinterpol(vx_m0,X.vx_vect,Y.vx_vect,ui_ht,ui_len,
				Xtab.vx_vect,Ytab.vx_vect,MZtab.vx_m0,MZtab.ui_ht,MZtab.ui_len,degX,degY);
		}

		void natCubSplineInterpol(cvta X, cvta Y, cvta Xtab, cvta Ytab, cmta MZtab)
		{
            if( ui_ht != Y.ui_size || ui_len != X.ui_size || !ui_size ||
                MZtab.ui_ht != Ytab.ui_size || MZtab.ui_len != Xtab.ui_size
                || !MZtab.ui_size )    throw OptiVec_SizeErr();
			if((Xtab.ui_size<3) || (Ytab.ui_size<3)) throw OptiVec_SmallSizeErr();
			MDnatCubSplineInterpol(vx_m0,X.vx_vect,Y.vx_vect,ui_ht,ui_len,
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
			MDaddM(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void addMT(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht,  MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MDaddMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void subM(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MDsubM(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void subMT(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht,  MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MDsubMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void subrM(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MDsubM(vx_m0, MB.vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void subrMT(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht,  MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MDsubrMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void mulC(cmta MA, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			MDmulC(vx_m0, MA.vx_m0, ui_ht, ui_len, C);
		}

		void divC(cmta MA, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			MDdivC(vx_m0, MA.vx_m0, ui_ht, ui_len, C);
		}

		void s_addM(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MDsaddM(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, C);
		}

		void s_addMT(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MDsaddMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, C);
		}

		void s_subM(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MDssubM(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, C);
		}

		void s_subMT(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MDssubMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, C);
		}

		void s_subrM(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MDssubM(vx_m0, MB.vx_m0, MA.vx_m0, ui_ht, ui_len, C);
		}

		void s_subrMT(cmta MA, cmta MB, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MDssubrMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, C);
		}

		void lincomb(cmta MA, cmta MB, cta CA, cta CB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MDlincomb(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, CA, CB);
		}

		//mixed multiplications matrix * vector belong to dVecObj
        void mulM( cmta MA, cmta MB )
        {
            if( ui_ht != MA.ui_ht || ui_len != MB.ui_len || MB.ui_ht != MA.ui_len )throw OptiVec_SizeErr();
            MDmulM( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_len);
        }

        void mulMT( cmta MA, cmta MB )
        {
            if( ui_ht != MA.ui_ht || ui_len != MB.ui_ht || MB.ui_len != MA.ui_len )throw OptiVec_SizeErr();
            MDmulMT( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_ht);
        }

        void TmulM( cmta MA, cmta MB )
        {
            if( ui_ht != MA.ui_len || ui_len != MB.ui_len || MB.ui_ht != MA.ui_ht )throw OptiVec_SizeErr();
            MDTmulM( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_len);
        }

        void TmulMT( cmta MA, cmta MB )
        {
            if( ui_ht != MA.ui_len || ui_len != MB.ui_ht || MB.ui_len != MA.ui_ht )throw OptiVec_SizeErr();
            MDTmulMT( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_ht);
        }

        void dia_mulM( cvta MADia, cmta MB )
        {
            if( ui_ht != MADia.ui_size || ui_len != MB.ui_len || MB.ui_ht != MADia.ui_size )throw OptiVec_SizeErr();
            MDdiamulM( vx_m0, MADia.vx_vect, MB.vx_m0, MB.ui_ht, MB.ui_len );
        }

        void dia_mulMT( cvta MADia, cmta MB )
        {
            if( ui_ht != MADia.ui_size || ui_len != MB.ui_ht || MB.ui_len != MADia.ui_size )throw OptiVec_SizeErr();
            MDdiamulMT( vx_m0, MADia.vx_vect, MB.vx_m0, MB.ui_ht, MB.ui_len );
        }

        void mulMdia( cmta MA, cvta MBDia )
        {
            if( ui_ht != MA.ui_ht || ui_len != MBDia.ui_size || MBDia.ui_size != MA.ui_len )throw OptiVec_SizeErr();
            MDmulMdia( vx_m0, MA.vx_m0, MBDia.vx_vect, MA.ui_ht, MA.ui_len );
        }

        void TmulMdia( cmta MA, cvta MBDia )
        {
            if( ui_ht != MA.ui_len || ui_len != MBDia.ui_size || MBDia.ui_size != MA.ui_ht )throw OptiVec_SizeErr();
            MDTmulMdia( vx_m0, MA.vx_m0, MBDia.vx_vect, MA.ui_ht, MA.ui_len );
        }

/////////////////////////////////////////////////////////////////////////////////////////
//Linear Algebra
//
        int LUdecompose( uiVecObj Ind, cmta MA )
        {
            if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len || ui_ht != Ind.ui_size )
                throw OptiVec_SizeErr();
            return MDLUdecompose( vx_m0, Ind.vx_vect, MA.vx_m0, ui_len );
        }

        int LUdecompose( uiVecObj* Ind, cmta MA )
        {
            if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len || ui_ht != Ind->ui_size )
                throw OptiVec_SizeErr();
            return MDLUdecompose( vx_m0, Ind->vx_vect, MA.vx_m0, ui_len );
        }

        int  LUDresult() const
        {
            return MD_LUDresult();
        }

		void LUDsetEdit(cta Thresh) const
		{
			MD_LUDsetEdit(Thresh);
		}

		t LUDgetEdit() const
		{
			return MD_LUDgetEdit();
		}

        void LUinv( cmta MLU, const uiVecObj& Ind )
        {
            if( ui_ht != MLU.ui_ht || ui_len != MLU.ui_len || ui_ht != ui_len || ui_ht != Ind.ui_size )
                throw OptiVec_SizeErr();
            MDLUinv( vx_m0, MLU.vx_m0, Ind.vx_vect, ui_len );
        }

        t LUdet( int permut ) const
        {
            if( ui_ht != ui_len ) throw OptiVec_SizeErr();
            return MDLUdet( vx_m0, ui_len, permut );
        }

		int CholeskyLdecompose( cmta MA )
		{
			if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
					throw OptiVec_SizeErr();
			return MDCholeskyLdecompose( vx_m0, MA.vx_m0, ui_len );
		}

		void CholeskyLinv( cmta ML )
		{
			if( ui_ht != ML.ui_ht || ui_len != ML.ui_len || ui_ht != ui_len )
					throw OptiVec_SizeErr();
			MDCholeskyLinv( vx_m0, ML.vx_m0, ui_len );
		}

		int CholeskyRdecompose( cmta MA )
		{
			if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
					throw OptiVec_SizeErr();
			return MDCholeskyRdecompose( vx_m0, MA.vx_m0, ui_len );
		}

		void CholeskyRinv( cmta MR )
		{
			if( ui_ht != MR.ui_ht || ui_len != MR.ui_len || ui_ht != ui_len )
					throw OptiVec_SizeErr();
			MDCholeskyRinv( vx_m0, MR.vx_m0, ui_len );
		}

		t CholeskyDet() const
		{
			if( ui_ht != ui_len ) throw OptiVec_SizeErr();
			return MDCholeskyDet( vx_m0, ui_len );
		}

        int SVdecompose( tMatObj *MV, tVecObj *W, cmta MA )
        {
            if( (MA.ui_ht < MA.ui_len ? (ui_ht != ui_len) : (ui_ht != MA.ui_ht))
              || ui_len != MA.ui_len || ui_len != MV->ui_len || ui_len != MV->ui_ht
              || ui_len != W->ui_size )   throw OptiVec_SizeErr();
            return MDSVdecompose( vx_m0, MV->vx_m0, W->vx_vect,
                                   MA.vx_m0, MA.ui_ht, MA.ui_len );
        }

        int SVdecompose( tMatObj MV, tVecObj W, cmta MA )
        {
            if( (MA.ui_ht < MA.ui_len ? (ui_ht != ui_len) : (ui_ht != MA.ui_ht))
              || ui_len != MA.ui_len || ui_len != MV.ui_len || ui_len != MV.ui_ht
              || ui_len != W.ui_size )   throw OptiVec_SizeErr();
            return MDSVdecompose( vx_m0, MV.vx_m0, W.vx_vect,
                                   MA.vx_m0, MA.ui_ht, MA.ui_len );
        }

		void SVsort( tMatObj *MVout, tVecObj *Wout, tMatObj MUraw, tMatObj MVraw, tVecObj Wraw )
		{
			if( (MUraw.ui_ht != ui_ht) || (MUraw.ui_len != ui_len) 
			  || ui_len != MVout->ui_len || ui_len != MVraw.ui_len 
			  || ui_len != MVout->ui_ht  || ui_len != MVraw.ui_ht
			  || ui_len != Wout->ui_size || ui_len != Wraw.ui_size )   throw OptiVec_SizeErr();
			MDSVsort( vx_m0, MVout->vx_m0, Wout->vx_vect,
			          MUraw.vx_m0, MVraw.vx_m0, Wraw.vx_vect, ui_ht, ui_len );
		}

		void SVsort( tMatObj MVout, tVecObj Wout, tMatObj MUraw, tMatObj MVraw, tVecObj Wraw )
		{
			if( (MUraw.ui_ht != ui_ht) || (MUraw.ui_len != ui_len)
			  || ui_len != MVout.ui_len || ui_len != MVraw.ui_len
			  || ui_len != MVout.ui_ht  || ui_len != MVraw.ui_ht
			  || ui_len != Wout.ui_size || ui_len != Wraw.ui_size )   throw OptiVec_SizeErr();
			MDSVsort( vx_m0, MVout.vx_m0, Wout.vx_vect,
			          MUraw.vx_m0, MVraw.vx_m0, Wraw.vx_vect, ui_ht, ui_len );
		}

		void SVDsetEdit(cta Thresh) const
		{
			MD_SVDsetEdit(Thresh);
		}

		t SVDgetEdit() const
		{
			return MD_SVDgetEdit();
		}

        int inv( cmta MA )
        {
            if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
                throw OptiVec_SizeErr();
            return MDinv( vx_m0, MA.vx_m0, ui_len );
        }

        t det() const
        {
            if( ui_ht != ui_len ) throw OptiVec_SizeErr();
            return MDdet( vx_m0, ui_len );
        }

		int sym_inv( cmta MA )
		{
			if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
				throw OptiVec_SizeErr();
			return MDsyminv( vx_m0, MA.vx_m0, ui_len );
		}

		t sym_det() const
		{
			if( ui_ht != ui_len ) throw OptiVec_SizeErr();
			return MDsymdet( vx_m0, ui_len );
		}


/////////////////////////////////////////////////////////////////////////////////////////
// Eigenvalues, Matrix Square-Root
//
// sym_eigenval is a member of tVecObj

        int sym_sqrt( cmta MA )
        {
            if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
                throw OptiVec_SizeErr();
            return MDs_sqrt( vx_m0, MA.vx_m0, ui_len );
        }


/////////////////////////////////////////////////////////////////////////////////////////
//Fourier Transforms, Convolutions, Filtering
//

		tcplx getRspEdit() const
		{
			return VD_getRspEdit();
		}

		void setRspEdit(const tcplx& trunc) const
		{
			VD_setRspEdit(trunc);
		}

		void p_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDpFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void p_Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDpRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void p_Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDpCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void b_FFT(cmta X, int dir, mta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MDbFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir,Buf.vx_m0);
		}

		void b_Rows_FFT(cmta X, int dir, mta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MDbRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir,Buf.vx_m0);
		}

		void b_Cols_FFT(cmta X, int dir, mta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MDbCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir,Buf.vx_m0);
		}

		//p_FFTtoC, b_FFTtoC members of cfMatObj

		void p_filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MDpfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void p_autocorr(cmta X)
		{
			enforcePow2();
			MDpautocorr(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void p_xcorr(cmta X, cmta Y)
		{
			enforcePow2();
			MDpxcorr(vx_m0, X.vx_m0, Y.vx_m0, ui_ht, ui_len);
		}

		void p_spectrum(cmta X, cmta Win)
		{
			ui htSpec=ui_ht-1, lenSpec=ui_len-1;
			if(!ui_isipow2(htSpec) || !ui_isipow2(lenSpec)) throw OptiVec_Pow2SizeErr();
			if(X.ui_ht < 2*htSpec || X.ui_len < 2*lenSpec) throw OptiVec_BigSizeErr();
			if(Win.ui_ht != 2*htSpec || Win.ui_len != 2*lenSpec) throw OptiVec_SizeErr();
			MDpspectrum(vx_m0, htSpec, lenSpec, X.vx_m0, X.ui_ht, X.ui_len, Win.vx_m0);
		}

		void p_convolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDpconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void p_convolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDpconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void p_deconvolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDpdeconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void p_deconvolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDpdeconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void l_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDlFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void l_Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDlRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void l_Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDlCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		//l_FFTtoC member of cdMatObj

		void l_filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MDlfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void l_autocorr(cmta X)
		{
			enforcePow2();
			MDlautocorr(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void l_xcorr(cmta X, cmta Y)
		{
			enforcePow2();
			MDlxcorr(vx_m0, X.vx_m0, Y.vx_m0, ui_ht, ui_len);
		}

		void l_spectrum(cmta X, cmta Win)
		{
			ui htSpec=ui_ht-1, lenSpec=ui_len-1;
			if(!ui_isipow2(htSpec) || !ui_isipow2(lenSpec)) throw OptiVec_Pow2SizeErr();
			if(X.ui_ht < 2*htSpec || X.ui_len < 2*lenSpec) throw OptiVec_BigSizeErr();
			if(Win.ui_ht != 2*htSpec || Win.ui_len != 2*lenSpec) throw OptiVec_SizeErr();
			MDlspectrum(vx_m0, htSpec, lenSpec, X.vx_m0, X.ui_ht, X.ui_len, Win.vx_m0);
		}

		void l_convolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDlconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void l_convolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDlconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void l_deconvolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDldeconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void l_deconvolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDldeconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void s_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDsFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void s_Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDsRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void s_Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDsCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		//s_FFTtoC member of cdMatObj

		void s_filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MDsfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void s_autocorr(cmta X)
		{
			enforcePow2();
			MDsautocorr(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void s_xcorr(cmta X, cmta Y)
		{
			enforcePow2();
			MDsxcorr(vx_m0, X.vx_m0, Y.vx_m0, ui_ht, ui_len);
		}

		void s_spectrum(cmta X, cmta Win)
		{
			ui htSpec=ui_ht-1, lenSpec=ui_len-1;
			if(!ui_isipow2(htSpec) || !ui_isipow2(lenSpec)) throw OptiVec_Pow2SizeErr();
			if(X.ui_ht < 2*htSpec || X.ui_len < 2*lenSpec) throw OptiVec_BigSizeErr();
			if(Win.ui_ht != 2*htSpec || Win.ui_len != 2*lenSpec) throw OptiVec_SizeErr();
			MDsspectrum(vx_m0, htSpec, lenSpec, X.vx_m0, X.ui_ht, X.ui_len, Win.vx_m0);
		}

		void s_convolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDsconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void s_convolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDsconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void s_deconvolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDsdeconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void s_deconvolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDsdeconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MDCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		//FFTtoC member of cdMatObj

		void filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MDfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void autocorr(cmta X)
		{
			enforcePow2();
			MDautocorr(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void xcorr(cmta X, cmta Y)
		{
			enforcePow2();
			MDxcorr(vx_m0, X.vx_m0, Y.vx_m0, ui_ht, ui_len);
		}

		void spectrum(cmta X, cmta Win)
		{
			ui htSpec=ui_ht-1, lenSpec=ui_len-1;
			if(!ui_isipow2(htSpec) || !ui_isipow2(lenSpec)) throw OptiVec_Pow2SizeErr();
			if(X.ui_ht < 2*htSpec || X.ui_len < 2*lenSpec) throw OptiVec_BigSizeErr();
			if(Win.ui_ht != 2*htSpec || Win.ui_len != 2*lenSpec) throw OptiVec_SizeErr();
			MDspectrum(vx_m0, htSpec, lenSpec, X.vx_m0, X.ui_ht, X.ui_len, Win.vx_m0);
		}

		void convolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void convolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void deconvolve(tMatObj* Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt->ui_ht)||(ui_len!=Flt->ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt->mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDdeconvolve(vx_m0, Flt->vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

		void deconvolve(tMatObj Flt, cmta X, cmta Rsp)
		{
			enforcePow2();
			if((ui_ht!=Flt.ui_ht)||(ui_len!=Flt.ui_len)||(ui_ht!=X.ui_ht)||(ui_len!=X.ui_len)||
				(ui_ht!=Rsp.ui_ht)||(ui_len!=Rsp.ui_len)) throw OptiVec_SizeErr();
			if((mx_matr==Rsp.mx_matr)||(Flt.mx_matr==X.mx_matr))
				throw OptiVec_Err();
			MDdeconvolve(vx_m0, Flt.vx_m0, X.vx_m0,
				Rsp.vx_m0, ui_ht, ui_len);
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Data fitting
// All of the fitting functions themselves belong to dVecObj (see below).
// Only a few helper functions follow here:

        void setLinfitNeglect( const t& Thresh ) const
        { VD_setLinfitNeglect( Thresh ); }

        t getLinfitNeglect() const
        {  return VD_getLinfitNeglect(); }

        t nonlinfit_getChi2( MD_NONLINFITWORKSPACE *ws ) const
        { return MD_nonlinfit_getChi2( ws );  }

        t nonlinfitwW_getChi2( MD_NONLINFITWORKSPACE *ws ) const
        { return MD_nonlinfitwW_getChi2( ws );  }

        unsigned nonlinfit_getTestRun( MD_NONLINFITWORKSPACE *ws ) const
        {   return MD_nonlinfit_getTestRun( ws ); }

        unsigned nonlinfitwW_getTestRun( MD_NONLINFITWORKSPACE *ws ) const
        {   return MD_nonlinfitwW_getTestRun( ws ); }

        unsigned nonlinfit_getTestPar( MD_NONLINFITWORKSPACE *ws ) const
        { return MD_nonlinfit_getTestPar( ws ); }

        unsigned nonlinfitwW_getTestPar( MD_NONLINFITWORKSPACE *ws ) const
        { return MD_nonlinfitwW_getTestPar( ws ); }

        int  nonlinfit_getTestDir( MD_NONLINFITWORKSPACE *ws ) const
        { return MD_nonlinfit_getTestDir( ws ); }

        int  nonlinfitwW_getTestDir( MD_NONLINFITWORKSPACE *ws ) const
        { return MD_nonlinfitwW_getTestDir( ws ); }

        void  nonlinfit_stop( MD_NONLINFITWORKSPACE *ws ) const
        {  MD_nonlinfit_stop( ws ); }

        void  nonlinfitwW_stop( MD_NONLINFITWORKSPACE *ws ) const
        {  MD_nonlinfitwW_stop( ws ); }

/////////////////////////////////////////////////////////////////////////////////////////
//Input and Output
//
		void fprint(FILE* stream, unsigned linewidth) const
		{
			enforceSize();
			MDfprint(stream,vx_m0,ui_ht, ui_len,linewidth);
		}

		void cprint() const
		{
			enforceSize();
			MDcprint(vx_m0,ui_ht,ui_len);
		}

		void print() const
		{
			fprint(stdout,80);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			MDwrite(stream,vx_m0,ui_ht,ui_len);
		}

		void read(FILE* stream)
		{
			enforceSize();
			MDread(vx_m0,ui_ht,ui_len,stream);
		}

		void setWriteFormat(char* formatString) const
		{
			VD_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VD_setWriteSeparate(sepString);
		}

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_ht,sizeof(ui),1,stream);
			fwrite(&ui_len,sizeof(ui),1,stream);
			VD_store(stream,vx_m0,ui_size);
		}

		void recall(FILE* stream)
		{
			fread(&ui_ht,sizeof(ui),1,stream);
			fread(&ui_len,sizeof(ui),1,stream);
			setSize(ui_ht,ui_len);
			VD_recall(vx_m0,ui_size,stream);
		}

            #ifdef __MGRAPH_H
                void xyzAutoDensityMap( cvta X, cvta Y, COLORREF mincol, COLORREF maxcol ) const
                {
                    enforceSize(X.ui_size,Y.ui_size);
                    MDxyzAutoDensityMap( X.vx_vect, Y.vx_vect, vx_m0, ui_ht, ui_len,
                                          mincol, maxcol );
                }

                void xyzDataDensityMap( cvta X, cvta Y ) const
                {
                    enforceSize(X.ui_size,Y.ui_size);
                    MDxyzDataDensityMap( X.vx_vect, Y.vx_vect, vx_m0, ui_ht, ui_len);
                }

                void zAutoDensityMap( COLORREF mincol, COLORREF maxcol ) const
                {
                    enforceSize();
                    MDzAutoDensityMap( vx_m0, ui_ht, ui_len, mincol, maxcol );
                }

                void zDataDensityMap() const
                {
                    enforceSize();
                    MDzDataDensityMap( vx_m0, ui_ht, ui_len);
                }

            #endif   // __MGRAPH_H
        };


	inline vt tVecObj::operator*(cmta MY)
	{
		tVecObj tmp(this->ui_size);
		tmp.enforceSize();
		VDmulM(tmp.vx_vect,vx_vect,MY.vx_m0,MY.ui_ht,MY.ui_len);
		return tmp;
	}

	inline void tVecObj::Row_extract(cmta MA, const ui iRow)
	{
		if( MA.ui_ht <= iRow || ui_size < MA.ui_len || !ui_size ) throw OptiVec_SizeErr();
		MDRow_extract( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len, iRow );
	}

	inline void tVecObj::Col_extract(cmta MA, const ui iCol)
	{
		if( MA.ui_len <= iCol || ui_size < MA.ui_ht || !ui_size ) throw OptiVec_SizeErr();
		MDCol_extract( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len, iCol );
	}

	inline void tVecObj::Dia_extract(cmta MA)
	{
		if( !ui_size || ui_size != MA.ui_len || (MA.ui_len != MA.ui_ht) )throw OptiVec_SizeErr();
		MDDia_extract( vx_vect, MA.vx_m0, MA.ui_len );
	}

	inline void tVecObj::Rows_max(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MDRows_max( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_max(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MDCols_max( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_min(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MDRows_min( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_min(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MDCols_min( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_absmax(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MDRows_absmax( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_absmax(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MDCols_absmax( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_absmin(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MDRows_absmin( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_absmin(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MDCols_absmin( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_sum(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MDRows_sum( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_sum(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MDCols_sum( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_ssq(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MDRows_ssq( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_ssq(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MDCols_ssq( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_prod(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MDRows_prod( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_prod(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MDCols_prod( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void uiMatObj::Rows_distribution(cvta Limits, cmta MA, int mode=0)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_ht != MA.ui_ht ) throw OptiVec_SizeErr();
		return MDRows_distribution(vx_m0,Limits.vx_vect,ui_size,MA.vx_m0,MA.ui_ht,MA.ui_len,mode);
	}

	inline void uiMatObj::Cols_distribution(cvta Limits, cmta MA, int mode=0)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_len != MA.ui_len ) throw OptiVec_SizeErr();
		return MDCols_distribution(vx_m0,Limits.vx_vect,ui_size,MA.vx_m0,MA.ui_ht,MA.ui_len,mode);
	}

	inline void tVecObj::MmulV( cmta MA, cvta X )
	{
		if( ui_size != MA.ui_ht || X.ui_size != MA.ui_len ) throw OptiVec_SizeErr();
		MDmulV( vx_vect, MA.vx_m0, X.vx_vect, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::MTmulV( cmta MA, cvta X )
	{
		if( ui_size != MA.ui_len || X.ui_size != MA.ui_ht ) throw OptiVec_SizeErr();
		MDTmulV( vx_vect, MA.vx_m0, X.vx_vect, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::mulM( cvta X, cmta MA )
	{
		if( ui_size != MA.ui_len || X.ui_size != MA.ui_ht ) throw OptiVec_SizeErr();
		VDmulM( vx_vect, X.vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::mulMT( cvta X, cmta MA )
	{
		if( ui_size != MA.ui_ht || X.ui_size != MA.ui_len ) throw OptiVec_SizeErr();
		VDmulMT( vx_vect, X.vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::LUsolve( cmta MLU, cvta B, const uiVecObj& Ind )
	{
		if( ui_size != MLU.ui_len || ui_size != MLU.ui_ht ||
		    ui_size != B.ui_size || ui_size != Ind.ui_size ) throw OptiVec_SizeErr();
		MDLUsolve( vx_vect, MLU.vx_m0, B.vx_vect, Ind.vx_vect, MLU.ui_len );
	}

	inline void tVecObj::LUimprove( cvta B, cmta MA, cmta MLU, const uiVecObj& Ind )
	{
		if( ui_size != MLU.ui_len || ui_size != MLU.ui_ht ||
		    ui_size != MA.ui_len || ui_size != MA.ui_ht ||
		    ui_size != B.ui_size || ui_size != Ind.ui_size ) throw OptiVec_SizeErr();
		MDLUimprove( vx_vect, B.vx_vect, MA.vx_m0, MLU.vx_m0, Ind.vx_vect, MLU.ui_len );
	}

	inline void tVecObj::CholeskyLsolve( cmta ML, cvta B )
	{
		if( ui_size != ML.ui_len || ui_size != ML.ui_ht ||
		    ui_size != B.ui_size ) throw OptiVec_SizeErr();
		MDCholeskyLsolve( vx_vect, ML.vx_m0, B.vx_vect, ML.ui_len );
	}

	inline void tVecObj::CholeskyLimprove( cvta B, cmta MA, cmta ML )
	{
		if( ui_size != ML.ui_len || ui_size != ML.ui_ht || ui_size != MA.ui_len 
		 || ui_size != MA.ui_ht || ui_size != B.ui_size ) throw OptiVec_SizeErr();
		MDCholeskyLimprove( vx_vect, B.vx_vect, MA.vx_m0, ML.vx_m0, ML.ui_len );
	}

	inline void tVecObj::CholeskyRsolve( cmta MR, cvta B )
	{
		if( ui_size != MR.ui_len || ui_size != MR.ui_ht ||
		    ui_size != B.ui_size ) throw OptiVec_SizeErr();
		MDCholeskyRsolve( vx_vect, MR.vx_m0, B.vx_vect, MR.ui_len );
	}

	inline void tVecObj::CholeskyRimprove( cvta B, cmta MA, cmta MR )
	{
		if( ui_size != MR.ui_len || ui_size != MR.ui_ht || ui_size != MA.ui_len 
		 || ui_size != MA.ui_ht || ui_size != B.ui_size ) throw OptiVec_SizeErr();
		MDCholeskyRimprove( vx_vect, B.vx_vect, MA.vx_m0, MR.vx_m0, MR.ui_len );
	}

	inline void tVecObj::SVsolve( cmta MU, cmta MV, cvta W, cvta B )
       { // result may overwrite B only for "normal", not for over- or under-determined systems
		if( MU.ui_ht < MU.ui_len || MU.ui_len != MV.ui_len || MV.ui_len != MV.ui_ht ||
		    B.ui_size != ui_size || W.ui_size != MV.ui_len || ui_size != MU.ui_ht )
		throw OptiVec_SizeErr();
		MDSVsolve( vx_vect, MU.vx_m0, MV.vx_m0, W.vx_vect, B.vx_vect, B.ui_size, MU.ui_len );
	}

	inline int tVecObj::solve( cmta MA, cvta B )
	{
		if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
		    ui_size != B.ui_size ) throw OptiVec_SizeErr();
		return MDsolve( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_len );
	}

    inline int tVecObj::sym_solve( cmta MA, cvta B )
    {
        if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
            ui_size != B.ui_size ) throw OptiVec_SizeErr();
        return MDsymsolve( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_len );
    }

	inline int tVecObj::solveBySVD( cmta MA, cvta B )
	{
		if(ui_size != MA.ui_len || (B.ui_size != MA.ui_ht && B.vx_vect != vx_vect)) throw OptiVec_SizeErr();
		return MDsolveBySVD( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_ht, MA.ui_len );
	}

	inline int tVecObj::safeSolve( cmta MA, cvta B )
	{
		if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
		   ui_size != B.ui_size ) throw OptiVec_SizeErr();
		return MDsafeSolve( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_len );
	}

	inline int tVecObj::sym_eigenvalues( tMatObj EigM, cmta MA, int CalcEigenVec )
	{
		if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
		   (CalcEigenVec && (ui_size != EigM.ui_len || ui_size != EigM.ui_ht)) )
		throw OptiVec_SizeErr();
		return( MDs_eigenvalues( vx_vect, EigM.vx_m0, MA.vx_m0, MA.ui_len, CalcEigenVec));
	}

	inline int tVecObj::sym_eigenvalues( tMatObj* EigM, cmta MA, int CalcEigenVec )
	{
		if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
		   (CalcEigenVec && (ui_size != EigM->ui_len || ui_size != EigM->ui_ht)) )
		throw OptiVec_SizeErr();
		return( MDs_eigenvalues( vx_vect, EigM->vx_m0, MA.vx_m0, MA.ui_len, CalcEigenVec));
	}

	inline int tVecObj::polyfit( cvta X, cvta Y )
	{
		unsigned deg = (unsigned)ui_size-1;
		if( deg >= X.ui_size || X.ui_size != Y.ui_size) throw OptiVec_SizeErr();
		return VD_polyfit( vx_vect, deg, X.vx_vect, Y.vx_vect, X.ui_size );
	}

	inline int tVecObj::polyfitwW( tMatObj Covar, cvta X, cvta Y, cvta InvVar )
	{
		unsigned deg = (unsigned)ui_size-1;
		if( deg >= X.ui_size || X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
		    Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size) throw OptiVec_SizeErr();
		return VDpolyfitwW( vx_vect, Covar.vx_m0, deg,
                     X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size );
	}

	inline int tVecObj::polyfitwW( tMatObj* Covar, cvta X, cvta Y, cvta InvVar )
	{   unsigned deg = (unsigned)ui_size-1;
		if( deg >= X.ui_size || X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
		    Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size) throw OptiVec_SizeErr();
		return VDpolyfitwW( vx_vect, Covar->vx_m0, deg,
                     X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size );
	}

	inline int tVecObj::linfit( const iVecObj& AStatus, cvta X, cvta Y,
                     void __vf funcs(tVector BasFuncs, t x, unsigned nfuncs) )
	{
		if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
		    X.ui_size != Y.ui_size) throw OptiVec_SizeErr();
		return VD_linfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size, X.vx_vect, Y.vx_vect, X.ui_size, funcs );
	}

	inline int tVecObj::linfitwW( tMatObj Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf funcs(tVector BasFuncs, t x, unsigned nfuncs) )
	{
		if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
		    X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
		Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size) throw OptiVec_SizeErr();
		return VDlinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                    X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size, funcs );
	}

	inline int tVecObj::linfitwW( tMatObj* Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf funcs(tVector BasFuncs, t x, unsigned nfuncs) )
	{
		if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
		    X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
		    Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size) throw OptiVec_SizeErr();
		return VDlinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                    X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size, funcs );
	}

	inline int tVecObj::linfit( const iVecObj& AStatus, cvta X, cvta Y, cmta MZ,
                     void __vf funcs(tVector BasFuncs, t x, t y, unsigned nfuncs) )
	{
		if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
		    X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht) throw OptiVec_SizeErr();
		return MDlinfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size,
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
		return MDlinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
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
		return MDlinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                   X.vx_vect, Y.vx_vect, MZ.vx_m0, MInvVar.vx_m0, MZ.ui_ht, MZ.ui_len, funcs );
	}

	inline void tVecObj::setLinfitNeglect( const t& Thresh ) const
	{ VD_setLinfitNeglect( Thresh ); }

	inline t tVecObj::getLinfitNeglect() const
	{  return VD_getLinfitNeglect(); }

	// nonlinfit functions with complete syntax:
    inline t tVecObj::nonlinfit( const iVecObj& AStatus, cvta X, cvta Y,
                         void __vf modelfunc(tVector YModel, tVector XModel, ui size),
                         void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar),
						VD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size) throw OptiVec_SizeErr();
        return VD_nonlinfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size, X.vx_vect, Y.vx_vect, X.ui_size,
                      modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

    inline t tVecObj::nonlinfitwW( tMatObj Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf modelfunc(tVector YModel, tVector XModel, ui size),
                     void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar),
						VD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size) throw OptiVec_SizeErr();
        return VDnonlinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                       X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size,
                       modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

    inline t tVecObj::nonlinfitwW( tMatObj* Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf modelfunc(tVector YModel, tVector XModel, ui size),
                     void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar),
						VD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size) throw OptiVec_SizeErr();
        return VDnonlinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                       X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size,
                       modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

    inline t tVecObj::nonlinfit( const iVecObj& AStatus, cvta X, cvta Y, cmta MZ,
                    void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
                    void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar),
						MD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht) throw OptiVec_SizeErr();
        return MDnonlinfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size,
                      X.vx_vect, Y.vx_vect, MZ.vx_m0, MZ.ui_ht, MZ.ui_len,
                      modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

    inline t tVecObj::nonlinfitwW( tMatObj Covar, const iVecObj& AStatus,
                     cvta X, cvta Y, cmta MZ, cmta MInvVar,
                     void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
                     void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar),
						MD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht ||
            MZ.ui_ht != MInvVar.ui_ht || MZ.ui_len != MInvVar.ui_len ||
            Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size)
            throw OptiVec_SizeErr();
        return MDnonlinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                        X.vx_vect, Y.vx_vect, MZ.vx_m0, MInvVar.vx_m0,
                        MZ.ui_ht, MZ.ui_len, modelfunc, derivatives, FitWorkSpace, FitOpts );
    }

    inline t tVecObj::nonlinfitwW( tMatObj* Covar, const iVecObj& AStatus,
                     cvta X, cvta Y, cmta MZ, cmta MInvVar,
                     void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
                     void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar),
						MD_NONLINFITWORKSPACE *FitWorkSpace, VD_NONLINFITOPTIONS *FitOpts )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht ||
            MZ.ui_ht != MInvVar.ui_ht || MZ.ui_len != MInvVar.ui_len ||
            Covar->ui_ht != Covar->ui_len || Covar->ui_ht != ui_size)
            throw OptiVec_SizeErr();
        return MDnonlinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
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
        return VD_nonlinfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size, X.vx_vect, Y.vx_vect, X.ui_size,
                      modelfunc, derivatives, NULL, NULL );
    }

    inline t tVecObj::nonlinfitwW( tMatObj Covar, const iVecObj& AStatus, cvta X, cvta Y, cvta InvVar,
                     void __vf modelfunc(tVector YModel, tVector XModel, ui size),
                     void __vf derivatives(tVector dYdAi,tVector X, ui size, unsigned iPar) )
    {
        if( ui_size > X.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != Y.ui_size || X.ui_size != InvVar.ui_size ||
            Covar.ui_ht != Covar.ui_len || Covar.ui_ht != ui_size) throw OptiVec_SizeErr();
        return VDnonlinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
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
        return VDnonlinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                       X.vx_vect, Y.vx_vect, InvVar.vx_vect, X.ui_size,
                       modelfunc, derivatives, NULL, NULL );
    }

    inline t tVecObj::nonlinfit( const iVecObj& AStatus, cvta X, cvta Y, cmta MZ,
                    void __vf modelfunc(tMatrix MZModel, ui htZ, ui lenZ, tVector X, tVector Y ),
                    void __vf derivatives(tMatrix dZdAi, ui htZ, ui lenZ, tVector X, tVector Y, unsigned ipar) )
    {
        if( ui_size > MZ.ui_size || ui_size != AStatus.ui_size ||
            X.ui_size != MZ.ui_len || Y.ui_size != MZ.ui_ht) throw OptiVec_SizeErr();
        return MDnonlinfit( vx_vect, AStatus.vx_vect, (unsigned)ui_size,
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
        return MDnonlinfitwW( vx_vect, Covar.vx_m0, AStatus.vx_vect, (unsigned)ui_size,
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
        return MDnonlinfitwW( vx_vect, Covar->vx_m0, AStatus.vx_vect, (unsigned)ui_size,
                        X.vx_vect, Y.vx_vect, MZ.vx_m0, MInvVar.vx_m0,
                        MZ.ui_ht, MZ.ui_len, modelfunc, derivatives, NULL, NULL );
    }

// all multifit functions can be called only in their normal C form,
// because MD_EXPERIMENT cannot work with VecObjects, but requires actual pointers

#ifdef FMATOBJ_H
	inline void fMatObj::DtoF(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_DtoF(vx_m0,X.vx_m0,ui_size);
	}

	inline void dMatObj::FtoD(const fMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_FtoD(vx_m0,X.vx_m0,ui_size);
	}
#endif //FMATOBJ_H

#ifdef EMATOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers defined
	inline void dMatObj::EtoD(const eMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_EtoD(vx_m0,X.vx_m0,ui_size);
	}

	inline void eMatObj::DtoE(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_DtoE(vx_m0,X.vx_m0,ui_size);
	}
#endif //__BORLANDC__
#endif //EMATOBJ_H

#ifdef BIMATOBJ_H
	inline void dMatObj::BItoD(const biMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_BItoD(vx_m0,X.vx_m0,ui_size);
	}

	inline int biMatObj::roundtoBI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_roundtoBI(vx_m0,X.vx_m0,ui_size);
	}

	inline int biMatObj::floortoBI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_floortoBI(vx_m0,X.vx_m0,ui_size);
	}

	inline int biMatObj::ceiltoBI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_ceiltoBI(vx_m0,X.vx_m0,ui_size);
	}

	inline int biMatObj::choptoBI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_choptoBI(vx_m0,X.vx_m0,ui_size);
	}
#endif //BIMATOBJ_H

#ifdef UBMATOBJ_H
	inline void dMatObj::UBtoD(const ubMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_UBtoD(vx_m0,X.vx_m0,ui_size);
	}

	inline int ubMatObj::roundtoUB(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_roundtoUB(vx_m0,X.vx_m0,ui_size);
	}

	inline int ubMatObj::floortoUB(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_floortoUB(vx_m0,X.vx_m0,ui_size);
	}

	inline int ubMatObj::ceiltoUB(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_ceiltoUB(vx_m0,X.vx_m0,ui_size);
	}

	inline int ubMatObj::choptoUB(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_choptoUB(vx_m0,X.vx_m0,ui_size);
	}
#endif //UBMATOBJ_H


#ifdef SIMATOBJ_H
	inline void dMatObj::SItoD(const siMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_SItoD(vx_m0,X.vx_m0,ui_size);
	}

	inline int siMatObj::roundtoSI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_roundtoSI(vx_m0,X.vx_m0,ui_size);
	}

	inline int siMatObj::floortoSI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_floortoSI(vx_m0,X.vx_m0,ui_size);
	}

	inline int siMatObj::ceiltoSI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_ceiltoSI(vx_m0,X.vx_m0,ui_size);
	}

	inline int siMatObj::choptoSI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_choptoSI(vx_m0,X.vx_m0,ui_size);
	}
#endif //SIMATOBJ_H

#ifdef USMATOBJ_H
	inline void dMatObj::UStoD(const usMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_UStoD(vx_m0,X.vx_m0,ui_size);
	}

	inline int usMatObj::roundtoUS(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_roundtoUS(vx_m0,X.vx_m0,ui_size);
	}

	inline int usMatObj::floortoUS(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_floortoUS(vx_m0,X.vx_m0,ui_size);
	}

	inline int usMatObj::ceiltoUS(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_ceiltoUS(vx_m0,X.vx_m0,ui_size);
	}

	inline int usMatObj::choptoUS(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_choptoUS(vx_m0,X.vx_m0,ui_size);
	}
#endif //USMATOBJ_H

#ifdef IMATOBJ_H
	inline void dMatObj::ItoD(const iMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_ItoD(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::roundtoI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_roundtoI(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::floortoI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_floortoI(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::ceiltoI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_ceiltoI(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::choptoI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_choptoI(vx_m0,X.vx_m0,ui_size);
	}
#endif //IMATOBJ_H

#ifdef UMATOBJ_H
	inline void dMatObj::UtoD(const uMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_UtoD(vx_m0,X.vx_m0,ui_size);
	}

	inline int uMatObj::roundtoU(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_roundtoU(vx_m0,X.vx_m0,ui_size);
	}

	inline int uMatObj::floortoU(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_floortoU(vx_m0,X.vx_m0,ui_size);
	}

	inline int uMatObj::ceiltoU(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_ceiltoU(vx_m0,X.vx_m0,ui_size);
	}

	inline int uMatObj::choptoU(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_choptoU(vx_m0,X.vx_m0,ui_size);
	}
#endif //UMATOBJ_H

#ifdef LIMATOBJ_H
	inline void dMatObj::LItoD(const liMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_LItoD(vx_m0,X.vx_m0,ui_size);
	}

	inline int liMatObj::roundtoLI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_roundtoLI(vx_m0,X.vx_m0,ui_size);
	}

	inline int liMatObj::floortoLI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_floortoLI(vx_m0,X.vx_m0,ui_size);
	}

	inline int liMatObj::ceiltoLI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_ceiltoLI(vx_m0,X.vx_m0,ui_size);
	}

	inline int liMatObj::choptoLI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_choptoLI(vx_m0,X.vx_m0,ui_size);
	}
#endif //LIMATOBJ_H

#ifdef ULMATOBJ_H
	inline void dMatObj::ULtoD(const ulMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_ULtoD(vx_m0,X.vx_m0,ui_size);
	}

	inline int ulMatObj::roundtoUL(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_roundtoUL(vx_m0,X.vx_m0,ui_size);
	}

	inline int ulMatObj::floortoUL(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_floortoUL(vx_m0,X.vx_m0,ui_size);
	}

	inline int ulMatObj::ceiltoUL(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_ceiltoUL(vx_m0,X.vx_m0,ui_size);
	}

	inline int ulMatObj::choptoUL(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_choptoUL(vx_m0,X.vx_m0,ui_size);
	}
#endif //ULMATOBJ_H

#ifdef UQMATOBJ_H
	inline void dMatObj::UQtoD(const uqMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_UQtoD(vx_m0,X.vx_m0,ui_size);
	}

	inline int uqMatObj::roundtoUQ(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_roundtoUQ(vx_m0,X.vx_m0,ui_size);
	}

	inline int uqMatObj::floortoUQ(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_floortoUQ(vx_m0,X.vx_m0,ui_size);
	}

	inline int uqMatObj::ceiltoUQ(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_ceiltoUQ(vx_m0,X.vx_m0,ui_size);
	}

	inline int uqMatObj::choptoUQ(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_choptoUQ(vx_m0,X.vx_m0,ui_size);
	}
#endif //UQMATOBJ_H

#ifdef QIMATOBJ_H
	inline void dMatObj::QItoD(const qiMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_QItoD(vx_m0,X.vx_m0,ui_size);
	}

	inline int qiMatObj::roundtoQI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_roundtoQI(vx_m0,X.vx_m0,ui_size);
	}

	inline int qiMatObj::floortoQI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_floortoQI(vx_m0,X.vx_m0,ui_size);
	}

	inline int qiMatObj::ceiltoQI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_ceiltoQI(vx_m0,X.vx_m0,ui_size);
	}

	inline int qiMatObj::choptoQI(const dMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VD_choptoQI(vx_m0,X.vx_m0,ui_size);
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
#ifdef __BORLANDC__
#pragma warn .inl
#endif

#define DMATOBJ_H
#endif //DMATOBJ_H
