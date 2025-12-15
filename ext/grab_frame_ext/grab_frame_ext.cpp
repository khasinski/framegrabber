#include <ruby.h>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <grab_frame_ext.hpp>
#include <unistd.h>

using namespace cv;
using namespace std;

static VALUE open(VALUE _self, VALUE deviceID) {
    int camID = NUM2INT(deviceID);
    cap.open(camID);

    if (!cap.isOpened()) {
      rb_raise(rb_eRuntimeError, "Unable to open camera %d", camID);
    }

    // Wait for camera to provide a valid frame
    Mat frame;
    int attempts = 0;
    const int max_attempts = 50; // 5 seconds at 100ms intervals
    while (attempts < max_attempts) {
      cap.read(frame);
      if (!frame.empty()) {
        break;
      }
      usleep(100000); // 100ms
      attempts++;
    }

    if (frame.empty()) {
      cap.release();
      rb_raise(rb_eRuntimeError, "Camera %d failed to provide valid frame within timeout", camID);
    }

    return Qnil;
}

static VALUE release(VALUE _self) {
    cap.release();
    return Qnil;
}

Mat grab()
{
    Mat frame;
    cap.read(frame);

    if (frame.empty()) {
        rb_raise(rb_eRuntimeError, "Empty frame captured");
    }
    return frame;
}

static VALUE grab_frame(VALUE _self) {
  Mat frame = grab();

  VALUE result = rb_ary_new_capa(frame.cols);

  if(frame.empty()) {
    return result;
  }

  int i = 0, j = 0;
  for(i=0; i<frame.rows; ++i) {
    VALUE row = rb_ary_new_capa(frame.cols);
    for(j=0; j<frame.cols; j++) {
      VALUE pixel = rb_ary_new_capa(3);
      unsigned char * p = frame.ptr(i, j); // Y first, X after
      rb_ary_store(pixel, 0, ULL2NUM(p[2])); // R
      rb_ary_store(pixel, 1, ULL2NUM(p[1])); // G
      rb_ary_store(pixel, 2, ULL2NUM(p[0])); // B

      rb_ary_store(row, j, pixel);
    }
    rb_ary_store(result, i, row);
  }
  return result;
}

extern "C"
void Init_grab_frame_ext(void) {
  VALUE Framegrabber = rb_const_get(rb_cObject, rb_intern("Framegrabber"));
  rb_define_module_function(Framegrabber, "grab_frame", grab_frame, 0);
  rb_define_module_function(Framegrabber, "open", open, 1);
  rb_define_module_function(Framegrabber, "release", release, 0);
}
