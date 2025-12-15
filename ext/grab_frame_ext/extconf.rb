require "mkmf"
require "pkg-config"

$CXXFLAGS << " -std=c++11 "

$INCFLAGS << " " + PKGConfig.cflags("opencv4")
$LDFLAGS << " " + PKGConfig.libs("opencv4")

have_header("unistd.h") # for usleep

create_makefile("grab_frame_ext")
