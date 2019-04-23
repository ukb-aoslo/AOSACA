/*  Mgraph.h

  matrix graphics functions for all floating-point data types
  for image processing

  Copyright (c) 1996-2017 by OptiCode - Dr. Martin Sander Software Dev.
  All Rights Reserved.
*/

#ifndef __MGRAPH_H
#define __MGRAPH_H
#if !defined( __VGRAPH_H )
   #include <VGraph.h>
#endif
#if !defined( __MATLIB_H )
    #include <MatLib.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

/*  Density map:  values are translated into a color between
    two extremes, given as mincolor and maxcolor.
*/

typedef struct {
      VCOORDSYSTEM CartesCoord;
      extended     z_max, z_min, z_range, z_maxoverrange,
                   x_LoBorder, x_HiBorder, x_Pad,
                   y_LoBorder, y_HiBorder, y_Pad,
      #if defined _WINDOWS
           z_densityScale[4];
      #else
           z_densityScale;
      #endif
      COLORREF z_minColor;
} MCOORDSYSTEM;

#define M_continuePlot V_continuePlot
void __vf M_getCoordSystem( MCOORDSYSTEM _VFAR *xcs );
void __vf M_setCoordSystem( MCOORDSYSTEM _VFAR *xcs );

void __vf M_findDensityMapBounds( extended xmin, extended xmax,
                                  extended ymin, extended ymax,
                                  extended zmin, extended zmax,
                                  COLORREF mincolor, COLORREF maxcolor );
void __vf M_setDensityMapBounds(  extended xmin, extended xmax,
                                  extended ymin, extended ymax,
                                  extended zmin, extended zmax,
                                  COLORREF mincolor, COLORREF maxcolor );
void __vf M_setDensityBounds(  extended zmin, extended zmax,
                               COLORREF mincolor, COLORREF maxcolor );

#define MF_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MFxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MF_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MFxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MF_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MFzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MF_zDataDensityMap( MZ, ht, len ) \
                 MFzDataDensityMap( (MZ)[0], ht, len )

void __vf MFxyzAutoDensityMap( fVector X, fVector Y, fPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MFxyzDataDensityMap( fVector X, fVector Y, fPMatrix MZ,
                             ui ht, ui len );
void __vf MFzAutoDensityMap( fPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MFzDataDensityMap( fPMatrix MZ, ui ht, ui len );

#define MD_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MDxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MD_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MDxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MD_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MDzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MD_zDataDensityMap( MZ, ht, len ) \
                 MDzDataDensityMap( (MZ)[0], ht, len )

void __vf MDxyzAutoDensityMap( dVector X, dVector Y, dPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MDxyzDataDensityMap( dVector X, dVector Y, dPMatrix MZ,
                             ui ht, ui len );
void __vf MDzAutoDensityMap( dPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MDzDataDensityMap( dPMatrix MZ, ui ht, ui len );

#if (defined __BORLANDC__) && !(defined _WIN64)   /* 80-bit reals supported ? */
#define ME_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MExyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define ME_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MExyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define ME_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MEzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define ME_zDataDensityMap( MZ, ht, len ) \
                 MEzDataDensityMap( (MZ)[0], ht, len )

void __vf MExyzAutoDensityMap( eVector X, eVector Y, ePMatrix MZ,
                               ui ht, ui len,
                               COLORREF mincolor, COLORREF maxcolor );
void __vf MExyzDataDensityMap( eVector X, eVector Y, ePMatrix MZ,
                               ui ht, ui len );
void __vf MEzAutoDensityMap( ePMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MEzDataDensityMap( ePMatrix MZ, ui ht, ui len );

#else   /* ME_ functions identical to MD_ for MSVC, Optima++ */
#define ME_xyzAutoDensityMap  MD_xyzAutoDensityMap
#define ME_xyzDataDensityMap  MD_xyzDataDensityMap
#define ME_zAutoDensityMap    MD_zAutoDensityMap
#define ME_zDataDensityMap    MD_zDataDensityMap
#endif   /*  Borland, Microsoft, Powersoft */

#define MBI_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MBIxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MBI_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MBIxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MBI_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MBIzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MBI_zDataDensityMap( MZ, ht, len ) \
                 MBIzDataDensityMap( (MZ)[0], ht, len )

void __vf MBIxyzAutoDensityMap( biVector X, biVector Y, biPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MBIxyzDataDensityMap( biVector X, biVector Y, biPMatrix MZ,
                             ui ht, ui len );
void __vf MBIzAutoDensityMap( biPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MBIzDataDensityMap( biPMatrix MZ, ui ht, ui len );


#define MUB_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MUBxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MUB_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MUBxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MUB_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MUBzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MUB_zDataDensityMap( MZ, ht, len ) \
                 MUBzDataDensityMap( (MZ)[0], ht, len )

void __vf MUBxyzAutoDensityMap( ubVector X, ubVector Y, ubPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MUBxyzDataDensityMap( ubVector X, ubVector Y, ubPMatrix MZ,
                             ui ht, ui len );
void __vf MUBzAutoDensityMap( ubPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MUBzDataDensityMap( ubPMatrix MZ, ui ht, ui len );


#define MSI_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MSIxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MSI_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MSIxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MSI_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MSIzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MSI_zDataDensityMap( MZ, ht, len ) \
                 MSIzDataDensityMap( (MZ)[0], ht, len )

void __vf MSIxyzAutoDensityMap( siVector X, siVector Y, siPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MSIxyzDataDensityMap( siVector X, siVector Y, siPMatrix MZ,
                             ui ht, ui len );
void __vf MSIzAutoDensityMap( siPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MSIzDataDensityMap( siPMatrix MZ, ui ht, ui len );


#define MUS_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MUSxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MUS_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MUSxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MUS_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MUSzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MUS_zDataDensityMap( MZ, ht, len ) \
                 MUSzDataDensityMap( (MZ)[0], ht, len )

void __vf MUSxyzAutoDensityMap( usVector X, usVector Y, usPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MUSxyzDataDensityMap( usVector X, usVector Y, usPMatrix MZ,
                             ui ht, ui len );
void __vf MUSzAutoDensityMap( usPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MUSzDataDensityMap( usPMatrix MZ, ui ht, ui len );


#define MI_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MIxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MI_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MIxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MI_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MIzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MI_zDataDensityMap( MZ, ht, len ) \
                 MIzDataDensityMap( (MZ)[0], ht, len )

void __vf MIxyzAutoDensityMap( iVector X, iVector Y, iPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MIxyzDataDensityMap( iVector X, iVector Y, iPMatrix MZ,
                             ui ht, ui len );
void __vf MIzAutoDensityMap( iPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MIzDataDensityMap( iPMatrix MZ, ui ht, ui len );


#define MU_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MUxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MU_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MUxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MU_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MUzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MU_zDataDensityMap( MZ, ht, len ) \
                 MUzDataDensityMap( (MZ)[0], ht, len )

void __vf MUxyzAutoDensityMap( uVector X, uVector Y, uPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MUxyzDataDensityMap( uVector X, uVector Y, uPMatrix MZ,
                             ui ht, ui len );
void __vf MUzAutoDensityMap( uPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MUzDataDensityMap( uPMatrix MZ, ui ht, ui len );


#define MLI_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MLIxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MLI_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MLIxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MLI_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MLIzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MLI_zDataDensityMap( MZ, ht, len ) \
                 MLIzDataDensityMap( (MZ)[0], ht, len )

void __vf MLIxyzAutoDensityMap( liVector X, liVector Y, liPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MLIxyzDataDensityMap( liVector X, liVector Y, liPMatrix MZ,
                             ui ht, ui len );
void __vf MLIzAutoDensityMap( liPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MLIzDataDensityMap( liPMatrix MZ, ui ht, ui len );


#define MUL_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MULxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MUL_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MULxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MUL_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MULzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MUL_zDataDensityMap( MZ, ht, len ) \
                 MULzDataDensityMap( (MZ)[0], ht, len )

void __vf MULxyzAutoDensityMap( ulVector X, ulVector Y, ulPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MULxyzDataDensityMap( ulVector X, ulVector Y, ulPMatrix MZ,
                             ui ht, ui len );
void __vf MULzAutoDensityMap( ulPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MULzDataDensityMap( ulPMatrix MZ, ui ht, ui len );


#define MQI_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MQIxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MQI_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MQIxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MQI_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MQIzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MQI_zDataDensityMap( MZ, ht, len ) \
                 MQIzDataDensityMap( (MZ)[0], ht, len )

void __vf MQIxyzAutoDensityMap( qiVector X, qiVector Y, qiPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MQIxyzDataDensityMap( qiVector X, qiVector Y, qiPMatrix MZ,
                             ui ht, ui len );
void __vf MQIzAutoDensityMap( qiPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MQIzDataDensityMap( qiPMatrix MZ, ui ht, ui len );

#ifdef _WIN64
#define MUQ_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MUQxyzAutoDensityMap( X, Y, (MZ)[0], ht, len, mincol, maxcol )
#define MUQ_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MUQxyzDataDensityMap( X, Y, (MZ)[0], ht, len )
#define MUQ_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MUQzAutoDensityMap( (MZ)[0], ht, len, mincol, maxcol )
#define MUQ_zDataDensityMap( MZ, ht, len ) \
                 MUQzDataDensityMap( (MZ)[0], ht, len )

void __vf MUQxyzAutoDensityMap( uqVector X, uqVector Y, uqPMatrix MZ,
                             ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MUQxyzDataDensityMap( uqVector X, uqVector Y, uqPMatrix MZ,
                             ui ht, ui len );
void __vf MUQzAutoDensityMap( uqPMatrix MZ, ui ht, ui len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MUQzDataDensityMap( uqPMatrix MZ, ui ht, ui len );
#endif

/*  Color-Map: each range of values is associated with a certain color.
    Values are defined in a vector ValScale, associated colors in ColScale.
    The parameter "mode" decides how to interpret ValScale:
    mode=0: Val is mid-point;      +1: Val gives upper limit;
        -1: Val gives lower limit.
*/
/* not yet implemented:
void __vf M_findColorMapBounds( extended xmin, extended xmax,
                                extended ymin, extended ymax,
                                extended zmin, extended zmax );
void __vf M_setColorMapBounds(  extended xmin, extended xmax,
                                extended ymin, extended ymax,
                                extended zmin, extended zmax );

void __vf MFxyzAutoColorMap( fVector X, fVector Y, fPMatrix MZ,
                             ui ht, ui len,
                             fVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MFxyzDataColorMap( fVector X, fVector Y, fPMatrix MZ,
                             ui ht, ui len );
void __vf MFzAutoColorMap(   fPMatrix MZ, ui ht, ui len,
                             fVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MFzDataColorMap(   fPMatrix MZ, ui ht, ui len );

void __vf MDxyzAutoColorMap( dVector X, dVector Y, dPMatrix MZ,
                             ui ht, ui len,
                             dVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MDxyzDataColorMap( dVector X, dVector Y, dPMatrix MZ,
                             ui ht, ui len );
void __vf MDzAutoColorMap(   dPMatrix MZ, ui ht, ui len,
                             dVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MDzDataColorMap(   dPMatrix MZ, ui ht, ui len );

void __vf MExyzAutoColorMap( eVector X, eVector Y, ePMatrix MZ,
                             ui ht, ui len,
                             eVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MExyzDataColorMap( eVector X, eVector Y, ePMatrix MZ,
                             ui ht, ui len );
void __vf MEzAutoColorMap(   ePMatrix MZ, ui ht, ui len,
                             eVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MEzDataColorMap(   ePMatrix MZ, ui ht, ui len );
*/

#ifdef __cplusplus
}  // end of extern "C"
#endif
#endif /* __MGRAPH_H */
