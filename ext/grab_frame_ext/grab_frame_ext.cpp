#include <ruby.h>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <grab_frame_ext.hpp>

using namespace cv;
using namespace std;

static VALUE open(VALUE _self, VALUE deviceID) {
    int camID = NUM2INT(deviceID);
    Mat frame;
    cap.open(camID);

    cap.read(frame);
    sleep(1);

    if (!cap.isOpened()) {
      rb_raise(rb_eRuntimeError, "Unable to open camera %d", camID);
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
      rb_ary_store(pixel, 2, ULL2NUM(p[2]*255)); // R
      rb_ary_store(pixel, 1, ULL2NUM(p[1]*255)); // G
      rb_ary_store(pixel, 0, ULL2NUM(p[0]*255)); // B

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
