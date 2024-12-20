//------------------------------- 
//GXDQBuf 接口一次获取一帧图像，本样例代码演示的就是如何用此接口获取一帧图像 
//------------------------------- 
#include "GxIAPI.h" 
#include "DxImageProc.h"
 
int main(int argc, char* argv[]) 
{ 
   GX_STATUS     status = GX_STATUS_SUCCESS; 
   GX_DEV_HANDLE hDevice = NULL; 
   uint32_t       nDeviceNum = 0; 
 
   //初始化库,申请资源  
   status = GXInitLib(); 

   
   if (status != GX_STATUS_SUCCESS) 
   { 
       return 0; 
   } 
  
   //枚举设备列表 
   status = GXUpdateDeviceList(&nDeviceNum, 1000); 
   if ((status != GX_STATUS_SUCCESS) || (nDeviceNum <= 0)) 
   { 
       return 0; 
   } 
  
   //打开设备 
   status = GXOpenDeviceByIndex(1, &hDevice); 
   if (status == GX_STATUS_SUCCESS) 
   { 
      //定义GXDQBuf 的传入参数 
      PGX_FRAME_BUFFER pFrameBuffer; 
  
      //开采 
      status = GXStreamOn(hDevice); 
      if (status == GX_STATUS_SUCCESS) 
      { 
         //调用GXDQBuf 取一帧图像 
         status = GXDQBuf(hDevice, &pFrameBuffer, 1000); 
if (status == GX_STATUS_SUCCESS) 
{ 
             if (pFrameBuffer->nStatus == GX_FRAME_STATUS_SUCCESS) 
             { 
                  //图像获取成功 
                  //对图像进行处理... 
     } 
 
//调用GXQBuf 将图像 buf 放回库中继续采图 
status = GXQBuf(hDevice, pFrameBuffer); 
}   
      } 
  
      //停采 
      status = GXStreamOff(hDevice);
    } 
    //释放资源
    status = GXCloseDevice(hDevice); 
    status = GXCloseLib(); 
 
    return 0; 
} 