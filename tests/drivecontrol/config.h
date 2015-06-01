#ifndef CONFIG_H
#define CONFIG_H

#ifdef __AVR__
  // Arduino
  #include "mower.h"
#else
  // simulator
  #include "sim/simarduino.h"
  #include "led.h"
  #include "motorcontrol.h"
  #include "sim/simmower.h"

  #include <opencv2/core/core.hpp>
  #include <opencv/cv.h>
  #include <opencv2/legacy/legacy.hpp>
  #include <opencv2/legacy/compat.hpp>
  #include <opencv2/highgui/highgui.hpp>
  #include <opencv2/imgproc/imgproc.hpp>
  #include <opencv2/features2d/features2d.hpp>

#endif // __AVR__


#endif



