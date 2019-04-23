#include "StdAfx.h"
#include "AOSACA.h"
#include "Camera.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include "FreeImage.h"


//#pragma comment(lib, "delayimp")
//#pragma comment(lib, "\\FreeImage\\FreeImage")

//Optivec library headers
#pragma once
#include "VecALL.h"
#include "MatALL.h"

using namespace std;

extern AOSACAParams	*g_AOSACAParams;

CCamera::CCamera(CAOSACADlg *parent)
{
	m_pParent = parent;
	m_pImgBuff = NULL;
	m_pBkgndBuff = NULL;
	m_pBuffer = new BGAPI2::Buffer;

	try {
		m_pSystemList = BGAPI2::SystemList::GetInstance();
		m_pSystemList->Refresh();
		m_pSystem = m_pSystemList->begin()->second;      //GigE: begin(); 
		m_pSystem->Open();
		m_pInterfaceList = m_pSystem->GetInterfaces();
		m_pInterfaceList->Refresh(100);
		m_pInterface = m_pInterfaceList->begin()++->second;
		m_pInterface->Open();
	}

	catch (BGAPI2::Exceptions::IException& ex)
	{
		g_AOSACAParams->g_stAppErrBuff = "No connection to camera!\n\nCheck network configuration (incl. firewall settings) and close any other active camera applications.";
		g_AOSACAParams->ShowError(MB_ICONERROR);
		BGAPI2::SystemList::ReleaseInstance();
		m_pInterface = NULL;
	}
			
	if (g_AOSACAParams->g_bCamReady = Camera_Initialization())	
	{ // Set camera thread and its events
		g_AOSACAParams->g_ehCamLive = CreateEventA(NULL, TRUE, FALSE, "WFS_CAM_LIVE_EVENT");
		g_AOSACAParams->g_ehCamSnap = CreateEventA(NULL, FALSE, FALSE, "WFS_CAM_SNAP_EVENT");
		g_AOSACAParams->g_ehCamNewFrame = CreateEventA(NULL, FALSE, FALSE, "WFS_CAM_NEW_FRAME_EVENT");
		m_ehCamThreadClose = CreateEventA(NULL, FALSE, FALSE, "WFS_CAM_THREAD_CLOSE_EVENT");
		m_ehCamThreadShutdown = CreateEventA(NULL, FALSE, FALSE, "WFS_CAM_THREAD_SHUTDOWN_EVENT");

		thd_handle = CreateThread(NULL, 0, CamThread, this, 0, &thdid_handle);
		SetThreadPriority(thd_handle, THREAD_PRIORITY_HIGHEST);
	}
}

CCamera::~CCamera(void)
{
	if (g_AOSACAParams->g_bCamReady)
	{
		if (g_AOSACAParams->g_frame_mode == LIVESHOW)
			ResetEvent(g_AOSACAParams->g_ehCamLive);
		SetEvent(m_ehCamThreadClose);
		::WaitForSingleObject(m_ehCamThreadShutdown, g_AOSACAParams->EXPOSURE_MS * 2);

		// Stop capturing images
		//m_pDevice->GetRemoteNode("AcquisitionStop")->Execute();
		//m_pDataStream->StopAcquisition();
		// Disconnect the camera
		m_pInterface->Close();
		m_pSystem->Close();
		BGAPI2::SystemList::ReleaseInstance();

		CloseHandle(g_AOSACAParams->g_ehCamNewFrame);
		CloseHandle(g_AOSACAParams->g_ehCamSnap);
		CloseHandle(m_ehCamThreadClose);
		CloseHandle(m_ehCamThreadShutdown);

	}

		if (g_AOSACAParams->g_pImgBuffPrc)
			g_AOSACAParams->g_pImgBuffPrc = NULL;
		if (m_pImgBuff != NULL)
			delete [] m_pImgBuff;
		if (m_pBkgndBuff != NULL)
			delete [] m_pBkgndBuff;

	g_AOSACAParams->g_bCamReady = false;

}

bool CCamera::Camera_Initialization()
{
	//load camera  
	if (!m_pInterface)
		return false;
	m_pDeviceList = m_pInterface->GetDevices();
	m_pDeviceList->Refresh(100);

    if (m_pDeviceList->size() < 1)
    {
		g_AOSACAParams->g_stAppErrBuff.Empty();
		g_AOSACAParams->g_stAppErrBuff = "No camera found!\n\nCheck for devices with Baumer Camera explorer!";
		g_AOSACAParams->ShowError(MB_ICONERROR);
        return false;
    }

	m_pDevice = m_pDeviceList->begin()->second;
	m_pDevice->Open();

	//SET TRIGGER SOURCE "SOFTWARE"
	BGAPI2::String sTriggerSourceNodeName = "";
	BGAPI2::NodeMap * pEnumNodes = m_pDevice->GetRemoteNode("TriggerSource")->GetEnumNodeList();
	if (pEnumNodes->GetNodePresent("SoftwareTrigger")) {
		sTriggerSourceNodeName = "SoftwareTrigger";
	}
	else if (pEnumNodes->GetNodePresent("Software")) {
		sTriggerSourceNodeName = "Software";
	}
	m_pDevice->GetRemoteNode("TriggerSource")->SetString(sTriggerSourceNodeName);

	m_pDevice->GetRemoteNode("TriggerMode")->SetString("On");
	m_pDevice->GetRemoteNode("PixelFormat")->SetString("Mono8");
	m_pDevice->GetRemoteNode("Width")->SetInt(512);
	m_pDevice->GetRemoteNode("OffsetX")->SetInt(72);
	UpdateExposureTime();
	UpdateCameraGain();
	m_pDataStreamList = m_pDevice->GetDataStreams();
	m_pDataStreamList->Refresh();
	m_pDataStream = m_pDataStreamList->begin()->second;
	m_pDataStream->Open();
	if (!m_pDataStream->IsOpen())
		return false;

	m_pBufferList = m_pDataStream->GetBufferList();
	m_pBufferList->Add(m_pBuffer);
	m_pDataStream->StartAcquisitionContinuous();
	m_pDevice->GetRemoteNode("AcquisitionStart")->Execute();

	m_nFrameSizeInBytes = g_AOSACAParams->IMAGE_WIDTH_PIX*g_AOSACAParams->IMAGE_HEIGHT_PIX*sizeof(unsigned char);	
	m_pImgBuff = new BYTE[m_nFrameSizeInBytes];
	ZeroMemory(m_pImgBuff, m_nFrameSizeInBytes);
	m_pBkgndBuff = new BYTE[m_nFrameSizeInBytes];
	ZeroMemory(m_pBkgndBuff, m_nFrameSizeInBytes);
	
	//Load background image into buffer if available
	CStringA filename = "utils\\background.bimg";	
	ifstream bkgndFile;
	bkgndFile.open(filename, ios::in | ios::binary);
	if (!bkgndFile.read ((char*)m_pBkgndBuff, m_nFrameSizeInBytes))
		ZeroMemory(m_pBkgndBuff, m_nFrameSizeInBytes);
	bkgndFile.close();

	return true;
}

bool CCamera::UpdateExposureTime(void)
{

	bo_double exp;
	exp = g_AOSACAParams->EXPOSURE_MS * 1000;

	BGAPI2::String sExposureNodeName = "";
	if (m_pDevice->GetRemoteNodeList()->GetNodePresent("ExposureTime")) {
		sExposureNodeName = "ExposureTime";
	}
	else if (m_pDevice->GetRemoteNodeList()->GetNodePresent("ExposureTimeAbs")) {
		sExposureNodeName = "ExposureTimeAbs";
	}
	m_pDevice->GetRemoteNode(sExposureNodeName)->SetDouble(exp);

	return true;
}

bool CCamera::UpdateCameraGain(void)
{

	bo_int gain = g_AOSACAParams->CAMGAIN_DB;
	m_pDevice->GetRemoteNode("Gain")->SetInt(gain);

	return true;
}

void CCamera::SubtractBackground(void)
{	
	long  i;
	BYTE *buf_f_ptr;
	BYTE *buf_b_ptr;

	// Read the current spots on the screen into buf_f
	buf_f_ptr = g_AOSACAParams->g_pImgBuffPrc;
	buf_b_ptr = m_pBkgndBuff;

	for ( i=0; i<m_nFrameSizeInBytes; i++) 
	{
		if(*(buf_f_ptr) >= *(buf_b_ptr))
			*(buf_f_ptr) = *(buf_f_ptr)- *(buf_b_ptr);
		else 
			*(buf_f_ptr) = 0;

		buf_f_ptr++;
		buf_b_ptr++;
	}
}

void CCamera::CatchFrame(void)
{
	m_pBuffer->QueueBuffer();
	m_pDevice->GetRemoteNode("TriggerSoftware")->Execute();
	m_pDataStream->GetFilledBuffer(100);
	m_pImgBuff = (BYTE*)m_pBuffer->GetMemPtr();
	/*for (size_t i = 0; i < m_nFrameSizeInBytes; ++i)
		g_AOSACAParams->g_pImgBuffPrc[m_nFrameSizeInBytes - 1 - i] = m_pImgBuff[i];*/
	
	memcpy(g_AOSACAParams->g_pImgBuffPrc, m_pImgBuff, m_nFrameSizeInBytes);
	m_pBufferList->DiscardAllBuffers();

	m_pImgBuff = NULL;
}

//*************************************************************************************************
DWORD WINAPI CCamera::CamThread( LPVOID pParam )
{
	CCamera *parent = (CCamera *)pParam;
	HANDLE hCamEvents[3];
	bool bRunCamThread = true;
	CString text;
	double telapse;
	
	hCamEvents[0] = parent->m_ehCamThreadClose; 
	hCamEvents[1] = g_AOSACAParams->g_ehCamLive;
	hCamEvents[2] = g_AOSACAParams->g_ehCamSnap;

	LARGE_INTEGER time1;
	LARGE_INTEGER time2;

	std::wofstream m_Logfile;
//	m_Logfile.open("Clogfile.txt", std::wofstream::out);
	
	do
	{
		switch (::WaitForMultipleObjects(3, hCamEvents, FALSE, INFINITE)) 
		{
		case WAIT_OBJECT_0:
			bRunCamThread = false;			
			//delete rawImage;
			//m_Logfile.close();
			break;
		case WAIT_OBJECT_0+1:			
		//	m_Logfile<<"ELiveT\n";
			g_AOSACAParams->g_frame_mode = LIVESHOW;
			//Get current CPU clock time
			QueryPerformanceCounter(&time1);
			//Retrieve an image
			/*	error = parent->m_FCcam.FireSoftwareTrigger();
				error = parent->m_FCcam.RetrieveBuffer( rawImage );
				pImagePixels = rawImage->GetData();
				memcpy(g_AOSACAParams->g_pImgBuffPrc, pImagePixels, parent->m_nFrameSizeInBytes);			*/

			parent->CatchFrame();
			//Send window update signal to WFS Image dialog	
			parent->m_pParent->PostMessage(WM_UPDATE_WINDOW, 0, UPDATE_WFSIMG_WINDOW);
			//Get current CPU clock time
			QueryPerformanceCounter(&time2);			
			telapse = (double)(g_AOSACAParams->m_lnFreq/(time2.QuadPart-time1.QuadPart));//ticks passed
			text.Format(_T("%2.2f"),telapse);
			(parent->m_pParent)->SetDlgItemText(IDE_FREQUENCY, text);
		//	m_Logfile<<"DLiveT\n";
			break;
		case WAIT_OBJECT_0+2:
		//	m_Logfile<<LPCTSTR(g_AOSACAParams->GetTimeStamp())<<"ESnapT\n";
			g_AOSACAParams->g_frame_mode = SNAPSHOT;
			/*	error = parent->m_FCcam.FireSoftwareTrigger();
				error = parent->m_FCcam.RetrieveBuffer( rawImage );
				pImagePixels = rawImage->GetData();
				memcpy(g_AOSACAParams->g_pImgBuffPrc, pImagePixels, parent->m_nFrameSizeInBytes);*/
			parent->CatchFrame();
			g_AOSACAParams->g_bSubstractBkGnd?parent->SubtractBackground():0;	
			SetEvent(g_AOSACAParams->g_ehCamNewFrame);
		//	m_Logfile<<LPCTSTR(g_AOSACAParams->GetTimeStamp())<<"DSnapT\n";
			break;
		default:
			break;
		}
	}while (bRunCamThread);
	SetEvent(parent->m_ehCamThreadShutdown);

	return 0;
}

BOOL CCamera::SaveImage(CStringA filename, bool bkgnd)
{
	BOOL result = FALSE;
	g_AOSACAParams->g_frame_mode = WAIT;	
	if (bkgnd)
		memcpy(m_pBkgndBuff, g_AOSACAParams->g_pImgBuffPrc, g_AOSACAParams->IMAGE_WIDTH_PIX*g_AOSACAParams->IMAGE_HEIGHT_PIX*sizeof(BYTE));

	/*FlyCapture2::Image saveImage(g_AOSACAParams->IMAGE_HEIGHT_PIX, 
										g_AOSACAParams->IMAGE_WIDTH_PIX, 
										g_AOSACAParams->IMAGE_WIDTH_PIX, 
										g_AOSACAParams->g_pImgBuffPrc, 
										g_AOSACAParams->IMAGE_WIDTH_PIX*g_AOSACAParams->IMAGE_HEIGHT_PIX, 
										PIXEL_FORMAT_MONO8, FlyCapture2::NONE);*/
	// now, we can create a FIBITMAP
	FIBITMAP *dib;
	dib = FreeImage_ConvertFromRawBits(g_AOSACAParams->g_pImgBuffPrc, g_AOSACAParams->IMAGE_WIDTH_PIX, g_AOSACAParams->IMAGE_HEIGHT_PIX, g_AOSACAParams->IMAGE_WIDTH_PIX, 8, 0, 0, 0, true);

	result = FreeImage_Save(FIF_TIFF, dib, filename, TIFF_NONE);
	// unload the FIBITMAP 
	FreeImage_Unload(dib);

	if (bkgnd)
	{
		memcpy(m_pBkgndBuff, g_AOSACAParams->g_pImgBuffPrc, g_AOSACAParams->IMAGE_WIDTH_PIX*g_AOSACAParams->IMAGE_HEIGHT_PIX*sizeof(BYTE));
		CStringA filename = "utils\\background.bimg";
		ofstream bkgndFile;
		bkgndFile.open(filename, ios::out | ios::binary);
		bkgndFile.write((const char*)m_pBkgndBuff, g_AOSACAParams->IMAGE_WIDTH_PIX*g_AOSACAParams->IMAGE_HEIGHT_PIX);
		bkgndFile.close();
		result = true;
	}
	return result;
}