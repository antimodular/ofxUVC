#ifdef __OFX_UVC_PROBER__
void useCameraByDeviceIndex(int i){
    int vendorID, productID;
    tie(vendorID,productID) = ofxUVCProber::getVendorIDAndProductIDByDeviceIndex(i);
    useCamera(vendorID,productID,0x00);
}
void useFirstCamera(){
    useCameraByDeviceIndex(0);
}
void useCameraByDeviceName(std::string s){
    int vendorID, productID;
    tie(vendorID,productID) = ofxUVCProber::getVendorIDAndProductIDByDeviceName(s);
    useCamera(vendorID,productID,0x00);
}
#endif
