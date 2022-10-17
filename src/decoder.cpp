/*
https://www.learnopencv.com/barcode-and-qr-code-scanner-using-zbar-and-opencv/
*/

#include <iostream>
#include <string>
#include <vector>
#include <zbar.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace zbar;

typedef struct
{
  string type;
  string data;
  vector<Point> location;
} decodedObject;

// Find and decode barcodes and QR codes
string decode(string imagePath)
{
  // Read image
  Mat im = imread(imagePath);

  // Variable for decoded objects
  vector<decodedObject> decodedObjects;

  // Create zbar scanner
  ImageScanner scanner;

  // Configure scanner
  scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

  // Convert image to grayscale
  Mat imGray;
  cvtColor(im, imGray, COLOR_BGR2GRAY);

  // Wrap image data in a zbar image
  Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

  // Scan the image for barcodes and QRCodes
  scanner.scan(image);

  decodedObject obj;

  for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
  {
    obj.type = symbol->get_type_name();
    obj.data = symbol->get_data();
    decodedObjects.push_back(obj);
  }

  // Return an empty result if nothing was found
  string result = "{\"results\": [";
  if (decodedObjects.empty())
  {
    return result += "]}";
  }

  // Construct result string with decoded information
  for (vector<decodedObject>::iterator elem = decodedObjects.begin(); elem != decodedObjects.end(); ++elem)
  {
    result += "{\"type\": \"" + (*elem).type + "\", \"data\": \"" + (*elem).data + "\"},";
  }
  result.pop_back();
  result += "]}";

  return result;
}
