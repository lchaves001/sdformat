/*
 * Copyright (C) 2019 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <gtest/gtest.h>
#include "sdf/AirPressure.hh"

/////////////////////////////////////////////////
TEST(DOMAirPressure, Construction)
{
  sdf::AirPressure air;
  sdf::Noise defaultNoise;
  EXPECT_EQ(defaultNoise, air.PressureNoise());
  EXPECT_DOUBLE_EQ(0.0, air.ReferenceAltitude());
}

/////////////////////////////////////////////////
TEST(DOMAirPressure, Set)
{
  sdf::AirPressure air;
  sdf::Noise defaultNoise, noise;
  EXPECT_EQ(defaultNoise, air.PressureNoise());
  EXPECT_DOUBLE_EQ(0.0, air.ReferenceAltitude());

  noise.SetType(sdf::NoiseType::GAUSSIAN);
  noise.SetMean(1.2);
  noise.SetStdDev(2.3);
  noise.SetBiasMean(4.5);
  noise.SetBiasStdDev(6.7);
  noise.SetPrecision(8.9);

  air.SetPressureNoise(noise);
  EXPECT_EQ(noise, air.PressureNoise());

  air.SetReferenceAltitude(10.2);
  EXPECT_DOUBLE_EQ(10.2, air.ReferenceAltitude());

  // Copy Constructor
  sdf::AirPressure air2(air);
  EXPECT_EQ(air, air2);

  // Copy operator
  sdf::AirPressure air3;
  air3 = air;
  EXPECT_EQ(air, air3);

  // Move Constructor
  sdf::AirPressure air4(std::move(air));
  EXPECT_EQ(air2, air4);

  air = air4;
  EXPECT_EQ(air2, air);

  // Move operator
  sdf::AirPressure air5;
  air5 = std::move(air2);
  EXPECT_EQ(air3, air5);

  // inequality
  sdf::AirPressure air6;
  EXPECT_NE(air3, air6);
}

/////////////////////////////////////////////////
TEST(DOMAirPressure, Load)
{
  sdf::ElementPtr sdf(std::make_shared<sdf::Element>());

  // No <noise> element
  sdf::AirPressure air;
  sdf::Errors errors = air.Load(sdf);
  EXPECT_FALSE(errors.empty());
  EXPECT_TRUE(errors[0].Message().find("is not a <air_pressure>")
      != std::string::npos) << errors[0].Message();

  EXPECT_NE(nullptr, air.Element());
  EXPECT_EQ(sdf.get(), air.Element().get());

  // The AirPressure::Load function is test more thouroughly in the
  // link_dom.cc integration test.
}
