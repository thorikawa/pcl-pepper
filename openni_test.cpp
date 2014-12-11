#include <openni2/OpenNI.h>
#include <iostream>
#include "Viewer.h"

using namespace std;
using namespace openni;

int main (int argc, char **argv) {
  openni::Status rc = openni::STATUS_OK;
  openni::Device device;
  openni::VideoStream depth, color;
  const char* deviceURI = openni::ANY_DEVICE;
  rc = OpenNI::initialize();
  printf("After initialization:\n%s\n", openni::OpenNI::getExtendedError());

  openni::Array<openni::DeviceInfo> deviceList;
  OpenNI::enumerateDevices(&deviceList);
  printf("size=%d\n", deviceList.getSize());
  for (int i = 0; i < deviceList.getSize(); ++i) {
    const openni::DeviceInfo& info = deviceList[i];
    string uri = info.getUri();
    cout << uri << endl;
    // device->open(uri.c_str());
    // char serialNumber[1024];
    // device->getProperty(ONI_DEVICE_PROPERTY_SERIAL_NUMBER, &serialNumber);
    // if (string(serialNumber) != wantedSerialNumber) {
    //     device->close();
    // } else {
    //     break;
    // }
  }

  rc = device.open(deviceURI);
  if (rc != openni::STATUS_OK)
  {
    printf("SimpleViewer: Device open failed:\n%s\n", openni::OpenNI::getExtendedError());
    openni::OpenNI::shutdown();
    return 1;
  }
  rc = depth.create(device, openni::SENSOR_DEPTH);
  if (rc == openni::STATUS_OK)
  {
    rc = depth.start();
    if (rc != openni::STATUS_OK)
    {
      printf("SimpleViewer: Couldn't start depth stream:\n%s\n", openni::OpenNI::getExtendedError());
      depth.destroy();
    }
  }
  else
  {
    printf("SimpleViewer: Couldn't find depth stream:\n%s\n", openni::OpenNI::getExtendedError());
  }
  rc = color.create(device, openni::SENSOR_COLOR);
  if (rc == openni::STATUS_OK)
  {
    rc = color.start();
    if (rc != openni::STATUS_OK)
    {
      printf("SimpleViewer: Couldn't start color stream:\n%s\n", openni::OpenNI::getExtendedError());
      color.destroy();
    }
  }
  else
  {
    printf("SimpleViewer: Couldn't find color stream:\n%s\n", openni::OpenNI::getExtendedError());
  }
  if (!depth.isValid() || !color.isValid())
  {
    printf("SimpleViewer: No valid streams. Exiting\n");
    openni::OpenNI::shutdown();
    return 2;
  }
  SampleViewer sampleViewer("Simple Viewer", device, depth, color);

  rc = sampleViewer.init(argc, argv);
  if (rc != openni::STATUS_OK)
  {
    openni::OpenNI::shutdown();
    return 3;
  }
  sampleViewer.run();
  return 0;
}
