#pragma once
#include "AOSACADlg.h"

//For Baumer WFS (GeniCam interface)
#include "bgapi2_genicam.hpp"

class CCamera
{
private:
	//variables
	CAOSACADlg	*m_pParent;
	HANDLE		m_ehCamThreadClose;
	HANDLE		m_ehCamThreadShutdown;
	DWORD		thdid_handle;			// Camera thread id
	HANDLE		thd_handle;				// Camera thread handle	
	long		m_nFrameSizeInBytes;

	// Camera variables
	BYTE		*m_pImgBuff;			// buffer to store the current active image from camera
	BYTE		*m_pBkgndBuff;			// buffer to store the background image
	
	// GeniCam (Baumer TXG03) specific
	BGAPI2::SystemList		*m_pSystemList;			// Collection of GeniCam system objects
	BGAPI2::System			*m_pSystem;				// Target System (NIC/USB)
	BGAPI2::InterfaceList	*m_pInterfaceList;		// List of available NICS for GeniCam devices
	BGAPI2::Interface		*m_pInterface;			// The used GeniCam interface
	BGAPI2::DeviceList		*m_pDeviceList;			// List of available Cameras
	BGAPI2::Device			*m_pDevice;				// The camera object
	BGAPI2::DataStreamList  *m_pDataStreamList;
	BGAPI2::DataStream		*m_pDataStream;
	BGAPI2::BufferList		*m_pBufferList;
	BGAPI2::Buffer			*m_pBuffer;

	//functions
	bool	Camera_Initialization(void);
	void	RotateImageCCW(unsigned char *in);
	void	RotateImageCW(unsigned char *in);
	void	FlipImageUD(unsigned char *in);
	void	FlipImageLR(unsigned char *in);
	void	antiTranspose(unsigned char *in);
	void	Transpose(unsigned char *in);
	static	DWORD WINAPI CamThread(LPVOID pParam);

public:
	CCamera(CAOSACADlg *parent);
	~CCamera(void);
	void	CatchFrame(void);
	bool	UpdateExposureTime(void);
	bool	UpdateCameraGain(void);
	void	SubtractBackground(void);
	BOOL	SaveImage(CStringA filename, bool bkgnd=false);
};

