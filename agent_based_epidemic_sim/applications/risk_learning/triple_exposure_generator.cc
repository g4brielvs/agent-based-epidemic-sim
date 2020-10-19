/*
 * Copyright 2020 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "agent_based_epidemic_sim/applications/risk_learning/triple_exposure_generator.h"

#include <cmath>
#include <random>

#include "absl/random/distributions.h"
#include "absl/random/random.h"
#include "absl/time/time.h"
#include "agent_based_epidemic_sim/core/constants.h"
#include "agent_based_epidemic_sim/core/exposure_generator.h"
#include "agent_based_epidemic_sim/core/random.h"

namespace abesim {

float TripleExposureGenerator::DrawDistance() const {
  absl::BitGenRef bitgen = GetBitGen();
  std::gamma_distribution<float> distance_distribution(distance_params_.shape,
                                                       distance_params_.scale);
  return distance_distribution(bitgen);
}

absl::Duration TripleExposureGenerator::DrawDuration() const {
  const float u = absl::Uniform(GetBitGen(), 0.0, 1.0);
  const float duration_intervals =
      duration_params_.shape / std::pow(u, 1 / duration_params_.scale);
  return kProximityTraceInterval * duration_intervals;
}

float TripleExposureGenerator::DistanceToAttenuation(float distance) const {
  const float mu =
      ble_params_.intercept + ble_params_.slope * std::log(distance);
  const float rssi = -std::exp(mu);
  const float attenuation = ble_params_.tx - (rssi + ble_params_.correction);
  return attenuation;
}

ExposurePair TripleExposureGenerator::Generate(float location_transmissibility,
                                               const Visit& visit_a,
                                               const Visit& visit_b) const {
  const absl::Duration duration = DrawDuration();
  const float distance = DrawDistance();
  const float attenuation = DistanceToAttenuation(distance);
  absl::Time start_time = std::max(visit_a.start_time, visit_b.start_time);
  return {.host_a =
              {
                  .start_time = start_time,
                  .duration = duration,
                  .distance = distance,
                  .attenuation = attenuation,
                  .infectivity = visit_b.infectivity,
                  .symptom_factor = visit_b.infectivity,
              },
          .host_b = {
              .start_time = start_time,
              .duration = duration,
              .distance = distance,
              .attenuation = attenuation,
              .infectivity = visit_a.infectivity,
              .symptom_factor = visit_a.symptom_factor,
          }};
}

}  // namespace abesim
