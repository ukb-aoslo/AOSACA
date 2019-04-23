/* ceMatObj.H

  object-oriented interface for OptiVec matrix functions of type "eComplex"

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef CEMATOBJ_H

#include <VecObj.h>
#include <ceVecObj.h>
#include <eMatObj.h>
#include <uiVecObj.h>
#include <iVecObj.h>
#if (defined __BORLANDC__) && !(defined _WIN64)   // 80-bit reals supported ?

#define cvta const vector<eComplex>&
#define cmta const matrix<eComplex>&
#define cua  const ui&
#define cuint const ui
#define cta  const eComplex&

#define vta  vector<eComplex>&
#define mta  matrix<eComplex>&
#define ta   eComplex&

#define vt   vector<eComplex>
#define mt   matrix<eComplex>
#define t    eComplex
#define tVector ceVector
#define tMatrix ceMatrix
#define tMatObj ceMatObj
#define tVecObj ceVecObj

#define tbase  extended

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
			{	mx_matr=MCE_matrix(ht,len); vx_m0=mx_matr[0];
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
				if(!fill.Re && !fill.Im) //fill == 0.0
		 	 	{	mx_matr=MCE_matrix0(ht,len); vx_m0=mx_matr[0];}
				else
				{	mx_matr=MCE_matrix(ht,len);  vx_m0=mx_matr[0];
					VCE_equC(vx_m0,ui_size,fill);}
	 		}
		}

		matrix(cmta init)
		{	if(init.ui_size)
			{	mx_matr= MCE_matrix(init.ui_ht, init.ui_len); vx_m0=mx_matr[0];
				ui_ht=init.ui_ht; ui_len=init.ui_len; ui_size=init.ui_size;
				VCE_equV(vx_m0, init.vx_m0, ui_size);
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
				mx_matr= MCE_matrix(ht, len); vx_m0=mx_matr[0];
				ui_len=len; ui_ht=ht; ui_size= size;
			}
		}

		void setSize(cmta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_len != X.ui_len || ui_ht != X.ui_ht) //only allocate if different sizes
			{	if(mx_matr) M_free(mx_matr);
				mx_matr= MCE_matrix(X.ui_ht, X.ui_len); vx_m0=mx_matr[0];
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
			VCE_equV(vx_m0, matr.vx_m0, ui_size);
			return *this;}

		mta operator=(cta scalar)
		{	enforceSize();
			VCE_equC(vx_m0, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		tVector operator[](const int& index){return mx_matr[index];}

		mta operator+=(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			VCE_accV(vx_m0, X.vx_m0, ui_size);
			return *this;}

		mta operator+=(cta scalar)
		{	enforceSize();
			VCE_addC(vx_m0, vx_m0, ui_size, scalar);
			return *this;}

		mta operator*=(cta scalar)
		{	enforceSize();
			VCE_mulC(vx_m0,vx_m0,ui_size,scalar);
			return *this;}

		mt operator+(cmta rhs)
		{	enforceSize(rhs.ui_ht, rhs.ui_len);
			tMatObj tmp(this->ui_ht, this->ui_len);
			VCE_addV(tmp.vx_m0,this->vx_m0,rhs.vx_m0,tmp.ui_size);
			return tmp;}

		mt operator+(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VCE_addC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		mt operator-(cmta rhs)
		{	enforceSize(rhs.ui_ht, rhs.ui_len);
			tMatObj tmp(this->ui_ht, this->ui_len);
			VCE_subV(tmp.vx_m0,this->vx_m0,rhs.vx_m0,tmp.ui_size);
			return tmp;}

		mt operator-(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VCE_subC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		mt operator*(cmta rhs)
		{	enforceLen(rhs.ui_ht);
			tMatObj tmp(this->ui_ht, rhs.ui_len);
			tmp.enforceSize();
			MCEmulM(tmp.vx_m0,this->vx_m0,rhs.vx_m0,this->ui_ht, this->ui_len,rhs.ui_len);
			return tmp;}

		vt operator*(cvta rhs)
		{	enforceLen(rhs.ui_size);
			tVecObj tmp(this->ui_ht);
			tmp.enforceSize();
			MCEmulV(tmp.vx_vect,this->vx_m0,rhs.vx_vect,this->ui_ht, this->ui_len);
			return tmp;}

		// operator*(cvta VX, cmta MY) is member of ceVecObj, see below

		mt operator*(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VCE_mulC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		mt operator/(cta C)
		{	tMatObj tmp(this->ui_ht, this->ui_len);
			tmp.enforceSize();
			VCE_divC(tmp.vx_m0,this->vx_m0,tmp.ui_size,C);
			return tmp;}

		friend mt operator+(cta C, cmta X)
		{	tMatObj tmp(X.ui_ht,X.ui_len);
			VCE_addC(tmp.vx_m0,X.vx_m0,tmp.ui_size,C);
			return tmp;}

		friend mt operator-(cta C, cmta X)
		{	tMatObj tmp(X.ui_ht,X.ui_len);
			VCE_subrC(tmp.vx_m0,X.vx_m0,tmp.ui_size,C);
			return tmp;}

		friend mt operator*(cta C, cmta X)
		{	tMatObj tmp(X.ui_ht,X.ui_len);
			VCE_mulC(tmp.vx_m0,X.vx_m0,tmp.ui_size,C);
			return tmp;}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//OptiVec functions in member format
//from MCXstd.h
//

/////////////////////////////////////////////////////////////////////////////////////////
//Generation
//
		//these are not recommended, better to use constructors
		void _matrix(cuint ht, cuint len) //underscore necessary to avoid confusing with constructor
		{
			dealloc();
			ui_size=((ui)ht)*len;
			if(ui_size){ ui_ht=ht;ui_len=len;mx_matr= MCE_matrix(ht,len);vx_m0=mx_matr[0];}
		}

		void _matrix0(cuint ht, cuint len) //underscore necessary to avoid confusing with constructor
		{
			dealloc();
			ui_size=((ui)ht)*len;
			if(ui_size){ ui_ht=ht;ui_len=len;mx_matr= MCE_matrix0(ht,len);vx_m0=mx_matr[0];}
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single matrix elements
//
		t* Pelement(cuint m, cuint n) const
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MCEPelement(vx_m0,ui_ht,ui_len,m,n);
		}

		t element(cuint m, cuint n) const
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MCEelement(vx_m0,ui_ht,ui_len,m,n);
		}

		void getElement(t *y, cuint m, cuint n)
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MCEgetElement(y,vx_m0,ui_ht,ui_len,m,n);
		}

		void setElement(cuint m, cuint n, cta C)
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			MCEsetElement(vx_m0,ui_ht,ui_len,m,n,C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//

		void equ0()
		{
			enforceSize();
			VCE_equ0(vx_m0,ui_size);
		}

		void equ1()
		{
			enforceSize();
			MCEequ1(vx_m0,ui_len);
		}

		void equm1()
		{
			enforceSize();
			MCEequm1(vx_m0,ui_len);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VCE_random(vx_m0, ui_size, seed, Min, Max);
		}

		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VCE_randomLC(vx_m0, ui_size, seed, Min, Max, state);
		}

		void outerprod(cvta X, cvta Y)
		{
			enforceSize( X.ui_size, Y.ui_size);
			MCEouterprod(vx_m0, X.vx_vect, Y.vx_vect, ui_ht, ui_len);
		}

		void Row_equ0(cuint iRow)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_equ0(vx_m0, ui_ht, ui_len, iRow);
		}

		void Col_equ0(cuint iCol)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_equ0(vx_m0, ui_ht, ui_len, iCol);
		}

		void Dia_equ0()
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MCEDia_equ0(vx_m0, ui_len);
		}

		void Row_equC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_equC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_equC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_equC(vx_m0, ui_ht, ui_len, iCol, C);
		}

		void Dia_equC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MCEDia_equC(vx_m0, ui_len, C);
		}

		void Row_equV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_equV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_equV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_equV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

		void Dia_equV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MCEDia_equV(vx_m0, ui_len, X.vx_vect);
		}

		void Trd_equM(cmta MTrd)
		{
			if( MTrd.ui_ht != 3 || ui_ht != ui_len || ui_len != MTrd.ui_len )throw OptiVec_SizeErr();
			MCETrd_equM(vx_m0, MTrd.vx_m0, ui_len);
		}

		void Trd_extract(cmta MA)
		{
			if( ui_ht != 3 || MA.ui_ht != MA.ui_len || MA.ui_len != ui_len )throw OptiVec_SizeErr();
			MCETrd_extract(vx_m0, MA.vx_m0, ui_len);
		}

		void equM(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			MCEequM(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void neg(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			MCEneg(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void conj(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			MCEconj(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void UequL()
		{
			if( !ui_len || ui_len != ui_ht )throw OptiVec_SizeErr();
			MCEUequL(vx_m0, ui_len);
		}

		void LequU()
		{
			if( !ui_len || ui_len != ui_ht )throw OptiVec_SizeErr();
			MCELequU(vx_m0, ui_len);
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//
		//defined by including cfMatObj.h
		void CFtoCE(const cfMatObj& X);

		//defined by including cdMatObj.h
		void CDtoCE(const cdMatObj& X);


/////////////////////////////////////////////////////////////////////////////////////////
//Submatrices
//
		void submatrix(cmta MSrce, cuint firstRowInCol, cuint sampInCol, cuint firstColInRow, cuint sampInRow )
		{
			if( (MSrce.ui_ht  <= firstRowInCol+(ui_ht-1) *sampInCol) ||
	 	 	    (MSrce.ui_len <= firstColInRow+(ui_len-1)*sampInRow) ) throw OptiVec_SizeErr();
			MCEsubmatrix(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
	 	 	       firstRowInCol, sampInCol, firstColInRow, sampInRow );
		}

		void submatrix_equM(cuint firstRowInCol, cuint sampInCol, cuint firstColInRow, cuint sampInRow, cmta MSrce)
		{
			if( (ui_ht  <= firstRowInCol+(MSrce.ui_ht-1) *sampInCol) ||
	 	 	     (ui_len <= firstColInRow+(MSrce.ui_len-1)*sampInRow) ) throw OptiVec_SizeErr();
			MCEsubmatrix_equM(vx_m0, ui_ht, ui_len,
	 	 	   firstRowInCol, sampInCol, firstColInRow, sampInRow,
	 	 	   MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len );
		}

		void equMblock(cmta MSrce, cuint firstRowInCol, cuint firstColInRow )
		{
			if( (MSrce.ui_ht  < firstRowInCol+ui_ht) ||
	 	 	  (MSrce.ui_len < firstColInRow+ui_len) ) throw OptiVec_SizeErr();
			MCEequMblock(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
	 	 	   firstRowInCol, firstColInRow );
		}

		void equMblockT(cmta MSrce, cuint firstRowInCol, cuint firstColInRow )
		{
			if( (MSrce.ui_ht  < firstRowInCol+ui_len) ||
	 	 	  (MSrce.ui_len < firstColInRow+ui_ht) ) throw OptiVec_SizeErr();
			MCEequMblockT(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
	 	 	   firstRowInCol, firstColInRow );
		}

		void block_equM(cuint firstRowInCol, cuint firstColInRow, cmta MSrce )
		{
			if( (ui_ht  < firstRowInCol+MSrce.ui_ht) ||
	 	 	  (ui_len < firstColInRow+MSrce.ui_len) ) throw OptiVec_SizeErr();
			MCEblock_equM(vx_m0, ui_ht, ui_len, firstRowInCol, firstColInRow,
	 	 	   MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len );
		}

		void block_equMT(cuint firstRowInCol, cuint firstColInRow, cmta MSrce )
		{
			if( (ui_ht  < firstRowInCol+MSrce.ui_len) ||
	 	 	  (ui_len < firstColInRow+MSrce.ui_ht) ) throw OptiVec_SizeErr();
			MCEblock_equMT(vx_m0, ui_ht, ui_len, firstRowInCol, firstColInRow,
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
				MCERow_delete(vx_m0, vx_m0, ui_ht--, ui_len, iRow);
			}
			else
			{	enforceSize(MA.ui_ht-1, MA.ui_len);
				MCERow_delete(vx_m0, MA.vx_m0, MA.ui_ht, MA.ui_len, iRow);
			}
		}

		void Col_delete(cmta MA, cuint iCol)
		{
			if( MA.ui_len <= iCol ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = MCE_matrix( ui_ht, ui_len-1 );
				MCECol_delete(tmp[0], MA.vx_m0, ui_ht, ui_len--, iCol);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size -= ui_ht;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht, MA.ui_len-1);
				MCECol_delete(vx_m0, MA.vx_m0, ui_ht, ui_len, iCol);
			}
		}

		void Row_insert(cmta MA, cuint iRow, cvta X)
		{
			if( ui_ht <= iRow ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = MCE_matrix( ++ui_ht, ui_len );
				MCERow_insert(tmp[0], MA.vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size += ui_len;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht+1, MA.ui_len);
				MCERow_insert(vx_m0, MA.vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
			}
		}

		void Col_insert(cmta MA, cuint iCol, cvta X)
		{
			if( ui_len <= iCol ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = MCE_matrix( ui_ht, ++ui_len );
				MCECol_insert(tmp[0], MA.vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size += ui_ht;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht, MA.ui_len+1);
				MCECol_insert(vx_m0, MA.vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
			}
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Basic arithmetic operations performed on one single row, or one single column
// of any matrix, or on the diagonal of a square matrix
//

		void Row_neg(cuint iRow)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_neg(vx_m0, ui_ht, ui_len, iRow);
		}

		void Col_neg(cuint iCol)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_neg(vx_m0, ui_ht, ui_len, iCol);
		}

		void Row_conj(cuint iRow)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_conj(vx_m0, ui_ht, ui_len, iRow);
		}

		void Col_conj(cuint iCol)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_conj(vx_m0, ui_ht, ui_len, iCol);
		}

		void Row_addC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_addC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_addC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_addC(vx_m0, ui_ht, ui_len, iCol, C);
		}

	 	 void Dia_addC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MCEDia_addC(vx_m0, ui_len, C);
		}

		void Row_addV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MCERow_addV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_addV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MCECol_addV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

	 	 void Dia_addV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MCEDia_addV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_subC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_subC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_subC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_subC(vx_m0, ui_ht, ui_len, iCol, C);
		}

	 	 void Dia_subC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MCEDia_subC(vx_m0, ui_len, C);
		}

		void Row_subV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MCERow_subV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_subV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MCECol_subV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

	 	void Dia_subV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MCEDia_subV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_subrC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_subrC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_subrC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_subrC(vx_m0, ui_ht, ui_len, iCol, C);
		}

	 	void Dia_subrC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MCEDia_subrC(vx_m0, ui_len, C);
		}

		void Row_subrV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MCERow_subrV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_subrV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MCECol_subrV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

	 	void Dia_subrV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MCEDia_subrV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_mulC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_mulC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_mulC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_mulC(vx_m0, ui_ht, ui_len, iCol, C);
		}

	 	void Dia_mulC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MCEDia_mulC(vx_m0, ui_len, C);
		}

		void Row_mulV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MCERow_mulV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_mulV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MCECol_mulV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

	 	void Dia_mulV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MCEDia_mulV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_divC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_divC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_divC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_divC(vx_m0, ui_ht, ui_len, iCol, C);
		}

	 	void Dia_divC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MCEDia_divC(vx_m0, ui_len, C);
		}

		void Row_divV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MCERow_divV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_divV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MCECol_divV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

	 	void Dia_divV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MCEDia_divV(vx_m0, ui_len, X.vx_vect);
		}

		void Row_divrC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MCERow_divrC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_divrC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MCECol_divrC(vx_m0, ui_ht, ui_len, iCol, C);
		}

	 	void Dia_divrC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MCEDia_divrC(vx_m0, ui_len, C);
		}

		void Row_divrV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) || (X.ui_size < ui_len))throw OptiVec_SmallSizeErr();
			MCERow_divrV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_divrV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) || (X.ui_size < ui_ht) )throw OptiVec_SmallSizeErr();
			MCECol_divrV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

	 	void Dia_divrV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) || (X.ui_size < ui_len) )throw OptiVec_SmallSizeErr();
			MCEDia_divrV(vx_m0, ui_len, X.vx_vect);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//One-dimensional vector operations
//performed along all rows or columns, or along the diagonal of a square matrix
//(some of these functions belong to eVecObj.h)

		t Dia_maxReIm() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_maxReIm(vx_m0, ui_len);
		}

		t Dia_minReIm() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_minReIm(vx_m0, ui_len);
		}

		tbase Dia_absmax() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_absmax(vx_m0, ui_len);
		}

		tbase Dia_absmin() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_absmin(vx_m0, ui_len);
		}

		t Dia_absmaxReIm() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_absmaxReIm(vx_m0, ui_len);
		}

		t Dia_absminReIm() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_absminReIm(vx_m0, ui_len);
		}

		t Dia_sabsmax() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_sabsmax(vx_m0, ui_len);
		}

		t Dia_sabsmin() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_sabsmin(vx_m0, ui_len);
		}

		t Dia_cabsmax() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_cabsmax(vx_m0, ui_len);
		}

		t Dia_cabsmin() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_cabsmin(vx_m0, ui_len);
		}

		t Dia_sum() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_sum(vx_m0, ui_len);
		}

		t Dia_prod() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MCEDia_prod(vx_m0, ui_len);
		}

		void Rows_runsum()
		{
			enforceSize();
			MCERows_runsum(vx_m0, ui_ht, ui_len);
		}

		void Cols_runsum()
		{
			enforceSize();
			MCECols_runsum(vx_m0, ui_ht, ui_len);
		}

		void Rows_runprod()
		{
			enforceSize();
			MCERows_runprod(vx_m0, ui_ht, ui_len);
		}

		void Cols_runprod()
		{
			enforceSize();
			MCECols_runprod(vx_m0, ui_ht, ui_len);
		}

		void Rows_rotate(const ssize_t pos)
		{
			enforceSize();
			MCERows_rotate(vx_m0, ui_ht, ui_len, pos);
		}

		void Cols_rotate(const ssize_t pos)
		{
			enforceSize();
			MCECols_rotate(vx_m0, ui_ht, ui_len, pos);
		}

		void Rows_rotate_buf(const ssize_t pos, cmta MBuf)
		{
			enforceSize();
			MCERows_rotate_buf(vx_m0, ui_ht, ui_len, pos, MBuf.vx_m0);
		}

		void Cols_rotate_buf(const ssize_t pos, cmta MBuf)
		{
			enforceSize();
			MCECols_rotate_buf(vx_m0, ui_ht, ui_len, pos, MBuf.vx_m0);
		}

		void Rows_reflect()
		{
			enforceSize();
			MCERows_reflect(vx_m0, ui_ht, ui_len);
		}

		void Cols_reflect()
		{
			enforceSize();
			MCECols_reflect(vx_m0, ui_ht, ui_len);
		}

		void Rows_rev()
		{
			enforceSize();
			MCERows_rev(vx_m0, ui_ht, ui_len);
		}

		void Cols_rev()
		{
			enforceSize();
			MCECols_rev(vx_m0, ui_ht, ui_len);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Operations involving two rows or two colums of one matrix
//
		void Rows_exchange(cuint row1, cuint row2)
		{
			if( !ui_len || (ui_ht <= row1) || (ui_ht <= row2))throw OptiVec_SizeErr();
			MCERows_exchange(vx_m0, ui_ht, ui_len, row1, row2);
		}

		void Cols_exchange(cuint col1, cuint col2)
		{
			if( !ui_len || (ui_ht <= col1) || (ui_ht <= col2))throw OptiVec_SizeErr();
			MCECols_exchange(vx_m0, ui_ht, ui_len, col1, col2);
		}

		void Rows_add(cuint destRow, cuint srceRow)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MCERows_add(vx_m0, ui_ht, ui_len, destRow, srceRow);
		}

		void Cols_add(cuint destCol, cuint srceCol)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol))throw OptiVec_SizeErr();
			MCECols_add(vx_m0, ui_ht, ui_len, destCol, srceCol);
		}

		void Rows_sub(cuint destRow, cuint srceRow)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MCERows_sub(vx_m0, ui_ht, ui_len, destRow, srceRow);
		}

		void Cols_sub(cuint destCol, cuint srceCol)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol))throw OptiVec_SizeErr();
			MCECols_sub(vx_m0, ui_ht, ui_len, destCol, srceCol);
		}

		void Rows_Cadd(cuint destRow, cuint srceRow, cta C)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MCERows_Cadd(vx_m0, ui_ht, ui_len, destRow, srceRow, C);
		}

		void Cols_Cadd(cuint destCol, cuint srceCol, cta C)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol))throw OptiVec_SizeErr();
			MCECols_Cadd(vx_m0, ui_ht, ui_len, destCol, srceCol, C);
		}

		void Rows_lincomb(cuint destRow, cta destC, cuint srceRow, cta srceC)
		{
			if( !ui_len || (ui_ht <= destRow) || (ui_ht <= srceRow))throw OptiVec_SizeErr();
			MCERows_lincomb(vx_m0, ui_ht, ui_len, destRow, destC, srceRow, srceC);
		}

		void Cols_lincomb(cuint destCol, cta destC, cuint srceCol, cta srceC)
		{
			if( !ui_len || (ui_ht <= destCol) || (ui_ht <= srceCol)) throw OptiVec_SizeErr();
			MCECols_lincomb(vx_m0, ui_ht, ui_len, destCol, destC, srceCol, srceC);
		}

/////////////////////////////////////////////////////////////////////////////////////////
// Matrix transposition and rotation
//
		void transpose(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MCEtranspose(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void hermconj(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MCEhermconj(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate90(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MCErotate90(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate180(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MCErotate180(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate270(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MCErotate270(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Matrix arithmetics
//(The following functions are more efficient than the arithmetic operators defined above)
//
		void addM(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MCEaddM(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void addMT(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht,  MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MCEaddMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void subM(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MCEsubM(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void subMT(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht,  MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MCEsubMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void subrM(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MCEsubM(vx_m0, MB.vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void subrMT(cmta MA, cmta MB)
		{
			enforceSize(MA.ui_ht,  MA.ui_len);
			enforceSize(MB.ui_len, MB.ui_ht);
			MCEsubrMT(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len);
		}

		void mulC(cmta MA, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			MCEmulC(vx_m0, MA.vx_m0, ui_ht, ui_len, C);
		}

		void divC(cmta MA, cta C)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			MCEdivC(vx_m0, MA.vx_m0, ui_ht, ui_len, C);
		}

		void lincomb(cmta MA, cmta MB, cta CA, cta CB)
		{
			enforceSize(MA.ui_ht, MA.ui_len);
			enforceSize(MB.ui_ht, MB.ui_len);
			MCElincomb(vx_m0, MA.vx_m0, MB.vx_m0, ui_ht, ui_len, CA, CB);
		}

		//mixed multiplications matrix * vector belong to eVecObj
		void mulM( cmta MA, cmta MB )
		{
	 		if( ui_ht != MA.ui_ht || ui_len != MB.ui_len || MB.ui_ht != MA.ui_len )throw OptiVec_SizeErr();
	 		MCEmulM( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_len);
		}

		void mulMT( cmta MA, cmta MB )
		{
 	 		if( ui_ht != MA.ui_ht || ui_len != MB.ui_ht || MB.ui_len != MA.ui_len )throw OptiVec_SizeErr();
	 		MCEmulMT( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_ht);
		}

		void mulMH( cmta MA, cmta MB )
		{
	 		if( ui_ht != MA.ui_ht || ui_len != MB.ui_ht || MB.ui_len != MA.ui_len )throw OptiVec_SizeErr();
	 		MCEmulMH( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_ht);
		}

		void TmulM( cmta MA, cmta MB )
		{
	 		if( ui_ht != MA.ui_len || ui_len != MB.ui_len || MB.ui_ht != MA.ui_ht )throw OptiVec_SizeErr();
	 		MCETmulM( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_len);
		}

		void HmulM( cmta MA, cmta MB )
		{
	 		if( ui_ht != MA.ui_len || ui_len != MB.ui_len || MB.ui_ht != MA.ui_ht )throw OptiVec_SizeErr();
	 		MCEHmulM( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_len);
		}

		void TmulMT( cmta MA, cmta MB )
		{
	 		if( ui_ht != MA.ui_len || ui_len != MB.ui_ht || MB.ui_len != MA.ui_ht )throw OptiVec_SizeErr();
	 		MCETmulMT( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_ht);
		}

		void TmulMH( cmta MA, cmta MB )
		{
	 		if( ui_ht != MA.ui_len || ui_len != MB.ui_ht || MB.ui_len != MA.ui_ht )throw OptiVec_SizeErr();
	 		MCETmulMH( vx_m0, MA.vx_m0, MB.vx_m0, MA.ui_ht, MA.ui_len, MB.ui_ht);
		}

		void dia_mulM( cvta MADia, cmta MB )
		{
			if( ui_ht != MADia.ui_size || ui_len != MB.ui_len || MB.ui_ht != MADia.ui_size )throw OptiVec_SizeErr();
	 		MCEdiamulM( vx_m0, MADia.vx_vect, MB.vx_m0, MB.ui_ht, MB.ui_len );
		}

		void dia_mulMT( cvta MADia, cmta MB )
		{
			if( ui_ht != MADia.ui_size || ui_len != MB.ui_ht || MB.ui_len != MADia.ui_size )throw OptiVec_SizeErr();
	 		MCEdiamulMT( vx_m0, MADia.vx_vect, MB.vx_m0, MB.ui_ht, MB.ui_len );
		}

		void mulMdia( cmta MA, cvta MBDia )
		{
			if( ui_ht != MA.ui_ht || ui_len != MBDia.ui_size || MBDia.ui_size != MA.ui_len )throw OptiVec_SizeErr();
			MCEmulMdia( vx_m0, MA.vx_m0, MBDia.vx_vect, MA.ui_ht, MA.ui_len );
		}

		void TmulMdia( cmta MA, cvta MBDia )
		{
			 if( ui_ht != MA.ui_len || ui_len != MBDia.ui_size || MBDia.ui_size != MA.ui_ht )throw OptiVec_SizeErr();
			MCETmulMdia( vx_m0, MA.vx_m0, MBDia.vx_vect, MA.ui_ht, MA.ui_len );
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Linear Algebra
//
		int LUdecompose( uiVecObj Ind, cmta MA )
		{
			if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len || ui_ht != Ind.ui_size )
				throw OptiVec_SizeErr();
			return MCELUdecompose( vx_m0, Ind.vx_vect, MA.vx_m0, ui_len );
		}

		int LUdecompose( uiVecObj* Ind, cmta MA )
		{
			if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len || ui_ht != Ind->ui_size )
				throw OptiVec_SizeErr();
			return MCELUdecompose( vx_m0, Ind->vx_vect, MA.vx_m0, ui_len );
		}

		int  LUDresult() const
		{
			return MCE_LUDresult();
		}

		void LUDsetEdit(const tbase& Thresh) const
		{
			MCE_LUDsetEdit(Thresh);
		}

		tbase LUDgetEdit() const
		{
			return MCE_LUDgetEdit();
		}

		void LUinv( cmta MLU, const uiVecObj& Ind )
		{
			if( ui_ht != MLU.ui_ht || ui_len != MLU.ui_len || ui_ht != ui_len || ui_ht != Ind.ui_size )
				throw OptiVec_SizeErr();
			MCELUinv( vx_m0, MLU.vx_m0, Ind.vx_vect, ui_len );
		}

		t LUdet( int permut ) const
		{
			if( ui_ht != ui_len ) throw OptiVec_SizeErr();
			return MCELUdet( vx_m0, ui_len, permut );
		}

/*  SVD not yet implemented:
		int SVdecompose( tMatObj *MV, tVecObj *W, cmta MA )
		{
		    if( (MA.ui_ht < MA.ui_len ? (ui_ht != ui_len) : (ui_ht != MA.ui_ht))
		      || ui_len != MA.ui_len || ui_len != MV->ui_len || ui_len != MV->ui_ht
		      || ui_len != W->ui_size )   throw OptiVec_SizeErr();
		    return MCESVdecompose( vx_m0, MV->vx_m0, W->vx_vect,
		                           MA.vx_m0, MA.ui_ht, MA.ui_len );
		}

		int SVdecompose( tMatObj MV, tVecObj W, cmta MA )
		{
		    if( (MA.ui_ht < MA.ui_len ? (ui_ht != ui_len) : (ui_ht != MA.ui_ht))
		      || ui_len != MA.ui_len || ui_len != MV.ui_len || ui_len != MV.ui_ht
		      || ui_len != W.ui_size )   throw OptiVec_SizeErr();
		    return MCESVdecompose( vx_m0, MV.vx_m0, W.vx_vect,
		                           MA.vx_m0, MA.ui_ht, MA.ui_len );
		}

		void SVDsetEdit(cta Thresh) const
		{
			MCE_SVDsetEdit(Thresh);
		}

		t SVDgetEdit() const
		{
			return MCE_SVDgetEdit();
		}
*/

		int inv( cmta MA )
		{
			if( ui_ht != MA.ui_ht || ui_len != MA.ui_len || ui_ht != ui_len )
				throw OptiVec_SizeErr();
			return MCEinv( vx_m0, MA.vx_m0, ui_len );
		}

		t det() const
		{
			if( ui_ht != ui_len ) throw OptiVec_SizeErr();
			return MCEdet( vx_m0, ui_len );
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Fourier Transforms, Convolutions, Filtering
//

		void FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCEFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCERows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCECols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void FFTtoC(const matrix<tbase>& X)
		{
			enforcePow2();
			MEFFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len);
		}

		void Rows_FFTtoC(const matrix<tbase>& X)
		{
			enforcePow2();
			MEpRows_FFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len);
		}

		void Cols_FFTtoC(const matrix<tbase>& X)
		{
			enforcePow2();
			MEpCols_FFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len);
		}

		void filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MCEfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void p_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCEpFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void p_Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCEpRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void p_Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCEpCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void b_FFT(cmta X, int dir, vta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MCEbFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir,Buf.vx_vect);
		}

		void b_Rows_FFT(cmta X, int dir, vta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MCEbRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir,Buf.vx_vect);
		}

		void b_Cols_FFT(cmta X, int dir, vta Buf)
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MCEbCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir,Buf.vx_vect);
		}

		void p_FFTtoC(const matrix<tbase>& X)
		{
			enforcePow2();
			MEpFFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len);
		}

		void p_Rows_FFTtoC(const matrix<tbase>& X)
		{
			enforcePow2();
			MEpRows_FFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len);
		}

		void p_Cols_FFTtoC(const matrix<tbase>& X)
		{
			enforcePow2();
			MEpCols_FFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len);
		}

		void b_FFTtoC(const matrix<tbase>& X, vta Buf )
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MEbFFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len,Buf.vx_vect);
		}

		void b_Rows_FFTtoC(const matrix<tbase>& X, vta Buf )
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MEbRows_FFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len,Buf.vx_vect);
		}

		void b_Cols_FFTtoC(const matrix<tbase>& X, vta Buf )
		{
			enforcePow2();
			if( Buf.ui_size < ui_size )	throw OptiVec_SizeErr();
			MEbCols_FFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len,Buf.vx_vect);
		}

		void p_filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MCEpfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void l_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCElFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void l_Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCElRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void l_Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCElCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void l_FFTtoC(const matrix<tbase>& X)
		{
			enforcePow2();
			MElFFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len);
		}

		void l_filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MCElfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}

		void s_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCEsFFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void s_Rows_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCEsRows_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void s_Cols_FFT(cmta X, int dir=1)
		{
			enforcePow2();
			MCEsCols_FFT(vx_m0,X.vx_m0,ui_ht,ui_len,dir);
		}

		void s_FFTtoC(const matrix<tbase>& X)
		{
			enforcePow2();
			MEsFFTtoC(vx_m0,X.vx_m0,ui_ht,ui_len);
		}

		void s_filter(cmta X, cmta Flt)
		{
			enforcePow2();
			MCEsfilter(vx_m0, X.vx_m0, Flt.vx_m0, ui_ht, ui_len);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Input and Output
//
		void fprint(FILE* stream, unsigned linewidth) const
		{
			enforceSize();
			MCEfprint(stream,vx_m0,ui_ht, ui_len,linewidth);
		}

		void cprint() const
		{
			enforceSize();
			MCEcprint(vx_m0,ui_ht,ui_len);
		}

		void print() const
		{
			fprint(stdout,80);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			MCEwrite(stream,vx_m0,ui_ht,ui_len);
		}

		void read(FILE* stream)
		{
			enforceSize();
			MCEread(vx_m0,ui_ht,ui_len,stream);
		}

		void setWriteFormat(char* formatString) const
		{
			VCE_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VCE_setWriteSeparate(sepString);
		}

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_ht,sizeof(ui),1,stream);
			fwrite(&ui_len,sizeof(ui),1,stream);
			VCE_store(stream,vx_m0,ui_size);
		}

		void recall(FILE* stream)
		{
			ui sz;
			fread(&ui_ht,sizeof(ui),1,stream);
			fread(&ui_len,sizeof(ui),1,stream);
			setSize(ui_ht,ui_len);
			VCE_recall(vx_m0,ui_size,stream);
		}
	};


	inline vt tVecObj::operator*(cmta MY)
	{
		tVecObj tmp(this->ui_size);
		tmp.enforceSize();
		VCEmulM(tmp.vx_vect,vx_vect,MY.vx_m0,MY.ui_ht,MY.ui_len);
		return tmp;
	}

	inline void tVecObj::Row_extract(cmta MA, const ui iRow)
	{
		if( MA.ui_ht <= iRow || ui_size < MA.ui_len || !ui_size ) throw OptiVec_SizeErr();
		MCERow_extract( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len, iRow );
	}

	inline void tVecObj::Col_extract(cmta MA, const ui iCol)
	{
		if( MA.ui_len <= iCol || ui_size < MA.ui_ht || !ui_size ) throw OptiVec_SizeErr();
		MCECol_extract( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len, iCol );
	}

	inline void tVecObj::Dia_extract(cmta MA)
	{
		if( !ui_size || ui_size != MA.ui_len || (MA.ui_len != MA.ui_ht) )throw OptiVec_SizeErr();
		MCEDia_extract( vx_vect, MA.vx_m0, MA.ui_len );
	}

	inline void tVecObj::Rows_maxReIm(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_maxReIm( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_maxReIm(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_maxReIm( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_minReIm(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_minReIm( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_minReIm(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_minReIm( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_absmaxReIm(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_absmaxReIm( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_absmaxReIm(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_absmaxReIm( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_absminReIm(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_absminReIm( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_absminReIm(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_absminReIm( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_sabsmax(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_sabsmax( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_sabsmax(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_sabsmax( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_sabsmin(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_sabsmin( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_sabsmin(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_sabsmin( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_cabsmax(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_cabsmax( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_cabsmax(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_cabsmax( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_cabsmin(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_cabsmin( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_cabsmin(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_cabsmin( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void vector<tbase>::Rows_absmax(cmta MA)
	{
	 	if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_absmax( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void vector<tbase>::Cols_absmax(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_absmax( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void vector<tbase>::Rows_absmin(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_absmin( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void vector<tbase>::Cols_absmin(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_absmin( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_sum(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_sum( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_sum(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_sum( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_prod(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MCERows_prod( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_prod(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MCECols_prod( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::MmulV( cmta MA, cvta X )
	{
		if( ui_size != MA.ui_ht || X.ui_size != MA.ui_len ) throw OptiVec_SizeErr();
		MCEmulV( vx_vect, MA.vx_m0, X.vx_vect, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::MTmulV( cmta MA, cvta X )
	{
		if( ui_size != MA.ui_len || X.ui_size != MA.ui_ht ) throw OptiVec_SizeErr();
		MCETmulV( vx_vect, MA.vx_m0, X.vx_vect, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::mulM( cvta X, cmta MA )
	{
		if( ui_size != MA.ui_len || X.ui_size != MA.ui_ht ) throw OptiVec_SizeErr();
		VCEmulM( vx_vect, X.vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::mulMT( cvta X, cmta MA )
	{
		if( ui_size != MA.ui_ht || X.ui_size != MA.ui_len ) throw OptiVec_SizeErr();
		VCEmulMT( vx_vect, X.vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::LUsolve( cmta MLU, cvta B, const uiVecObj& Ind )
	{
		if( ui_size != MLU.ui_len || ui_size != MLU.ui_ht ||
	 	     ui_size != B.ui_size || ui_size != Ind.ui_size ) throw OptiVec_SizeErr();
		MCELUsolve( vx_vect, MLU.vx_m0, B.vx_vect, Ind.vx_vect, MLU.ui_len );
	}

	inline void tVecObj::LUimprove( cvta B, cmta MA, cmta MLU, const uiVecObj& Ind )
	{
		if( ui_size != MLU.ui_len || ui_size != MLU.ui_ht ||
 		     ui_size != MA.ui_len || ui_size != MA.ui_ht ||
	 	     ui_size != B.ui_size || ui_size != Ind.ui_size ) throw OptiVec_SizeErr();
		MCELUimprove( vx_vect, B.vx_vect, MA.vx_m0, MLU.vx_m0, Ind.vx_vect, MLU.ui_len );
	}

/* SVD not yet implemented:
	inline void tVecObj::SVsolve( cmta MU, cmta MV, cvta W, cvta B )
	{ // result may overwrite B only for "normal", not for over- or under-determined systems
		if( MU.ui_ht < MU.ui_len || MU.ui_len != MV.ui_len || MV.ui_len != MV.ui_ht ||
	 	     B.ui_size != ui_size || W.ui_size != MV.ui_len || ui_size != MU.ui_ht )
	 	throw OptiVec_SizeErr();
		MCESVsolve( vx_vect, MU.vx_m0, MV.vx_m0, W.vx_vect, B.vx_vect, B.ui_size, MU.ui_len );
	}
*/
	inline int tVecObj::solve( cmta MA, cvta B )
	{
		if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
	 	     ui_size != B.ui_size ) throw OptiVec_SizeErr();
		return MCEsolve( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_len );
	}

/*	inline int tVecObj::solveBySVD( cmta MA, cvta B )
	{
		if(ui_size != MA.ui_len || (B.ui_size != MA.ui_ht && B.vx_vect != vx_vect)) throw OptiVec_SizeErr();
		return MCEsolveBySVD( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_ht, MA.ui_len );
	}

	inline int tVecObj::safeSolve( cmta MA, cvta B )
	{
		if( ui_size != MA.ui_len || ui_size != MA.ui_ht ||
	 	     ui_size != B.ui_size ) throw OptiVec_SizeErr();
		return MCEsafeSolve( vx_vect, MA.vx_m0, B.vx_vect, MA.ui_len );
	}
*/

#ifdef CFMATOBJ_H
	inline void cfMatObj::CEtoCF(const ceMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_CEtoCF(vx_m0,X.vx_m0,ui_size);
	}

	inline void ceMatObj::CFtoCE(const cfMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_CFtoCE(vx_m0,X.vx_m0,ui_size);
	}
#endif //CEMATOBJ_H

#ifdef CDMATOBJ_H
	inline void cdMatObj::CEtoCD(const ceMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_CEtoCD(vx_m0,X.vx_m0,ui_size);
	}

	inline void ceMatObj::CDtoCE(const cdMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_CDtoCE(vx_m0,X.vx_m0,ui_size);
	}
#endif //CDMATOBJ_H

#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
}  // end of namespace OptiVec
#endif

#undef cvta
#undef cmta
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
#undef tVecObj
#undef tMatObj

#undef vtbase
#undef tbase

#undef tVecObj
#undef tMatObj
// #ifdef __BORLANDC__
#pragma warn .inl
#endif

#if defined (_INC_CRTDBG) && defined (_CRTDBG_MAP_ALLOC)
    // restore definition of free
    #define   free(p)    _free_dbg(p, _NORMAL_BLOCK)
#endif

#define CEMATOBJ_H
#endif //CEMATOBJ_H
