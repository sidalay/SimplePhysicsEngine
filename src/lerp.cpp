#include <cmath>

#include "lerp.hpp"

namespace spe
{
  float Lerp(float a, float b, float t)
  {
    return a * (1.f - t) + b * t;
  }

  float InvLerp(float a, float b, float v)
  {
    return (v - a) / (b - a);
  }

  float Remap(float iMin, float iMax, float oMin, float oMax, float v)
  {
    float t = spe::InvLerp(iMin, iMax, v);
    return spe::Lerp(oMin, oMax, t);
  }

  float EaseIn(float t) 
  {
    return t * t;
  }

  float EaseOut(float t)
  {
    return 1.f - (1.f - t) * (1.f - t);
  }

  float Smoothstep(float t)
  {
    return std::lerp(spe::EaseIn(t), spe::EaseOut(t), t);
  }

  float Parabola(float t, float k) 
  {
    return std::pow(4.f * t * (1.f - t), k);
  }

  float Triangle(float t)
  {
    return 1.f - 2.f * std::abs(t - 0.5f);
  }

  float ElasticOut(float t) 
  {
    return std::sin(-13.f * (t + 1.f) * 3.14f/2.f) * std::pow(2.0, -10.0 * t) + 1.0;
  }

  float BounceOut(float t)
  {
    const float nl{7.5625f};
    const float dl{2.75f};

    if (t < 1.f / dl) {
      return nl * t * t;
    } else if (t < 2.f / dl) {
      t -= 1.5f / dl;
      return nl * t * t + 0.75f;
    } else if (t < 2.5f / dl) {
      t -= 2.25f / dl;
      return nl * t * t + 0.9375f;
    } else {
      t -= 2.625f / dl;
      return nl * t * t + 0.984375f;
    }
  }
}