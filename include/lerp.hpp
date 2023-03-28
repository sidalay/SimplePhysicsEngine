#ifndef LERP_HPP
#define LERP_HPP

namespace spe 
{
  static float blend{};
  static float direction{0.01};

  float Lerp(float a, float b, float t);
  float InvLerp(float a, float b, float v);
  float Remap(float iMin, float iMax, float oMin, float oMax, float v);
  float EaseIn(float t);
  float EaseOut(float t);
  float Smoothstep(float t);
  float Parabola(float t, float k);
  float Triangle(float t);
  float ElasticOut(float t);
  float BounceOut(float t);
}

#endif // LERP_HPP