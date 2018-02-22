#import <Foundation/Foundation.h>
#include <CoreFoundation/CoreFoundation.h>

#include <IOKit/IOKitLib.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>

//http://phoboslab.org/log/2009/07/uvc-camera-control-for-mac-os-x#comment107

#define USE_C920


#define UVC_INPUT_TERMINAL_ID 0x01

#ifdef USE_C920
#define UVC_PROCESSING_UNIT_ID 0x03 //changed this to work with c920, might not work with others
#else
#define UVC_PROCESSING_UNIT_ID 0x02
#endif


#define UVC_CONTROL_INTERFACE_CLASS 14
#define UVC_CONTROL_INTERFACE_SUBCLASS 1

#define UVC_SET_CUR	0x01
#define UVC_GET_CUR	0x81
#define UVC_GET_MIN	0x82
#define UVC_GET_MAX	0x83
#define UVC_GET_INFO 0x86

typedef struct {
	int min, max;
} uvc_range_t;

typedef struct {
	int unit;
	int selector;
	int size;
} uvc_control_info_t;

typedef struct {
	uvc_control_info_t autoExposure;
	uvc_control_info_t exposure;
	uvc_control_info_t absoluteFocus;
	uvc_control_info_t autoFocus;
	uvc_control_info_t focus;
	uvc_control_info_t brightness;
	uvc_control_info_t contrast;
	uvc_control_info_t gain;
	uvc_control_info_t saturation;
	uvc_control_info_t sharpness;
	uvc_control_info_t whiteBalance;
	uvc_control_info_t autoWhiteBalance;
    uvc_control_info_t incremental_exposure;
    uvc_control_info_t powerLineFrequency;
    uvc_control_info_t backlightCompensation;
    uvc_control_info_t hue;
    uvc_control_info_t gamma;
} uvc_controls_t ;


@interface UVCCameraControl : NSObject {
	long dataBuffer;
	IOUSBInterfaceInterface190 **interface;
    
    long interfaceNum;
}


- (id)initWithLocationID:(UInt32)locationID;
- (id)initWithVendorID:(long)vendorID productID:(long)productID interfaceNum:(long)interfaceNum;
- (IOUSBInterfaceInterface190 **)getControlInferaceWithDeviceInterface:(IOUSBDeviceInterface **)deviceInterface;

- (BOOL)sendControlRequest:(IOUSBDevRequest)controlRequest;
- (BOOL)setData:(long)value withLength:(int)length forSelector:(int)selector at:(int)unitID;
- (long)getDataFor:(int)type withLength:(int)length fromSelector:(int)selector at:(int)unitID;

- (uvc_range_t)getRangeForControl:(const uvc_control_info_t *)control;
- (float)mapValue:(float)value fromMin:(float)fromMin max:(float)fromMax toMin:(float)toMin max:(float)toMax;
- (float)getValueForControl:(const uvc_control_info_t *)control;
- (BOOL)setValue:(float)value forControl:(const uvc_control_info_t *)control;

- (void) incrementExposure;
- (void) decrementExposure;
- (void) setDefaultExposure;

- (long) getInfoForControl:(uvc_control_info_t *)control;
- (uvc_controls_t *) getControls;

- (BOOL)setAutoExposure:(BOOL)enabled;
- (BOOL)getAutoExposure;
- (BOOL)setExposure:(float)value;
- (float)getExposure;

- (BOOL)setAutoFocus:(BOOL)enabled;
- (BOOL)getAutoFocus;
- (BOOL)setAbsoluteFocus:(float)value;
- (float)getAbsoluteFocus;

- (BOOL)setAutoWhiteBalance:(BOOL)enabled;
- (BOOL)getAutoWhiteBalance;
- (BOOL)setWhiteBalance:(float)value;
- (float)getWhiteBalance;


- (BOOL)setGain:(float)value;
- (float)getGain;
- (BOOL)setBrightness:(float)value;
- (float)getBrightness;
- (BOOL)setContrast:(float)value;
- (float)getContrast;
- (BOOL)setSaturation:(float)value;
- (float)getSaturation;
- (BOOL)setSharpness:(float)value;
- (float)getSharpness;
- (BOOL)setPowerLineFrequency:(float)value;
- (float)getPowerLineFrequency;
- (BOOL)setBacklightCompensation:(float)value;
- (float)getBacklightCompensation;
- (BOOL)setHue:(float)value;
- (float)getHue;
- (BOOL)setGamma:(float)value;
- (float)getGamma;
@end
