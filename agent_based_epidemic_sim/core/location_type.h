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

#ifndef AGENT_BASED_EPIDEMIC_SIM_APPLICATIONS_HOME_WORK_LOCATION_TYPE_H_
#define AGENT_BASED_EPIDEMIC_SIM_APPLICATIONS_HOME_WORK_LOCATION_TYPE_H_

#include <functional>
#include <initializer_list>

#include "agent_based_epidemic_sim/agent_synthesis/population_profile.pb.h"
#include "agent_based_epidemic_sim/core/integral_types.h"

namespace abesim {

using LocationTypeFn = std::function<LocationReference::Type(int64 uuid)>;

}  // namespace abesim

#endif  // AGENT_BASED_EPIDEMIC_SIM_APPLICATIONS_HOME_WORK_LOCATION_TYPE_H_
