#include <ruby.h>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

VideoCapture cap;

static VALUE open(VALUE _self, VALUE deviceID);

static VALUE release(VALUE _self);

Mat grab();

static VALUE grab_frame(VALUE _self);

extern "C" void Init_grab_frame_ext(void);
