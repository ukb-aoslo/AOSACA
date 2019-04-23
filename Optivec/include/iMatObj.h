/* iMatObj.H

  object-oriented interface for OptiVec matrix functions of type "int"

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef IMATOBJ_H

#include <VecObj.h>
#include <iVecObj.h>
#include <uVecObj.h>
#include <iVecObj.h>
#include <MIstd.h>

#define cmta const matrix<int>&
#define cvta const vector<int>&
#define cta  const int&
#define cua  const ui&
#define cuint const ui

#define mta  matrix<int>&
#define vta  vector<int>&
#define ta   int&

#define mt   matrix<int>
#define vt   vector<int>
#define t    int
#define tMatrix iMatrix
#define tVector iVector

#define tMatObj iMatObj
#define tVecObj iVecObj
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
			{	mx_matr=MI_matrix(ht,len); vx_m0=mx_matr[0];
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
				{	mx_matr=MI_matrix0(ht,len); vx_m0=mx_matr[0];}
				else
				{	mx_matr=MI_matrix(ht,len);  vx_m0=mx_matr[0];
					VI_equC(vx_m0,ui_size,fill);}
			}
		}

		matrix(cmta init)
		{	if(init.ui_size)
			{	mx_matr= MI_matrix(init.ui_ht, init.ui_len); vx_m0=mx_matr[0];
				ui_ht=init.ui_ht; ui_len=init.ui_len; ui_size=init.ui_size;
				VI_equV(vx_m0, init.vx_m0, ui_size);
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
				mx_matr= MI_matrix(ht, len); vx_m0=mx_matr[0];
				ui_len=len; ui_ht=ht; ui_size= size;
			}
		}

		void setSize(cmta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_len != X.ui_len || ui_ht != X.ui_ht) //only allocate if different sizes
			{	if(mx_matr) M_free(mx_matr);
				mx_matr= MI_matrix(X.ui_ht, X.ui_len); vx_m0=mx_matr[0];
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

		void dealloc()   // identical to free
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
			VI_equV(vx_m0, matr.vx_m0, ui_size);
			return *this;}

		mta operator=(cta scalar)
		{	enforceSize();
			VI_equC(vx_m0, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		tVector operator[](const int& index){return mx_matr[index];}


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
			if(ui_size){ ui_ht=ht;ui_len=len;mx_matr= MI_matrix(ht,len);vx_m0=mx_matr[0];}
		}

		void _matrix0(cuint ht, cuint len) //underscore necessary to avoid confusing with constructor
		{
			dealloc();
			ui_size=((ui)ht)*len;
			if(ui_size){ ui_ht=ht;ui_len=len;mx_matr= MI_matrix0(ht,len);vx_m0=mx_matr[0];}
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single matrix elements
//
		t* Pelement(cuint m, cuint n) const
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MIPelement(vx_m0,ui_ht,ui_len,m,n);
		}

		t element(cuint m, cuint n) const
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MIelement(vx_m0,ui_ht,ui_len,m,n);
		}

		void getElement(t *y, cuint m, cuint n)
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			return MIgetElement(y,vx_m0,ui_ht,ui_len,m,n);
		}

		void setElement(cuint m, cuint n, cta C)
		{
			if(ui_ht<=m || ui_len<=n) throw OptiVec_SmallSizeErr();
			MIsetElement(vx_m0,ui_ht,ui_len,m,n,C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//

		void equ0()
		{
			enforceSize();
			VI_equ0(vx_m0,ui_size);
		}

		void equ1()
		{
			enforceSize();
			MIequ1(vx_m0,ui_len);
		}

		void equm1()
		{
			enforceSize();
			MIequm1(vx_m0,ui_len);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VI_random(vx_m0, ui_size, seed, Min, Max);
		}

		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VI_randomLC(vx_m0, ui_size, seed, Min, Max, state);
		}

		void outerprod(cvta X, cvta Y)
		{
			enforceSize( X.ui_size, Y.ui_size);
			MIouterprod(vx_m0, X.vx_vect, Y.vx_vect, ui_ht, ui_len);
		}

		void Row_equ0(cuint iRow)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MIRow_equ0(vx_m0, ui_ht, ui_len, iRow);
		}

		void Col_equ0(cuint iCol)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MICol_equ0(vx_m0, ui_ht, ui_len, iCol);
		}

		void Dia_equ0()
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MIDia_equ0(vx_m0, ui_len);
		}

		void Row_equC(cuint iRow, cta C)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MIRow_equC(vx_m0, ui_ht, ui_len, iRow, C);
		}

		void Col_equC(cuint iCol, cta C)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MICol_equC(vx_m0, ui_ht, ui_len, iCol, C);
		}

		void Dia_equC(cta C)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MIDia_equC(vx_m0, ui_len, C);
		}

		void Row_equV(cuint iRow, cvta X)
		{
			if( !ui_len || (ui_ht <= iRow) )throw OptiVec_SmallSizeErr();
			MIRow_equV(vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
		}

		void Col_equV(cuint iCol, cvta X)
		{
			if( !ui_ht || (ui_len <= iCol) )throw OptiVec_SmallSizeErr();
			MICol_equV(vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
		}

		void Dia_equV(cvta X)
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SmallSizeErr();
			MIDia_equV(vx_m0, ui_len, X.vx_vect);
		}

		void Trd_equM(cmta MTrd)
		{
			if( MTrd.ui_ht != 3 || ui_ht != ui_len || ui_len != MTrd.ui_len )throw OptiVec_SizeErr();
			MITrd_equM(vx_m0, MTrd.vx_m0, ui_len);
		}

		void Trd_extract(cmta MA)
		{
			if( ui_ht != 3 || MA.ui_ht != MA.ui_len || MA.ui_len != ui_len )throw OptiVec_SizeErr();
			MITrd_extract(vx_m0, MA.vx_m0, ui_len);
		}

		void equM(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			MIequM(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void neg(cmta X)
		{
			enforceSize(X.ui_ht, X.ui_len);
			MIneg(vx_m0, X.vx_m0, ui_ht, ui_len);
		}

		void UequL()
		{
			if( !ui_len || ui_len != ui_ht )throw OptiVec_SizeErr();
			MIUequL(vx_m0, ui_len);
		}

		void LequU()
		{
			if( !ui_len || ui_len != ui_ht )throw OptiVec_SizeErr();
			MILequU(vx_m0, ui_len);
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//
		//defined by including uMatObj.h
		void UtoI(const uMatObj& X);

		//defined by including biMatObj.h
		void BItoI(const biMatObj& X);

		//defined by including siMatObj.h
		void SItoI(const siMatObj& X);

		//defined by including liMatObj.h
		void LItoI(const liMatObj& X);

		//defined by including qiMatObj.h
		void QItoI(const qiMatObj& X);

		//defined by including fMatObj.h
		int roundtoI(const fMatObj& X);
		int floortoI(const fMatObj& X);
		int ceiltoI(const fMatObj& X);
		int choptoI(const fMatObj& X);
		int trunctoI(const fMatObj& X)
		{
			return choptoI(X);
		}

		//defined by including dMatObj.h
		int roundtoI(const dMatObj& X);
		int floortoI(const dMatObj& X);
		int ceiltoI(const dMatObj& X);
		int choptoI(const dMatObj& X);
		int trunctoI(const dMatObj& X)
		{
			return choptoI(X);
		}

#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eMatObj.h
		int roundtoI(const eMatObj& X);
		int floortoI(const eMatObj& X);
		int ceiltoI(const eMatObj& X);
		int choptoI(const eMatObj& X);
		int trunctoI(const eMatObj& X)
		{
			return choptoI(X);
		}
#endif //__BORLANDC__

/////////////////////////////////////////////////////////////////////////////////////////
//Submatrices
//
		void submatrix(cmta MSrce, cuint firstRowInCol, cuint sampInCol, cuint firstColInRow, cuint sampInRow )
		{
			if( (MSrce.ui_ht  <= firstRowInCol+(ui_ht-1) *sampInCol) ||
			   (MSrce.ui_len <= firstColInRow+(ui_len-1)*sampInRow) ) throw OptiVec_SizeErr();
			MIsubmatrix(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
			      firstRowInCol, sampInCol, firstColInRow, sampInRow );
		}

		void submatrix_equM(cuint firstRowInCol, cuint sampInCol, cuint firstColInRow, cuint sampInRow, cmta MSrce)
		{
			if( (ui_ht  <= firstRowInCol+(MSrce.ui_ht-1) *sampInCol) ||
			    (ui_len <= firstColInRow+(MSrce.ui_len-1)*sampInRow) ) throw OptiVec_SizeErr();
			MIsubmatrix_equM(vx_m0, ui_ht, ui_len,
			    firstRowInCol, sampInCol, firstColInRow, sampInRow,
			    MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len );
		}

		void equMblock(cmta MSrce, cuint firstRowInCol, cuint firstColInRow )
		{
			if( (MSrce.ui_ht  < firstRowInCol+ui_ht) ||
			    (MSrce.ui_len < firstColInRow+ui_len) ) throw OptiVec_SizeErr();
			MIequMblock(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
			            firstRowInCol, firstColInRow );
		}

		void equMblockT(cmta MSrce, cuint firstRowInCol, cuint firstColInRow )
		{
			if( (MSrce.ui_ht  < firstRowInCol+ui_len) ||
			    (MSrce.ui_len < firstColInRow+ui_ht) ) throw OptiVec_SizeErr();
			MIequMblockT(vx_m0, ui_ht, ui_len, MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len,
			             firstRowInCol, firstColInRow );
		}

		void block_equM(cuint firstRowInCol, cuint firstColInRow, cmta MSrce )
		{
			if( (ui_ht  < firstRowInCol+MSrce.ui_ht) ||
			     (ui_len < firstColInRow+MSrce.ui_len) ) throw OptiVec_SizeErr();
			MIblock_equM(vx_m0, ui_ht, ui_len, firstRowInCol, firstColInRow,
			             MSrce.vx_m0, MSrce.ui_ht, MSrce.ui_len );
		}

		void block_equMT(cuint firstRowInCol, cuint firstColInRow, cmta MSrce )
		{
			if( (ui_ht  < firstRowInCol+MSrce.ui_len) ||
			    (ui_len < firstColInRow+MSrce.ui_ht) ) throw OptiVec_SizeErr();
			MIblock_equMT(vx_m0, ui_ht, ui_len, firstRowInCol, firstColInRow,
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
				MIRow_delete(vx_m0, vx_m0, ui_ht--, ui_len, iRow);
			}
			else
			{	enforceSize(MA.ui_ht-1, MA.ui_len);
				MIRow_delete(vx_m0, MA.vx_m0, MA.ui_ht, MA.ui_len, iRow);
			}
		}

		void Col_delete(cmta MA, cuint iCol)
		{
			if( MA.ui_len <= iCol ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = MI_matrix( ui_ht, ui_len-1 );
				MICol_delete(tmp[0], MA.vx_m0, ui_ht, ui_len--, iCol);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size -= ui_ht;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht, MA.ui_len-1);
				MICol_delete(vx_m0, MA.vx_m0, ui_ht, ui_len, iCol);
			}
		}

		void Row_insert(cmta MA, cuint iRow, cvta X)
		{
			if( ui_ht <= iRow ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = MI_matrix( ++ui_ht, ui_len );
				MIRow_insert(tmp[0], MA.vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size += ui_len;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht+1, MA.ui_len);
				MIRow_insert(vx_m0, MA.vx_m0, ui_ht, ui_len, iRow, X.vx_vect);
			}
		}

		void Col_insert(cmta MA, cuint iCol, cvta X)
		{
			if( ui_len <= iCol ) throw OptiVec_SmallSizeErr();
			if( mx_matr == MA.mx_matr ) // overwrite MA?
			{
				tMatrix tmp = MI_matrix( ui_ht, ++ui_len );
				MICol_insert(tmp[0], MA.vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
				M_free( mx_matr );
				vx_m0 = tmp[0];
				ui_size += ui_ht;
				mx_matr = tmp;
			}
			else
			{
				enforceSize(MA.ui_ht, MA.ui_len+1);
				MICol_insert(vx_m0, MA.vx_m0, ui_ht, ui_len, iCol, X.vx_vect);
			}
		}


/////////////////////////////////////////////////////////////////////////////////////////
//One-dimensional vector operations
//performed along all rows or columns, or along the diagonal of a square matrix
//(some of these functions belong to iVecObj.h)

		t Dia_max() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MIDia_max(vx_m0, ui_len);
		}

		t Dia_min() const
		{
			if( !ui_len || (ui_len != ui_ht) )throw OptiVec_SizeErr();
			return MIDia_min(vx_m0, ui_len);
		}

		void Rows_rotate(const ssize_t pos)
		{
			enforceSize();
			MIRows_rotate(vx_m0, ui_ht, ui_len, pos);
		}

		void Cols_rotate(const ssize_t pos)
		{
			enforceSize();
			MICols_rotate(vx_m0, ui_ht, ui_len, pos);
		}

		void Rows_rotate_buf(const ssize_t pos, cmta MBuf)
		{
			enforceSize();
			MIRows_rotate_buf(vx_m0, ui_ht, ui_len, pos, MBuf.vx_m0);
		}

		void Cols_rotate_buf(const ssize_t pos, cmta MBuf)
		{
			enforceSize();
			MICols_rotate_buf(vx_m0, ui_ht, ui_len, pos, MBuf.vx_m0);
		}

		void Rows_reflect()
		{
			enforceSize();
			MIRows_reflect(vx_m0, ui_ht, ui_len);
		}

		void Cols_reflect()
		{
			enforceSize();
			MICols_reflect(vx_m0, ui_ht, ui_len);
		}

		void Rows_rev()
		{
			enforceSize();
			MIRows_rev(vx_m0, ui_ht, ui_len);
		}

		void Cols_rev()
		{
			enforceSize();
			MICols_rev(vx_m0, ui_ht, ui_len);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Operations involving two rows or two colums of one matrix
//
		void Rows_exchange(cuint row1, cuint row2)
		{
			if( !ui_len || (ui_ht <= row1) || (ui_ht <= row2))throw OptiVec_SizeErr();
			MIRows_exchange(vx_m0, ui_ht, ui_len, row1, row2);
		}

		void Cols_exchange(cuint col1, cuint col2)
		{
			if( !ui_len || (ui_ht <= col1) || (ui_ht <= col2))throw OptiVec_SizeErr();
			MICols_exchange(vx_m0, ui_ht, ui_len, col1, col2);
		}

/////////////////////////////////////////////////////////////////////////////////////////
// Matrix transposition and rotation
//
		void transpose(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MItranspose(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate90(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MIrotate90(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate180(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MIrotate180(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

		void rotate270(cmta MA)
		{
			enforceSize(MA.ui_len, MA.ui_ht);
			MIrotate270(vx_m0, MA.vx_m0, ui_ht, ui_len);
		}

/////////////////////////////////////////////////////////////////////////////////////////
//Interpolation of Matrix Elements
//
/////////////////////////////////////////////////////////////////////////////////////////
//Matrix arithmetics

/////////////////////////////////////////////////////////////////////////////////////////
//Linear Algebra
//

/////////////////////////////////////////////////////////////////////////////////////////
// Eigenvalues, Matrix Square-Root
//

/////////////////////////////////////////////////////////////////////////////////////////
//Fourier Transforms, Convolutions, Filtering
//

/////////////////////////////////////////////////////////////////////////////////////////
//Data fitting
// All of the fitting functions themselves belong to iVecObj.
// Only a few helper functions follow here:


/////////////////////////////////////////////////////////////////////////////////////////
//Input and Output
//
		void fprint(FILE* stream, unsigned linewidth) const
		{
			enforceSize();
			MIfprint(stream,vx_m0,ui_ht, ui_len,linewidth);
		}

		void cprint() const
		{
			enforceSize();
			MIcprint(vx_m0,ui_ht,ui_len);
		}

		void print() const
		{
			fprint(stdout,80);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			MIwrite(stream,vx_m0,ui_ht,ui_len);
		}

		void read(FILE* stream)
		{
			enforceSize();
			MIread(vx_m0,ui_ht,ui_len,stream);
		}

		void setWriteFormat(char* formatString) const
		{
			VI_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VI_setWriteSeparate(sepString);
		}

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_ht,sizeof(ui),1,stream);
			fwrite(&ui_len,sizeof(ui),1,stream);
			VI_store(stream,vx_m0,ui_size);
		}

		void recall(FILE* stream)
		{
			fread(&ui_ht,sizeof(ui),1,stream);
			fread(&ui_len,sizeof(ui),1,stream);
			setSize(ui_ht,ui_len);
			VI_recall(vx_m0,ui_size,stream);
		}

		#ifdef __MGRAPH_H
			void xyzAutoDensityMap( cvta X, cvta Y, COLORREF mincol, COLORREF maxcol ) const
			{
				enforceSize(X.ui_size,Y.ui_size);
				MIxyzAutoDensityMap( X.vx_vect, Y.vx_vect, vx_m0, ui_ht, ui_len,
														mincol, maxcol );
			}

			void xyzDataDensityMap( cvta X, cvta Y ) const
			{
				enforceSize(X.ui_size,Y.ui_size);
				MIxyzDataDensityMap( X.vx_vect, Y.vx_vect, vx_m0, ui_ht, ui_len);
			}

			void zAutoDensityMap( COLORREF mincol, COLORREF maxcol ) const
			{
				enforceSize();
				MIzAutoDensityMap( vx_m0, ui_ht, ui_len, mincol, maxcol );
			}

			void zDataDensityMap() const
			{
				enforceSize();
				MIzDataDensityMap( vx_m0, ui_ht, ui_len);
			}

		#endif   // __MGRAPH_H
	};  // end of class matrix<T>


	inline void tVecObj::Row_extract(cmta MA, const ui iRow)
	{
		if( MA.ui_ht <= iRow || ui_size < MA.ui_len || !ui_size ) throw OptiVec_SizeErr();
		MIRow_extract( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len, iRow );
	}

	inline void tVecObj::Col_extract(cmta MA, const ui iCol)
	{
		if( MA.ui_len <= iCol || ui_size < MA.ui_ht || !ui_size ) throw OptiVec_SizeErr();
		MICol_extract( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len, iCol );
	}

	inline void tVecObj::Dia_extract(cmta MA)
	{
		if( !ui_size || ui_size != MA.ui_len || (MA.ui_len != MA.ui_ht) )throw OptiVec_SizeErr();
		MIDia_extract( vx_vect, MA.vx_m0, MA.ui_len );
	}

	inline void tVecObj::Rows_max(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MIRows_max( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_max(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MICols_max( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Rows_min(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_ht ) throw OptiVec_SizeErr();
		MIRows_min( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void tVecObj::Cols_min(cmta MA)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_size < MA.ui_len ) throw OptiVec_SizeErr();
		MICols_min( vx_vect, MA.vx_m0, MA.ui_ht, MA.ui_len );
	}

	inline void uiMatObj::Rows_distribution(cvta Limits, cmta MA, int mode=0)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_ht != MA.ui_ht ) throw OptiVec_SizeErr();
		return MIRows_distribution(vx_m0,Limits.vx_vect,ui_size,MA.vx_m0,MA.ui_ht,MA.ui_len,mode);
	}

	inline void uiMatObj::Cols_distribution(cvta Limits, cmta MA, int mode=0)
	{
		if( !MA.ui_ht || !MA.ui_len || ui_len != MA.ui_len ) throw OptiVec_SizeErr();
		return MICols_distribution(vx_m0,Limits.vx_vect,ui_size,MA.vx_m0,MA.ui_ht,MA.ui_len,mode);
	}


#ifdef UMATOBJ_H
	inline void iMatObj::UtoI(const uMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_UtoI(vx_m0,X.vx_m0,ui_size);
	}

	inline void uMatObj::ItoU(const iMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_ItoU(vx_m0,X.vx_m0,ui_size);
	}
#endif //UMATOBJ_H

#ifdef BIMATOBJ_H
	inline void iMatObj::BItoI(const biMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_BItoI(vx_m0,X.vx_m0,ui_size);
	}

	inline void biMatObj::ItoBI(const iMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_ItoBI(vx_m0,X.vx_m0,ui_size);
	}
#endif //BIMATOBJ_H

#ifdef SIMATOBJ_H
	inline void iMatObj::SItoI(const siMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_SItoI(vx_m0,X.vx_m0,ui_size);
	}

	inline void siMatObj::ItoSI(const iMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_ItoSI(vx_m0,X.vx_m0,ui_size);
	}
#endif //SIMATOBJ_H

#ifdef LIMATOBJ_H
	inline void iMatObj::LItoI(const liMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_LItoI(vx_m0,X.vx_m0,ui_size);
	}

	inline void liMatObj::ItoLI(const iMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_ItoLI(vx_m0,X.vx_m0,ui_size);
	}
#endif //LIMATOBJ_H

#ifdef QIMATOBJ_H
	inline void iMatObj::QItoI(const qiMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_QItoI(vx_m0,X.vx_m0,ui_size);
	}

	inline void qiMatObj::ItoQI(const iMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_ItoQI(vx_m0,X.vx_m0,ui_size);
	}
#endif //QIMATOBJ_H

#ifdef FMATOBJ_H
	inline void fMatObj::ItoF(const iMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		V_ItoF(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::roundtoI(const fMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VF_roundtoI(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::floortoI(const fMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VF_floortoI(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::ceiltoI(const fMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VF_ceiltoI(vx_m0,X.vx_m0,ui_size);
	}

	inline int iMatObj::choptoI(const fMatObj& X)
	{
		enforceSize(X.ui_ht, X.ui_len);
		return VF_choptoI(vx_m0,X.vx_m0,ui_size);
	}
#endif //FMATOBJ_H

#ifdef DMATOBJ_H
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

#endif //DMATOBJ_H

#ifdef EMATOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers defined
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

#endif //__BORLANDC__
#endif //EMATOBJ_H

#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
}  // end of namespace OptiVec
#endif

#undef cmta
#undef cvta
#undef cua
#undef cta

#undef vta
#undef mta
#undef cuint
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

#define IMATOBJ_H
#endif //IMATOBJ_H
